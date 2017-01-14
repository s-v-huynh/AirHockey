///////////////////////////////////////////////////////////////////////////
/// @file NoeudRondelle.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudRondelle.h"
#include "Utilitaire.h"
#include "AideCollision.h"
#include "FacadeModele.h"


#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
const double  VITESSE_DEPLACEMENT_MINIMAL = 0.0;
const double VITESSE_DEPLACEMENT_MAXIMAL = 3.0;

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	
	rayonRondelle_ = 1.0;
	couleurRondelle_[0] = 255;
	couleurRondelle_[1] = 0;
	couleurRondelle_[2] = 255;
	//nbInstances_++;
	vitesseRondelle_ = { 0.0, 0.0 };
	angleDeplacement_ = 0;
	//dx_ = vitesseRondelle_.x *static_cast<float>(cos(utilitaire::DEG_TO_RAD(angleDeplacement_)));
	//dy_ = vitesseRondelle_.y *static_cast<float>(sin(utilitaire::DEG_TO_RAD(angleDeplacement_)));
	//dx_ = 1.0;
	//dy_ = 1.0;
	vitesseMax_ = VITESSE_DEPLACEMENT_MAXIMAL;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::NoeudRondelle(const NoeudRondelle &)
///
/// Ce constructeur par copie
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur par copie).
///
////////////////////////////////////////////////////////////////////////
NoeudRondelle::NoeudRondelle(const NoeudRondelle &)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::copierAttributs(NoeudRondelle& destination)
///
/// Cette fonction permet de copier les attributs d'un noeud
///
/// @param[in] destination : Le type du noeud.
///
/// @return Aucune 
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::copierAttributs(NoeudRondelle& destination)
{
    destination.angleRotation_ = angleRotation_;
    destination.facteurEchelle_ = facteurEchelle_;
    destination.rayonRondelle_ = rayonRondelle_;
    destination.coefRebondissement_ = coefRebondissement_;
	destination.vitesseRondelle_.x = VITESSE_DEPLACEMENT_MINIMAL;
	destination.vitesseRondelle_.y = VITESSE_DEPLACEMENT_MINIMAL;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::~NoeudRondelle()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
NoeudRondelle::~NoeudRondelle()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::afficherConcret(const
/// glm::mat4& vueProjection, const bool& attribuerCouleur)const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le mod�le � sa position voulue.
///				attribuerCouleur : attribuer une couleur au noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	glPushName(id_);
	glPushMatrix();
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(matrVue, matrProjection, vueProjection, attribuerCouleur);
	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurRondelle_[0];
	couleurObjet[1] = couleurRondelle_[1];
	couleurObjet[2] = couleurRondelle_[2];
	GLubyte couleurSelection[3];
	couleurSelection[0] = couleurSelection_[0];
	couleurSelection[1] = couleurSelection_[1];
	couleurSelection[2] = couleurSelection_[2];
	// R�volution autour du centre.
	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(1.0, 0.0, .0));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::scale(transformationRelative_, glm::vec3(rayonRondelle_, rayonRondelle_, rayonRondelle_));
	// Affichage du mod�le.
	if (!FacadeModele::obtenirInstance()->modeEdition())
	vbo_->dessiner(estSelectionne(), attribuerCouleur, couleurObjet, couleurSelection, modele, matrVue, matrProjection, vueProjection*modele);
	glPopMatrix();
	glPopName();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::animer(float temps)
{
	if (!FacadeModele::obtenirInstance()->modeEdition()) {
		table_ = dynamic_cast<NoeudTable*>(obtenirParent());
		if (estModifier_) {
			redefinirSommets();
			estModifier_ = false;
		}
		glm::dvec3 position(0.0f);
		if (vitesseRondelle_.x > VITESSE_DEPLACEMENT_MAXIMAL)
			vitesseRondelle_.x = VITESSE_DEPLACEMENT_MAXIMAL;
		if (vitesseRondelle_.x < -VITESSE_DEPLACEMENT_MAXIMAL)
			vitesseRondelle_.x = -VITESSE_DEPLACEMENT_MAXIMAL;
		if (vitesseRondelle_.y > VITESSE_DEPLACEMENT_MAXIMAL)
			vitesseRondelle_.y = VITESSE_DEPLACEMENT_MAXIMAL;
		if (vitesseRondelle_.y < -VITESSE_DEPLACEMENT_MAXIMAL)
			vitesseRondelle_.y = -VITESSE_DEPLACEMENT_MAXIMAL;

		vitesseRondelle_.x *= table_->obtenirFriction();
		vitesseRondelle_.y *= table_->obtenirFriction();
		//std::cout << "vx: " << vitesseRondelle_.x  << " vy: " << vitesseRondelle_.y << std::endl;
		//Depplacer la rodelle

		position[0] = obtenirPositionRelative().x + vitesseRondelle_.x;

		position[1] = obtenirPositionRelative().y + vitesseRondelle_.y;
		if (estDansLaTable())
			assignerPositionRelative(position);
		if (!FacadeModele::obtenirInstance()->modeEdition())
			table_->chercherCollisions();
	}
	
	// Appel � la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::redessiner()
///
/// Cette fonction permet de redessiner
///
/// @param[in] aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::redessiner()
{
	/*table_ = dynamic_cast<NoeudTable*>(obtenirParent());
	glm::dvec3 position(0.0f);
	if (vitesseRondelle_.x > VITESSE_DEPLACEMENT_MAXIMAL)
		vitesseRondelle_.x = VITESSE_DEPLACEMENT_MAXIMAL;
	if(vitesseRondelle_.x < -VITESSE_DEPLACEMENT_MAXIMAL)
		vitesseRondelle_.x = -VITESSE_DEPLACEMENT_MAXIMAL;
	if (vitesseRondelle_.y > VITESSE_DEPLACEMENT_MAXIMAL)
		vitesseRondelle_.y = VITESSE_DEPLACEMENT_MAXIMAL;
	if (vitesseRondelle_.y < -VITESSE_DEPLACEMENT_MAXIMAL)
		vitesseRondelle_.y = -VITESSE_DEPLACEMENT_MAXIMAL;
	table_->chercherCollisions();
	vitesseRondelle_.x *= table_->obtenirFriction();
	vitesseRondelle_.y *= table_->obtenirFriction();

	position[0] = obtenirPositionRelative().x + vitesseRondelle_.x;

	position[1] = obtenirPositionRelative().y + vitesseRondelle_.y;
	table_->chercherCollisions();
	assignerPositionRelative(position);*/

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::modifierRayonRondelle(double rayonRondelle)
///
/// Cette fonction permet de modifier le rayon de la rondelle
///
/// @param[in] rayonPortail : le rayon de la rondelle
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::modifierRayonRondelle(double rayonRondelle)
{
	rayonRondelle_ = rayonRondelle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::redefinirSommets()
///
/// Cette fonction permet de redefinir les sommets du noeud
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::redefinirSommets()
{
	sommets_.erase(sommets_.begin(), sommets_.end());
	//sommets_.push_back(glm::dvec3(rayonRondelle_ + positionRelative_.x, rayonRondelle_ + positionRelative_.y, positionRelative_.z));
	utilitaire::BoiteEnglobante modeleRondelle = utilitaire::calculerBoiteEnglobante(*modele_);
	sommets_.push_back(glm::dvec3(modeleRondelle.coinMin.x, modeleRondelle.coinMax.y, modeleRondelle.coinMin.z));
	sommets_.push_back(glm::dvec3(modeleRondelle.coinMax.x, modeleRondelle.coinMax.y, modeleRondelle.coinMin.z));
	sommets_.push_back(glm::dvec3(modeleRondelle.coinMax.x, modeleRondelle.coinMin.y, modeleRondelle.coinMin.z));
	sommets_.push_back(glm::dvec3(modeleRondelle.coinMin.x, modeleRondelle.coinMin.y, modeleRondelle.coinMin.z));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudRondelle::estDansLaTable()
///
/// Cette fonction verifier si le noeud est dans la table
///
/// @param[in] Aucun
///
/// @return bool
///
////////////////////////////////////////////////////////////////////////
bool NoeudRondelle::estDansLaTable()
{
	if (estModifier_)
		redefinirSommets();
	std::vector<glm::dvec3> sommetsTable = this->obtenirParent()->obtenirSommets();
	return (utilitaire::pointsDansPolygone2D(sommets_, sommetsTable));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudRondelle::obtenirRayonRondelle()
///
/// Cette fonction permet d'obtenir le rayon de la rondelle.
///
/// @param[in] Aucun
///
/// @return Le rayon d'attraction (double)
///
////////////////////////////////////////////////////////////////////////
double NoeudRondelle::obtenirRayonRondelle()
{
	return rayonRondelle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::modifierVitesse(glm::dvec2 vitesse)
///
/// Cette fonction permet de modifier la vitesse de la rondelle.
///
///
/// @param[in] vitesse : dvec2

/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::modifierVitesse(glm::dvec2 vitesse)
{
	vitesseRondelle_ = vitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn glm::dvec2 NoeudRondelle::obtenirVitesse()
///
/// Cette fonction permet d'obtenir la vitesse de la rondelle.
///
///
/// @param[in] vitesse : dvec2

/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
glm::dvec2 NoeudRondelle::obtenirVitesse()
{
	return vitesseRondelle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
///
/// Cette fonction d'assigner l'objet rendu
///
///
/// @param[in] modele : Modele3D
///				liste : VBO
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	sphere_ = utilitaire::calculerSphereEnglobante(*modele_);
	rayonRondelle_ = sphere_.rayon*2;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::accepterVisiteur
///										(VisiteurAbstrait * visiteur)
///
/// Accepte le visiteur.
///
/// @param[in] visiteur : le type visiteur
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRondelle::accepterVisiteur(VisiteurAbstrait * visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
