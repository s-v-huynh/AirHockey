#pragma once
///////////////////////////////////////////////////////////////////////////
/// @file PointControle.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_POINTCONTROLE_H__
#define __ARBRE_NOEUDS_POINTCONTROLE_H__


#include "NoeudComposite.h"
#include "NoeudTable.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class PointControle
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class PointControl : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	PointControl(const std::string& typeNoeud);
	/// Destructeur.
	~PointControl();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const;
	void obtenirPoint();
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	void attribuerCouleur();
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	void deplacementPointControl(double x, double y);
	bool verifierSelection(GLubyte couleurObjet[]);

	//void initialisationCreation(glm::dvec3 cursor, glm::dvec3 cursor1) override {};
protected:
	std::vector<PointControl*>listePoints_;
private:
	/// Angle dans le sinus de l'oscillation
	float angle_{ 0 };
	GLubyte couleurPointControl_[3];
	static int pControl_;
	NoeudTable* table_;
	int ptAppuye_;
	glm::dvec3  ptControle_[9];
	glm::dvec3 sommetT_[13];
};


#endif // __ARBRE_NOEUDS_PointControle_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
