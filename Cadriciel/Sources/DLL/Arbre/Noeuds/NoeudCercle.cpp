///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudCercle.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include "FacadeModele.h"
#include "Modele3D.h"
#include "OpenGL_VBO.h"
//nbInstances_ = 0;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCercle::NoeudCercle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCercle::NoeudCercle(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	nbInstances_++;
	rayon_ = 1.0;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCercle::~NoeudCercle()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCercle::~NoeudCercle()
{
}

void NoeudCercle::copierAttributs(NoeudCercle& destination)
{
	destination.rayon_ = rayon_;
	destination.angleRotation_ = angleRotation_;
	destination.facteurEchelle_ = facteurEchelle_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCercle::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le mod�le � sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCercle::afficherConcret(const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	glPushName(id_);
	glPushMatrix();
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(vueProjection, attribuerCouleur);

	// R�volution autour du centre.
	//glScaled(5.0, 5.0, 1.0);
	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(0, 1, 0));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::scale(modele, glm::vec3(3, 3, 1.0));
	GLubyte couleurObjet[3]= { 215,123,52 };;
	GLubyte couleurSelection[3] = {215,123,52};

	// Affichage du mod�le.
	if (FacadeModele::obtenirInstance()->obtenirPeutAfficherAttractionPortail())
		vbo_->dessiner(true, attribuerCouleur, couleurObjet, couleurSelection, vueProjection*modele);
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
void NoeudCercle::animer(float temps)
{
	// Appel � la version de la classe de base pour l'animation des enfants.

	if (estModifier_) {
		redefinirSommets();
		estModifier_ = false;
	}
	NoeudComposite::animer(temps);
}

bool NoeudCercle::estDansLaTable()
{
	if (estModifier_) {
		redefinirSommets();
	}
	std::vector<glm::dvec3> sommetsTable = this->obtenirParent()->obtenirSommets();
	return utilitaire::pointsDansPolygone2D(obtenirSommets(), sommetsTable);
}
void NoeudCercle::redefinirSommets()
{
	sommets_.erase(sommets_.begin(), sommets_.end());
	sommets_.push_back(glm::dvec3(rayon_ + obtenirPositionRelative().x, rayon_ + obtenirPositionRelative().y, obtenirPositionRelative().z));
}
void NoeudCercle::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	rayon_ = utilitaire::calculerSphereEnglobante(*modele_).rayon;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCercle::accepterVisiteur
///									(VisiteurAbstrait* visiteur)
///
/// Accepte le visiteur.
///
/// @param[in] visiteur : le type visiteur
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudCercle::accepterVisiteur(VisiteurAbstrait* visiteur) {
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
