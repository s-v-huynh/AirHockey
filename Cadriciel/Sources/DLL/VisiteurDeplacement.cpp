//////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurDeplacement.h"
#include "Utilitaire.h"
#include "AideGL.h"
#include "GL\gl.h"
#include "GL\glew.h"
#include "GL\glew.h"
#include "GL\wglew.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::VisiteurDeplacement()
///
/// Ce constructeur ne fait que donner une position par defaut pour le
/// deplacement (nul).
///
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::VisiteurDeplacement() {

	glm::dvec3 position_(0, 0, 0);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDeplacement::~VisiteurDeplacement()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDeplacement::~VisiteurDeplacement() {

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::modifierPosition(glm::dvec3 position)
///
/// Cette fonction modifie la variation de la position qui appliquera le
/// deplacement sur l'objet.
///
/// @param[in] position: le deplacement a faire
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::modifierPosition(glm::dvec3 position)
{
	position_ = position;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::visiter(NoeudComposite* noeud)
///
/// Cette fonction visite un noeud pour appliquer le deplacement selon
/// la distance voulu avec l'attribut du visiteur. Le visiteur parcourera
/// le noeud composite et assignera la nouvelle position de l'objet. 
///
/// @param[in] noeud: noeud qu'on visite pour appliquer le deplacement
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudComposite* noeud) {

	for (int i = 0; i < noeud->obtenirEnfants().size(); i++)
	{
		//accept visitor a appeler
		noeud->assignerPositionRelative(position_);
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::visiter(NoeudMaillet* noeud)
///
/// Cette fonction visite un noeud pour appliquer le deplacement selon
/// la distance voulu avec l'attribut du visiteur. Le visiteur visitera
/// le noeud et changera la position de l'objet.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer le deplacement
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudMaillet* noeud) {
	position_ += noeud->obtenirPositionRelative();
	if(noeud->obtenirParent()->curseurEstDansTable(position_*1.04))
		noeud->assignerPositionRelative(position_);
	noeud->modifier();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::visiter(NoeudMuret* noeud)
///
/// Cette fonction visite un noeud pour appliquer le deplacement selon
/// la distance voulu avec l'attribut du visiteur. Le visiteur visitera
/// le noeud et changera la position de l'objet.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer le deplacement
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudMuret* noeud) {
	position_ += noeud->obtenirPositionRelative();
	if (noeud->obtenirParent()->curseurEstDansTable(position_))
		noeud->assignerPositionRelative(position_);
	noeud->modifier();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::visiter(NoeudPortail* noeud)
///
/// Cette fonction visite un noeud pour appliquer le deplacement selon
/// la distance voulu avec l'attribut du visiteur. Le visiteur visitera
/// le noeud et changera la position de l'objet.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer le deplacement
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudPortail* noeud) {
	position_ += noeud->obtenirPositionRelative();
	if (noeud->obtenirParent()->curseurEstDansTable(position_*1.14))
		noeud->assignerPositionRelative(position_);
	noeud->modifier();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::visiter(NoeudRondelle* noeud)
///
/// Cette fonction visite un noeud pour appliquer le deplacement selon
/// la distance voulu avec l'attribut du visiteur. Le visiteur visitera
/// le noeud et changera la position de l'objet.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer le deplacement
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudRondelle* noeud) {
	position_ += noeud->obtenirPositionRelative();
	if (noeud->obtenirParent()->curseurEstDansTable(position_))
		noeud->assignerPositionRelative(position_);
	noeud->modifier();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::visiter(NoeudTable* noeud)
///
/// Cette fonction visite un noeud pour appliquer le deplacement selon
/// la distance voulu avec l'attribut du visiteur. Le visiteur visitera
/// le noeud et changera la position de l'objet.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer le deplacement
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudTable* noeud) {
	//Rien faire
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacement::visiter(NoeudBonusAccelerateur* noeud)
///
/// Cette fonction visite un noeud pour appliquer le deplacement selon
/// la distance voulu avec l'attribut du visiteur. Le visiteur visitera
/// le noeud et changera la position de l'objet.
///
/// @param[in] noeud: noeud qu'on visite pour appliquer le deplacement
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacement::visiter(NoeudBonusAccelerateur* noeud) {
	position_ += noeud->obtenirPositionRelative();
	if (noeud->obtenirParent()->curseurEstDansTable(position_*1.16))
		noeud->assignerPositionRelative(position_);
	noeud->modifier();
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////