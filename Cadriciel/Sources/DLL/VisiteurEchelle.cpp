//////////////////////////////////////////////////////////////////////////
/// @file VisiteurEchelle.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurEchelle.h"
#include "NoeudTypes.h"
double grand = 1.01;
double petit = 0.99;

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurEchelle::VisiteurEchelle(double facteur)
///
/// Ce constructeur assigne le facteur de la mise a l'echelle.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurEchelle::VisiteurEchelle(double facteur)
{
	facteur_ = facteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurEchelle::~VisiteurEchelle()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurEchelle::~VisiteurEchelle()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEchelle::modifierFacteur(double facteur)
///
/// Cette fonction modifie le facteur de la mise a l'echelle de l'objet
/// 
///
/// @param[in] facteur: nouveau facteur
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEchelle::modifierFacteur(double facteur)
{
	facteur_ = facteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double VisiteurEchelle::obtenirFacteur()
///
/// Obtenir le facteur de la mise a l'echelle
/// 
///
///
/// @return le facteur de la mise a echelle courant
///
////////////////////////////////////////////////////////////////////////
double VisiteurEchelle::obtenirFacteur()
{
	return facteur_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::visiter(NoeudComposite* noeud)
///
/// On ne fait rien lorsqu'on visite le noeud composite, puisque le
/// comportement est le meme pour tous les objets. Donc, chaque noeud 
/// accepte individuellement chaque visiteur.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer le deplacement
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEchelle::visiter(NoeudComposite* noeud)
{
	//for (NoeudAbstrait const* enfant : noeud->obtenirEnfants)
	//{
	//	//accept visitor a appeler
	//	//enfant->accepterVisiteur(this);
	//}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEchelle::visiter(NoeudMaillet* noeud)
///
/// Lorsqu'on visite le noeud, la taille de l'objet est modifiee selon
/// le facteur de la mise a echelle.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer la mise a 
///						l'echelle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEchelle::visiter(NoeudMaillet* noeud)
{
	if (facteur_ == grand || facteur_ == petit)
	{
		noeud->modifierRayonMaillet(noeud->obtenirRayonMaillet() * facteur_);
		noeud->modifierFacteurEchelle(noeud->obtenirRayonMaillet());
		noeud->modifier();
	}
	else
	{
		noeud->modifierRayonMaillet(noeud->obtenirFacteurEchelle());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEchelle::visiter(NoeudMuret * noeud)
///
/// Lorsqu'on visite le noeud, la taille de l'objet est modifiee selon
/// le facteur de la mise a echelle.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer la mise a 
///						l'echelle
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEchelle::visiter(NoeudMuret * noeud)
{
	if (facteur_ == grand || facteur_ == petit)
	{
		noeud->modifierLongueurMuret(noeud->obtenirLongueurMuret() * facteur_);
		noeud->modifierFacteurEchelle(noeud->obtenirLongueurMuret());
		noeud->modifier();
	}
	else
	{
		noeud->modifierLongueurMuret(noeud->obtenirFacteurEchelle());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEchelle::visiter(NoeudPortail * noeud)
///
/// Lorsqu'on visite le noeud, la taille de l'objet est modifiee selon
/// le facteur de la mise a echelle.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer la mise a 
///						l'echelle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEchelle::visiter(NoeudPortail * noeud)
{

	if (facteur_ == grand || facteur_ == petit)
	{
		noeud->modifierRayon(noeud->obtenirRayon() * facteur_);
		noeud->modifierFacteurEchelle(noeud->obtenirRayon());
		noeud->modifier();
	}
	else
	{
		noeud->modifierRayon(noeud->obtenirFacteurEchelle());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEchelle::visiter(NoeudRondelle * noeud)
///
/// Lorsqu'on visite le noeud, la taille de l'objet est modifiee selon
/// le facteur de la mise a echelle.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer la mise a 
///						l'echelle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEchelle::visiter(NoeudRondelle * noeud)
{
	if (facteur_ == grand || facteur_ == petit)
	{
		noeud->modifierRayonRondelle(noeud->obtenirRayonRondelle() * facteur_);
		noeud->modifierFacteurEchelle(noeud->obtenirRayonRondelle());
		noeud->modifier();
	}
	else
	{
		noeud->modifierRayonRondelle(noeud->obtenirFacteurEchelle());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEchelle::visiter(NoeudTable * noeud)
///
/// On ne fait rien, puisque la taille de la table est constante
///
/// @param[in] noeud: noeud qu'on visite pour appliquer la mise a 
///						l'echelle
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEchelle::visiter(NoeudTable * noeud)
{
	//NE PAS TOUCHER
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEchelle::visiter(NoeudBonusAccelerateur * noeud)
///
/// Lorsqu'on visite le noeud, la taille de l'objet est modifiee selon
/// le facteur de la mise a echelle.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer la mise a 
///						l'echelle
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEchelle::visiter(NoeudBonusAccelerateur * noeud)
{
	if (facteur_ == grand || facteur_ == petit)
	{
		noeud->modifierRayonBonusAccelerateur(noeud->obtenirRayonBonusAccelerateur() * facteur_);
		noeud->modifierFacteurEchelle(noeud->obtenirRayonBonusAccelerateur());
		noeud->modifier();
	}
	else
	{
		noeud->modifierRayonBonusAccelerateur(noeud->obtenirFacteurEchelle());
	}
}
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////