///////////////////////////////////////////////////////////////////////////
/// @file NoeudMaillet.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudMuret.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "../Arbre/Texture.h"
#include "../Utilitaire/Utilitaire.h"

#define INITIAL 0
#define FINAL 1
#define BAS_INITIAL_1 0
#define BAS_INITIAL_2 1
#define HAUT_INITIAL_1 2
#define HAUT_INITIAL_2 3
#define BAS_FINAL_1 4
#define BAS_FINAL_2 5
#define HAUT_FINAL_1 6
#define HAUT_FINAL_2 7
#define NORMALE_COURT_INITIAL 0
#define NORMALE_COURT_FINAL 1
#define NORMALE_LONG_1 2
#define NORMALE_LONG_2 3
int NoeudAbstrait::compteurMuret_ = 0;
int NoeudMuret::compteurBleu_ = 0;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////

NoeudMuret::NoeudMuret(const std::string& typeNoeud/*, double x, double y*/)
	: NoeudComposite{ typeNoeud }, hauteurMuret_(5.0), epaisseurMuret_(-0.6)
{
	compteurMuret_++;
	couleurMuret_[0] = 0;
	couleurMuret_[1] = 0;
	couleurMuret_[2] = 255;
	couleurSelection_[1] = 0;
	longueurMuret_ = 5.0;
	attribuerCouleur();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::~NoeudTable()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMuret::~NoeudMuret()
{
}

void NoeudMuret::copierAttributs(NoeudMuret& destination)
{
	destination.hauteurMuret_ = hauteurMuret_;
	destination.epaisseurMuret_ = epaisseurMuret_;
	destination.longueurMuret_ = longueurMuret_;
	destination.angleRotation_ = angleRotation_;
	destination.facteurEchelle_ = facteurEchelle_;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMuret::afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	glPushName(id_);
	glPushMatrix();
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(matrVue, matrProjection, vueProjection, attribuerCouleur);

	// Révolution autour du centre.
	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurMuret_[0];
	couleurObjet[1] = couleurMuret_[1];
	couleurObjet[2] = couleurMuret_[2];
	GLubyte couleurSelection[3];
	couleurSelection[0] = couleurSelection_[0];
	couleurSelection[1] = couleurSelection_[1];
	couleurSelection[2] = couleurSelection_[2];

	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(sqrtf(2), sqrtf(2), 0));
	//modele = glm::translate(modele, scale_);
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0, 0, 1.0));
	//modele = glm::translate(modele, scale_);
	modele = glm::scale(modele, glm::vec3(2, longueurMuret_, 1));
	// Affichage du modèle.
	vbo_->dessiner(estSelectionne(), attribuerCouleur, couleurObjet, couleurSelection, modele, matrVue, matrProjection, vueProjection*modele);
	glPopMatrix();
	glPopName();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMuret::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);
	if (estModifier_) {
		redefinirSommets();
		estModifier_ = false;
	}
}

void NoeudMuret::attribuerCouleur()
{
	if (NoeudAbstrait::compteurPortail_ < 180)
	{
		couleurMuret_[0] = 255 - NoeudMuret::compteurMuret_ + 1;
		couleurMuret_[1] = 60;
		couleurMuret_[2] = 255 - NoeudMuret::compteurBleu_;
		//std::cout << "couleur attribuée: " << (int)couleurMuret_[0] << ";" << (int)couleurMuret_[1] << ";" << (int)couleurMuret_[2] << std::endl;

	}
	else
	{
		NoeudAbstrait::compteurMuret_ = 1;
		NoeudMuret::compteurBleu_++;
		couleurMuret_[0] = 255;
		couleurMuret_[1] = 0;
		couleurMuret_[2] = NoeudMuret::compteurBleu_;
	}
}
bool NoeudMuret::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;
	//std::cout << " couleur Objet: " << (int)couleurObjet[0] << ";" << (int)couleurObjet[1] << ";" << (int)couleurObjet[2] << std::endl;

	//std::cout << "couleur Selection_: " << (int)couleurSelection_[0] << ";" << (int)couleurSelection_[1] << ";" << (int)couleurSelection_[2] << std::endl;
	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;
	}
	else if (couleurObjet[0] == couleurMuret_[0] && couleurObjet[1] == couleurMuret_[1] && couleurObjet[2] == couleurMuret_[2])
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
void NoeudMuret::accepterVisiteur(VisiteurAbstrait* visiteur) {
	visiteur->visiter(this);
}

void NoeudMuret::modifierLongueurMuret(double longueurMuret)
{
	longueurMuret_ = longueurMuret;
}

void NoeudMuret::redefinirSommets()
{
	sommets_.erase(sommets_.begin(), sommets_.end());
	sommets_.push_back(obtenirPositionRelative());
	/*if(obtenirPositionRelative()[1] > 0)
		sommets_.push_back(glm::dvec3(obtenirPositionRelative()[0]*sin(angleRotation_), obtenirPositionRelative()[1] * obtenirLongueurMuret()*cos(angleRotation_), obtenirPositionRelative()[2]));
	else if(obtenirPositionRelative()[1] < 0)
		sommets_.push_back(glm::dvec3(obtenirPositionRelative()[0]* sin(angleRotation_), -obtenirPositionRelative()[1] * obtenirLongueurMuret()*cos(angleRotation_), obtenirPositionRelative()[2]));
	else
		sommets_.push_back(glm::dvec3(obtenirPositionRelative()[0]*sin(angleRotation_), obtenirLongueurMuret()*sin(angleRotation_), obtenirPositionRelative()[2]));*/
	if(obtenirPositionRelative()[1] > 0)
		sommets_.push_back(glm::dvec3(obtenirPositionRelative()[0], obtenirPositionRelative()[1] * obtenirLongueurMuret(), obtenirPositionRelative()[2]));
		else if(obtenirPositionRelative()[1] < 0)
		sommets_.push_back(glm::dvec3(obtenirPositionRelative()[0], -obtenirPositionRelative()[1] * obtenirLongueurMuret(), obtenirPositionRelative()[2]));
		else
	sommets_.push_back(glm::dvec3(obtenirPositionRelative()[0], obtenirLongueurMuret(), obtenirPositionRelative()[2]));
}

bool NoeudMuret::estDansLaTable()
{
	if (estModifier_)
		redefinirSommets();
	std::vector<glm::dvec3> sommetsTable = this->obtenirParent()->obtenirSommets();
	return (utilitaire::pointsDansPolygone2D(sommets_, sommetsTable));
}

double NoeudMuret::obtenirLongueurMuret()
{
	return longueurMuret_;
}


////////////////////////////////////////////////////////////////////////
