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
#include "NoeudMuret.h"
#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "tinyxml2.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudMaillet
/// @brief Classe qui représente une usine capable de créer des noeuds de
///		   type NoeudPortail.
///
/// @author Equipe06
/// @date 2016-09-30
///////////////////////////////////////////////////////////////////////////
class UsineNoeudMuret : public UsineAbstraite
{
public:
	///Constructeur par paramètres
	inline UsineNoeudMuret(const std::string& nom);
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

inline UsineNoeudMuret::UsineNoeudMuret(const std::string& nom)
	:UsineAbstraite(nom)
{
	//muret(2).obj
	modele_.charger("media/muretblend.obj");
	vbo_ = opengl::VBO(&modele_);
	vbo_.charger();
}

NoeudAbstrait* UsineNoeudMuret::creerNoeud() const
{
	auto noeud = new NoeudMuret{ obtenirNom()};
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;
}

NoeudAbstrait* UsineNoeudMuret::creerNoeud(tinyxml2::XMLNode * node)const
{
	NoeudMuret* noeud = new NoeudMuret(obtenirNom());

	double x = 0, y = 0, z = 0, angleRotation = 0, facteur = 0, sommet1X=0, sommet1Y=0, sommet2X, sommet2Y=0;
	int longueur = 0;
	node->ToElement()->QueryDoubleAttribute("X", &x);
	node->ToElement()->QueryDoubleAttribute("Y", &y);
	node->ToElement()->QueryDoubleAttribute("Z", &z);

	node->ToElement()->QueryDoubleAttribute("ANGLE_ROTATION", &angleRotation);

	node->ToElement()->QueryDoubleAttribute("FACTEUR_ECHELLE", &facteur);

	node->ToElement()->QueryIntAttribute("LONGUEUR", &longueur);

	node->ToElement()->QueryDoubleAttribute("SOMMET1_X", &sommet1X);

	node->ToElement()->QueryDoubleAttribute("SOMMET1_Y", &sommet1Y);

	node->ToElement()->QueryDoubleAttribute("SOMMET2_X", &sommet2X);

	node->ToElement()->QueryDoubleAttribute("SOMMET2_Y", &sommet2Y);
	glm::vec3 positionRelative;
	positionRelative[0] = x;
	positionRelative[1] = y;
	positionRelative[2] = z;

	vector<glm::dvec3> sommets;

	glm::dvec3 sommet1;
	sommet1.x = sommet1X;
	sommet1.y = sommet1Y;
	sommet1.z = 0.0;

	glm::dvec3 sommet2;
	sommet2.x = sommet2X;
	sommet2.y = sommet2Y;
	sommet2.z = 0.0;

	sommets.push_back(sommet1);
	sommets.push_back(sommet2);

	noeud->assignerPositionRelative(positionRelative);
	noeud->modifierAngleRotation(angleRotation);
	noeud->modifierFacteurEchelle(facteur);
	noeud->assignerSommets(sommets);

	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;


}