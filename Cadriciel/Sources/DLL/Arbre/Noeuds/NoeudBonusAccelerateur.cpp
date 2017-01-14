///////////////////////////////////////////////////////////////////////////
/// @file NoeudBonusAccelerateur.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudBonusAccelerateur.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
int NoeudBonusAccelerateur::compteurYellow_ = 0;
int NoeudAbstrait::compteurBonus_ = 0;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonusAccelerateur::NoeudBonusAccelerateur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonusAccelerateur::NoeudBonusAccelerateur(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	NoeudAbstrait::compteurBonus_++;

	couleurBonus_[0] = 255;
	couleurBonus_[1] = 0;
	couleurBonus_[2] = 0;
	couleurSelection_[1] = 0;
	rayonBonusAccelerateur_ = 1.0;

	//std::cout << "couleur attribue : (" << (int)couleurBonus_[0] << ", " << (int)couleurBonus_[1] << ", " << (int)couleurBonus_[2] << ")" << std::endl;

	attribuerCouleur();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBonusAccelerateur::~NoeudBonusAccelerateur()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBonusAccelerateur::~NoeudBonusAccelerateur()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::copierAttributs(NoeudBonusAccelerateur& destination)
///
/// La fonction copie les attributs d'un autre noeud
///
/// @param[in] destination : NoeudBonusAccelerateur
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::copierAttributs(NoeudBonusAccelerateur& destination)
{
    destination.rayonBonusAccelerateur_ = rayonBonusAccelerateur_;
    destination.angleRotation_ = angleRotation_;
    destination.facteurEchelle_ = facteurEchelle_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::afficherConcret() const
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
void NoeudBonusAccelerateur::afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	glPushName(id_);
	glPushMatrix();

	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(matrVue, matrProjection, vueProjection, attribuerCouleur);

	// Révolution autour du centre.
	//glScaled(5.0, 5.0, 1.0);
	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(sqrtf(2), sqrtf(2), 0));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::scale(modele, glm::vec3(rayonBonusAccelerateur_, rayonBonusAccelerateur_, rayonBonusAccelerateur_));
	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurBonus_[0];
	couleurObjet[1] = couleurBonus_[1];
	couleurObjet[2] = couleurBonus_[2];
	GLubyte couleurSelection[3];
	couleurSelection[0] = couleurSelection_[0];
	couleurSelection[1] = couleurSelection_[1];
	couleurSelection[2] = couleurSelection_[2];
	// Affichage du modèle.
	vbo_->dessiner(estSelectionne(), attribuerCouleur, couleurObjet, couleurSelection, modele, matrVue, matrProjection, vueProjection*modele);
	glPopMatrix();
	glPopName();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::animer(float temps)
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
/// @fn bool NoeudBonusAccelerateur::verifierSelection
///											(GLubyte couleurObjet[])
///
/// Cette fonction verifie si le noeud est selectionne.
///
/// @param[in] couleurObjet : Le code RGB de l'objet
///
/// @return Faux si le noeud n'est pas selectione et vice-versa.
///
////////////////////////////////////////////////////////////////////////
bool NoeudBonusAccelerateur::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;
	//std::cout << " couleur Objet: " << (int)couleurObjet[0] << ";" << (int)couleurObjet[1] << ";" << (int)couleurObjet[2] << std::endl;

	//std::cout << "couleur Selection_: " << (int)couleurSelection_[0] << ";" << (int)couleurSelection_[1] << ";" << (int)couleurSelection_[2] << std::endl;
	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;
	}
	else if (couleurObjet[0] == couleurBonus_[0] && couleurObjet[1] == couleurBonus_[1] && couleurObjet[2] == couleurBonus_[2])
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
/// @fn bool NoeudBonusAccelerateur::estDansLaTable()
///
/// Cette fonction verifie si le noeud est dans la table
///
/// @param[in] Aucun
///
/// @return si l'objet est dans la table (bool)
///
////////////////////////////////////////////////////////////////////////
bool NoeudBonusAccelerateur::estDansLaTable()
{
	if (estModifier_) {
		redefinirSommets();
	}
	std::vector<glm::dvec3> sommetsTable = this->obtenirParent()->obtenirSommets();
	return utilitaire::pointsDansPolygone2D(obtenirSommets(), sommetsTable);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::redefinirSommets()
///
/// Cette fonction redefinit les sommets
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::redefinirSommets()
{
	sommets_.erase(sommets_.begin(), sommets_.end());
	sommets_.push_back(glm::dvec3(rayonBonusAccelerateur_ + obtenirPositionRelative().x, rayonBonusAccelerateur_ + obtenirPositionRelative().y, obtenirPositionRelative().z));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::assignerObjetRendu\
///    (modele::Modele3D const * modele, opengl::VBO const * liste)
///
/// Cette fonction assigne le rendu de l'objet
///
/// @param[in] modele : Modele3D, liste : VBO
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	rayonBonusAccelerateur_ = utilitaire::calculerSphereEnglobante(*modele_).rayon / 20.0;
}
void NoeudBonusAccelerateur::modifierRayonBonusAccelerateur(double rayon)
{
	rayonBonusAccelerateur_ = rayon;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::attribuerCouleur()
///
/// Cette fonction attribut une couleur.
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::attribuerCouleur()
{
	if (NoeudAbstrait::compteurBonus_ < 180)
	{
		couleurBonus_[0] = 255 - NoeudAbstrait::compteurBonus_ + 1;
		couleurBonus_[1] = 0;
		couleurBonus_[2] = NoeudBonusAccelerateur::compteurYellow_;
	}
	else
	{
		NoeudAbstrait::compteurBonus_ = 1;
		NoeudBonusAccelerateur::compteurYellow_++;
		couleurBonus_[0] = 255;
		couleurBonus_[1] = 0;
		couleurBonus_[2] = NoeudBonusAccelerateur::compteurYellow_;
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBonusAccelerateur::accepterVisiteur
///									(VisiteurAbstrait* visiteur)
///
/// Accepte le visiteur.
///
/// @param[in] visiteur : le type visiteur
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudBonusAccelerateur::accepterVisiteur(VisiteurAbstrait* visiteur) {
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
