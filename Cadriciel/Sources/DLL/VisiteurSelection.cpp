///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @author equipe06
/// @date 2016-09-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "VisiteurSelection.h"
#include <iostream>
#include "FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::visiter(NoeudComposite* noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudComposite
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudComposite* noeud)
{
	//for (NoeudAbstrait const* enfant : noeud->obtenirEnfants)
	//{
	//	//accept visitor a appeler
	//	//enfant->accepterVisiteur(this);
	//}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  VisiteurSelection::visiter(NoeudPortail* noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudPortail
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void  VisiteurSelection::visiter(NoeudPortail* noeud)
{
		if (noeud->estSelectionnable() && noeud->verifierSelection(couleurObjet_)) // si le noeud est touche
		{
			if (selectionunique_)
			{

				noeud->obtenirParent()->deselectionnerTout();
				noeud->assignerSelection(true);
				selectionexiste_ = true;
			}
			else
			{
				if (noeud->obtenirParent()->selectionExiste())
				{
					noeud->obtenirParent()->deselectionnerTout();
				}
				else
				{
					noeud->obtenirParent()->selectionnerTout();
					selectionexiste_ = true;
				}
				//noeud.obtenirParent()->assignerEstVisite(true);
			}
		}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::visiter(NoeudMuret* noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudMuret.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudMuret* noeud)
{

		//cout << "Seigneur:: " << (int)couleurObjet_[0] << (int)couleurObjet_[1] << (int)couleurObjet_[2] << endl;

		if (noeud->estSelectionnable() && noeud->verifierSelection(couleurObjet_)) // si le noeud est touche
		{

			if (selectionunique_)
			{
				noeud->obtenirParent()->deselectionnerTout();
				noeud->assignerSelection(true);
				selectionexiste_ = true;
			}
			else
				noeud->inverserSelection();
		}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::visiter(NoeudBonusAccelerateur* noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudBonusAccelerateur.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudBonusAccelerateur* noeud)
{

		if (noeud->estSelectionnable() && noeud->verifierSelection(couleurObjet_)) // si le noeud est touche
		{

			if (selectionunique_)
			{
				noeud->obtenirParent()->deselectionnerTout();
				noeud->assignerSelection(true);
				selectionexiste_ = true;
			}
			else
				noeud->inverserSelection();
		}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::visiter(NoeudMaillet* noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudMaillet.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudMaillet* noeud)
{

		if (noeud->estSelectionnable() && noeud->verifierSelection(couleurObjet_)) // si le noeud est touche
		{

			if (selectionunique_)
			{
				noeud->obtenirParent()->deselectionnerTout();
				noeud->assignerSelection(true);
				selectionexiste_ = true;
			}
			else
				noeud->inverserSelection();
		}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::vvisiter(NoeudMailletVirtuel* noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudMailletVirtuel.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudMailletVirtuel* noeud)
{

		if (noeud->estSelectionnable() && noeud->verifierSelection(couleurObjet_)) // si le noeud est touche
		{

			if (selectionunique_)
			{
				noeud->obtenirParent()->deselectionnerTout();
				noeud->assignerSelection(true);
				selectionexiste_ = true;
			}
			else
				noeud->inverserSelection();
		}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::visiter(NoeudRondelle* noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudRondelle.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudRondelle* noeud)
{

		if (noeud->estSelectionnable() && noeud->verifierSelection(couleurObjet_)) // si le noeud est touche
		{

			if (selectionunique_)
			{
				noeud->obtenirParent()->deselectionnerTout();
				noeud->assignerSelection(true);
				selectionexiste_ = true;
			}
			else
				noeud->inverserSelection();
		}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::visiter(NoeudTable* noeud)
///
/// Cette methode permet d'appliquer l'algorithme de selection
/// à un objet de la classe NoeudTable.
///
/// @param[in] noeud : le noeud en question.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
//void VisiteurSelection::visiter(NoeudTable* noeud)
//{
//
//}

////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
