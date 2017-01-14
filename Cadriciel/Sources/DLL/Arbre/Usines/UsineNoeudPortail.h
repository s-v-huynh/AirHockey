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
#include "NoeudPortail.h"
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
class UsineNoeudPortail: public UsineAbstraite
{
public:
	///Constructeur par paramètres
	inline UsineNoeudPortail(const std::string& nom);
	/// Fonction pour créer un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
	/// Fonction pour créer un noeud à partir d'un noeud XML
	virtual NoeudAbstrait* creerNoeud(tinyxml2::XMLNode * node)const;
	NoeudAbstrait* creerNoeud(tinyxml2::XMLNode * node, NoeudPortail* noeud)const;

protected: 
	/// Modèle 3D correspondant à ce noeud.
	modele::Modele3D modele_;
	/// Storage pour le dessin du modèle
	opengl::VBO vbo_;

private: 
	std::string nom_;
	

};

inline UsineNoeudPortail::UsineNoeudPortail(const std::string& nom)
	:UsineAbstraite(nom)
{
	modele_.charger("media/portail1.obj");
	vbo_ = opengl::VBO(&modele_);
	vbo_.charger();
}

NoeudAbstrait* UsineNoeudPortail::creerNoeud() const
{
	auto noeud = new NoeudPortail{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;
}

NoeudAbstrait* UsineNoeudPortail::creerNoeud(tinyxml2::XMLNode * node)const {
	NoeudPortail* portail= nullptr;
	return creerNoeud(node, portail);
}
NoeudAbstrait* UsineNoeudPortail::creerNoeud(tinyxml2::XMLNode * node, NoeudPortail* noeudFrere)const
{
	NoeudPortail* noeud = new NoeudPortail(obtenirNom());
	NoeudPortail* frere = new NoeudPortail(obtenirNom());

	double x = 0, y = 0, z = 0, angleRotation = 0, rayon = 0, attraction = 0, facteur = 0;
	node->ToElement()->QueryDoubleAttribute("X", &x);
	node->ToElement()->QueryDoubleAttribute("Y", &y);
	node->ToElement()->QueryDoubleAttribute("Z", &z);

	node->ToElement()->QueryDoubleAttribute("ANGLE_ROTATION", &angleRotation);

	node->ToElement()->QueryDoubleAttribute("RAYON", &rayon);

	node->ToElement()->QueryDoubleAttribute("ATTRACTION", &attraction);

	node->ToElement()->QueryDoubleAttribute("FACTEUR_ECHELLE", &facteur);
	
	glm::vec3 positionRelative;
	positionRelative[0] = x;
	positionRelative[1] = y;
	positionRelative[2] = z;

	noeud->assignerPositionRelative(positionRelative);
	noeud->modifierAngleRotation(angleRotation);
	noeud->modifierRayon(rayon);
	noeud->modifierFacteurEchelle(facteur);

	double x1 = 0, y1 = 0, z1 = 0, angleRotation1 = 0, rayon1 = 0, attraction1 = 0, facteur1 = 0;

	node->ToElement()->QueryDoubleAttribute("X1", &x1);
	node->ToElement()->QueryDoubleAttribute("Y1", &y1);
	node->ToElement()->QueryDoubleAttribute("Z1", &z1);

	node->ToElement()->QueryDoubleAttribute("ANGLE_ROTATION1", &angleRotation1);

	node->ToElement()->QueryDoubleAttribute("RAYON1", &rayon1);

	node->ToElement()->QueryDoubleAttribute("ATTRACTION1", &attraction1);

	node->ToElement()->QueryDoubleAttribute("FACTEUR_ECHELLE1", &facteur1);

	glm::vec3 positionRelative1;
	positionRelative1[0] = x1;
	positionRelative1[1] = y1;
	positionRelative1[2] = z1;
	
	frere->assignerPositionRelative(positionRelative1);
	frere->modifierAngleRotation(angleRotation1);
	frere->modifierRayon(rayon1);
	frere->modifierFacteurEchelle(facteur1);

	noeud->setFrere(frere);
	frere->setFrere(noeud);

	noeud->assignerObjetRendu(&modele_, &vbo_);
	frere->assignerObjetRendu(&modele_, &vbo_);
	noeudFrere = frere;
	return noeud;

	
}