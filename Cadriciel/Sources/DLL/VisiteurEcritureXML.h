//////////////////////////////////////////////////////////////////////////
/// @file VisiteurEcritureXML.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef	VISITEUR_ECRITURE_XML_H
#define VISITEUR_ECRITURE_XML_H


#include "VisiteurAbstrait.h"
#include "Utilitaire.h"
#include "../../tinyxml2/include/tinyxml2.h"
class VisiteurEcritureXML : public VisiteurAbstrait
{

public:

	///constructor
	VisiteurEcritureXML(tinyxml2::XMLElement* racine);
	///destructeur
	~VisiteurEcritureXML();


	///visites des differents noeuds
	virtual void visiter(NoeudComposite* noeud) ;
	virtual void visiter(NoeudMaillet* noeud) ;
	virtual void visiter(NoeudMuret* noeud) ;
	virtual void visiter(NoeudPortail* noeud) ;
	virtual void visiter(NoeudRondelle* noeud) ;
	virtual void visiter(NoeudTable* noeud) ;
	virtual void visiter(NoeudBonusAccelerateur* noeud) ;
	
	///Racine
	tinyxml2::XMLElement* racine_;

};

#endif