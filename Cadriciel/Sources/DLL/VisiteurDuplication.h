//////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef	VISITEUR_DUPLICATION_H
#define VISITEUR_DUPLICATION_H
#include "VisiteurAbstrait.h"
#include <vector>
class ArbreRenduINF2990;
class ArbreRendu;

/// Le choix du conteneur pour les etampes.
using conteneur_etampes = std::vector<NoeudAbstrait*>;

class VisiteurDuplication : public VisiteurAbstrait {
public:
	///Constructeur 
	VisiteurDuplication(ArbreRenduINF2990*) ;
	///Destructeur
	~VisiteurDuplication() ;
	void definirPosition(glm::dvec3);
	void deplacerEtampe();


	///visites des differents noeuds
	virtual void visiter(NoeudComposite*) ;
	virtual void visiter(NoeudMaillet*) ;
	virtual void visiter(NoeudMuret*) ;
	virtual	void visiter(NoeudPortail*) ;
	virtual void visiter(NoeudRondelle*) ;
	virtual void visiter(NoeudTable*) ;
	virtual void visiter(NoeudBonusAccelerateur*) ;
private:
	ArbreRenduINF2990* arbreAVisiter_;
	NoeudTable * zoneJeu_;
	conteneur_etampes etampes_;
	glm::dvec3 position_;
};

#endif