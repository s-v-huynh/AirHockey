///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.cpp
/// @author equipe06
/// @date 2016-09-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurSuppression.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::VisiteurSuppression()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur par defaut).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::VisiteurSuppression() {

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::~VisiteurSuppression()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::~VisiteurSuppression() {

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSuppression::visiter(NoeudComposite *t)
///
/// Le visiteur visite le noeud et l'efface
///
/// @param[in] t : le noeud qui sera supprime.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudComposite *t)
{
	for (unsigned int i = 0; i < t->obtenirNombreEnfants(); i++) {
		t->chercher(i)->effacerSelection();
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSuppression::visiter(NoeudMaillet * ma)
///
///  Le visiteur visite le noeud et l'efface
///
/// @param[in] ma: noeud qu'on visite pour le supprimer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudMaillet * ma)
{
	//ma->obtenirParent()->effacerSelection();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSuppression::visiter(NoeudMuret * m)
///
///  Le visiteur visite le noeud et l'efface
///
/// @param[in] m: noeud qu'on visite pour le supprimer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudMuret * m)
{
	m->obtenirParent()->effacerSelection();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::visiter(NoeudPortail * p)
///
///  Le visiteur visite le noeud et l'efface
///
/// @param[in] p: noeud qu'on visite pour le supprimer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudPortail * p)
{
	p->obtenirParent()->effacer(p->getFrere());
	p->obtenirParent()->effacerSelection();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSuppression::visiter(NoeudRondelle * r)
///
///  Le visiteur visite le noeud et l'efface
///
/// @param[in] r: noeud qu'on visite pour le supprimer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudRondelle * r)
{
	//r->obtenirParent()->effacerSelection();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSuppression::visiter(NoeudTable* t)
///
///  Le visiteur visite le noeud et l'efface
///
/// @param[in] t: noeud qu'on visite pour le supprimer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudTable* t)
{
	t->effacerSelection();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSuppression::visiter(NoeudBonusAccelerateur * acc)
///
///  Le visiteur visite le noeud et l'efface
///
/// @param[in] acc: noeud qu'on visite pour le supprimer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudBonusAccelerateur * acc)
{
	acc->obtenirParent()->effacerSelection();
}
