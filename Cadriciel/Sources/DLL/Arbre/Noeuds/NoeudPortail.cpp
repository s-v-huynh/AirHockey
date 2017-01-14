///////////////////////////////////////////////////////////////////////////
/// @file NoeudMaillet.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudPortail.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "FacadeModele.h"
#include "glm/glm.hpp"


const float PROPORTION_ATTRACTION = 5.0;
const float  VITESSE_ROTATION_MINIMAL = 10.6f;
const float VITESSE_ROTATION_MAXIMAL = 25.0f;
int NoeudPortail::nbInstances_ = 0;
int NoeudPortail::compteurRed_ = 0;
int NoeudAbstrait::compteurPortail_ = 0;


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
NoeudPortail::NoeudPortail(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	NoeudAbstrait::compteurPortail_++;
	couleurPortail_[0] = 0;
	couleurPortail_[1] = 0;
	couleurPortail_[2] = 255;
	couleurSelection_[1] = 0;
	attribuerCouleur();
	vitesseRotation_ = VITESSE_ROTATION_MINIMAL;
	estLier_ = false;
	portailFrere_ = NULL;
	attraction_ = true;
	nbInstances_++;
	rayonPortail_ = 1.0;
	rayonAttraction_ = 1.0;
	afficherRayonAttraction_ = true;
	assignerEstSelectionnable(true); //un portail est toujour selectionnable
	cercle_ = nullptr;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::~NoeudTable()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPortail::~NoeudPortail()
{
	nbInstances_--;
}

void NoeudPortail::copierAttributs(NoeudPortail& destination)
{
    destination.rayonPortail_ = rayonPortail_;
	destination.rayonAttraction_ = rayonAttraction_;
    destination.angleRotation_ = angleRotation_;
    destination.facteurEchelle_ = facteurEchelle_;
	destination.vitesseRotation_ = vitesseRotation_;
	destination.estLier_ = false;
	destination.portailFrere_ = nullptr;
	//On incremente le nombre d'instance a chaque copie
	nbInstances_++;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le mod�le � sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
//void NoeudPortail::afficherConcret(const glm::mat4& vueProjection) const
void NoeudPortail::afficherConcret(const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{

	glPushName(id_);
	glPushMatrix();

	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurPortail_[0];
	couleurObjet[1] = couleurPortail_[1];
	couleurObjet[2] = couleurPortail_[2];
	GLubyte couleurSelection[3];
	couleurSelection[0] = couleurSelection_[0];
	couleurSelection[1] = couleurSelection_[1];
	couleurSelection[2] = couleurSelection_[2];
	//Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(vueProjection, attribuerCouleur);
	//R�volution autour du centre.
	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(sqrtf(2), sqrtf(2), 0));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::scale(modele, glm::vec3(rayonPortail_, rayonPortail_, rayonPortail_));
	vbo_->dessiner(estSelectionne(), attribuerCouleur, couleurObjet, couleurSelection, vueProjection*modele);
	glPopMatrix();
	glPopName();
	glEnable(GL_DEPTH_TEST);
	
}


void NoeudPortail::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

void NoeudPortail::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	rayonPortail_ = utilitaire::calculerSphereEnglobante(*modele_).rayon/6;
	rayonAttraction_ = rayonPortail_*PROPORTION_ATTRACTION;
}

void NoeudPortail::afficherRayonAttraction(bool afficher)
{
	afficherRayonAttraction_ = afficher;
}

void NoeudPortail::assignerCercle(NoeudCercle * noeud)
{
	cercle_ = noeud;
}

void NoeudPortail::modifierRayon(float rayonPortail)
{
	rayonPortail_ = rayonPortail;
}

void NoeudPortail::modifierVitesseRotation(float vitesse)
{
	vitesseRotation_ += vitesse;

	if (vitesseRotation_ > VITESSE_ROTATION_MAXIMAL)
		vitesseRotation_ = VITESSE_ROTATION_MAXIMAL;

}


float NoeudPortail::obtenirRayon()
{
	return rayonPortail_;
}

void NoeudPortail::redefinirSommets()
{
	sommets_.erase(sommets_.begin(), sommets_.end());
	rayonAttraction_ = PROPORTION_ATTRACTION*rayonPortail_;
	sommets_.push_back(glm::dvec3(rayonPortail_ + obtenirPositionRelative().x, rayonPortail_ + obtenirPositionRelative().y, obtenirPositionRelative().z));
	/*utilitaire::BoiteEnglobante modelePortail = utilitaire::calculerBoiteEnglobante(*modele_);
	sommets_.push_back(glm::dvec3(modelePortail.coinMin.x, modelePortail.coinMax.y, modelePortail.coinMin.z));
	sommets_.push_back(glm::dvec3(modelePortail.coinMax.x, modelePortail.coinMax.y, modelePortail.coinMin.z));
	sommets_.push_back(glm::dvec3(modelePortail.coinMax.x, modelePortail.coinMin.y, modelePortail.coinMin.z));
	sommets_.push_back(glm::dvec3(modelePortail.coinMin.x, modelePortail.coinMin.y, modelePortail.coinMin.z));*/
	cercle_->assignerPositionRelative(obtenirPositionRelative());
	cercle_->modifierRayon(rayonAttraction_);
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


void NoeudPortail::animer(float temps)
{
	// Appel � la version de la classe de base pour l'animation des enfants.
	angleRotation_ = fmod(angleRotation_ + vitesseRotation_, 360.0f);
	//angleRotation_ = fmod(angleRotation_ + temps/4.0f * 360.0f, 360.0f);
	if (estModifier_) {
		redefinirSommets();
		estModifier_ = false;
	}
	NoeudComposite::animer(temps);

}
void NoeudPortail::redessiner()
{
	NoeudComposite::redessiner();
}
//bool NoeudPortail::clickToucheNoeud(glm::dvec3 point)
//{
//	utilitaire::SphereEnglobante sphere = utilitaire::calculerSphereEnglobante(*modele_);
//	return (sqrt(pow(point.x - obtenirPositionRelative().x, 2) + pow(point.y - obtenirPositionRelative().y, 2))
//		<= (sphere.rayon - 3.2));
//}
void NoeudPortail::attribuerCouleur()
{
	if (NoeudAbstrait::compteurPortail_ < 180)
	{
		couleurPortail_[0] = NoeudPortail::compteurRed_;
		couleurPortail_[1] = 0;
		couleurPortail_[2] = 255 - NoeudAbstrait::compteurPortail_ + 1;
		//std::cout << "couleur attribu�e: " << (int)couleurPortail_[0] << ";" << (int)couleurPortail_[1] << ";" << (int)couleurPortail_[2] << std::endl;

	}
	else
	{
		NoeudAbstrait::compteurPortail_ = 1;
		NoeudPortail::compteurRed_++;
		couleurPortail_[0] = NoeudPortail::compteurRed_;
		couleurPortail_[1] = 0;
		couleurPortail_[2] = 255;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::verifierSelection(GLubyte couleurObjet[])
///
/// Cette fonction permet de v�rifier si le noeud est selectionn� 
///
/// @param[in] couleurObjet[] : Couleurs RGB du pixel.
///
/// @return bool�an: true si le noeud est s�lectionn� ou false sinon.
///
////////////////////////////////////////////////////////////////////////
bool NoeudPortail::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;
	//cout << "couleur objet selection: " << (int)couleurSelection_[2] << endl;

	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;

	}
	else if (couleurObjet[0] == couleurPortail_[0] && couleurObjet[1] == couleurPortail_[1] && couleurObjet[2] == couleurPortail_[2])
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

void NoeudPortail::setFrere(NoeudPortail* noeud) {
	portailFrere_ = noeud;
}

bool NoeudPortail::estDansLaTable()
{
	if (estModifier_) {
		redefinirSommets();
	}
	std::vector<glm::dvec3> sommetsTable = this->obtenirParent()->obtenirSommets();
	return utilitaire::pointsDansPolygone2D(obtenirSommets(), sommetsTable);
}

NoeudPortail* NoeudPortail::getFrere() {
	return portailFrere_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPortail::obtenirRayonAttraction()
///
/// Cette fonction permet d'obtenir le rayon d'attraction.
///
///
/// @return double.
///
////////////////////////////////////////////////////////////////////////
//double NoeudPortail::obtenirRayonAttraction()
//{
//
//}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////