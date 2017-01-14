#ifndef	VISITEUR_DEPLACEMENT_H
#define VISITEUR_DEPLACEMENT_H

//afin de lui permettre d'heriter des methodes a sucharger
#include "VisiteurAbstrait.h"

//afin d'eviter l'erreur de classe imcomplete 
#include "NoeudAbstrait.h"
#include "NoeudTable.h"
#include "NoeudRondelle.h"
#include "NoeudPortail.h"
#include "NoeudMuret.h"
#include "NoeudMaillet.h"
#include "NoeudBonusAccelerateur.h"
#include "NoeudComposite.h"



//structure representant la position de deplacement

class VisiteurDeplacement : public VisiteurAbstrait
{

public:

	//constructor
	VisiteurDeplacement();
	//destructeur
	~VisiteurDeplacement();

	//modificateurs 
	void modifierPosition(glm::dvec3 position);

	//recuperateurs
	float obtenirX();
	float obtenirY();
	float obtenirZ();

	//visites des differents noeuds
	virtual void visiter(NoeudComposite* noeud) ;
	virtual void visiter(NoeudMaillet* noeud);
	virtual void visiter(NoeudMuret* noeud) ;
	virtual void visiter(NoeudPortail* noeud) ;
	virtual void visiter(NoeudRondelle* noeud) ;
	virtual void visiter(NoeudTable* noeud) ;
	virtual void visiter(NoeudBonusAccelerateur* noeud) ;

private:

	glm::dvec3 position_;

};


#endif
