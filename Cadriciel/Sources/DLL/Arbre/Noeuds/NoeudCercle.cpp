///////////////////////////////////////////////////////////////////////////
/// @file NoeudCercle.cpp
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
/// et donner des valeurs par défaut aux variables membres.
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
	rayon_ = rayonPortail_/2;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCercle::~NoeudCercle()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCercle::~NoeudCercle()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCercle::copierAttributs(NoeudCercle& destination)
///
/// La fonction copie les attributs d'un autre noeud
///
/// @param[in] destination : NoeudCercle
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudCercle::copierAttributs(NoeudCercle& destination)
{
	destination.rayon_ = rayon_;
	destination.angleRotation_ = angleRotation_;
	destination.facteurEchelle_ = facteurEchelle_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCercle::afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///				attribuerCouleur : bool
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCercle::afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	glPushName(id_);
	glPushMatrix();
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(matrVue, matrProjection, vueProjection, attribuerCouleur);

	// Révolution autour du centre.
	//glScaled(5.0, 5.0, 1.0);
	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(0, 1, 0));
	modele = glm::translate(modele, glm::vec3(0, 0, 0));
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::scale(modele, glm::vec3(rayon_*0.5, rayon_*0.5, 0.0));
	GLubyte couleurObjet[3]= { 215,123,52 };
	GLubyte couleurSelection[3] = {215,123,52};

	// Affichage du modèle.
	if (FacadeModele::obtenirInstance()->obtenirPeutAfficherAttractionPortail())
		vbo_->dessiner(true, attribuerCouleur, couleurObjet, couleurSelection, modele, matrVue, matrProjection, vueProjection*modele);
	glPopMatrix();
	glPopName();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCercle::animer(float temps)
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
	// Appel à la version de la classe de base pour l'animation des enfants.

	if (estModifier_) {
		redefinirSommets();
		estModifier_ = false;
	}
	NoeudComposite::animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudCercle::estDansLaTable()
///
/// Cette fonction verifie si le noeud est dans la table.
///
/// @param[in] Aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool NoeudCercle::estDansLaTable()
{
	if (estModifier_) {
		redefinirSommets();
	}
	std::vector<glm::dvec3> sommetsTable = this->obtenirParent()->obtenirSommets();
	return utilitaire::pointsDansPolygone2D(obtenirSommets(), sommetsTable);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCercle::redefinirSommets()
///
/// Cette fonction redefinit les sommets
///
/// @param[in] Aucun
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCercle::redefinirSommets()
{
	sommets_.erase(sommets_.begin(), sommets_.end());
	sommets_.push_back(glm::dvec3(rayon_ + obtenirPositionRelative().x, rayon_ + obtenirPositionRelative().y, obtenirPositionRelative().z));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCercle::assignerObjetRendu
///      (modele::Modele3D const * modele, opengl::VBO const * liste)
///
/// Cette fonction assigne le rendu de l'objet
///
/// @param[in] modele : Modele3D, liste : VBO
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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
