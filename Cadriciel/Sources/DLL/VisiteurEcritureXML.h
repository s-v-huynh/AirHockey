#ifndef	VISITEUR_ECRITURE_XML_H
#define VISITEUR_ECRITURE_XML_H


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
#include "ArbreRenduINF2990.h"
#include "tinyxml2.h"

class VisiteurEcritureXML : public VisiteurAbstrait
{

public:

	//constructor
	VisiteurEcritureXML(tinyxml2::XMLElement* racine);
	//destructeur
	~VisiteurEcritureXML();


	//visites des differents noeuds
	virtual void visiter(NoeudComposite* noeud) ;
	virtual void visiter(NoeudMaillet* noeud) ;
	virtual void visiter(NoeudMuret* noeud) ;
	virtual void visiter(NoeudPortail* noeud) ;
	virtual void visiter(NoeudRondelle* noeud) ;
	virtual void visiter(NoeudTable* noeud) ;
	virtual void visiter(NoeudBonusAccelerateur* noeud) ;
	
	tinyxml2::XMLElement* racine_;

};

#endif