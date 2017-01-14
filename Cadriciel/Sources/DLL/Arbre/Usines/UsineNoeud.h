///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeud.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUD_H__
#define __ARBRE_USINES_USINENOEUD_H__

#include <type_traits>
#include <string>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include "tinyxml2.h"

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class UsineAbstraite
/// @brief Classe de base abstraite des usines qui seront utilisées pour
///        créer les différents noeuds de l'arbre de rendu.
///
/// @author Martin Bisson
/// @date 2001-01-28
///////////////////////////////////////////////////////////////////////////
class UsineAbstraite {
public:
	/// Fonction de création de noeud à surcharger
	inline virtual NoeudAbstrait* creerNoeud() const;
	/// Fonction de création de noeud à partir d'un noeud XML à surcharger
	inline virtual NoeudAbstrait* creerNoeud(tinyxml2::XMLNode * node) const;

	inline ~UsineAbstraite() {
		vbo_.liberer();
	}

	inline UsineAbstraite(const std::string& nomUsine, const std::string& nomModele)
		: UsineAbstraite{ nomUsine }
	{
		modele_.charger(nomModele);
		vbo_ = opengl::VBO{ &modele_ };
		vbo_.charger();
	}

protected:
	UsineAbstraite(std::string nom) : nom_(nom) {}

	/// Retourne le nom associé à l'usine
	inline const std::string& obtenirNom() const;
	modele::Modele3D modele_;
	opengl::VBO vbo_;
private:
	/// Le nom associé à l'usine
	std::string nom_;
};



////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& UsineNoeud::obtenirNom() const
///
/// Cette fonction retourne une chaîne représentante le nom associé à
/// l'usine.
///
/// @return Le nom associé à l'usine.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& UsineAbstraite::obtenirNom() const
{
	return nom_;
}


NoeudAbstrait* UsineAbstraite::creerNoeud() const {
	NoeudAbstrait*  noeud = new NoeudAbstrait{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;
}

inline NoeudAbstrait * UsineAbstraite::creerNoeud(tinyxml2::XMLNode * node) const
{
	NoeudAbstrait* noeud = new NoeudAbstrait(obtenirNom());

	double x = 0, y = 0, z = 0, angleRotation = 0, rayon = 0, attraction = 0, facteur = 0;
	node->ToElement()->QueryDoubleAttribute("X", &x);
	node->ToElement()->QueryDoubleAttribute("Y", &y);
	node->ToElement()->QueryDoubleAttribute("Z", &z);

	node->ToElement()->QueryDoubleAttribute("ANGLE_ROTATION", &angleRotation);

	glm::vec3 positionRelative;
	positionRelative[0] = x;
	positionRelative[1] = y;
	positionRelative[2] = z;

	noeud->assignerPositionRelative(positionRelative);
	noeud->modifierAngleRotation(angleRotation);

	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;
}


#endif // __ARBRE_USINES_USINENOEUD_H__



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


