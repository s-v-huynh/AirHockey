//////////////////////////////////////////////////////////////////////////
/// @file VisiteurEcritureXML.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "VisiteurEcritureXML.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "tinyxml2.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurEcritureXML::VisiteurEcritureXML
///		(tinyxml2::XMLElement * racine)
///
/// Le constructeur du visiteur assigne une racine, qui est un element
/// XML. Les noeuds seront ajoutes comme enfants de cette racine.
///
/// @param[in] racine: Element XML qui est la racine de l'arbre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurEcritureXML::VisiteurEcritureXML(tinyxml2::XMLElement * racine)
{
	racine_ = racine;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurEcritureXML::~VisiteurEcritureXML()
///
/// Le destructeur met la racine a un pointeur nul
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurEcritureXML::~VisiteurEcritureXML()
{
	racine_ = NULL;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEcritureXML::visiter(NoeudComposite * noeud)
///
/// Le visiteur visite le noeud et cree un noeud XML avec les attributs
/// du noeud. Il est ensuite ajoute a la racine du fichier XML. 
///
/// @param[in] noeud: noeud qu'on prend pour creer un noeud XML
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEcritureXML::visiter(NoeudComposite * noeud)
{
	tinyxml2::XMLElement* enfant = (racine_->GetDocument())->NewElement("enfant");


	enfant->SetName(noeud->obtenirType().c_str());
	enfant->SetAttribute("X", noeud->obtenirPositionRelative()[0]);
	enfant->SetAttribute("Y", noeud->obtenirPositionRelative()[1]);
	enfant->SetAttribute("Z", noeud->obtenirPositionRelative()[2]);
	enfant->SetAttribute("ANGLE_ROTATION", noeud->obtenirAngleRotation());
	racine_->LinkEndChild(enfant);
	racine_ = enfant;

	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}


}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEcritureXML::visiter(NoeudMaillet * noeud)
///
/// Le visiteur visite le noeud et cree un noeud XML avec les attributs
/// du noeud. Il est ensuite ajoute a la racine du fichier XML. 
///
/// @param[in] noeud: noeud qu'on prend pour creer un noeud XML
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEcritureXML::visiter(NoeudMaillet * noeud)
{
	//tinyxml2::XMLElement* enfant = (racine_->GetDocument())->NewElement("enfant");
	//enfant->SetName(noeud->obtenirType().c_str());
	//enfant->SetAttribute("X", noeud->obtenirPositionRelative()[0]);
	//enfant->SetAttribute("Y", noeud->obtenirPositionRelative()[1]);
	//enfant->SetAttribute("Z", noeud->obtenirPositionRelative()[2]);
	//enfant->SetAttribute("ANGLE_ROTATION", noeud->obtenirAngleRotation());
	//enfant->SetAttribute("FACTEUR_ECHELLE", noeud->obtenirFacteurEchelle());
	//enfant->SetAttribute("RAYON_MAILLET", noeud->obtenirRayonMaillet());

	////Attributs a ajouter
	//racine_->LinkEndChild(enfant);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEcritureXML::visiter(NoeudMuret * noeud)
///
/// Le visiteur visite le noeud et cree un noeud XML avec les attributs
/// du noeud. Il est ensuite ajoute a la racine du fichier XML. 
///
/// @param[in] noeud: noeud qu'on prend pour creer un noeud XML
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEcritureXML::visiter(NoeudMuret * noeud)
{
	tinyxml2::XMLElement* enfant = (racine_->GetDocument())->NewElement("enfant");
	enfant->SetName(noeud->obtenirType().c_str());
	enfant->SetAttribute("X", noeud->obtenirPositionRelative()[0]);
	enfant->SetAttribute("Y", noeud->obtenirPositionRelative()[1]);
	enfant->SetAttribute("Z", noeud->obtenirPositionRelative()[2]);
	enfant->SetAttribute("FACTEUR_ECHELLE", noeud->obtenirFacteurEchelle());
	enfant->SetAttribute("ANGLE_ROTATION", noeud->obtenirAngleRotation());
	enfant->SetAttribute("LONGUEUR", noeud->obtenirLongueurMuret());
	enfant->SetAttribute("SOMMET1_X", noeud->obtenirSommets()[0].x);
	enfant->SetAttribute("SOMMET1_Y", noeud->obtenirSommets()[0].y);
	enfant->SetAttribute("SOMMET2_X", noeud->obtenirSommets()[1].x);
	enfant->SetAttribute("SOMMET2_Y", noeud->obtenirSommets()[1].y);
	//Attributs a ajouter
	racine_->LinkEndChild(enfant);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEcritureXML::visiter(NoeudPortail * noeud)
///
/// Le visiteur visite le noeud et cree un noeud XML avec les attributs
/// du noeud. Il est ensuite ajoute a la racine du fichier XML. 
///
/// @param[in] noeud: noeud qu'on prend pour creer un noeud XML
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEcritureXML::visiter(NoeudPortail * noeud)
{
	tinyxml2::XMLElement* enfant = (racine_->GetDocument())->NewElement("enfant");
	enfant->SetName(noeud->obtenirType().c_str());
	enfant->SetAttribute("X", noeud->obtenirPositionRelative()[0]);
	enfant->SetAttribute("Y", noeud->obtenirPositionRelative()[1]);
	enfant->SetAttribute("Z", noeud->obtenirPositionRelative()[2]);
	enfant->SetAttribute("ANGLE_ROTATION", noeud->obtenirAngleRotation());
	enfant->SetAttribute("RAYON", noeud->obtenirRayon());
	enfant->SetAttribute("ATTRACTION", noeud->obtenirAttraction());
	enfant->SetAttribute("FACTEUR_ECHELLE", noeud->obtenirFacteurEchelle());
	enfant->SetAttribute("X1", noeud->getFrere()->obtenirPositionRelative()[0]);
	enfant->SetAttribute("Y1", noeud->getFrere()->obtenirPositionRelative()[1]);
	enfant->SetAttribute("Z1", noeud->getFrere()->obtenirPositionRelative()[2]);
	enfant->SetAttribute("ANGLE_ROTATION1", noeud->getFrere()->obtenirAngleRotation());
	enfant->SetAttribute("RAYON1", noeud->getFrere()->obtenirRayon());
	enfant->SetAttribute("ATTRACTION1", noeud->getFrere()->obtenirAttraction());
	enfant->SetAttribute("FACTEUR_ECHELLE1", noeud->getFrere()->obtenirFacteurEchelle());
	//Attributs a ajouter
	racine_->LinkEndChild(enfant);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEcritureXML::visiter(NoeudRondelle * noeud)
///
/// Le visiteur visite le noeud et cree un noeud XML avec les attributs
/// du noeud. Il est ensuite ajoute a la racine du fichier XML. 
///
/// @param[in] noeud: noeud qu'on prend pour creer un noeud XML
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEcritureXML::visiter(NoeudRondelle * noeud)
{
	//tinyxml2::XMLElement* enfant = (racine_->GetDocument())->NewElement("enfant");
	//enfant->SetName(noeud->obtenirType().c_str());
	//enfant->SetAttribute("X", noeud->obtenirPositionRelative()[0]);
	//enfant->SetAttribute("Y", noeud->obtenirPositionRelative()[1]);
	//enfant->SetAttribute("Z", noeud->obtenirPositionRelative()[2]);
	//enfant->SetAttribute("FACTEUR_ECHELLE", noeud->obtenirFacteurEchelle());
	//enfant->SetAttribute("ANGLE_ROTATION", noeud->obtenirAngleRotation());
	//enfant->SetAttribute("RAYON_RONDELLE", noeud->obtenirRayonRondelle());
	////Attributs a ajouter
	//racine_->LinkEndChild(enfant);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEcritureXML::visiter(NoeudTable * noeud)
///
/// Le visiteur visite le noeud et cree un noeud XML avec les attributs
/// du noeud. Il est ensuite ajoute a la racine du fichier XML. 
///
/// @param[in] noeud: noeud qu'on prend pour creer un noeud XML
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEcritureXML::visiter(NoeudTable * noeud)
{
	tinyxml2::XMLElement* enfant = (racine_->GetDocument())->NewElement("enfant");
	enfant->SetName(noeud->obtenirType().c_str());



	//enfant->SetAttribute("PT_C_X0", )

	/*enfant->SetAttribute("X", noeud->obtenirPositionRelative()[0]);
	enfant->SetAttribute("Y", noeud->obtenirPositionRelative()[1]);
	enfant->SetAttribute("Z", noeud->obtenirPositionRelative()[2]);
	enfant->SetAttribute("ANGLE_ROTATION", noeud->obtenirAngleRotation());
	enfant->SetAttribute("FACTEUR_ECHELLE", noeud->obtenirFacteurEchelle());
	enfant->SetAttribute("ACCELERATION", noeud->obtenirAcceleration());
	enfant->SetAttribute("COEFFICIENT_REBONDISSEMENT", noeud->obtenirCoefRebondissement());
	enfant->SetAttribute("COEFFICIENT_FRICTION", noeud->obtenirFriction());
	racine_->LinkEndChild(enfant);
	racine_ = enfant;*/

	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurEcritureXML::visiter(NoeudBonusAccelerateur * noeud)
///
/// Le visiteur visite le noeud et cree un noeud XML avec les attributs
/// du noeud. Il est ensuite ajoute a la racine du fichier XML. 
///
/// @param[in] noeud: noeud qu'on prend pour creer un noeud XML
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void VisiteurEcritureXML::visiter(NoeudBonusAccelerateur * noeud)
{
	tinyxml2::XMLElement* enfant = (racine_->GetDocument())->NewElement("enfant");
	enfant->SetName(noeud->obtenirType().c_str());
	enfant->SetAttribute("X", noeud->obtenirPositionRelative()[0]);
	enfant->SetAttribute("Y", noeud->obtenirPositionRelative()[1]);
	enfant->SetAttribute("Z", noeud->obtenirPositionRelative()[2]);
	enfant->SetAttribute("FACTEUR_ECHELLE", noeud->obtenirFacteurEchelle());
	enfant->SetAttribute("ANGLE_ROTATION", noeud->obtenirAngleRotation());
	//enfant->SetAttribute("RAYON_ACCELERATEUR", noeud->obtenirRayonBonusAccelerateur());
	racine_->LinkEndChild(enfant);
	racine_ = enfant;
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
