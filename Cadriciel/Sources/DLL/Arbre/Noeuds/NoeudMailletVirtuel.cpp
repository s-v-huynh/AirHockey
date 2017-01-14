///////////////////////////////////////////////////////////////////////////
/// @file NoeudMailletVirtuel.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudMailletVirtuel.h"
#include "Utilitaire.h"
#include "FacadeModele.h"
#include "GL/glew.h"
#include <cmath>
#include "ArbreRenduINF2990.h"
#include "Modele3D.h"
#include "OpenGL_VBO.h"

#define VITESSE_MAX 5.0
#define VITESSE_MAX_MAILLET 20.0
#define DISTANCE_DU_BUT 7.0
int NoeudMailletVirtuel::compteurGreen_ = 0;
int NoeudAbstrait::compteurMailletV_ = 0;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMailletVirtuel::NoeudMailletVirtuel(const std::string& typeNoeud)
/// : NoeudComposite { typeNoeud }
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMailletVirtuel::NoeudMailletVirtuel(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	NoeudAbstrait::compteurMailletV_++;
	couleurMailletVirtuel_[0] = 255;
	couleurMailletVirtuel_[1] = 0;
	couleurMailletVirtuel_[2] = 255;
	couleurSelection_[1] = 0;
	rayonMailletV_ = 0.0;
	vitesse_ = 1.0;
	vitesseDeFrappe_[0] = vitesseDeFrappe_[1] = 0.0;
	//angleDeplacement_ = 60;
	largeurBut_ = 60.0;
	attribuerCouleur();
	dx_ = vitesse_ * static_cast<float>(cos(utilitaire::DEG_TO_RAD(angleDeplacement_)));
	dy_ = vitesse_ * static_cast<float>(sin(utilitaire::DEG_TO_RAD(angleDeplacement_)));
	//std::cout << dx_ << "   " << dy_ << std::endl;

	rondelle_ = NULL;
	//probabilite_ = 0;
	
	vitesseDeFrappe_[1] = vitesseDeFrappe_[0] = 0.0;
	/*forceImpulsion_[0] = 0.26;
	forceImpulsion_[1] = 0.06;*/
	offensif_ = false;
	passif_ = false;
	srand((unsigned int)time(NULL));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMailletVirtuel::~NoeudMailletVirtuel()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMailletVirtuel::~NoeudMailletVirtuel()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMailletVirtuel::NoeudMailletVirtuel(NoeudMailletVirtuel& noeud)
///
/// Le constructeur par copie
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMailletVirtuel::NoeudMailletVirtuel(NoeudMailletVirtuel& noeud)
{
	noeud.angleRotation_ = angleRotation_;
	noeud.facteurEchelle_ = facteurEchelle_;
	noeud.rayonMailletV_ = rayonMailletV_;
	noeud.coefRebondissement = coefRebondissement;
	rondelle_ = noeud.rondelle_;
	vitesse_ = 1.0;
	largeurBut_ = 2.0;
	probabilite_ = 0;
	vitesseDeFrappe_[0]= vitesseDeFrappe_[1] = vitesse_= noeud.vitesse_;
	forceImpulsion_= noeud.forceImpulsion_;
	offensif_ = false;
	passif_ = false;
	srand((unsigned int)time(NULL));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletVirtuel::afficherConcret
/// (const glm::mat4& vueProjection, const bool& attribuerCouleur)const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///				attribuerCouleur : booleen
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	glPushName(id_);
	glPushMatrix();
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(matrVue, matrProjection, vueProjection, attribuerCouleur);

	// Révolution autour du centre.
	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurMailletVirtuel_[0];
	couleurObjet[1] = couleurMailletVirtuel_[1];
	couleurObjet[2] = couleurMailletVirtuel_[2];
	GLubyte couleurSelection[3];
	couleurSelection[0] = couleurSelection_[0];
	couleurSelection[1] = couleurSelection_[1];
	couleurSelection[2] = couleurSelection_[2];

	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(1.0, 0.0, .0));
	modele = glm::translate(modele, glm::vec3(0.0, 0.0, 0.0));

	modele = glm::translate(modele, centreRotation_);
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0, 0, 1.0));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::scale(modele, glm::vec3(rayonMailletV_, rayonMailletV_, rayonMailletV_));
	// Affichage du modèle.
	if (!FacadeModele::obtenirInstance()->modeEdition())
	vbo_->dessiner(estSelectionne(), attribuerCouleur, couleurObjet, couleurSelection, modele, matrVue, matrProjection, vueProjection*modele);
	glPopMatrix();
	glPopName();
}

//deplacement en y 
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletVirtuel::moveY(double temps)
///
/// Cette fonction deplaceer l'objet en y
///
/// @param[in] temps : double
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::moveY(double temps)
{
	rondelle_ = dynamic_cast <NoeudRondelle*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("rondelle"));
	glm::dvec3 positionDepY;
	glm::dvec3 position(0.0);

	double random = (float)(rand() % 50 + 1) / 10.0f; // valeur aléatoire entre 0.01 et 0.5
	if (rondelle_->obtenirPositionRelative()[1] > table_->obtenirSommets()[1].x /*&& obtenirPositionRelative()[1]*/) {
		positionDepY = rondelle_->obtenirPositionRelative();
		position[0] = obtenirPositionRelative()[0];
		position[1] = positionDepY[1]+ 4;
		if (estDansLaTable())
		assignerPositionRelative(position);
	}
	else if (rondelle_->obtenirPositionRelative()[1] < table_->obtenirSommets()[1].x /*&& obtenirPositionRelative()[1]>table_->obtenirSommets()[2].y*/) {
		positionDepY = rondelle_->obtenirPositionRelative();
		position[0] = obtenirPositionRelative()[0];
		position[1] = positionDepY[1] - 5;
		if (estDansLaTable())
		assignerPositionRelative(position);
	}
	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletVirtuel::moveX(double temps)
///
/// Cette fonction effectue le simultanement le mode offensif et defensif de la 
///rondelle sur l'axe des x
///
/// @param[in] temps : le temps d'animation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::moveX(double temps)
{
	rondelle_ = dynamic_cast <NoeudRondelle*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("rondelle"));
	glm::dvec3 positionDepX;
	glm::dvec3 position(0.0);
	double random = (float)(rand() % 50 + 1) / 100.0f; // valeur aléatoire entre 0.01 et 0.5
	//cout << random << endl;

	if (rondelle_->obtenirPositionRelative()[0] > table_->obtenirSommets()[3].x && obtenirPositionRelative()[0] > table_->obtenirSommets()[3].x && obtenirPositionRelative()[0]>rondelle_->obtenirPositionRelative()[0])
	{
		
		positionDepX = rondelle_->obtenirPositionRelative();

		position[0] = obtenirPositionRelative()[0];
		//cout << random << endl;
		position[0] -= random;
		//cout <<"okido" << endl;
		position[1] = obtenirPositionRelative()[1];
		if (estDansLaTable())
		assignerPositionRelative(position);

	}
	else if(rondelle_->obtenirPositionRelative()[0] < table_->obtenirSommets()[3].x && obtenirPositionRelative()[0]<table_->obtenirSommets()[2].x -5 && obtenirPositionRelative()[0]<rondelle_->obtenirPositionRelative()[0])
	{
		positionDepX = rondelle_->obtenirPositionRelative();

		position[0] = obtenirPositionRelative()[0];
		position[0] += random*temps;
		//cout << "okida" << endl;
		position[1] = obtenirPositionRelative()[1]- random;
		if (estDansLaTable())
		assignerPositionRelative(position);
	}
	else if (obtenirPositionRelative()[0] < rondelle_->obtenirPositionRelative()[0])
	{
		positionDepX = rondelle_->obtenirPositionRelative();
		

		position[0] = obtenirPositionRelative()[0];
		position[0] += 0.5;
		position[1] = obtenirPositionRelative()[1]-3;
		if (estDansLaTable())
		assignerPositionRelative(position);
	}
	else if (rondelle_->obtenirPositionRelative()[0] < table_->obtenirSommets()[3].x && obtenirPositionRelative()[0]<table_->obtenirSommets()[2].x-5)
	{
		position[0] = obtenirPositionRelative()[0];
		position[0] += 0.5 ;
		position[1] = obtenirPositionRelative()[1];
		if (estDansLaTable())
			assignerPositionRelative(position);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletVirtuel::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);
	table_ = dynamic_cast<NoeudTable*>(obtenirParent());
	rondelle_ = dynamic_cast <NoeudRondelle*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("rondelle"));
	if (FacadeModele::obtenirInstance()->adversaireEstVirtuel())
	{
		moveY(temps);
		moveX(temps);
	}
	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMailletVirtuel::attribuerCouleur(
///
/// Cette fonction attribut une couleur.
///
/// @param[in] Aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::attribuerCouleur()
{
	if (NoeudAbstrait::compteurMailletV_ < 180)
	{
		couleurMailletVirtuel_[0] = NoeudMailletVirtuel::compteurGreen_;
		couleurMailletVirtuel_[1] = 170 - NoeudAbstrait::compteurMailletV_ + 1;
		couleurMailletVirtuel_[2] = 255;
		//std::cout << "couleur attribuée: " << (int)couleurPortail_[0] << ";" << (int)couleurPortail_[1] << ";" << (int)couleurPortail_[2] << std::endl;

	}
	else
	{
		NoeudAbstrait::compteurMailletV_ = 1;
		NoeudMailletVirtuel::compteurGreen_++;
		couleurMailletVirtuel_[0] = NoeudMailletVirtuel::compteurGreen_;
		couleurMailletVirtuel_[1] = 0;
		couleurMailletVirtuel_[2] = 155;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudMailletVirtuel::verifierSelection(GLubyte couleurObjet[])
///
/// Cette fonction verifie si le noeud est selectionne.
///
/// @param[in] couleurObjet : Le code RGB de l'objet
///
/// @return Faux si le noeud n'est pas selectione et vice-versa.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMailletVirtuel::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;
	//cout << "couleur objet selection: " << (int)couleurSelection_[2] << endl;
	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;
	}
	else if (couleurObjet[0] == couleurMailletVirtuel_[0] && couleurObjet[1] == couleurMailletVirtuel_[1] && couleurObjet[2] == couleurMailletVirtuel_[2])
	{
		estPointe = true;
		if (couleurSelection_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			attribuerCouleurSelection();
		}
	}
	return estPointe;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletVirtuel::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Accepte le visiteur.
///
/// @param[in] visiteur : le type visiteur
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::accepterVisiteur(VisiteurAbstrait* visiteur) {
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMaillet::modifierRayonMaillet(double rayonMaillet)
///
/// Modifie le rayon du maillet
///
/// @param[in] rayonMaillet : le rayon du maillet
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::modifierRayonMaillet(double rayonMaillet)
{
	rayonMailletV_ = rayonMaillet;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudMailletVirtuel::obtenirRayonMaillet()
///
/// Obtenir le rayon du Maillet Virtuel
///
/// @return le rayon du Maillet Virtuel
///
////////////////////////////////////////////////////////////////////////
double NoeudMailletVirtuel::obtenirRayonMailletV()
{
	return rayonMailletV_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudMailletVirtuel::assignerProbabiliteDeJeu(double p)
///
/// assigne une  probabilité de jeu au Maillet Virtuel
///
/// @param[in] proba : double
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::assignerProbabiliteDeJeu(double proba)
{
	if (proba > 1)
		proba /= 100;
	if (proba < 0)
		proba = -proba;
	probabilite_ = proba;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudMailletVirtuel::assignerRondelle(NoeudRondelle * rondelle)
///
/// assigne la rondelle au Maillet Virtuel
///
/// @param[in] rondelle : NoeudRondelle *
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::assignerRondelle(NoeudRondelle * rondelle)
{
	rondelle_ = rondelle;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudMailletVirtuel::assignerVitesse(double vitesse)
///
/// assigne une vitesse au Maillet Virtuel
///
/// @param[in] vitesse : double
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////

void NoeudMailletVirtuel::assignerVitesse(double vitesse)
{
	if (vitesse > VITESSE_MAX) // vitesse maximale du joueur virtuel
		vitesse = VITESSE_MAX;
	if (vitesse < 0)
		vitesse = -vitesse;
	vitesseDeFrappe_[0] = vitesseDeFrappe_[1]= vitesse_ = vitesse ;
}
double NoeudMailletVirtuel::obtenirVitesse()
{
	return vitesse_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudMailletVirtuel::assignerLargeurButs(int largeurButs)
///
/// assigne une largeur de but au Maillet Virtuel
///
/// @param[in] largeurButs : int
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::assignerLargeurButs(int largeurButs)
{
	largeurBut_ = largeurButs;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletVirtuel::assignerObjetRendu
///     (modele::Modele3D const * modele, opengl::VBO const * liste)
///
/// assigne l'objet rendu au Maillet Virtuel
///
/// @param[in] modele : Modele3D
///				liste : VBO
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	rayonMailletV_ = utilitaire::calculerSphereEnglobante(*modele_).rayon;
	redefinirSommets();
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMailletVirtuel::redefinirSommets()
///
/// redefini les sommets
///
/// @param[in] aucun
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void NoeudMailletVirtuel::redefinirSommets()
{
	rayonMailletV_ *= facteurEchelle_;
	sommets_.erase(sommets_.begin(), sommets_.end());
	sommets_.push_back(glm::dvec3(rayonMailletV_ + obtenirPositionRelative().x, rayonMailletV_ + obtenirPositionRelative().y, obtenirPositionRelative().z));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudMailletVirtuel::estDansLaTable()
///
/// verifie si le noeud est dans la table
///
/// @param[in] aucun
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
bool NoeudMailletVirtuel::estDansLaTable()
{
	if (estModifier_) {
		redefinirSommets();
	}
	std::vector<glm::dvec3> sommetsTable = this->obtenirParent()->obtenirSommets();
	return utilitaire::pointsDansPolygone2D(obtenirSommets(), sommetsTable);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
