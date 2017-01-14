//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef	VISITEUR_ABSTRAIT_H
#define VISITEUR_ABSTRAIT_H
#include "GL/glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>

using namespace std;
// afin d'eviter une erreur de double inclusion 
class NoeudAbstrait;
class NoeudTable;
class NoeudRondelle;
class NoeudPortail;
class NoeudMuret;
class NoeudMaillet;
class NoeudMailletVirtuel;
class NoeudBonusAccelerateur;
class NoeudComposite; // le noeud conteneur :)

static const std::string VISITEUR_DEFAULT{ "visiteur default" };

class VisiteurAbstrait
{
  

	public :
	/// Visiteur
    VisiteurAbstrait () {}
	virtual ~VisiteurAbstrait() {};
	virtual void visiter(NoeudComposite* noeud) {};
	virtual void visiter(NoeudMaillet* noeud) {};
	virtual void visiter(NoeudMuret* noeud) {};
	virtual void visiter(NoeudPortail* noeud) {};
	virtual void visiter(NoeudRondelle* noeud) {};
	virtual void visiter(NoeudTable* noeud) {};
	virtual void visiter(NoeudBonusAccelerateur* noeud) {};
	virtual void visiter(NoeudMailletVirtuel* noeud) {};


	/*virtual void visiter(NoeudBonusAccelerateur& noeud) {};
	///Algorithme de visite pour NoeudMur
	virtual void visiter(NoeudMuret& noeud) {};
	///Algorithme de visite pour NoeudTable
	virtual void visiter(NoeudTable& noeud) {};
	///Algorithme de visite pour NoeudFleche
	virtual void visiter(NoeudMaillet& noeud) {};
	virtual void visiter(NoeudPortail& noeud) {};
	virtual void visiter(NoeudRondelle&) {};*/

protected:
//	/// Type de visiteur.
	std::string  type_;

};

#endif
