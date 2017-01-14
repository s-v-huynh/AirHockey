#ifndef	VISITEUR_SUPPRESSION_H
#define VISITEUR_SUPPRESSION_H
#include "VisiteurAbstrait.h"

class VisiteurSuppression : public VisiteurAbstrait {
public:
	//Constructeur 
	VisiteurSuppression();
	//Destructeur
	~VisiteurSuppression();


	//visites des differents noeuds
	virtual void visiter(NoeudComposite*) ;
	virtual void visiter(NoeudMaillet*) ;
	virtual void visiter(NoeudMuret*) ;
	virtual void visiter(NoeudPortail*) ;
	virtual void visiter(NoeudRondelle*) ;
	virtual void visiter(NoeudTable*) ;
	virtual void visiter(NoeudBonusAccelerateur*) ;

};
#endif
