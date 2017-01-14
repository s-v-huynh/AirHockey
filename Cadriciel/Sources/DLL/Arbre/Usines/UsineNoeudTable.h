
///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudTable.h
/// @author equipe06
/// @date 2016-09-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#pragma once

#include "UsineNoeud.h"
#include "NoeudTable.h"
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
class UsineNoeudTable : public UsineAbstraite
{
public:
	///Constructeur par paramètres
	inline UsineNoeudTable(const std::string& nom);
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

inline UsineNoeudTable::UsineNoeudTable(const std::string& nom)
	:UsineAbstraite(nom)
{
	//media/tableF.obj
	modele_.charger("");
	vbo_ = opengl::VBO(&modele_);
	vbo_.charger();
}

NoeudAbstrait* UsineNoeudTable::creerNoeud() const
{
	auto noeud = new NoeudTable{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;
}

NoeudAbstrait* UsineNoeudTable::creerNoeud(tinyxml2::XMLNode * node)const
{
	NoeudTable* noeud = new NoeudTable(obtenirNom());

	double x = 0, y = 0, z = 0, angleRotation=0, facteur=0;
	int acceleration = 0, rebondissement=0, friction=0;
	//std::vector<Vect3> pointsControle;

	//node->ToElement()->QueryDoubleAttribute("PT_C_X0", &x);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Y0", &y);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Z0", &z);
	//
	//pointsControle.push_back(Vect3(x, y, z));

	//node->ToElement()->QueryDoubleAttribute("PT_C_X1", &x);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Y1", &y);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Z1", &z);
	//
	//pointsControle.push_back(Vect3(x, y, z));

	//node->ToElement()->QueryDoubleAttribute("PT_C_X2", &x);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Y2", &y);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Z2", &z);

	//pointsControle.push_back(Vect3(x, y, z));

	//node->ToElement()->QueryDoubleAttribute("PT_C_X3", &x);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Y3", &y);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Z3", &z);

	//pointsControle.push_back(Vect3(x, y, z));

	//node->ToElement()->QueryDoubleAttribute("PT_C_X4", &x);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Y4", &y);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Z4", &z);

	//pointsControle.push_back(Vect3(x, y, z));

	//node->ToElement()->QueryDoubleAttribute("PT_C_X5", &x);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Y5", &y);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Z5", &z);

	//pointsControle.push_back(Vect3(x, y, z));

	//node->ToElement()->QueryDoubleAttribute("PT_C_X6", &x);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Y6", &y);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Z6", &z);

	//pointsControle.push_back(Vect3(x, y, z));

	//node->ToElement()->QueryDoubleAttribute("PT_C_X7", &x);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Y7", &y);
	//node->ToElement()->QueryDoubleAttribute("PT_C_Z7", &z);

	//pointsControle.push_back(Vect3(x, y, z));

	node->ToElement()->QueryDoubleAttribute("X", &x);
	node->ToElement()->QueryDoubleAttribute("Y", &y);
	node->ToElement()->QueryDoubleAttribute("Z", &z);

	node->ToElement()->QueryDoubleAttribute("ANGLE_ROTATION", &angleRotation);

	node->ToElement()->QueryDoubleAttribute("FACTEUR_ECHELLE", &facteur);

	node->ToElement()->QueryIntAttribute("ACCELERATION", &acceleration);
	node->ToElement()->QueryIntAttribute("COEFFICIENT_REBONDISSEMENT", &rebondissement );
	node->ToElement()->QueryIntAttribute("COEFFICIENT_FRICTION" ,&friction);

	glm::vec3 positionRelative;
	positionRelative[0] = x;
	positionRelative[1] = y;
	positionRelative[2] = z;

	noeud->assignerPositionRelative(positionRelative);
	noeud->modifierAngleRotation(angleRotation);
	noeud->modifierFacteurEchelle(facteur);
	noeud->modifierAcceleration(acceleration);
	noeud->modifierCoefRebondissement(rebondissement);
	noeud->modifierFriction(friction);





	//Modifier pts controle
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;


}
