////////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la premi�re page de la documentation Doxygen.
/**

@mainpage Projet int�grateur de deuxi�me ann�e -- INF2990

*/

#include <windows.h>
#include <cassert>

#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"

#include "VueOrtho.h"
#include "VueOrbite.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"
#include <vector>

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, �t� 2011
#include "tinyxml2.h"
#include "NoeudTable.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../VisiteurSelection.h"
//#include "FTGL/ftgl.h"
#include "../../FTGL/include/FTGL/ftgl.h"


class NoeudAbstrait;
class ArbreRenduINF2990;
class NoeudTable;
/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };

/// Cha�ne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };

FTGLPixmapFont* font_;

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas �t� cr��e, elle la cr�e.  Cette
/// cr�ation n'est toutefois pas n�cessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa cr�ation.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == nullptr)
		instance_ = new FacadeModele;

	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction lib�re l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur lib�re les objets du mod�le.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	delete arbre_;
	delete vue_;
	delete vueOrtho_;
	delete vueOrbite_;
	delete table_;
	delete duplicateur_;
	delete deplacement_;
	delete supprimeur_;
	delete rotateur_;
	delete visiteurEchelle_;
	delete haut_;
	delete bas_;
	delete gauche_;
	delete droite_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle cr�e
/// un contexte OpenGL sur la fen�tre pass�e en param�tre, initialise
/// FreeImage (utilis�e par le chargeur de mod�les) et assigne des 
/// param�tres du contexte OpenGL.
///
/// @param[in] hWnd : La poign�e ("handle") vers la fen�tre � utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre cr��.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilis�e par le chargeur, doit �tre initialis�e
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);

	// Qualit�
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	//glEnable(GL_DEPTH_TEST);

	// Le cull face
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Cr�ation de l'arbre de rendu.  � moins d'�tre compl�tement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de cr�er
	// l'arbre apr�s avoir cr�� le contexte OpenGL.
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	//Creation de la table
	table_ = dynamic_cast < NoeudTable* >(arbre_->chercher("table"));
	//mur_ = dynamic_cast < NoeudTable* >(arbre_->chercher("table"));
	font_ = new FTGLPixmapFont("media/arial.ttf");


	duplicateur_ = new VisiteurDuplication(obtenirArbreRenduINF2990());
	deplacement_ = new VisiteurDeplacement();
	supprimeur_ = new VisiteurSuppression();
	rotateur_ = new VisiteurRotation();
	visiteurEchelle_ = new VisiteurEchelle();
	collision_ = new VisiteurCollision();
	collision_->initialiserScores();
	boite_ = new utilitaire::BoiteEnvironnement("media/right.png", "media/left.png",
		"media/bottom.png", "media/top.png",
		"media/front.png", "media/back.png", 2048);
	ambianteEstActive_ = true;
	utiliserDirectionnelle_ = true;
	spotActive_ = true;
	// On cr�e une vue par d�faut.
	vueOrtho_ = new vue::VueOrtho{
		vue::Camera{
		glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
		glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0),false },
		vue::ProjectionOrtho{
		500, 500,
		1, 1000, 1, 10000, 1.25,
		200, 200 }
	};
	vue_ = vueOrtho_;

	vueOrbite_ = new vue::VueOrbite{
		vue::Camera{
		glm::dvec3(0, -250, 250), glm::dvec3(0, 0, 0),
		glm::dvec3(0, 1, 0),   glm::dvec3(0, 1, 0),true },
		vue::ProjectionOrbite{
		500, 500,
		1, 1000, 1, 10000, 1.25,
		200.0, 200.0 }
	};
	//forest
	/*boite_ = new utilitaire::BoiteEnvironnement("media/front.jpg", "media/back.jpg",
	"media/bottom.jpg", "media/top.jpg",
	"media/left.jpg", "media/right.jpg", 1024);*/

	//ice
	/*boite_ = new utilitaire::BoiteEnvironnement("media/front.jpg", "media/back.jpg",
	"media/bottom.jpg", "media/top.jpg",
	"media/right.jpg", "media/left.jpg", 512);*/

	//Sky
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration � partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est g�n�r� �
/// partir de valeurs par d�faut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// V�rification de l'existance du ficher


	// Si le fichier n'existe pas, on le cr�e.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire � partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les diff�rentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction g�n�re un fichier XML de configuration � partir de
/// valeurs par d�faut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	tinyxml2::XMLDocument document;
	// �crire la d�claration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

	// On enregistre les diff�rentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);

	// �crire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libere le contexte OpenGL et desinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On lib�re les instances des diff�rentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre d�truit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la sc�ne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Afficher la scène
	afficherBase();

	//glMatrixMode(GL_MODELVIEW);
	//vue_->appliquerCamera();
	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	if (!modeEdition_ && !modeTest_)
	{
		/*std::string s1 = std::to_string(fenetreX_);
		char const *pchar1 = s1.c_str();
		std::string s2 = std::to_string(fenetreY_);
		char const *pchar2 = s2.c_str();*/

		string joueur1 = afficherNom1_ + " - " + to_string(butJoueur1_);
		string joueur2 = afficherNom2_ + " - " + to_string(butJoueur2_);
		char const *j1 = joueur1.c_str();
		char const *j2 = joueur2.c_str();

		char const *temps = tempsJouer_.c_str();

		//FTGLPixmapFont* font_;
		//font_ = new FTGLPixmapFont("media/arial.ttf");
		//FTGLPixmapFont* font_ = new FTGLPixmapFont("media/arial.ttf");

		font_->FaceSize(30);

		if (fenetreX_ == 0 && fenetreY_ == 0)
		{
		//	// Original 603, 581
			font_->Render(j1, -1, FTPoint(0, 531));
			font_->Render(temps, -1, FTPoint(266, 531));
			font_->Render(j2, -1, FTPoint(603 - joueur2.length() * 14, 531));
		}
		else
		{
			font_->Render(j1, -1, FTPoint(0, fenetreY_ - 50));
			font_->Render(temps, -1, FTPoint(fenetreX_ / 2 - 35, fenetreY_ - 50));
			font_->Render(j2, -1, FTPoint(fenetreX_ - joueur2.length() * 14, fenetreY_ - 50));
		}
	}


	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la sc�ne, c'est-�-dire
/// qu'elle met en place l'�clairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la cam�ra
	//cout << &vue_->obtenirProjection().obtenirMatrice() << endl;
	//glm::mat4 vueProjection(vue_->obtenirProjection().obtenirMatrice() * vue_->obtenirCamera().obtenirMatrice());
	glm::mat4 vueProjection(vue_->obtenirProjection().obtenirMatrice() * vue_->obtenirCamera().obtenirMatrice());

	boite_->afficher(vue_->obtenirProjection().obtenirMatrice(), vue_->obtenirCamera().obtenirMatrice());
	// Afficher la scène.
	//arbre_->afficher(vueProjection, attribuerCouleur);

	bool attribuerCouleur = false;
	if (modeApplication_ == 'R')
		attribuerCouleur = true;
	// Afficher la scène.
	arbre_->afficher(vue_->obtenirCamera().obtenirMatrice(), vue_->obtenirProjection().obtenirMatrice(), vueProjection, attribuerCouleur);
	//arbre_->afficher(vueProjection, attribuerCouleur);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction r�initialise la sc�ne � un �tat "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// R�initialisation de la sc�ne.
	NoeudAbstrait::compteurPortail_ = 0;
	NoeudAbstrait::compteurMuret_ = 0;
	NoeudAbstrait::compteurMaillet_ = 0;
	NoeudAbstrait::compteurBonus_ = 0;
	arbre_->initialiser();
	VisiteurDuplication* dublication_ = new VisiteurDuplication(obtenirArbreRenduINF2990());

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les diff�rents calculs d'animations
/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise � jour des objets.
	arbre_->animer(temps);

	// Mise � jour de la vue.
	vue_->animer(temps);
}
void FacadeModele::redessiner()
{
	// Mise � jour des objets.
	arbre_->redessiner();

	// Mise � jour de la vue.
	vue_->redessiner();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNouveauElement(char* nom, int x, int y)
///
/// Cette fonction permet d'ajouter un noeud
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::ajouterNouveauElement(char* nom, int x, int y)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(x, y, point);
	return arbre_->ajouterNouveauElement(nom, point);
}

int FacadeModele::ajouterNouveauPortail(char* nom, int x, int y) {
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(x, y, point);
	return arbre_->ajouterNouveauPortail(nom, point);
}

void FacadeModele::initialiserRectangleElas(int x, int y)
{
	pointAncrageX_ = x;
	pointAncrageY_ = y;
	pointFinalX_ = pointAncrageX_;
	pointFinalY_ = pointAncrageY_;
	glm::ivec2 pointInitial;
	pointInitial.x = pointAncrageX_;
	pointInitial.y = pointAncrageY_;
	aidegl::initialiserRectangleElastique(pointInitial);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::creerRectangleElastique(double& x, double& y)
///
/// Cette fonction cree et affiche le rectangle elastique 
///
/// @param[in] x : position x de la souris.
/// @param[in] y : position y de la souris.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::mettreAJourRectangleElas(int x, int y)
{
	glm::ivec2 pointActuel;
	pointActuel.x = x;
	pointActuel.y = y;
	glm::ivec2 pointAncrage;
	pointAncrage.x = pointAncrageX_;
	pointAncrage.y = pointAncrageY_;
	glm::ivec2 pointFinal;
	pointFinal.x = pointFinalX_;
	pointFinal.y = pointFinalY_;
	aidegl::mettreAJourRectangleElastique(pointAncrage, pointFinal, pointActuel);
	pointFinalX_ = x;
	pointFinalY_ = y;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::creerRectangleElastique(double& x, double& y)
///
/// Cette fonction cree et affiche le rectangle elastique 
///
/// @param[in] x : position x de la souris.
/// @param[in] y : position y de la souris.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::terminerRectangleElas()
{
	glm::ivec2 pointAncrage;
	pointAncrage.x = pointAncrageX_;
	pointAncrage.y = pointAncrageY_;
	glm::ivec2 pointFinal;
	pointFinal.x = pointFinalX_;
	pointFinal.y = pointFinalY_;
	selectionnerRectangle(pointAncrage.x, pointAncrage.y, std::abs(pointFinal.x - pointAncrage.x), std::abs(pointFinal.y - pointAncrage.y), false);
	aidegl::terminerRectangleElastique(pointAncrage, pointFinal);
	/*glm::ivec2 pointActuel;
	pointActuel.x = x;
	pointActuel.y = y;
	aidegl::mettreAJourRectangleElastique(pointAncrage, pointFinal, pointActuel);*/
	//glEnd();

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::determinerCouleurPixel
/// (int mouseX, int mouseY, GLubyte  couleurPixel[])
///
/// Cette fonction prend un pixel a la position de la souris et determine 
/// le RGB de la couleur de ce meme pixel. 
/// 
///
/// @param[in] mouseX: position de la souris en X
/// @param[in] mouseY: position de la souris en Y
/// @param[in] couleurPixel: tableau que contient le RGB du pixel
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::determinerCouleurPixel(int mouseX, int mouseY, GLubyte  couleurPixel[])
{
	GLubyte couleurDuPixel[3];
	for (unsigned int i = 0; i < 3; i++)
		couleurDuPixel[i] = couleurPixel[i];
	glFlush();
	glFinish();
	GLint cloture[4]; glGetIntegerv(GL_VIEWPORT, cloture);
	GLint posX = mouseX, posY = cloture[3] - mouseY;
	glReadBuffer(GL_BACK);
	glReadPixels(posX, posY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, couleurDuPixel);
	for (unsigned int i = 0; i < 3; i++)
		couleurPixel[i] = couleurDuPixel[i];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectionObjet
/// (int posX, int posY, bool selectionUnique)
///
/// Cette fonction selectionne un objet a l'aide d'un visiteur.
/// La selection se fait a l'aide de la couleur des pixels de l'objet.
/// Il est egalement possible de selectionner un objet uniquement.
/// 
///
/// @param[in] posX: position en X du point du noeud a selectionne
/// @param[in] posY: position en Y du point du noeud a selectionne
/// @param[in] couleurPixel: tableau que contient le RGB du pixel
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectionObjet(int posX, int posY, bool selectionUnique)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(posX, posY, point);
	GLubyte  couleurPixel[3];
	determinerCouleurPixel(posX, posY, couleurPixel);
	//std::cout << "valeur  : (" << point.x << ", " << point.y << std::endl;

	bool estAlExterieurTable = couleurPixel[0] == 0 && couleurPixel[1] == 0 && couleurPixel[2] == 0;
	if (!estAlExterieurTable)
	{
		//std::cout << "couleurPixelSelectObject : (" << (int)couleurPixel[0] << ", " << (int)couleurPixel[1] << ", " << (int)couleurPixel[2] << ")" << std::endl;

		auto visiteurSelObj = new VisiteurSelection(point, selectionUnique, couleurPixel, true);
		table_->accepterVisiteur(visiteurSelObj, selectionUnique);
		delete visiteurSelObj;
		visiteurSelObj = new VisiteurSelection(point, selectionUnique, couleurPixel, false);
		table_->accepterVisiteur(visiteurSelObj, selectionUnique);
		if (!visiteurSelObj->obtenirselectionExiste() && selectionUnique)
			table_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
		delete visiteurSelObj;
	}
	else if (selectionUnique)
	{
		arbre_->chercher(arbre_->NOM_TABLE)->deselectionnerTout();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::mettreAEchelle(int x, int y)
///
/// Cette fonction met a l'echelle un objet par un certain facteur.
/// Il est possible d'agrandir ou de rapetisser l'objet selon les
/// coordonnees de la souris.
/// 
///
/// @param[in] x: position de la souris en X
/// @param[in] y: position de la souris en Y
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::mettreAEchelle(int x, int y)
{
	if (y < 0)
	{
		visiteurEchelle_->modifierFacteur(0.99);
	}

	if (y > 0)
	{
		visiteurEchelle_->modifierFacteur(1.01);
	}

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			table_->chercher(i)->accepterVisiteur(visiteurEchelle_);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserRotation(int pointY)
///
/// Cette fonction initialise la rotation de l'objet en prenant la position
/// initiale de la souris en Y, puisque la modification de l'angle de
/// rotation ne se fait qu'avec la variation en Y de la souris. 
/// 
///
/// @param[in] pointY: point initiale de la souris en Y
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserRotation(int pointY)
{
	pointInitialY_ = pointY;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserDeplacement(int pointX, int pointY)
///
/// Cette fonction initialise le deplacement d'un noeud en prenant la 
/// position initiale de la souris
/// 
///
/// @param[in] pointX: point initiale de la souris en X
/// @param[in] pointY: point initiale de la souris en Y
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserDeplacement(int pointX, int pointY)
{
	glm::dvec3 position;
	vue_->convertirClotureAVirtuelle(pointX, pointY, position);
	//pointInitialX_ = pointX;
	//pointInitialY_ = pointY;

	pointInitialX_ = position.x;
	pointInitialY_ = position.y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::effectuerRotation(int pointY)
///
/// Cette fonction effectue la rotation sur un groupe d'objets
/// selectionnes ou un objet unique selectionne. La rotation se fait a
/// l'aide d'un appel a un visiteur.
/// 
///
/// @param[in] pointY: point courante de la souris en Y
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::effectuerRotation(int pointY)
{
	glm::mat4 vueProjection(vue_->obtenirProjection().obtenirMatrice() * vue_->obtenirCamera().obtenirMatrice());
	float varY = 0;
	varY = pointInitialY_ - pointY;
	if (varY < 0)
	{
		varY = -0.1;
	}
	else if (varY > 0)
		varY = 0.1;
	rotateur_->modifierVarY(varY);
	if (table_->calculerNombreSelectionner() == 1) {
		for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
			if (table_->chercher(i)->estSelectionne())
				table_->chercher(i)->accepterVisiteur(rotateur_);
		}
	}
	else {
		table_->accepterVisiteur(rotateur_, true);
	}
	pointInitialY_ = pointY;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::effectuerDeplacement(float x, float y)
///
/// Cette fonction effectue le deplacement sur un groupe d'objets
/// selectionnes ou un objet unique selectionne. Le deplacement se fait a
/// l'aide d'un appel a un visiteur.
/// 
///
/// @param[in] x: position courante en X de la souris
/// @param[in] Y: position courante en Y de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::effectuerDeplacement(float x, float y)
{

	glm::dvec3 positionSouris;
	glm::dvec3 variation;

	vue_->convertirClotureAVirtuelle(x, y, positionSouris);
	variation.x = positionSouris.x - pointInitialX_;
	variation.y = positionSouris.y - pointInitialY_;
	deplacement_->modifierPosition(variation);
	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		deplacement_->modifierPosition(variation);
		if (table_->chercher(i)->estSelectionne())
			table_->chercher(i)->accepterVisiteur(deplacement_);

		glm::dvec3 variation;
		NoeudComposite* enfants = dynamic_cast<NoeudComposite*>(arbre_->obtenirEnfants()[0]);
		conteneur_enfants enfantsTable = enfants->obtenirEnfants();
		VisiteurDeplacement* visiteur = new VisiteurDeplacement();
		glm::dvec3 positionSouris;

		vue_->convertirClotureAVirtuelle(x, y, positionSouris);
		variation.x = positionSouris.x - pointInitialX_;
		variation.y = positionSouris.y - pointInitialY_;

		//positionSouris[0] = -varX;
		//positionSouris[1] = varY;
	}

	pointInitialX_ = positionSouris.x;
	pointInitialY_ = positionSouris.y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirFrictionTable()
///
/// Cette fonction retourne le coefficient de friction de la table.
///
///
/// @return le coefficient de friction de la table.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirFrictionTable()
{
	return table_->obtenirFriction();
}
void FacadeModele::deplacer(double deplacementX, double deplacementY)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirAccelerationBonus()
///
/// Cette fonction retourne l'acceleration des bonus de la table.
///
///
/// @return le coefficient d'acceleration des bonus de la table.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirAccelerationBonus()
{
	return table_->obtenirAcceleration();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirCoefRebondissement()
///
/// Cette fonction retourne le coefficient de rebondissement de la table.
///
///
/// @return le coefficient de rebondissement de la table.
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirCoefRebondissement()
{
	return table_->obtenirCoefRebondissement();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirPositionObjetX()
///
/// Cette fonction retourne la position en X d'un objet selectionne.
/// Cette fonction est utilisee lorsqu'un seul objet est selectionne. 
///
///
/// @return la position de l'objet en X
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirPositionObjetX()
{
	/*conteneur_enfants conteneurEnfants = table_->obtenirEnfants();

	return conteneurEnfants[0]->obtenirPositionRelative().x;*/

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			//table_->chercher(i)->accepterVisiteur(visiteurEchelle_);
			return table_->chercher(i)->obtenirPositionRelative().x;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirPositionObjetY()
///
/// Cette fonction retourne la position en y d'un objet selectionne.
/// Cette fonction est utilisee lorsqu'un seul objet est selectionne. 
///
///
/// @return la position de l'objet en y
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirPositionObjetY()
{
	/*conteneur_enfants conteneurEnfants = table_->obtenirEnfants();

	return conteneurEnfants[0]->obtenirPositionRelative().y;*/

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			//table_->chercher(i)->accepterVisiteur(visiteurEchelle_);
			return table_->chercher(i)->obtenirPositionRelative().y;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirPositionObjetZ()
///
/// Cette fonction retourne la position en Z d'un objet selectionne.
/// Cette fonction est utilisee lorsqu'un seul objet est selectionne. 
///
///
/// @return la position de l'objet en z
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirPositionObjetZ()
{
	/*conteneur_enfants conteneurEnfants = table_->obtenirEnfants();

	return conteneurEnfants[0]->obtenirPositionRelative().z;*/

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			//table_->chercher(i)->accepterVisiteur(visiteurEchelle_);
			return table_->chercher(i)->obtenirPositionRelative().z;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirAngleRotationObjet()
///
/// Cette fonction retourne l'angle de rotation d'un objet selectionne.
/// Elle est utilisee lorsqu'un seul objet est selectionne. 
///
///
/// @return l'angle de rotation
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirAngleRotationObjet()
{
	/*conteneur_enfants conteneurEnfants = table_->obtenirEnfants();

	return conteneurEnfants[0]->obtenirAngleRotation();*/

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			//table_->chercher(i)->accepterVisiteur(visiteurEchelle_);
			return table_->chercher(i)->obtenirAngleRotation();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirFacteurEchelleObjet()
///
/// Cette fonction retourne le facteur d'echelle d'un objet selectionne.
/// Cette fonction est utilisee lorsqu'un seul objet est selectionne. 
///
///
/// @return le facteur d'echelle du noeud
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirFacteurEchelleObjet()
{
	/*conteneur_enfants conteneurEnfants = table_->obtenirEnfants();

	return conteneurEnfants[0]->obtenirFacteurEchelle();*/

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			//table_->chercher(i)->accepterVisiteur(visiteurEchelle_);
			return table_->chercher(i)->obtenirFacteurEchelle();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::mettreEchelleObjetBouton(double facteur)
///
/// Cette fonction modifie le facteur de mise a l'echelle d'un objet en
/// prenant la valeur dans la boite de proprietes. 
///
/// @param[in] facteur: Facteur de mise a echelle voulu
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::mettreEchelleObjetBouton(double facteur)
{

	/*conteneur_enfants conteneurEnfants = table_->obtenirEnfants();
	visiteurEchelle_->modifierFacteur(facteur);
	conteneurEnfants[0]->modifierFacteurEchelle(facteur);
	conteneurEnfants[0]->accepterVisiteur(visiteurEchelle_);*/

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++)
	{
		if (table_->chercher(i)->estSelectionne())
		{
			visiteurEchelle_->modifierFacteur(facteur);
			table_->chercher(i)->modifierFacteurEchelle(facteur);
			table_->chercher(i)->accepterVisiteur(visiteurEchelle_);
		}
	}
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::rotationObjetBouton(int angle)
///
/// Cette fonction modifie la rotation d'un objet en
/// prenant la valeur dans la boite de proprietes. 
///
/// @param[in] angle: angle voulu
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::rotationObjetBouton(int angle)
{
	//conteneur_enfants conteneurEnfants = table_->obtenirEnfants();

	//rotateur_->modifierVarY(angle);
	//conteneurEnfants[0]->accepterVisiteur(rotateur_);
	//
	////conteneurEnfants[2]->modifierAngleRotation(angle);

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++)
	{
		if (table_->chercher(i)->estSelectionne())
		{
			//rotateur_->modifierVarY(angle);
			//table_->chercher(i)->accepterVisiteur(rotateur_);
			table_->chercher(i)->modifierAngleRotation(angle);
		}
	}

}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacementObjetBouton(float pointX, float pointY)
///
/// Cette fonction modifie la position d'un objet en
/// prenant la valeur dans la boite de proprietes. 
///
/// @param[in] pointX: point en X ou l'objet doit se deplacer
/// @param[in] pointY: point 
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacementObjetBouton(float pointX, float pointY)
{

	/*conteneur_enfants conteneurEnfants = table_->obtenirEnfants();

	glm::dvec3 nouvellePosition;
	nouvellePosition[0] = pointX;
	nouvellePosition[1] = pointY;

	conteneurEnfants[0]->assignerPositionRelative(nouvellePosition);*/

	glm::dvec3 nouvellePosition;
	nouvellePosition[0] = pointX;
	nouvellePosition[1] = pointY;

	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++)
	{
		if (table_->chercher(i)->estSelectionne())
		{
			table_->chercher(i)->assignerPositionRelative(nouvellePosition);;
		}
	}

}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::frictionTableBouton(double frictionTable)
///
/// Cette fonction modifie le coefficient de friction de la table
/// avec la valeur inscrite dans la barre de proprietes.
/// 
///
/// @param[in] frictionTable: coefficient de friction voulu
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////

void FacadeModele::frictionTableBouton(double frictionTable)
{
	table_->modifierFriction(frictionTable);
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::accelerationBonusBouton
/// (double accelerationBonus)
///
/// Cette fonction modifie l'acceleration des bonus de la table 
/// avec  la valeur inscrite dans la barre de proprietes.
/// 
///
/// @param[in] accelerationBonus: coefficient d'acceleration voulu
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::accelerationBonusBouton(double accelerationBonus)
{
	table_->modifierAcceleration(accelerationBonus);
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::coefRebondissementBouton
/// (double coefRebondissement)
///
/// Cette fonction modifie le coefficient de rebondissement de la
/// table avec  la valeur inscrite dans la barre de proprietes.
/// 
///
/// @param[in] coefRebondissement: coefficient de rebondissementvoulu
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::coefRebondissementBouton(double coefRebondissement)
{

	table_->modifierCoefRebondissement(coefRebondissement);
}
glm::dvec3 FacadeModele::obtenirPositionSouris()
{
	/*glm::dvec3 positionSouris;
	vue_->convertirClotureAVirtuelle(x, y, positionSouris);
	positionSouris_ = positionSouris;*/
	GLint viewport[4];					//var to hold the viewport info
	GLdouble modelview[16];				//var to hold the modelview info
	GLdouble projection[16];			//var to hold the projection matrix info
	GLfloat winX, winY, winZ;			//variables to hold screen x,y,z coordinates
	GLdouble worldX, worldY, worldZ;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);	//get the modelview info
	glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
	glGetIntegerv(GL_VIEWPORT, viewport);			//get the viewport info



	POINT mouse;							// Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(hWnd_, &mouse);

	winX = (float)mouse.x;                  // Holds The Mouse X Coordinate
	winY = (float)mouse.y;                  // Holds The Mouse Y Coordinate

	winY = (float)viewport[3] - (float)winY;

	glReadPixels(mouse.x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	//winZ = 0;
	//get the world coordinates from the screen coordinates
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);

	return glm::dvec3(static_cast<double>(worldX), static_cast<double>(worldY), 0.0);
}
void FacadeModele::sauverSouris()
{

	positionSouris_ = obtenirPositionSouris();
}
void FacadeModele::deplacerSouris(int x, int y)
{
	vue_->deplacerSouris(glm::dvec3(x, y, 0.0));
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectionner(int x, int y, bool selectionUnique)
///
/// Cette fonction selectionne un objet qui se figure aux points en
/// parametres dans la table. Les points sont la position de la souris
/// lors de la selection.
/// 
///
/// @param[in] x: position courante de la souris en x
/// @param[in] y: position courante de la souris en y
/// @param[in] selectionUnique: indique si l'objet est le seul objet
///				qui doit etre selectionne.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectionner(int x, int y, bool selectionUnique)
{
	table_->selectionnerObjets(x, y, 0.0, 0.0, etatCTRL_, selectionUnique);
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectionnerRectangle
/// (int x, int y, int hauteur, int largeur, bool selectionUnique)
///
/// Cette fonction selectionne tous les objets qui se figurent dans la
/// rectangle definit par la hauteur et la largeur du rectangle. 
/// 
///
/// @param[in] x: position courante de la souris en x
/// @param[in] y: position courante de la souris en y
/// @param[in] hauteur: la hauteur du rectangle
/// @param[in] largeur: la largeur du rectangle
/// @param[in] selectionUnique: indique si l'objet est le seul objet
///				qui doit etre selectionne.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectionnerRectangle(int x, int y, int hauteur, int largeur, bool selectionUnique)
{
	table_->selectionnerObjets(x, y, hauteur, largeur, etatCTRL_, selectionUnique);
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::modifierEtatCTRL(bool etatCTRL)
///
/// Cette fonction fait une mise a jour du bouton de clavier CTRL 
/// 
///
/// @param[in] etatCTRL: mis a jour de l'etat de controle
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::modifierEtatCTRL(bool etatCTRL)
{
	etatCTRL_ = etatCTRL;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::effacerSelection()
///
/// Cette fonction efface la selection en appelant la fonction de 
/// selection de la table.
/// 
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::effacerSelection()
{
	table_->effacerSelection();
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::selectionnerTout()
///
/// Cette fonction selectionne tous les objets dans la table en appelant
/// la methode de selection de la table.
/// 
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::selectionnerTout()
{
	table_->selectionnerTout();
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deselectionnerTout()
///
/// Cette fonction deselectionne tous les objets dans la table en appelant
/// la methode de deselection de la table.
/// 
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deselectionnerTout()
{
	table_->deselectionnerTout();
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::dupliquerSelection(int x, int y)
///
/// Cette fonction duplique les objets en selection. Un visiteur
/// est appele pour dupliquer en parcourant la table pour voir 
/// si les objets sont selectionnes.
/// 
/// @param[in] x: position en x de la souris ou apparaitra l'objet duplique
/// @param[in] y: position en y de la souris ou apparaitra l'objet duplique
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::dupliquerSelection(int x, int y)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(x, y, point);
	duplicateur_->definirPosition(point);
	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			table_->chercher(i)->accepterVisiteur(duplicateur_);
	}
}

//////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::supprimerSelection(int x, int y)
///
/// Cette fonction supprime les objets selectionnes. Le visiteur
/// est appele pour supprimer les objets en parcourant la table et aller
/// chercher tous les objets selectionnes.
/// 
/// @param[in] x: position en x de la souris ou apparaitra l'objet supprime
/// @param[in] y: position en y de la souris ou apparaitra l'objet supprime
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerSelection()
{
	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			table_->chercher(i)->accepterVisiteur(supprimeur_);
	}
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::deplacerSelection(int x, int y)
///
/// Cette fonction deplace les objets selectionnes. Le visiteur
/// est appele pour deplacer les objets en parcourant la table et aller
/// chercher tous les objets selectionnes.
/// 
/// @param[in] x: position en x de la souris ou l'objet sera deplace
/// @param[in] y: position en y de la souris ou l'objet sera deplace
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::deplacerSelection(int x, int y)
{
	glm::dvec3 point;
	vue_->convertirClotureAVirtuelle(x, y, point);
	deplacement_->modifierPosition(point);
	for (unsigned int i = 0; i < table_->obtenirNombreEnfants(); i++) {
		if (table_->chercher(i)->estSelectionne())
			table_->chercher(i)->accepterVisiteur(deplacement_);
	}
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::sauvegardeParDefaut()
///
/// Cette fonction sauvegarde la structure de l'arbre dans un fichier
/// XML par defaut.
/// 
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sauvegardeParDefaut()
{
	char* fichierParDefaut = "default.xml";
	sauvegarderArbre(fichierParDefaut);
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::sauvegarderArbre(std::string nomFichier)
///
/// Cette fonction sauvegarde l'arbre dans un fichier XML mis en
/// parametre. On a recours a un visiteur pour sauvegarder tous les noeuds
/// de la table.
///
/// 
/// @param[in] nomFichier: nom du fichier ou on sauvegarde l'arbre
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sauvegarderArbre(std::string nomFichier)
{
	tinyxml2::XMLDocument document(nomFichier.c_str());
	//// �crire la d�claration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

	tinyxml2::XMLElement* root = { document.NewElement("root") };
	document.LinkEndChild(root);

	VisiteurEcritureXML visiteurEcriture(root);

	// On enregistre les diff�rentes configurations.
	visiteurEcriture.visiter(table_);

	// �crire dans le fichier
	document.SaveFile(nomFichier.c_str());
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialisationParDefaut()
///
/// Cette fonction initialise le chargement de l'arbre avec un fichier 
/// XML par defaut. Elle ne fait que specifier le nom de fichier avant 
/// d'appeler la fonction d'initialisation de chargement de l'arbre.
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialisationParDefaut()
{
	char* fichierParDefaut = "../Exe/zones/default.xml";
	initialiserChargement(fichierParDefaut);
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserChargement(std::string nomFichier)
///
/// Cette fonction charge l'arbre a partir d'un fichier XML avec le nom 
/// en parametre. Elle initialise l'arbre en creant la racine XML d'abord.
/// 
/// @param[in] nomFichier: nom du fichier XML qui chargera l'arbre
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserChargement(std::string nomFichier)
{
	if (utilitaire::fichierExiste(nomFichier))
	{
		tinyxml2::XMLDocument document;

		document.LoadFile(nomFichier.c_str());

		tinyxml2::XMLHandle handle(&document);

		//Arbre->Table->Noeud
		tinyxml2::XMLNode *racine = handle.FirstChildElement().FirstChildElement().ToNode();
		//Lecture seulement si au moins un element dans le fichier
		for (size_t i = 0; i < arbre_->chercher("table")->obtenirNombreEnfants(); i++)
		{
			if (arbre_->chercher("table")->chercher(i)->obtenirType() != ArbreRenduINF2990::NOM_MAILLET_1&&
				arbre_->chercher("table")->chercher(i)->obtenirType() != ArbreRenduINF2990::NOM_RONDELLE&&
				arbre_->chercher("table")->chercher(i)->obtenirType() != ArbreRenduINF2990::NOM_MAILLET_V)
			{
				arbre_->chercher(ArbreRenduINF2990::NOM_TABLE)->effacer(arbre_->chercher("table")->chercher(i));
			}
		}
		chargerArbre(arbre_, arbre_, racine);
	}
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::dupliquerSelection(int x, int y)
///
/// Cette fonction charge l'arbre en ajoutant un noeud a la fois a 
/// l'aide de la recursivite. Si le noeud a ajoute est une table, on
/// l'assigne a notre arbre.
/// 
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerArbre(ArbreRenduINF2990 * arbre, NoeudAbstrait* noeudCourant, tinyxml2::XMLNode * parent)
{
	bool existeDeja = false;
	NoeudAbstrait* noeud = arbre->creerNoeud(parent->ToElement()->Name(), parent);
	if (parent->ToElement()->Name() != ArbreRenduINF2990::NOM_PORTAIL) {
		NoeudAbstrait* noeud = arbre->creerNoeud(parent->ToElement()->Name(), parent);
	}
	else
	{

		for (size_t i = 0; i < table_->obtenirListePortails().size(); i++)
		{
			if (table_->obtenirListePortails()[i]->obtenirPositionRelative().x == noeud->obtenirPositionRelative().x &&
				table_->obtenirListePortails()[i]->obtenirPositionRelative().y == noeud->obtenirPositionRelative().y &&
				table_->obtenirListePortails()[i]->obtenirPositionRelative().z == noeud->obtenirPositionRelative().z)
			{
				existeDeja = true;
			}
		}
		//arbre_->ajouterPairePortails(noeud);

	}
	if (!existeDeja)
	{
		table_->ajouter(noeud);
	}
	if (noeud->obtenirType() == ArbreRenduINF2990::NOM_TABLE)
	{
		arbre->assignerZoneJeux(noeud);
	}


	for (tinyxml2::XMLNode* node = parent->FirstChild(); node; node = node->NextSibling())
	{
		chargerArbre(arbre, noeud, node);
	}
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfigurationOptions()
///
/// Cette fonction charge tous les options du menu configuration sauf
/// pour les profils virtuels a partir des donnees dans le fichier xml
/// options.xml. 
/// 
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfigurationOptions()
{
	//Valeurs par defaut si le fichier n'existe pa



	if (!utilitaire::fichierExiste("../Exe/donnees/options.xml"))
	{
		peutAfficherDebogage_ = false;
		peutAfficherCollision_ = false;
		peutAfficherVitesseRondelle_ = false;
		peutAfficherEclairage_ = false;
		peutAfficherAttractionPortail_ = false;

		nbButs_ = 2;

		estVirtuel_ = true;
	}
	else
	{
		tinyxml2::XMLDocument document;

		//Lire options.xml
		document.LoadFile("../Exe/donnees/options.xml");
		const tinyxml2::XMLElement* elementConfig{ document.FirstChildElement("configuration") };

		if (elementConfig != nullptr)
		{
			const tinyxml2::XMLElement* elementAffichage{ elementConfig->FirstChildElement("Affichage") };
			if (elementAffichage != nullptr)
			{
				if (elementAffichage->QueryBoolAttribute("DEBUG", &peutAfficherDebogage_) != tinyxml2::XML_SUCCESS)
				{
					std::cerr << "Erreur: DEBUG  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
				}
				if (elementAffichage->QueryBoolAttribute("TYPE_OBJET_COLLISION", &peutAfficherCollision_) != tinyxml2::XML_SUCCESS)
				{
					std::cerr << "Erreur: TYPE_OBJET  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
				}
				if (elementAffichage->QueryBoolAttribute("VITESSE_RONDELLE", &peutAfficherVitesseRondelle_) != tinyxml2::XML_SUCCESS)
				{
					std::cerr << "Erreur: VITESSE_RONDELLE  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
				}
				if (elementAffichage->QueryBoolAttribute("ETAT_ECLAIRAGE", &peutAfficherEclairage_) != tinyxml2::XML_SUCCESS)
				{
					std::cerr << "Erreur: ETAT_ECLAIRAGE  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
				}
				if (elementAffichage->QueryBoolAttribute("ATTRACTION_PORTAILS", &peutAfficherAttractionPortail_) != tinyxml2::XML_SUCCESS)
				{
					std::cerr << "Erreur: ATTRACTION_PORTAILS  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
				}
				const tinyxml2::XMLElement* elementOptions{ elementAffichage->NextSiblingElement("Options") };
				if (elementOptions != nullptr)
				{
					if (elementOptions->QueryIntAttribute("NB_BUTS", &nbButs_) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: NB_BUTS  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					haut_ = (char*)elementOptions->Attribute("HAUT");
					sHaut_ = haut_;
					bas_ = (char*)elementOptions->Attribute("BAS");
					sBas_ = bas_;
					gauche_ = (char*)elementOptions->Attribute("GAUCHE");
					sGauche_ = gauche_;
					droite_ = (char*)elementOptions->Attribute("DROITE");
					sDroite_ = droite_;

					//if(haut_==nullptr)
					//	std::cerr << "Erreur: HAUT  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					//if (bas_ == nullptr)
					//	std::cerr << "Erreur: BAS  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					//if (gauche_ == nullptr)
					//	std::cerr << "Erreur: GAUCHE  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					//if (droite_ == nullptr)
					//	std::cerr << "Erreur: DROITE  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					if (elementOptions->QueryBoolAttribute("TYPE_JOUEUR", &estVirtuel_) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: TYPE_JOUEUR  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
				}
			}
		}
	}

}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::miseAJourSauvegardeConfiguration(bool peutAfficherDebogage,
/// bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage,
/// bool peutAfficherAttractionPortail, int nbButs, char* haut, char* bas,
/// char* gauche, char* droite, bool estVirtuel)
///
/// Cette fonction fait la mise a jour des donnees pour le passage du C# au C++ pour
/// ensuite sauvegarder les donnees dans un fichier xml
/// 
///@param [in] peutAfficherDebogage: Permet d'afficher les elements de debogage a la console.
///@param [in] peutAfficherCollision: Permet d'afficher le type d'objet entre en collision 
/// avec la rondelle.
/// @param [in] peutAfficherVitesseRondelle: Permet d'afficher la vitesse de la rondelle.
/// @param [in] peutAfficherEclairage: Permet d'afficher l'etat de l'eclairage
/// @param [in] peutAfficherAttractionPortail: Permet d'afficher le rayon d'attraction
/// @param [in] nbButs: nombre de buts necessaires pour gagner une partie.
/// @param [in] haut: touche de controler pour deplacer le portail.
/// 
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::miseAJourSauvegardeConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
	int nbButs, char* haut, char* bas, char* gauche, char* droite, bool estVirtuel)
{
	peutAfficherDebogage_ = peutAfficherDebogage;
	peutAfficherCollision_ = peutAfficherCollision;
	peutAfficherVitesseRondelle_ = peutAfficherVitesseRondelle;
	peutAfficherEclairage_ = peutAfficherEclairage;
	peutAfficherAttractionPortail_ = peutAfficherAttractionPortail;
	nbButs_ = nbButs;
	haut_ = haut;
	bas_ = bas;
	gauche_ = gauche;
	droite_ = droite;
	estVirtuel_ = estVirtuel;
	//TODO


}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::miseAJourSauvegardeConfiguration(bool peutAfficherDebogage,
/// bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage,
/// bool peutAfficherAttractionPortail, int nbButs, char* haut, char* bas,
/// char* gauche, char* droite, bool estVirtuel)
///
/// Cette fonction fait la mise a jour des donnees pour le passage du C# au C++ pour
/// ensuite charger les donnees dans un fichier xml
/// 
///@param [in] peutAfficherDebogage: Permet d'afficher les elements de debogage a la console.
///@param [in] peutAfficherCollision: Permet d'afficher le type d'objet entre en collision 
/// avec la rondelle.
/// @param [in] peutAfficherVitesseRondelle: Permet d'afficher la vitesse de la rondelle.
/// @param [in] peutAfficherEclairage: Permet d'afficher l'etat de l'eclairage
/// @param [in] peutAfficherAttractionPortail: Permet d'afficher le rayon d'attraction
/// @param [in] nbButs: nombre de buts necessaires pour gagner une partie.
/// @param [in] haut: touche de controler pour deplacer le portail.
/// 
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::miseAJourChargementConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
	int nbButs, char * haut, char * bas, char * gauche, char * droite, bool estVirtuel)
{
	peutAfficherDebogage = peutAfficherDebogage_;
	peutAfficherCollision = peutAfficherCollision_;
	peutAfficherVitesseRondelle = peutAfficherVitesseRondelle_;
	peutAfficherEclairage = peutAfficherEclairage_;
	peutAfficherAttractionPortail = peutAfficherAttractionPortail_;
	nbButs = nbButs_;
	haut = haut_;
	bas = bas_;
	gauche = gauche_;
	droite = droite_;
	estVirtuel = estVirtuel_;
	//TODO
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::sauvegarderConfigurationOptions(char* haut,
/// char* bas, char* gauche, char* droite)
///
/// Cette fonction sauvegarde toutes les options du menu configuration
/// dans un fichier XML. Les controles, les options de debogage, le
/// nombre de buts necessaires et le type de joueur dans mode test
/// sont sauvegardes
/// 
/// @param[in] haut: la touche pour deplacer le maillet vers le haut
/// pour joueur 2
/// @param[in] bas: la touche pour deplacer le maillet vers le bas 
/// pour joueur 2
/// @param[in] gauche: la touche pour deplacer le maillet vers la gauche
/// pour joueur 2
/// @param[in] droite: la touche pour deplacer le maillet vers la droite
/// pour joueur 2
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sauvegarderConfigurationOptions(char* haut, char* bas, char* gauche, char* droite)
{
	//A COMPLETER
	haut_ = haut;
	bas_ = bas;
	gauche_ = gauche;
	droite_ = droite;
	//miseAJourConfiguration(...);
	tinyxml2::XMLDocument fichierConfig;
	fichierConfig.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

	// sauvegarde des options
	tinyxml2::XMLElement* elementConfig{ fichierConfig.NewElement("configuration") };
	//Ajout des options d'affichage
	tinyxml2::XMLElement* elementAffichage{ fichierConfig.NewElement("Affichage") };
	elementAffichage->SetAttribute("DEBUG", peutAfficherDebogage_);
	elementAffichage->SetAttribute("TYPE_OBJET_COLLISION", peutAfficherCollision_);
	elementAffichage->SetAttribute("VITESSE_RONDELLE", peutAfficherVitesseRondelle_);
	elementAffichage->SetAttribute("ETAT_ECLAIRAGE", peutAfficherEclairage_);
	elementAffichage->SetAttribute("ATTRACTION_PORTAILS", peutAfficherAttractionPortail_);
	//Lien avec le noeud configuration
	elementConfig->LinkEndChild(elementAffichage);

	//Ajout des options generales
	tinyxml2::XMLElement* elementOptions{ fichierConfig.NewElement("Options") };
	elementOptions->SetAttribute("NB_BUTS", nbButs_);
	elementOptions->SetAttribute("HAUT", haut_);
	elementOptions->SetAttribute("BAS", bas_);
	elementOptions->SetAttribute("GAUCHE", gauche_);
	elementOptions->SetAttribute("DROITE", droite_);

	elementOptions->SetAttribute("TYPE_JOUEUR", estVirtuel_);
	//Lien avec le noeud configuration
	elementConfig->LinkEndChild(elementOptions);

	//Lien du noeud configuration au noeud principal
	fichierConfig.LinkEndChild(elementConfig);

	fichierConfig.SaveFile("../Exe/donnees/options.xml");

}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::sauvegarderConfigurationOptions(char* haut,
/// char* bas, char* gauche, char* droite)
///
/// Cette fonction retourne si l'affichage au debogage est permise ou non
/// 
///
/// @return retourne vrai s'il est possible d'afficher les options a la
/// console.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirPeutAfficherDebogage()
{
	return peutAfficherDebogage_;
}
///////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::obtenirPeutAfficherCollision()
///
/// Cette fonction retourne si l'affichage au debogage est permise ou non
/// 
///
/// @return retourne vrai s'il est possible d'afficher les options a la
/// console.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirPeutAfficherCollision()
{
	return peutAfficherCollision_;
}
///////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::obtenirPeutAfficherVitesse()
///
/// Cette fonction retourne si l'affichage de la vitesse de la rondelle
/// au debogage est permise ou non
/// 
///
/// @return retourne vrai s'il est possible d'afficher la vitesse de
/// la rondelle a la console.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirPeutAfficherVitesse()
{
	return peutAfficherVitesseRondelle_;
}
///////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::obtenirPeutAfficherEclairage()
///
/// Cette fonction retourne si l'affichage de l'etat de l'eclairage
/// au debogage est permise ou non
/// 
///
/// @return retourne vrai s'il est possible d'afficher l'etat de l'eclairage
/// a la console.
///
////////////////////////////////////////////////////////////////////////
//bool FacadeModele::obtenirPeutAfficherEclairage()
//{
//	return peutAfficherEclairage_;
//}
///////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::obtenirPeutAfficherAttractionPortail()
///
/// Cette fonction retourne si l'affichage de l'etat de l'eclairage
/// au debogage est permise ou non
/// 
///
/// @return retourne vrai s'il est possible d'afficher l'etat de l'eclairage
/// a la console.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirPeutAfficherAttractionPortail()
{
	return peutAfficherAttractionPortail_;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirNbButs()
///
/// Cette fonction retourne le nombre de buts necessaires pour gagner
/// une partie
/// 
///
/// @return le nombre de buts necessaires pour gagner
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirNbButs()
{
	return nbButs_;
}
///////////////////////////////////////////////////////////////////////
///
/// @fn const char* FacadeModele::obtenirHaut()
///
/// Cette fonction retourne la touche pour deplacer le maillet vers le
/// haut pour le joueur 2
/// 
///
/// @return la touche de controle pour deplacer vers le haut
///
////////////////////////////////////////////////////////////////////////
const char* FacadeModele::obtenirHaut()
{
	return sHaut_.c_str();
}
///////////////////////////////////////////////////////////////////////
///
/// @fn const char* FacadeModele::obtenirBas()
///
/// Cette fonction retourne la touche pour deplacer le maillet vers le
/// bas pour le joueur 2
/// 
///
/// @return la touche de controle pour deplacer vers le bas
///
////////////////////////////////////////////////////////////////////////
const char* FacadeModele::obtenirBas()
{
	return sBas_.c_str();
}
///////////////////////////////////////////////////////////////////////
///
/// @fn const char* FacadeModele::obtenirGauche()
///
/// Cette fonction retourne la touche pour deplacer le maillet vers la
/// gauche pour le joueur 2
/// 
///
/// @return la touche de controle pour deplacer vers la gauche
///
////////////////////////////////////////////////////////////////////////
const char* FacadeModele::obtenirGauche()
{
	return sGauche_.c_str();
}
///////////////////////////////////////////////////////////////////////
///
/// @fn const char* FacadeModele::obtenirDroite()
///
/// Cette fonction retourne la touche pour deplacer le maillet vers la
/// droite pour le joueur 2
/// 
///
/// @return la touche de controle pour deplacer vers la droite
///
////////////////////////////////////////////////////////////////////////
const char* FacadeModele::obtenirDroite()
{
	return sDroite_.c_str();
}
///////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::obtenirEstVirtuel()
///
/// Cette fonction le type de joueur que le joueur joue contre
/// 
///
/// @return vrai si le joueur est virtuel
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirEstVirtuel()
{
	return estVirtuel_;
}
void FacadeModele::deplacerClavier(double x, double y)
{
	vue_->deplacerClavier(x, y);
}
///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::creerProfil(char* nom, int vitesse, int passivite)
///
/// Cette fonction cree une profil pour un joueur virtuel. Ce profil a un
/// nom, la vitesse du maillet et son degre de passivite.
/// 
/// @param[in] nom: nom du profil
/// @param[in] vitesse: vitesse du maillet'
/// @param[in] passivite: degre de passivite du joueur virtuel
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::creerProfil(char* nom, int vitesse, int passivite)
{
	ProfilVirtuel(nom, vitesse, passivite);
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::creerProfil(char* nom, int vitesse, int passivite)
///
/// Cette fonction cree une profil pour un joueur virtuel. Ce profil a un
/// nom, la vitesse du maillet et son degre de passivite.
/// 
/// @param[in] nom: nom du profil
/// @param[in] vitesse: vitesse du maillet'
/// @param[in] passivite: degre de passivite du joueur virtuel
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterProfil(ProfilVirtuel profil)
{
	listeProfils.push_back(profil);
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNouveauProfil(char* nom, int vitesse, int passivite)
///
/// Cette fonction ajoute un profil a la liste de profils qui peuvent etre 
/// choisis.
/// 
/// @param[in] nom: Profil du joueur virtuel a ajouter dans la liste
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNouveauProfil(char* nom, int vitesse, int passivite)
{
	bool trouve = false;
	for (size_t i = 0; i < listeProfils.size(); i++)
	{
		if (nom == listeProfils[i].obtenirNom())
		{
			trouve = true;
		}
	}
	if (!trouve)
	{
		std::string sNom = nom;
		ProfilVirtuel profil = ProfilVirtuel(sNom, vitesse, passivite);
		listeProfils.push_back(profil);
	}
}
///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNouveauProfil(std::string nom,
/// int vitesse, int passivite)
///
/// Cette fonction cree une profil pour un joueur virtuel. Ce profil a un
/// nom, la vitesse du maillet et son degre de passivite. Il est ensuite
/// ajoute dans la liste de profils de joueur virtuel
/// 
/// @param[in] nom: nom du profil
/// @param[in] vitesse: vitesse du maillet'
/// @param[in] passivite: degre de passivite du joueur virtuel
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNouveauProfil(std::string nom, int vitesse, int passivite)
{
	bool trouve = false;
	for (size_t i = 0; i < listeProfils.size(); i++)
	{
		if (nom == listeProfils[i].obtenirNom())
		{
			trouve = true;
		}
	}
	if (!trouve)
	{
		ProfilVirtuel profil = ProfilVirtuel(nom, vitesse, passivite);
		listeProfils.push_back(profil);
	}
}
///////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::nombreProfils()
///
/// Cette fonction retourne le nombre de profils qui existent dans la
/// liste de profils
///
/// @return le nombre de profils dans la liste.
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::nombreProfils()
{
	return listeProfils.size();
}


///////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::vitesseDuProfil(int profilChoisi)
///
/// Cette fonction retourne la vitesse du profil souhaite qui est dans la 
/// liste de profil.
///
/// @param[in] profilChoisi: le profil qu'on veut obtenir le nom
/// dans la liste
///
/// @return la vitesse du profil choisi
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::vitesseDuProfil(int profilChoisi)
{
	return listeProfils[profilChoisi].obtenirVitesse();

}

///////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::passiviteDuProfil(int profilChoisi)
///
/// Cette fonction retourne la vitesse du profil souhaite qui est dans la 
/// liste de profil.
///
/// @param[in] profilChoisi: le profil qu'on veut obtenir le nom
/// dans la liste
///
/// @return la vitesse du profil choisi
///
////////////////////////////////////////////////////////////////////////
int FacadeModele::passiviteDuProfil(int profilChoisi)
{
	return listeProfils[profilChoisi].obtenirPassivite();

}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::sauvegardeProfils()
///
/// Cette fonction sauvegarde tous les profils dans le menu de configuration
/// dans un fichier XML.
///
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::sauvegardeProfils()
{
	if (utilitaire::fichierExiste(FICHIER_CONFIGURATION))
	{
		std::remove("../Exe/donnees/profils.xml");
	}
	clearXML();
	tinyxml2::XMLDocument fichierProfils;
	fichierProfils.Clear();
	fichierProfils.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	// sauvegarde des options
	tinyxml2::XMLElement* elementListe{ fichierProfils.NewElement("listeProfils") };
	//Ajout des options d'affichage
	for (size_t i = 0; i < listeProfils.size(); i++)
	{
		//if (profilEstDansXML(listeProfils[i].obtenirNom()))
		//{
		tinyxml2::XMLElement* elementProfil{ fichierProfils.NewElement("profil") };
		elementProfil->SetAttribute("nom", listeProfils[i].obtenirNom());
		elementProfil->SetAttribute("vitesse", listeProfils[i].obtenirVitesse());
		elementProfil->SetAttribute("passivite", listeProfils[i].obtenirPassivite());
		elementListe->LinkEndChild(elementProfil);
		//}
	}
	fichierProfils.LinkEndChild(elementListe);
	fichierProfils.SaveFile("../Exe/donnees/profils.xml");
	//for (size_t i = 0; i < listeProfils.size(); i++)
	//{
	//	cout << "Profile " << i << ": " << listeProfils[i].obtenirNom() << ", " << listeProfils[i].obtenirVitesse() << " ," << listeProfils[i].obtenirPassivite() << "C++" << std::endl;
	//}
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargementProfils()
///
/// Cette fonction charge les profils d'un fichier XML dans le menu de
/// configuration 
///
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargementProfils()
{
	//char* tmpChar = new char();
	int tmpVitesse = 0;
	int tmpPassivite = 0;
	int compteur = 0;
	listeProfils.clear();
	//nomProfils.clear();


	tinyxml2::XMLDocument document;
	document.LoadFile("../Exe/donnees/profils.xml");

	tinyxml2::XMLElement* elementListeProfils{ document.FirstChildElement("listeProfils") };

	if (elementListeProfils != nullptr)
	{
		tinyxml2::XMLElement* elementProfil = elementListeProfils->FirstChildElement("profil");
		while (elementProfil != nullptr)
		{
			charProfils.push_back((char*)elementProfil->Attribute("nom"));
			//charProfils.push_back(tmpChar);
			nomProfils.push_back(charProfils[compteur]);
			//tmpNom = tmpChar;
			if (elementProfil->QueryIntAttribute("vitesse", &tmpVitesse) != tinyxml2::XML_SUCCESS)
			{
				std::cerr << "Erreur: vitesse  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
			}
			if (elementProfil->QueryIntAttribute("passivite", &tmpPassivite) != tinyxml2::XML_SUCCESS)
			{
				std::cerr << "Erreur: passivite  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
			}
			ajouterNouveauProfil(charProfils[compteur], tmpVitesse, tmpPassivite);

			elementProfil = elementProfil->NextSiblingElement("profil");
			compteur++;
		}
	}
	//for (size_t i = 0; i < listeProfils.size(); i++)
	//{
	//	cout << "Profile " << i << ": " << listeProfils[i].obtenirNom() << ", " << listeProfils[i].obtenirVitesse() << " ," << listeProfils[i].obtenirPassivite();
	//}
	//delete tmpChar;
}
///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargementProfils()
///
/// Cette fonction efface le contenu du fichier des profils XML avant 
/// la sauvegarde.
///
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::clearXML()
{
	tinyxml2::XMLDocument document;
	document.LoadFile("../Exe/donnees/profils.xml");
	document.Clear();
	//listeProfils.clear();
	nomProfils.clear();
	charProfils.clear();
}


///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::supprimerProfil(std::string nom)
///
/// Cette fonction charge les profils d'un fichier XML dans le menu de
/// configuration 
///
/// @param[in] nom: nom du profil a supprimer
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerProfil(std::string nom)
{
	string tmp = "";
	for (std::vector<ProfilVirtuel>::iterator it = listeProfils.begin(); it != listeProfils.end(); it++)
	{
		tmp = string(it->obtenirNom());
		if (tmp == nom)
		{
			//std::cout << tmp << ": in fm" << std::endl;;
		}
	}
}
///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiserProfils()
///
/// Cette fonction reinitialise la liste de profils en effacant son 
/// son contenu
///
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiserProfils()
{
	listeProfils.clear();
}

void FacadeModele::reinitialiserTest()
{
	arbre_->chercher("maillet")->assignerPositionRelative(glm::dvec3(arbre_->chercher("table")->obtenirSommets()[5].x + 5.0, 0.0, 0.0));
	arbre_->chercher("table")->chercher(2)->assignerPositionRelative(glm::dvec3(arbre_->chercher("table")->obtenirSommets()[1].x - 5.0, 0.0, 0.0));

	//maillet2->assignerPositionRelative(glm::dvec3(arbre_->chercher("table")->obtenirSommets()[5].x + 5.0, 0.0, 0.0));
	arbre_->chercher("rondelle")->assignerPositionRelative(glm::dvec3(0.0, 0.0, 0.0));
	NoeudRondelle* rondelle = dynamic_cast<NoeudRondelle*> (arbre_->chercher(ArbreRenduINF2990::NOM_RONDELLE));
	rondelle->modifierVitesse(glm::dvec2(0.0, 0.0));
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::ajouterNomProfil(std::string nom)
///
/// Cette fonction ajoute le nom d'un profil dans une liste. Ceci est 
/// necessaire pour pouvoir acceder les noms des profils apres le
/// chargement du fichier des profils XML
///
/// @param[in] nom: nom du profil a supprimer
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::ajouterNomProfil(std::string nom)
{
	nomProfils.push_back(nom);
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomInElas()
///
/// Cette fonction fait un zoom avec les points du rectangle elastique 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomInElas()
{

	glm::ivec2 coin1(pointAncrageX_, pointAncrageY_);
	glm::ivec2 coin2(pointFinalX_, pointFinalY_);
	vue_->zoomerInElastique(coin1, coin2);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomOutElas()
///
/// Cette fonction fait un zoom avec les points du rectangle elastique 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomOutElas()
{

	glm::ivec2 coin1(pointAncrageX_, pointAncrageY_);
	glm::ivec2 coin2(pointFinalX_, pointFinalY_);
	vue_->zoomerOutElastique(coin1, coin2);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomOut()
///
/// Cette fonction fait un zoom avec les points 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomOut()
{
	vue_->zoomerOut();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::zoomIn()
///
/// Cette fonction fait un zoom avec les points 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::zoomIn()
{
	vue_->zoomerIn();
}

void FacadeModele::selectionRectangle()
{

	conteneur_enfants conteneurEnfants = table_->obtenirEnfants();
	glm::dvec3 coinSup;
	glm::dvec3 coinInf;
	if (pointAncrageX_ <= pointFinalX_)
	{
		coinSup.x = pointAncrageX_;
		coinInf.x = pointFinalX_;
	}
	else
	{
		coinSup.x = pointFinalX_;
		coinInf.x = pointAncrageX_;
	}

	if (pointAncrageY_ <= pointFinalY_)
	{
		coinSup.y = pointAncrageY_;
		coinInf.y = pointFinalY_;
	}
	else
	{
		coinSup.y = pointFinalY_;
		coinInf.y = pointAncrageY_;
	}


	vue_->convertirClotureAVirtuelle(coinSup.x, coinSup.y, coinSup);
	vue_->convertirClotureAVirtuelle(coinInf.x, coinInf.y, coinInf);

	for (std::vector<NoeudAbstrait*>::iterator it = conteneurEnfants.begin(); it != conteneurEnfants.end(); ++it)
	{
		NoeudAbstrait* node = *it;

		glm::dvec3 position = node->obtenirPositionRelative();

		//if ((position.x >= pointAncrageVirtuelle.x && position.x <= pointFinalVirtuelle.x) || (position.x <= pointAncrageVirtuelle.x && position.x >= pointFinalVirtuelle.x)*/)
		//{
		//	if ((position.y >= pointAncrageVirtuelle.y && position.y <= pointFinalVirtuelle.y) /* || (position.x <= pointAncrageVirtuelle.x && position.x >= pointFinalVirtuelle.x)*/)
		//	{
		//		node->inverserSelection();
		//	}
		//}

		if (position[0] >= coinSup[0] && position[0] <= coinInf[0])
		{

			if (position[1] >= coinInf[1] && position[1] <= coinSup[1])
			{
				node->inverserSelection();
				//node->selection
			}
		}

	}
}

void FacadeModele::initialiserPartie(int nbBut, bool estVirtuel)
{
	butJoueur1_ = 0;
	butJoueur2_ = 0;
	activerBut_ = true;
	adversaireVirtuel(estVirtuel);
	/*if (estVirtuel)
	arbre_->initialiserPartieAvecVirtuel();
	else
	arbre_->initialiserPartieAvecVirtuel();*/
	partieEnCours_ = new Partie(nbBut, estVirtuel);
	//partieEnCours_->miseEnPlaceMaillet(estVirtuel);
	afficherPanelRapide_ = false;
	//std::cout << "bitch dab" << std::endl;
}

void FacadeModele::initialiserPartieTournoi()
{
	tournoiEnCours_ = new Tournoi();
}

void FacadeModele::arreterPartie()
{

	if (enTournoi_)
	{
		////nextPartie();
		//nbMaxPartieTournoi_--;

		//switch (nbMaxPartieTournoi_)
		//{
		//case 1:
		//	nomVainqueur2_ = partieEnCours_->obtenirVainqueur();
		//	break;
		//case 2:
		//	nomVainqueur1_ = partieEnCours_->obtenirVainqueur();
		//	break;
		//case 0:
		//	gagnant_ = partieEnCours_->obtenirVainqueur();
		//	enTournoi_ = false;
		//	break;
		//default:
		//	break;
		//}

		///*delete partieEnCours_;
		//partieEnCours_ = nullptr;*/
		nextPartie();

	}
	else
	{
		/////////////////////////A commenter maybe//////////////////////////////
		activerBut_ = false;
		/*delete partieEnCours_;
		partieEnCours_ = nullptr;*/
	}


}
void FacadeModele::arreterPartie(std::string nom)
{
	if (!enTournoi_)
	{
		afficherPanelRapide_ = true;
		gagnantPartieRapide_ = nom;
		if (nom == "Joueur 1")
		{
			leVainqueur_ = true;
			scoreFinalLooser_ = partieEnCours_->obtenirButJoueur2();
		}
		else if (nom == "Joueur 2")
		{
			leVainqueur_ = false;
			scoreFinalLooser_ = partieEnCours_->obtenirButJoueur1();
		}

	}

	//std::cout << "           LE gagnant est         " << nom << std::endl;

	if (enTournoi_)
	{
		nbMaxPartieTournoi_--;

		switch (nbMaxPartieTournoi_)
		{
		case 1:
			nomVainqueur2_ = nom;
			actualiser2_ = true;
			if (nom3_ == nomVainqueur2_)
			{
				joueur3Passe_ = true;
			}
			break;
		case 2:

			nomVainqueur1_ = nom;
			actualiser1_ = true;
			if (nom1_ == nomVainqueur1_)
			{
				joueur1Passe_ = true;
			}
			break;
		case 0:
			gagnant_ = nom;
			actualiser3_ = true;
			if (nomVainqueur1_ == gagnant_)
			{
				vainqueur1Passe_ = true;
			}
			enTournoi_ = false;
			break;
		default:
			break;
		}
	}

	arreterPartie();

}

void FacadeModele::arreterTournoi()
{
	enTournoi_ = false;
	delete tournoiEnCours_;
	tournoiEnCours_ = nullptr;
}

void FacadeModele::lancerPartieRapide()
{
	//partieEnCours_ = new Partie()
}
void FacadeModele::lancerPartieTournoi(std::string nom1, std::string nom2)
{
	if (enTournoi_)
	{

		if (nbMaxPartieTournoi_ > 0)
		{
			activerBut_ = true;
			//std::cout << "les joueurs sont " << nom1 << "  et   "<< nom2 <<std::endl;
			if (nom1 == nom1_ && nom2 == nom2_)
			{
				partieEnCours_ = new Partie(nbButs_, j1_, nom1_, j2_, nom2_);
				if ((j1_ && !j2_) || (!j1_ && j2_))
				{
					adversaireVirtuel_ = true;
					joueurVirtuelDansPartieCourante_ = true;
				}
				else
				{
					adversaireVirtuel_ = false;
					joueurVirtuelDansPartieCourante_ = false;
				}

			}
			else if (nom1 == nom3_ && nom2 == nom4_)
			{
				partieEnCours_ = new Partie(nbButs_, j3_, nom3_, j4_, nom4_);
				if ((j3_ && !j4_) || (!j3_ && j4_))
				{
					adversaireVirtuel_ = true;
					joueurVirtuelDansPartieCourante_ = true;
				}
				else
				{
					adversaireVirtuel_ = false;
					joueurVirtuelDansPartieCourante_ = false;
				}
			}
			else if (nom1 == nom1_ && nom2 == nom3_)
			{
				partieEnCours_ = new Partie(nbButs_, j1_, nom1_, j3_, nom3_);
				if ((j1_ && !j3_) || (!j1_ && j3_))
				{
					adversaireVirtuel_ = true;
					joueurVirtuelDansPartieCourante_ = true;
				}
				else
				{
					adversaireVirtuel_ = false;
					joueurVirtuelDansPartieCourante_ = false;
				}
			}
			else if (nom1 == nom1_ && nom2 == nom4_)
			{
				partieEnCours_ = new Partie(nbButs_, j1_, nom1_, j4_, nom4_);
				if ((j1_ && !j4_) || (!j1_ && j4_))
				{
					adversaireVirtuel_ = true;
					joueurVirtuelDansPartieCourante_ = true;
				}
				else
				{
					adversaireVirtuel_ = false;
					joueurVirtuelDansPartieCourante_ = false;
				}
			}
			else if (nom1 == nom2_ && nom2 == nom3_)
			{
				partieEnCours_ = new Partie(nbButs_, j2_, nom2_, j3_, nom3_);
				if ((j2_ && !j3_) || (!j2_ && j3_))
				{
					adversaireVirtuel_ = true;
					joueurVirtuelDansPartieCourante_ = true;
				}
				else
				{
					adversaireVirtuel_ = false;
					joueurVirtuelDansPartieCourante_ = false;
				}
			}
			else if (nom1 == nom2_ && nom2 == nom4_)
			{
				partieEnCours_ = new Partie(nbButs_, j2_, nom2_, j4_, nom4_);
				if ((j2_ && !j4_) || (!j2_ && j4_))
				{
					adversaireVirtuel_ = true;
					joueurVirtuelDansPartieCourante_ = true;
				}
				else
				{
					adversaireVirtuel_ = false;
					joueurVirtuelDansPartieCourante_ = false;
				}
			}
		}
	}


}

void FacadeModele::assignerBut(bool joueur1)
{
	if (joueur1)
	{
		//std::cout << " TChiki 7 " << std::endl;
		if (activerBut_)
		{
			//std::cout << " TChiki 7 " << std::endl;
			partieEnCours_->assignerbutJ1();
			butJoueur1_++;
			//std::cout << " TChiki 8 " << std::endl;
		}

		//std::cout << " TChiki 8 " << std::endl;
		//std::cout << "DRAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
	}
	else
	{
		//std::cout << " TChiki 7 " << std::endl;
		if (activerBut_)
		{
			//std::cout << " TChiki 9 " << std::endl;
			partieEnCours_->assignerbutJ2();
			butJoueur2_++;
			//std::cout << " TChiki 10 " << std::endl;
		}

		//std::cout << " TChiki 8 " << std::endl;
		//std::cout << "DRAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
	}

}

void FacadeModele::initialiserTournoi(int but, bool j1, string nom1, bool j2, string nom2, bool j3, string nom3, bool j4, string nom4)
{
	butJoueur1_ = 0;
	butJoueur2_ = 0;
	activerBut_ = true;
	enTournoi_ = true;
	int nbButs_ = but;
	j1_ = j1;
	//if(j1_)
	nom1_ = nom1;
	j2_ = j2;
	nom2_ = nom2;
	j3_ = j3;
	nom3_ = nom3;
	j4_ = j4;
	nom4_ = nom4;
	vainqueur1_ = "";
	vainqueur2_ = "";
	gagnant_ = "";
	nbMaxPartieTournoi_ = 3;
	//std::cout << "les joueurs present sont " << nom1 << "  et   " << nom2 << "  et   " << nom3 << "  et   " << nom4 << std::endl;
	joueur1Passe_ = false;
	joueur3Passe_ = false;
	vainqueur1Passe_ = false;
	actualiser1_ = false;
	actualiser2_ = false;
	actualiser3_ = false;
	nextPartie();
}

void FacadeModele::joueurMaillet1(int x, int y)
{
	glm::dvec3 positionSouris;
	positionSouris.z = 2.0;
	vue_->convertirClotureAVirtuelle(x, y, positionSouris);
	NoeudAbstrait* noeud = table_->chercher(0);
	//cout << noeud->obtenirType() << endl;

	if (table_->curseurEstDansZone(positionSouris*1.02) && (positionSouris.x)*1.04 <= 0.0 && positionSouris.y <= 41.0 )
		noeud->assignerPositionRelative(positionSouris);
}
void FacadeModele::joueurMaillet2(double x, double y)
{

	NoeudAbstrait* noeud = table_->chercher(2);
	glm::dvec3 positionFuture = glm::dvec3(noeud->obtenirPositionRelative().x + x, noeud->obtenirPositionRelative().y + y, 0);
	if (table_->curseurEstDansTable(positionFuture) && positionFuture.x > 0)
		noeud->assignerPositionRelative(glm::dvec3(noeud->obtenirPositionRelative().x + x, noeud->obtenirPositionRelative().y + y, 0));

}

void FacadeModele::nextPartie()
{
	//std::cout << " TChiki 3 en tournoi " << enTournoi_ << "   nbPartie " <<  nbMaxPartieTournoi_ << std::endl;
	//Partie* tmp = &(*partieEnCours_);
	if (enTournoi_ && nbMaxPartieTournoi_ > 0)
	{

		activerBut_ = true;
		switch (nbMaxPartieTournoi_)
		{
		case 1:
			afficherNom1_ = nomVainqueur1_;
			afficherNom2_ = nomVainqueur2_;
			lancerPartieTournoi(nomVainqueur1_, nomVainqueur2_);

			break;
		case 2:
			afficherNom1_ = nom3_;
			afficherNom2_ = nom4_;
			lancerPartieTournoi(nom3_, nom4_);
			break;
		case 3:
			afficherNom1_ = nom1_;
			afficherNom2_ = nom2_;
			lancerPartieTournoi(nom1_, nom2_);
			break;
		default:
			break;
		}


	}


}
bool FacadeModele::afficherPanelRapide()
{
	return afficherPanelRapide_;
}
int FacadeModele::scoreFinalPerdant()
{
	return scoreFinalLooser_;
}
bool FacadeModele::nomVainqueurPartieRapide()
{
	return leVainqueur_;
}
bool FacadeModele::getJoueur1Passe()
{
	return joueur1Passe_;
}
bool FacadeModele::getJoueur3Passe()
{
	return joueur3Passe_;
}
bool FacadeModele::getVainqueur1Passe()
{
	return vainqueur1Passe_;
}
bool FacadeModele::getActualiser1()
{
	return actualiser1_;
}
bool FacadeModele::getActualiser2()
{
	return actualiser2_;
}
bool FacadeModele::getActualiser3()
{
	return actualiser3_;
}

void FacadeModele::reinitialiserPartie()
{
	arbre_->chercher("maillet")->assignerPositionRelative(glm::dvec3(arbre_->chercher("table")->obtenirSommets()[5].x + 5.0, 0.0, 0.0));
	arbre_->chercher("mailletV")->assignerPositionRelative(glm::dvec3(arbre_->chercher("table")->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
	butJoueur1_ = 0;
	butJoueur2_ = 0;
	//maillet2->assignerPositionRelative(glm::dvec3(arbre_->chercher("table")->obtenirSommets()[5].x + 5.0, 0.0, 0.0));
	arbre_->chercher("rondelle")->assignerPositionRelative(glm::dvec3(0.0, 0.0, 0.0));
	NoeudRondelle* rondelle = dynamic_cast<NoeudRondelle*> (arbre_->chercher(ArbreRenduINF2990::NOM_RONDELLE));
	rondelle->modifierVitesse(glm::dvec2(0.0, 0.0));
	afficherPanelRapide_ = false;
	activerBut_ = true;
	partieEnCours_->reinitialiser();
}

bool FacadeModele::butsActifs()
{
	return activerBut_;
}

void FacadeModele::adversaireVirtuel(bool virtuel)
{
	adversaireVirtuel_ = virtuel;
}
bool  FacadeModele::adversaireEstVirtuel() {
	return adversaireVirtuel_;
}
void FacadeModele::enModeEdition(bool modeEdition)
{
	modeEdition_ = modeEdition;
	activerBut_ = modeEdition;
	adversaireVirtuel_ = obtenirEstVirtuel();
	/*if(modeEdition)
	arbre_->initialiserPartieAvecHumain();*/
}
void FacadeModele::enModeTest(bool modeTest)
{
	modeTest_ = modeTest;
}
void FacadeModele::sizeFenetre(int x, int y)
{
	fenetreX_ = x;
	fenetreY_ = y;
}
void FacadeModele::tempsJouer(char* tempsJouer)
{
	tempsJouer_ = tempsJouer;
}
bool FacadeModele::joueurVirtuelDansPartieCourante()
{
	return joueurVirtuelDansPartieCourante_;
}

void FacadeModele::setTypeValue(bool value)
{
	//typeVue_ = value;
	//cout << "lol:" << typeVue_ << endl;
}
void FacadeModele::sauvegarderTournoi()
{
	//miseAJourConfiguration(...);
	//initialiserSauvegardeTournoi();
	tinyxml2::XMLDocument fichierTournoi;
	fichierTournoi.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");

	// sauvegarde des options
	tinyxml2::XMLElement* elementConfig{ fichierTournoi.NewElement("tournoi") };
	//Ajout des options d'affichage
	tinyxml2::XMLElement* elementJoueurs{ fichierTournoi.NewElement("joueurs") };
	elementJoueurs->SetAttribute("NOM1", listeJoueursTournoi[0].getNom().c_str());
	elementJoueurs->SetAttribute("NOM2", listeJoueursTournoi[1].getNom().c_str());
	elementJoueurs->SetAttribute("NOM3", listeJoueursTournoi[2].getNom().c_str());
	elementJoueurs->SetAttribute("NOM4", listeJoueursTournoi[3].getNom().c_str());
	elementJoueurs->SetAttribute("TYPE1", listeJoueursTournoi[0].estVirtuel());
	elementJoueurs->SetAttribute("TYPE2", listeJoueursTournoi[1].estVirtuel());
	elementJoueurs->SetAttribute("TYPE3", listeJoueursTournoi[2].estVirtuel());
	elementJoueurs->SetAttribute("TYPE4", listeJoueursTournoi[3].estVirtuel());
	elementJoueurs->SetAttribute("PROFIL1", indexTournoi[0]);
	elementJoueurs->SetAttribute("PROFIL2", indexTournoi[1]);
	elementJoueurs->SetAttribute("PROFIL3", indexTournoi[2]);
	elementJoueurs->SetAttribute("PROFIL4", indexTournoi[3]);
	//Lien avec le noeud configuration
	elementConfig->LinkEndChild(elementJoueurs);


	//Lien du noeud configuration au noeud principal
	fichierTournoi.LinkEndChild(elementConfig);

	fichierTournoi.SaveFile("../Exe/donnees/tournoi.xml");

}
//bool FacadeModele::getTypeValue()
//{
//	
////	return typeVue_;
//}
void FacadeModele::activationVueOrbite()
{
	vue_ = vueOrbite_;
}
void FacadeModele::activationVueOrtho()
{
	vue_ = vueOrtho_;
}

void FacadeModele::initialiserSauvegardeTournoi()
{
	/*listeJoueursTournoi[0] = NoeudJoueur(false, "");
	listeJoueursTournoi[1] = NoeudJoueur(false, "");
	listeJoueursTournoi[2] = NoeudJoueur(false, "");
	listeJoueursTournoi[3] = NoeudJoueur(false, "");*/
}

void FacadeModele::initaliserSono()
{
	FMOD_System_Create(&leSysteme_);
	FMOD_System_Init(leSysteme_, 8, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(leSysteme_, "media/ke.mp3", FMOD_CREATESAMPLE, 0, &collisionMur_);
	FMOD_System_CreateSound(leSysteme_, "media/anotherDRAAA.mp3", FMOD_CREATESAMPLE, 0, &but_);
	FMOD_System_CreateSound(leSysteme_, "media/draa.mp3", FMOD_CREATESAMPLE, 0, &collisionMaillet_);
	FMOD_System_CreateSound(leSysteme_, "media/littletimmy.mp3", FMOD_CREATESAMPLE, 0, &collisionPortail_);
	FMOD_System_CreateSound(leSysteme_, "media/CARCR111.WAV", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sonDeFond_);
	//FMOD_System_CreateSound(leSysteme_, "media/TT.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sonDeFond_);
	//CARCR111
	FMOD_Sound_SetLoopCount(sonDeFond_, -1997);

	//FMOD_System_PlaySound(leSysteme_, FMOD_CHANNEL_FREE, sonDeFond_, 0, NULL);
}
void FacadeModele::jouerSonMaillet()
{
	
	
		FMOD_System_PlaySound(leSysteme_, FMOD_CHANNELINDEX(1), collisionMaillet_, 0, NULL);
		FMOD_System_GetChannel(leSysteme_, 1, &chaine_);
		FMOD_Channel_SetVolume(chaine_, 0.30);
	
	
}
void FacadeModele::jouerSonMur()
{
	
	
		FMOD_System_PlaySound(leSysteme_, FMOD_CHANNELINDEX(2), collisionMur_, 0, NULL);
		FMOD_System_GetChannel(leSysteme_, 2, &chaine_);
		FMOD_Channel_SetVolume(chaine_, 0.30);
	
}
void FacadeModele::jouerSonDeFond()
{
	if (!modeTest_)
	{
		FMOD_System_PlaySound(leSysteme_, FMOD_CHANNELINDEX(3), sonDeFond_, 0, NULL);
		FMOD_System_GetChannel(leSysteme_, 3, &chaine_);
		FMOD_BOOL enPause;
		FMOD_System_GetChannel(leSysteme_, 3, &chaine_);
		FMOD_Channel_GetPaused(chaine_, &enPause);
		if (enPause)
		{
			FMOD_Channel_SetPaused(chaine_, 0);
		}
		FMOD_Channel_SetVolume(chaine_, 0.14);
	}
}
void FacadeModele::jouerSonPortail()
{
	
	
		FMOD_System_PlaySound(leSysteme_, FMOD_CHANNELINDEX(4), collisionPortail_, 0, NULL);
		FMOD_System_GetChannel(leSysteme_, 4, &chaine_);
		FMOD_Channel_SetVolume(chaine_, 0.30);
	
}
void FacadeModele::jouerSonBut()
{
		FMOD_System_PlaySound(leSysteme_, FMOD_CHANNELINDEX(5), but_, 0, NULL);
		FMOD_System_GetChannel(leSysteme_, 5, &chaine_);
		FMOD_Channel_SetVolume(chaine_, 0.60);
}
void FacadeModele::mettreEnPause()
{
	FMOD_BOOL enPause;
	FMOD_System_GetChannel(leSysteme_, 3, &chaine_);
	FMOD_Channel_GetPaused(chaine_, &enPause);
	if (!enPause)
	{
		FMOD_Channel_SetPaused(chaine_, 1);
	}

	//FMOD_Channel_Stop(chaine_);
	/*else
	{
		FMOD_Channel_SetPaused(chaine_, 0);
	}*/
}
void FacadeModele::relacherMusique()
{
	FMOD_Sound_Release(collisionMur_);
	FMOD_Sound_Release(but_);
	FMOD_Sound_Release(collisionMaillet_);
	FMOD_Sound_Release(collisionPortail_);
	FMOD_Sound_Release(sonDeFond_);
	FMOD_System_Close(leSysteme_);
	FMOD_System_Release(leSysteme_);
}






void FacadeModele::chargementTournoi()
{
	for (size_t i = 0; i < 4; i++)
	{
		indexTournoi[i] = 0;
	}
		bool tmpBool = false;
		int tmpInt = 0;

		if (!utilitaire::fichierExiste("../Exe/donnees/tournoi.xml"))
		{
			assignerJoueur1Tournoi("", false, 1);
			assignerJoueur2Tournoi("", false, 1);
			assignerJoueur3Tournoi("", false, 1);
			assignerJoueur4Tournoi("", false, 1);
		}
		else
		{
			tinyxml2::XMLDocument document;

			//Lire tournoi.xml
			document.LoadFile("../Exe/donnees/tournoi.xml");
			const tinyxml2::XMLElement* elementTournoi{ document.FirstChildElement("tournoi") };

			if (elementTournoi != nullptr)
			{
				const tinyxml2::XMLElement* elementJoueurs{ elementTournoi->FirstChildElement("joueurs") };
				if (elementJoueurs != nullptr)
				{
					if (elementJoueurs->QueryBoolAttribute("TYPE1", &tmpBool) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: TYPE1  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					if (elementJoueurs->QueryIntAttribute("PROFIL1", &tmpInt) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: PROFIL1 : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					listeNomTournoi[0] = elementJoueurs->Attribute("NOM1");
					assignerJoueur1Tournoi(listeNomTournoi[0].c_str(), tmpBool, tmpInt);
					if (elementJoueurs->QueryBoolAttribute("TYPE2", &tmpBool) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: TYPE2  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					if (elementJoueurs->QueryIntAttribute("PROFIL2", &tmpInt) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: PROFIL2 : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					listeNomTournoi[1] = elementJoueurs->Attribute("NOM2");
					assignerJoueur1Tournoi(listeNomTournoi[1].c_str(), tmpBool, tmpInt);
					if (elementJoueurs->QueryBoolAttribute("TYPE3", &tmpBool) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: TYPE3  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					if (elementJoueurs->QueryIntAttribute("PROFIL3", &tmpInt) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: PROFIL3 : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					listeNomTournoi[2] = elementJoueurs->Attribute("NOM3");
					assignerJoueur1Tournoi(listeNomTournoi[2].c_str(), tmpBool, tmpInt);
					if (elementJoueurs->QueryBoolAttribute("TYPE4", &tmpBool) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: TYPE4  : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					if (elementJoueurs->QueryIntAttribute("PROFIL4", &tmpInt) != tinyxml2::XML_SUCCESS)
					{
						std::cerr << "Erreur: PROFIL4 : chargement XML : attribut inexistant ou type incorrect. " << std::endl;
					}
					listeNomTournoi[3] = elementJoueurs->Attribute("NOM4");
					assignerJoueur1Tournoi(listeNomTournoi[3].c_str(), tmpBool, tmpInt);
				}
			}
		}
}

void FacadeModele::assignerJoueur1Tournoi(const char* nom, bool estVirtuel, int index)
{
	listeJoueursTournoi[0] = NoeudJoueur(false, "");
	indexTournoi[0] = index;
	listeJoueursTournoi[0].assignerNom(nom);
	listeJoueursTournoi[0].setVirtuel(estVirtuel);
}
void FacadeModele::assignerJoueur2Tournoi(const char* nom, bool estVirtuel, int index)
{
	listeJoueursTournoi[1] = NoeudJoueur(false, "");
	indexTournoi[1] = index;
	listeJoueursTournoi[1].assignerNom(nom);
	listeJoueursTournoi[1].setVirtuel(estVirtuel);
}
void FacadeModele::assignerJoueur3Tournoi(const char* nom, bool estVirtuel, int index)
{
	listeJoueursTournoi[2] = NoeudJoueur(false, "");
	indexTournoi[2] = index;
	listeJoueursTournoi[2].assignerNom(nom);
	listeJoueursTournoi[2].setVirtuel(estVirtuel);
}
void FacadeModele::assignerJoueur4Tournoi(const char* nom, bool estVirtuel, int index)
{
	listeJoueursTournoi[3] = NoeudJoueur(false, "");
	indexTournoi[3] = index;
	listeJoueursTournoi[3].assignerNom(nom);
	listeJoueursTournoi[3].setVirtuel(estVirtuel);
}

const char * FacadeModele::obtenirNomJoueur1Tournoi()
{
	return listeNomTournoi[0].c_str();
}

const char * FacadeModele::obtenirNomJoueur2Tournoi()
{
	return listeNomTournoi[1].c_str();
}

const char * FacadeModele::obtenirNomJoueur3Tournoi()
{
	return listeNomTournoi[2].c_str();
}

const char * FacadeModele::obtenirNomJoueur4Tournoi()
{
	return listeNomTournoi[3].c_str();
}

bool FacadeModele::obtenirTypeJoueur1Tournoi()
{
	return listeJoueursTournoi[0].estVirtuel();
}

bool FacadeModele::obtenirTypeJoueur2Tournoi()
{
	return listeJoueursTournoi[1].estVirtuel();
}

bool FacadeModele::obtenirTypeJoueur3Tournoi()
{
	return listeJoueursTournoi[2].estVirtuel();
}

bool FacadeModele::obtenirTypeJoueur4Tournoi()
{
	return listeJoueursTournoi[3].estVirtuel();
}

int FacadeModele::obtenirProfilJoueur1Tournoi()
{
	return indexTournoi[0];
}

int FacadeModele::obtenirProfilJoueur2Tournoi()
{
	return indexTournoi[1];
}

int FacadeModele::obtenirProfilJoueur3Tournoi()
{
	return indexTournoi[2];
}

int FacadeModele::obtenirProfilJoueur4Tournoi()
{
	return indexTournoi[3];
}

///////////////////////////////////////////////////////////////////////
///
/// @fn bool FacadeModele::obtenirPeutAfficherEclairage()
///
/// Cette fonction retourne si l'affichage de l'etat de l'eclairage
/// au debogage est permise ou non
/// 
///
/// @return retourne vrai s'il est possible d'afficher l'etat de l'eclairage
/// a la console.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirPeutAfficherEclairage()
{
	return peutAfficherEclairage_;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn const char* FacadeModele::nomDuProfil(int profilChoisi)
///
/// Cette fonction retourne le nom du profil souhaite qui est dans la 
/// liste de profil.
///
/// @param[in] profilChoisi: le profil qu'on veut obtenir le nom
/// dans la liste
///
/// @return le nom du profil choisi
///
////////////////////////////////////////////////////////////////////////
const char* FacadeModele::nomDuProfil(int profilChoisi)
{
	//return listeProfils[profilChoisi].obtenirNom();
	//return charProfils[profilChoisi];
	//return "abc";
	return nomProfils[profilChoisi].c_str();

}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
