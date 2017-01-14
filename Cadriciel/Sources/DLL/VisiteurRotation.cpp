///////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "VisiteurRotation.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation()
///
///	Initialise les variables de la classe par defaut
///
/// @return Aucune (constructeur par defaut).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation()
{
	centreRotation_ = 0;
	varY_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation(float centreX, float centreY, float varY)
///
/// Initialisation des membres de la classe
///
/// @param[in] centreX: centre de l'objet sur l'axe des X
/// @param[in] centreY: centre de l'objet sur l'axe des Y
/// @param[in] varY: Variation en Y de la souris qui variera l'angle de
/// rotation de l'objet
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation(float centreX, float centreY, float varY)
{
	centreRotation_->X = centreX;
	centreRotation_->Y = centreY;
	varY_ = varY;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn float VisiteurRotation::obtenirCentreX()
///
/// Cette fonction retourne la coordonnée en X du centre de rotation
/// de l'objet
///
/// @return La valeur de la coordonnee en X du centre de l'objet
///
////////////////////////////////////////////////////////////////////////

float VisiteurRotation::obtenirCentreX()
{
	return centreRotation_->X;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn float VisiteurRotation::obtenirCentreY()
///
/// Cette fonction retourne la coordonnée en Y du centre de rotation
/// de l'objet
///
/// @return La valeur de la coordonnee en Y du centre de l'objet
///
////////////////////////////////////////////////////////////////////////
float VisiteurRotation::obtenirCentreY()
{
	return centreRotation_->Y;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn float VisiteurRotation::obtenirVarY()
///
/// Cette fonction retourne la variation en Y qui sera utilisée
/// pour modifier l'angle de rotation de l'objet
///
///
/// @return la variation en Y de la souris lorsqu'elle bouge
///
////////////////////////////////////////////////////////////////////////
float VisiteurRotation::obtenirVarY()
{
	return varY_;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::modifierCentre(float X, float Y)
///
/// Cette fonction modifie les coordonnées en X et Y du centre de
/// rotation de l'objet en question
///
///@param[in] X: Valeur qui modifie la coordonnee en X
///@param[in] Y: Valeur qui modifie la coordonnee en Y
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::modifierCentre(float X, float Y)
{
	centreRotation_->X = X;
	centreRotation_->Y = Y;

}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::modifierCentre(float X, float Y)
///
/// Cette fonction modifie la variation en Y de la souris
/// 
/// La variation de la souris sera mis en paramètre de cette fonction
/// pour permettre la variation de l'angle de rotation selon les 
/// mouvements de la souris
///
///@param[in] X: Valeur qui modifie la coordonnee en X
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::modifierVarY(float varY)
{
	varY_ = varY;
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudComposite * noeud)
///
/// Cette fonction effectue une rotation sur les enfants d'un noeud composite 
///
/// Un centre de rotation est calcule selon la position relative des enfants
///
///@param[in] noeud: Noeud Composite que le visiteur visitera pour effectuer
/// la modification d'angle pour chacun des enfants
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudComposite * noeud)
{

	glm::dvec3 position;
	glm::vec3 centreComposite;
	std::vector<glm::dvec3> positionInitiale;
	double minX = 0;
	double minY = 0;
	double maxX = 0;
	double maxY = 0;
	NoeudAbstrait* enfant;
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->obtenirEnfants()[i];
		//if (enfant->estSelectionne())
		//{
		position = enfant->obtenirPositionRelative();
		positionInitiale.push_back(enfant->obtenirPositionRelative());
		if (position[0] < minX)
			minX = position[0];
		if (position[0] > maxX)
			maxX = position[0];
		if (position[1] < minY)
			minY = position[1];
		if (position[1] > maxY)
			maxY = position[1];

		//}
	}

	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->obtenirEnfants()[i];
		//if (enfant->estSelectionne()) {
			centreComposite[0] = ((maxX + minX) / 2) - positionInitiale[i][0];
			centreComposite[1] = ((maxY + minY) / 2) - positionInitiale[i][1];
			enfant->modifierCentreRotation(centreComposite);

			enfant->accepterVisiteur(this);
			enfant->assignerPositionRelative(positionInitiale[i]);
		//}
	}
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudMaillet * noeud)
///
/// Le noeud visité subira une modification à son angle de rotation
///
///@param[in] noeud: Noeud que le visiteur visitera pour effectuer
/// la modification d'angle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudMaillet * noeud)
{
	float angleRotation = noeud->obtenirAngleRotation();
	angleRotation += varY_;
	if (angleRotation >= 360.0f)
		angleRotation -= 360.0f;
	else if (angleRotation < -360.0f)
		angleRotation += 360.0f;
	noeud->modifierAngleRotation(angleRotation);
	noeud->modifier();
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudMuret * noeud)
///
/// Le noeud visité subira une modification à son angle de rotation
///
///@param[in] noeud: Noeud que le visiteur visitera pour effectuer
/// la modification d'angle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudMuret * noeud)
{
	float angleRotation = noeud->obtenirAngleRotation();
	angleRotation = angleRotation + varY_;
	if (angleRotation >= 360.0f)
		angleRotation -= 360.0f;
	else if (angleRotation < -360.0f)
		angleRotation += 360.0f;
	noeud->modifierAngleRotation(angleRotation);
	noeud->modifier();
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudPortail * noeud)
///
/// Le noeud visité subira une modification à son angle de rotation
///
///@param[in] noeud: Noeud que le visiteur visitera pour effectuer
/// la modification d'angle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudPortail * noeud)
{
	float angleRotation = noeud->obtenirAngleRotation();
	angleRotation = angleRotation + varY_;
	if (angleRotation >= 360.0f)
		angleRotation -= 360.0f;
	else if (angleRotation < -360.0f)
		angleRotation += 360.0f;
	noeud->modifierAngleRotation(angleRotation);
	noeud->modifier();
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudRondelle * noeud)
///
/// Le noeud visité subira une modification à son angle de rotation
///
///@param[in] noeud: Noeud que le visiteur visitera pour effectuer
/// la modification d'angle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudRondelle * noeud)
{
	float angleRotation = noeud->obtenirAngleRotation();
	angleRotation += varY_;
	if (angleRotation >= 360.0f)
		angleRotation -= 360.0f;
	else if (angleRotation < -360.0f)
		angleRotation += 360.0f;
	noeud->modifierAngleRotation(angleRotation);
	noeud->modifier();
}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudTable * noeud)
///
/// Le noeud visité subira une modification à son angle de rotation
///
///@param[in] noeud: Noeud que le visiteur visitera pour effectuer
/// la modification d'angle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudTable * noeud)
{

	glm::dvec3 position;
	glm::vec3 centreComposite;
	std::vector<glm::dvec3> positionInitiale;
	double minX = 0;
	double minY = 0;
	double maxX = 0;
	double maxY = 0;
	NoeudAbstrait* enfant;
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->obtenirEnfants()[i];
		//std::cout << "Type enfant visiteur rotation: " << enfant->obtenirType() << std::endl;
		//if (enfant->estSelectionne())
		//{
		position = enfant->obtenirPositionRelative();
		positionInitiale.push_back(enfant->obtenirPositionRelative());
		if (position[0] < minX)
			minX = position[0];
		if (position[0] > maxX)
			maxX = position[0];
		if (position[1] < minY)
			minY = position[1];
		if (position[1] > maxY)
			maxY = position[1];

		//}
	}

	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->obtenirEnfants()[i];
		centreComposite[0] = ((maxX + minX) / 2) - positionInitiale[i][0];
		centreComposite[1] = ((maxY + minY) / 2) - positionInitiale[i][1];
		enfant->modifierCentreRotation(centreComposite);
		//std::cout << "Centre de rotation" << centreComposite[0] << "\t" << centreComposite[1] << std::endl;

		enfant->accepterVisiteur(this);
		enfant->assignerPositionRelative(positionInitiale[i]);
	}

}

///////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiter(NoeudBonusAccelerateur * noeud)
///
/// Le noeud visité subira une modification à son angle de rotation
///
///@param[in] noeud: Noeud que le visiteur visitera pour effectuer
/// la modification d'angle
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudBonusAccelerateur * noeud)
{
	float angleRotation = noeud->obtenirAngleRotation();
	angleRotation += varY_;
	if (angleRotation >= 360.0f)
		angleRotation -= 360.0f;
	else if (angleRotation < -360.0f)
		angleRotation += 360.0f;
	noeud->modifierAngleRotation(angleRotation);
	//noeud->modifier();
}
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////