///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeud.h"
#include "UsineNoeudPortail.h"
#include "UsineNoeudTable.h"
#include "UsineNoeudMaillet1.h"
#include "UsineNoeudMailletVirtuel.h"
#include "UsineNoeudMuret.h"
#include "UsineNoeudBonusAccelerateur.h"
#include "UsineNoeudRondelle.h"
#include "UsineNoeudCercle.h"
#include "FacadeModele.h"

#include "EtatOpenGL.h"
#include "Noeuds/NoeudTypes.h"
#include <cmath>


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };
/// La chaîne représentant le type de table.
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
/// La chaîne représentant le type de rondelle.
const std::string ArbreRenduINF2990::NOM_RONDELLE{ "rondelle" };
/// La chaîne représentant le type de maillet.
const std::string ArbreRenduINF2990::NOM_MAILLET_1{ "maillet" };
const std::string ArbreRenduINF2990::NOM_MAILLET_V{ "mailletV" };
const std::string ArbreRenduINF2990::NOM_MAILLET_2{ "maillet2" };

/// La chaîne représentant le type de bonus.
const std::string ArbreRenduINF2990::NOM_BONUS{ "bonus" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_MURET{ "muret" };
const std::string ArbreRenduINF2990::NOM_CERCLE{ "cercle" };





////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	//ajouterUsine(NOM_TABLE, new UsineNoeud<NoeudTable>{ NOM_TABLE, std::string{ "media/table7.obj" } });
	//ajouterUsine(NOM_PORTAIL, new UsineNoeud<NoeudPortail>{ NOM_PORTAIL, std::string{ "media/portail1.obj" } });
	//ajouterUsine(NOM_PORTAIL_SELECTIONNE, new UsineNoeud<NoeudPortail>{ NOM_PORTAIL_SELECTIONNE, std::string{ "media/portail2.obj" } });
	//ajouterUsine(NOM_MAILLET_1, new UsineNoeud<NoeudMaillet>{ NOM_MAILLET_1, std::string{ "media/maillet.obj" } });
	//ajouterUsine(NOM_MAILLET_2, new UsineNoeud<NoeudMaillet>{ NOM_MAILLET_2, std::string{ "media/maillet1.obj" } });
	//ajouterUsine(NOM_BONUS, new UsineNoeud<NoeudBonusAccelerateur>{ NOM_BONUS, std::string{ "media/accelerator2.obj" } });


	//ajouterUsine(NOM_MURET, new UsineNoeud<NoeudMuret>{ NOM_MURET, std::string{ "media/maillet.obj" } });
	//NoeudAbstrait* noeudPortailSelect = creerNoeud(NOM_PORTAIL_SELECTIONNE);
	//listObjetSelecitonne[NOM_PORTAIL] = noeudPortailSelect->obtenirVBO();

	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail(NOM_PORTAIL));
	ajouterUsine(NOM_TABLE, new UsineNoeudTable(NOM_TABLE));
	ajouterUsine(NOM_MAILLET_1, new UsineNoeudMaillet1(NOM_MAILLET_1));
	ajouterUsine(NOM_MAILLET_2, new UsineNoeudMaillet1(NOM_MAILLET_2));

	ajouterUsine(NOM_MAILLET_V, new UsineNoeudMailletVirtuel(NOM_MAILLET_V));
	ajouterUsine(NOM_BONUS, new UsineNoeudBonusAccelerateur(NOM_BONUS));
	ajouterUsine(NOM_MURET, new UsineNoeudMuret(NOM_MURET));
	ajouterUsine(NOM_RONDELLE, new UsineNoeudRondelle(NOM_RONDELLE));
	ajouterUsine(NOM_CERCLE, new UsineNoeudCercle(NOM_CERCLE));

	supprimer_ = new VisiteurSuppression();
	continuer_ = true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	// On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
	NoeudAbstrait* maillet1{ creerNoeud(NOM_MAILLET_1) };
	 maillet2_=creerNoeud(NOM_MAILLET_2) ;
	 mailletVir_=creerNoeud(NOM_MAILLET_V);
	NoeudAbstrait* rondelle{ creerNoeud(NOM_RONDELLE) };

	zoneJeux_ = { creerNoeud(NOM_TABLE) };
	zoneJeux_->modifierId(1);
	ajouter(zoneJeux_);
	zoneJeux_->ajouter(maillet1);
	maillet1->modifierId(2);
	maillet1->assignerPositionRelative(glm::dvec3(zoneJeux_->obtenirSommets()[5].x + 5.0, 0.0, 0.0));
	maillet1->assignerPositionInitial(glm::dvec3(zoneJeux_->obtenirSommets()[5].x + 5.0, 0.0, 0.0));
	zoneJeux_->ajouter(rondelle);
	rondelle->assignerPositionRelative(glm::dvec3(0.0, 0.0, 0.0));
	zoneJeux_->ajouter(mailletVir_);
	mailletVir_->modifierId(3);
	mailletVir_->assignerPositionRelative(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
	mailletVir_->assignerPositionInitial(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
	//cout << "--------------------------------" << endl;
	
	/*float rayon = utilitaire::calculerSphereEnglobante(*rondelle->obtenirModele()).rayon;
	rondelle->modifierRayon(rayon );*/
}
void ArbreRenduINF2990::initialiserPartieAvecVirtuel()
{

		zoneJeux_->ajouter(mailletVir_);
		mailletVir_->modifierId(3);
		mailletVir_->assignerPositionRelative(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
		mailletVir_->assignerPositionInitial(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
}
void ArbreRenduINF2990::initialiserPartieAvecHumain()

{
	zoneJeux_->ajouter(maillet2_);
	maillet2_->modifierId(3);
	maillet2_->assignerPositionRelative(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
	maillet2_->assignerPositionInitial(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
}
int ArbreRenduINF2990::ajouterNouveauElement(const std::string& nomObjet, glm::dvec3 positionR)
{
	NoeudAbstrait* nouveauNoeud{ creerNoeud(nomObjet) };
    if (nomObjet == "portail") {
        NoeudPortail* noeud = dynamic_cast<NoeudPortail*>(nouveauNoeud);
		NoeudAbstrait* cercle{ creerNoeud("cercle") };
		nouveauNoeud->ajouter(cercle);
		noeud->assignerCercle(dynamic_cast<NoeudCercle*>(cercle));
        listePortail_.push_back(make_pair(noeud, nullptr));
    }
    nouveauNoeud->modifierId(obtenirProchainId() + 1);
	modifierProchainId(obtenirProchainId() + 1);
	//nouveauNoeud->assignerSelection(true);
	nouveauNoeud->assignerPositionRelative(positionR);
	nouveauNoeud->redefinirSommets();
	nouveauNoeud->modifierVBO(listObjetSelecitonne[nomObjet]);
	if (nouveauNoeud->obtenirId() != 0)
		zoneJeux_->ajouter(nouveauNoeud);
	if (!nouveauNoeud->estDansLaTable()) {
		nouveauNoeud->obtenirParent()->effacer(nouveauNoeud);
		continuer_ = false;
	}
	return (obtenirProchainId() - 1);
}
int ArbreRenduINF2990::ajouterNouveauPortail(const std::string& nomObjet, glm::dvec3 positionR)
{
	if (continuer_) {
    NoeudAbstrait* nouveauNoeud{ creerNoeud(nomObjet) };
    NoeudPortail* noeud = dynamic_cast<NoeudPortail*>(nouveauNoeud);
	NoeudAbstrait* cercle{ creerNoeud("cercle") };
	nouveauNoeud->ajouter(cercle);
	noeud->assignerCercle(dynamic_cast<NoeudCercle*>(cercle));
    listePortail_.back().second = noeud;
    listePortail_.back().second->setFrere(listePortail_.back().first);
    listePortail_.back().first->setFrere(noeud);
    nouveauNoeud->modifierId(obtenirProchainId() + 1);
    modifierProchainId(obtenirProchainId() + 1);
    nouveauNoeud->assignerPositionRelative(positionR);
	nouveauNoeud->redefinirSommets();
    nouveauNoeud->modifierVBO(listObjetSelecitonne[nomObjet]);
    nouveauNoeud->assignerSelection(true);
    if (nouveauNoeud->obtenirId() != 0)
        zoneJeux_->ajouter(nouveauNoeud);
		if (!nouveauNoeud->estDansLaTable()) {
			nouveauNoeud->obtenirParent()->effacer(noeud->getFrere());
			nouveauNoeud->obtenirParent()->effacer(nouveauNoeud);
		}
    return (obtenirProchainId() - 1);
}
	continuer_ = true;
	return 0;
	
}
void ArbreRenduINF2990::ajouterPairePortails(NoeudAbstrait * noeud)
{
	NoeudPortail * portail = dynamic_cast<NoeudPortail*>(noeud);
	if (portail->getFrere() != nullptr)
		listePortail_.push_back(make_pair(portail, portail->getFrere()));
}
void ArbreRenduINF2990::marquerSelection(int identifiant, bool enInverse) {
	NoeudAbstrait* noeud = zoneJeux_->chercher(identifiant);
	if (enInverse) {
		noeud->assignerEstSelectionnable(enInverse);
		noeud->assignerSelection(!noeud->estSelectionne());
	}
	else {
		zoneJeux_->deselectionnerTout();
		noeud->assignerSelection(!noeud->estSelectionne());
	}

}

void ArbreRenduINF2990::assignerZoneJeux(NoeudAbstrait * zone)
{
	zoneJeux_ = zone;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
