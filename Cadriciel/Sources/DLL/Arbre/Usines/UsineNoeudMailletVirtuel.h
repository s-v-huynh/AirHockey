///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudMaillet.h
/// @author equipe06
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#pragma once

#include "UsineNoeud.h"
#include "NoeudMailletVirtuel.h"
#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "tinyxml2.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudMaillet
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///		   type NoeudPortail.
///
/// @author Equipe06
/// @date 2016-09-30
///////////////////////////////////////////////////////////////////////////
class UsineNoeudMailletVirtuel : public UsineAbstraite
{
public:
	///Constructeur par param�tres
	inline UsineNoeudMailletVirtuel(const std::string& nom);
	/// Fonction pour cr�er un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
	/// Fonction pour cr�er un noeud � partir d'un noeud XML
	virtual NoeudAbstrait* creerNoeud(tinyxml2::XMLNode * node)const;

protected:
	/// Mod�le 3D correspondant � ce noeud.
	modele::Modele3D modele_;
	/// Storage pour le dessin du mod�le
	opengl::VBO vbo_;

private:
	std::string nom_;


};

inline UsineNoeudMailletVirtuel::UsineNoeudMailletVirtuel(const std::string& nom)
	:UsineAbstraite(nom)
{
	modele_.charger("media/mailletL3.obj");
	vbo_ = opengl::VBO(&modele_);
	vbo_.charger();
}

NoeudAbstrait* UsineNoeudMailletVirtuel::creerNoeud() const
{
	auto noeud = new NoeudMailletVirtuel{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;
}

NoeudAbstrait* UsineNoeudMailletVirtuel::creerNoeud(tinyxml2::XMLNode * node)const
{
	NoeudMaillet* noeud = new NoeudMaillet(obtenirNom());

	double x = 0, y = 0, z = 0, angleRotation = 0, rayon = 0, attraction = 0, facteur = 0;
	node->ToElement()->QueryDoubleAttribute("X", &x);
	node->ToElement()->QueryDoubleAttribute("Y", &y);
	node->ToElement()->QueryDoubleAttribute("Z", &z);

	node->ToElement()->QueryDoubleAttribute("ANGLE_ROTATION", &angleRotation);

	node->ToElement()->QueryDoubleAttribute("FACTEUR_ECHELLE", &facteur);

	node->ToElement()->QueryDoubleAttribute("RAYON_MAILLET", &rayon);

	glm::vec3 positionRelative;
	positionRelative[0] = x;
	positionRelative[1] = y;
	positionRelative[2] = z;

	noeud->assignerPositionRelative(positionRelative);
	noeud->modifierAngleRotation(angleRotation);
	noeud->modifierRayonMaillet(rayon);

	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;


}