#ifndef	VISITEUR_ROTATION_H
#define VISITEUR_ROTATION_H
#include "VisiteurAbstrait.h"
#include "NoeudAbstrait.h"
#include "NoeudBonusAccelerateur.h"
#include "NoeudComposite.h"
#include "NoeudMaillet.h"
#include "NoeudMuret.h"
#include "NoeudPortail.h"
#include "NoeudRondelle.h"
#include "NoeudTable.h"
#include "Utilitaire.h"

typedef struct {
	float X, Y;
}position;

//Structure qui represente  les angles de rotation

class VisiteurRotation :public VisiteurAbstrait
{

public:

	//Constructor
	VisiteurRotation();
	VisiteurRotation(float centreX, float centreY, float varY);
	//Destructeur
	~VisiteurRotation() {}

	//accesseurs
	float obtenirCentreX();
	float obtenirCentreY();
	float obtenirVarY();

	//modificateurs
	void modifierCentre(float X, float Y);
	void modifierVarY(float varY);

	//Visiter les noeuds
	virtual void visiter(NoeudComposite* noeud) ;
	virtual void visiter(NoeudMaillet* noeud) ;
	virtual void visiter(NoeudMuret* noeud) ;
	virtual void visiter(NoeudPortail* noeud) ;
	virtual void visiter(NoeudRondelle* noeud) ;
	virtual void visiter(NoeudTable* noeud) ;
	virtual void visiter(NoeudBonusAccelerateur* noeud) ;

private:
	//Variation de la distance de la souris dans l'axe des Y
	float varY_;

	//Centre de rotation de l'objet ou de plusieurs objets
	position* centreRotation_;

};

#endif


