//////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurDuplication.h"
#include "ArbreRenduINF2990.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::VisiteurDuplication(ArbreRenduINF2990* arbre)
///
/// Ce constructeur assigne l'arbre qui sera visite et cherche la table
/// associe a l'arbre
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication(ArbreRenduINF2990* arbre) : arbreAVisiter_(arbre){
	zoneJeu_ = dynamic_cast < NoeudTable* >(arbreAVisiter_->chercher("table"));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::~VisiteurDuplication()
///
/// Ce destructeur detruit les etampes.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::~VisiteurDuplication() {
	delete arbreAVisiter_;
	for (int i = 0; i < etampes_.size(); i++)
	{
		delete (etampes_[i]);
	}
	etampes_.clear();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::definirPosition(glm::dvec3 position)
///
/// Cette fonction definit la position du noeud nouvellement duplique
///
/// @param[in] position: position de l'objet nouvellement cree 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::definirPosition(glm::dvec3 position)
{
	position_ = position;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::deplacerEtampe()
///
/// Cette fonction deplace l'etampe de l'objet qui sera cree avant la
/// creation d'un objet.
/// 
///
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::deplacerEtampe()
{
	for (unsigned int i = 0; i < etampes_.size(); i++) {
		NoeudAbstrait* noeud = etampes_[i];
		zoneJeu_->ajouter(noeud);
	}
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visiter(NoeudComposite * comp)
///
/// Cette fonction visite un noeud pour dupliquer un noeud. Lorsque le
/// visiteur visite un noeud composite, chacun des enfants acceptent le
/// visiteur. 
///
/// @param[in] comp: noeud qu'on visite pour dupliquer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudComposite * comp)
{
	for (unsigned int i = 0; i < comp->obtenirNombreEnfants(); i++) {
		comp->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visiter(NoeudMaillet * ma)
///
/// Cette fonction visite un noeud pour dupliquer un noeud. Lorsque le
/// visiteur visite ce noeud, un noeud identique sera cree
/// visiteur. 
///
/// @param[in] ma: noeud qu'on visite pour dupliquer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudMaillet * ma)
{
	/*NoeudAbstrait* noeud{ arbreAVisiter_->creerNoeud("maillet") };
	NoeudMaillet* nouveauMaillet = dynamic_cast <NoeudMaillet*>(noeud);
	ma->copierAttributs(*nouveauMaillet);
	etampes_.push_back(nouveauMaillet);
	nouveauMaillet->assignerPositionRelative(position_);
	deplacerEtampe();*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visiter(NoeudMuret* m)
///
/// Cette fonction visite un noeud pour dupliquer un noeud. Lorsque le
/// visiteur visite ce noeud, un noeud identique sera cree
/// visiteur. 
///
/// @param[in] m: noeud qu'on visite pour dupliquer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudMuret* m)
{
	NoeudAbstrait* noeud{ arbreAVisiter_->creerNoeud("muret") };
	NoeudMuret* nouveauMuret = dynamic_cast <NoeudMuret*>(noeud);
	m->copierAttributs(*nouveauMuret);
	nouveauMuret->assignerPositionRelative(position_);
	etampes_.push_back(nouveauMuret);
	deplacerEtampe();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visiter(NoeudMuret* p)
///
/// Cette fonction visite un noeud pour dupliquer un noeud. Lorsque le
/// visiteur visite ce noeud, un noeud identique sera cree
/// visiteur. 
///
/// @param[in] p: noeud qu'on visite pour dupliquer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudPortail * p)
{
	if (p->getFrere()->estSelectionne()) {
		NoeudAbstrait* noeud1{ arbreAVisiter_->creerNoeud("portail") };
		NoeudAbstrait* noeud2{ arbreAVisiter_->creerNoeud("portail") };
		NoeudPortail* nouveauPortail1 = dynamic_cast <NoeudPortail*>(noeud1);
		NoeudPortail* nouveauPortail2 = dynamic_cast <NoeudPortail*>(noeud2);
		//p->assignerSelection(false);
		//p->getFrere()->assignerSelection(false);
		//nouveauPortail1->assignerSelection(true);
		//nouveauPortail2->assignerSelection(true);
		nouveauPortail1->setFrere(nouveauPortail2);
		nouveauPortail2->setFrere(nouveauPortail1);
		p->copierAttributs(*nouveauPortail1);
		p->getFrere()->copierAttributs(*nouveauPortail2);
		glm::dvec3 position1 = glm::dvec3(p->obtenirPositionRelative().x, p->obtenirPositionRelative().y, p->obtenirPositionRelative().z);
		glm::dvec3 position2 = glm::dvec3(p->getFrere()->obtenirPositionRelative().x, p->getFrere()->obtenirPositionRelative().y, p->getFrere()->obtenirPositionRelative().z);
		nouveauPortail1->assignerPositionRelative(position1);
		nouveauPortail2->assignerPositionRelative(position2);
		etampes_.push_back(nouveauPortail1);
		etampes_.push_back(nouveauPortail2);
		deplacerEtampe();
	}	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visiter(NoeudMuret* r)
///
/// Cette fonction visite un noeud pour dupliquer un noeud. Lorsque le
/// visiteur visite ce noeud, un noeud identique sera cree
/// visiteur. 
///
/// @param[in] r: noeud qu'on visite pour dupliquer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudRondelle * r)
{
	/*NoeudAbstrait* noeud{ arbreAVisiter_->creerNoeud("rondelle") };
	NoeudRondelle* nouvelleRondelle = dynamic_cast <NoeudRondelle*>(noeud);
	r->copierAttributs(*nouvelleRondelle);
	nouvelleRondelle->assignerPositionRelative(position_);
	etampes_.push_back(nouvelleRondelle);
	deplacerEtampe();*/
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visiter(NoeudBonusAccelerateur * acc)
///
/// Cette fonction visite un noeud pour dupliquer un noeud. Lorsque le
/// visiteur visite ce noeud, un noeud identique sera cree
/// visiteur. 
///
/// @param[in] acc: noeud qu'on visite pour dupliquer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudBonusAccelerateur * acc)
{
	NoeudAbstrait* noeud{ arbreAVisiter_->creerNoeud("bonus") };
	NoeudBonusAccelerateur* nouveauBonus = dynamic_cast <NoeudBonusAccelerateur*>(noeud);
	acc->copierAttributs(*nouveauBonus);
	nouveauBonus->assignerPositionRelative(position_);
	etampes_.push_back(nouveauBonus);
	deplacerEtampe();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visiter(NoeudTable* t)
///
/// Cette fonction visite un noeud pour dupliquer un noeud. Lorsque le
/// visiteur visite ce noeud, un noeud identique sera cree
/// visiteur. 
///
/// @param[in] t: noeud qu'on visite pour dupliquer
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudTable* t)
{
	for (unsigned int i = 0; i < t->obtenirNombreEnfants(); i++) {
		t->chercher(i)->accepterVisiteur(this);
	}
}
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////

