///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPortail.h
/// @author equipe06
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#pragma once

#include "UsineNoeud.h"
#include "NoeudBonusAccelerateur.h"
#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "tinyxml2.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPortail
/// @brief Classe qui représente une usine capable de créer des noeuds de
///		   type NoeudPortail.
///
/// @author Equipe06
/// @date 2016-09-30
///////////////////////////////////////////////////////////////////////////
class UsineNoeudBonusAccelerateur : public UsineAbstraite
{
public:
	///Constructeur par paramètres
	inline UsineNoeudBonusAccelerateur(const std::string& nom);
	/// Fonction pour créer un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
	/// Fonction pour créer un noeud à partir d'un noeud XML
	virtual NoeudAbstrait* creerNoeud(tinyxml2::XMLNode * node)const;

protected:
	/// Modèle 3D correspondant à ce noeud.
	modele::Modele3D modele_;
	/// Storage pour le dessin du modèle
	opengl::VBO vbo_;

private:
	std::string nom_;


};

inline UsineNoeudBonusAccelerateur::UsineNoeudBonusAccelerateur(const std::string& nom)
	:UsineAbstraite(nom)
{
	modele_.charger("media/acceN.obj");
	vbo_ = opengl::VBO(&modele_);
	vbo_.charger();
}

NoeudAbstrait* UsineNoeudBonusAccelerateur::creerNoeud() const
{
	auto noeud = new NoeudBonusAccelerateur{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;
}

NoeudAbstrait* UsineNoeudBonusAccelerateur::creerNoeud(tinyxml2::XMLNode * node)const
{
	NoeudBonusAccelerateur* noeud = new NoeudBonusAccelerateur(obtenirNom());

	double x = 0, y = 0, z = 0, angleRotation = 0, rayon = 0, facteur = 0;
	node->ToElement()->QueryDoubleAttribute("X", &x);
	node->ToElement()->QueryDoubleAttribute("Y", &y);
	node->ToElement()->QueryDoubleAttribute("Z", &z);

	node->ToElement()->QueryDoubleAttribute("ANGLE_ROTATION", &angleRotation);

	node->ToElement()->QueryDoubleAttribute("RAYON_ACCELERATEUR", &rayon);


	node->ToElement()->QueryDoubleAttribute("FACTEUR_ECHELLE", &facteur);

	glm::vec3 positionRelative;
	positionRelative[0] = x;
	positionRelative[1] = y;
	positionRelative[2] = z;

	noeud->assignerPositionRelative(positionRelative);
	noeud->modifierAngleRotation(angleRotation);
	//noeud->modifierRayonBonusAccelerateur(rayon);

	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;


}