#pragma once
///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @author equipe06
/// @date 2016-09-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////

#ifndef	VISITEURSELECTIONOBJET_H
#define VISITEURSELECTIONOBJET_H

#include "VisiteurAbstrait.h"
#include "../Arbre/Noeuds/NoeudTypes.h" 

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelectObjet
/// @brief Classe qui implémentante le visiteur concrêt permettant de 
///		   parcourir l'arbre de rendu et de visiter chaque noeud afin de
///		   permettre la selection par clic.
///
///		   Les visiteurs concrêts pourront faire différents traîtements en 
///		   fonction du type de noeud visité, car ils possedent des attributs differents. 
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
#include <iostream>
class VisiteurSelection : public VisiteurAbstrait
{
public:

	///Constucteur 
	VisiteurSelection(glm::dvec3 & point, bool selectionUnique, GLubyte couleurPixel[], const bool& initialiserVisite)
	{
		type_ = VISITEUR_DEFAULT;
		point_ = point;
		selectionunique_ = selectionUnique;
		selectionexiste_ = false;
		int a = (int)couleurObjet_[2];
		for (unsigned int i = 0; i < 3; i++)
			couleurObjet_[i] = couleurPixel[i];
		initialiserVisite_ = initialiserVisite;
		//cout << "je me suis initialiser" << endl;

	};


	/// Destructeur
	~VisiteurSelection() {};
	virtual void visiter(NoeudComposite*) ;
	///Algorithme de visite pour NoeudPortail
	virtual void visiter(NoeudPortail* noeud);
	///Algorithme de visite pour NoeudMuret
	virtual void visiter(NoeudMuret* noeud);
	///Algorithme de visite pour NoeudTable
	//virtual void visiter(NoeudTable* noeud);
	///Algorithme de visite pour NoeudMaillet
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudMailletVirtuel* noeud);
	///Algorithme de visite pour bonus
	virtual void visiter(NoeudBonusAccelerateur* noeud);
	///Algorithme de visite pour rondelle
	virtual void visiter(NoeudRondelle* noeud);


	///Methode permettant le retour de la selectionexiste
	bool obtenirselectionExiste() {
		return selectionexiste_;
	};


private:
	///Point de selection.
	glm::dvec3 point_;
	///Booleen representant une selection unique ou non.
	bool selectionunique_;
	///Booleen representant si une selection existe ou non.
	bool  selectionexiste_;
	/// Couleur de l'objet
	GLubyte couleurObjet_[3];
	/// Booleen pour initialiser la visite
	bool initialiserVisite_;
};

#endif
//VISITEURSELECTIONOBJET_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////


