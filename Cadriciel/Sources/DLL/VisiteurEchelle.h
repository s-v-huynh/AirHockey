#ifndef	VISITEUR_ECHELLE_H
#define VISITEUR_ECHELLE_H
#include "VisiteurAbstrait.h"
#include "NoeudAbstrait.h"
#include "NoeudTable.h"
#include "NoeudRondelle.h"
#include "NoeudPortail.h"
#include "NoeudMuret.h"
#include "NoeudMaillet.h"
#include "NoeudBonusAccelerateur.h"
#include "NoeudComposite.h"

class VisiteurEchelle : public VisiteurAbstrait
{
public:
	//constructor
	VisiteurEchelle(double facteur = 1.0);
	//destructeur
	~VisiteurEchelle();

	//modificateurs 
	void modifierFacteur(double facteur);

	//recuperateurs
	double obtenirFacteur();

	//visites des differents noeuds
	virtual void visiter(NoeudComposite*) ;
	virtual void visiter(NoeudMaillet*) ;
	virtual void visiter(NoeudMuret*) ;
	virtual void visiter(NoeudPortail*) ;
	virtual void visiter(NoeudRondelle*) ;
	virtual void visiter(NoeudTable*) ;
	void visiter(NoeudBonusAccelerateur*) ;

private:
	double facteur_;
};

#endif


