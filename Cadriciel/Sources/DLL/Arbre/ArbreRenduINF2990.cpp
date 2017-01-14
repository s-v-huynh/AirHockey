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
#include "UsinePointControl.h"

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
const std::string ArbreRenduINF2990::NOM_POINTCONTROL_0{ "point0" }; const std::string ArbreRenduINF2990::NOM_POINTCONTROL_1{ "point1" };
const std::string ArbreRenduINF2990::NOM_POINTCONTROL_2{ "point2" }; const std::string ArbreRenduINF2990::NOM_POINTCONTROL_3{ "point3" };
const std::string ArbreRenduINF2990::NOM_POINTCONTROL_4{ "point4" }; const std::string ArbreRenduINF2990::NOM_POINTCONTROL_5{ "point5" };
const std::string ArbreRenduINF2990::NOM_POINTCONTROL_6{ "point6" }; const std::string ArbreRenduINF2990::NOM_POINTCONTROL_7{ "point7" };
const std::string ArbreRenduINF2990::NOM_POINTCONTROL_8{ "point8" }; const std::string ArbreRenduINF2990::NOM_POINTCONTROL{ "poin" };





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

	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail(NOM_PORTAIL));
	ajouterUsine(NOM_TABLE, new UsineNoeudTable(NOM_TABLE));
	ajouterUsine(NOM_MAILLET_1, new UsineNoeudMaillet1(NOM_MAILLET_1));
	ajouterUsine(NOM_MAILLET_2, new UsineNoeudMaillet1(NOM_MAILLET_2));
	ajouterUsine(NOM_POINTCONTROL, new UsinePointControl(NOM_POINTCONTROL));
	ajouterUsine(NOM_POINTCONTROL_0, new UsinePointControl(NOM_POINTCONTROL_0));ajouterUsine(NOM_POINTCONTROL_1, new UsinePointControl(NOM_POINTCONTROL_1));
	ajouterUsine(NOM_POINTCONTROL_2, new UsinePointControl(NOM_POINTCONTROL_2));ajouterUsine(NOM_POINTCONTROL_3, new UsinePointControl(NOM_POINTCONTROL_3));
	ajouterUsine(NOM_POINTCONTROL_4, new UsinePointControl(NOM_POINTCONTROL_4));ajouterUsine(NOM_POINTCONTROL_5, new UsinePointControl(NOM_POINTCONTROL_5));
	ajouterUsine(NOM_POINTCONTROL_6, new UsinePointControl(NOM_POINTCONTROL_6));ajouterUsine(NOM_POINTCONTROL_0, new UsinePointControl(NOM_POINTCONTROL_7));
	ajouterUsine(NOM_POINTCONTROL_8, new UsinePointControl(NOM_POINTCONTROL_8));
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
	/*NoeudAbstrait* P0{ creerNoeud(NOM_POINTCONTROL_0) };	NoeudAbstrait* P1{ creerNoeud(NOM_POINTCONTROL_1) };NoeudAbstrait* P2{ creerNoeud(NOM_POINTCONTROL_2) };
	NoeudAbstrait* P3{ creerNoeud(NOM_POINTCONTROL_3) };	NoeudAbstrait* P4{ creerNoeud(NOM_POINTCONTROL_4) };NoeudAbstrait* P5{ creerNoeud(NOM_POINTCONTROL_5) };
	NoeudAbstrait* P6{ creerNoeud(NOM_POINTCONTROL_6) };	NoeudAbstrait* P7{ creerNoeud(NOM_POINTCONTROL_7) }; NoeudAbstrait* P8{ creerNoeud(NOM_POINTCONTROL_8) };
	//std::vector<PointControl> listePoint;*/
	NoeudAbstrait* P0{ creerNoeud(NOM_POINTCONTROL) };	NoeudAbstrait* P1{ creerNoeud(NOM_POINTCONTROL) };NoeudAbstrait* P2{ creerNoeud(NOM_POINTCONTROL) };
	NoeudAbstrait* P3{ creerNoeud(NOM_POINTCONTROL) };	NoeudAbstrait* P4{ creerNoeud(NOM_POINTCONTROL) };NoeudAbstrait* P5{ creerNoeud(NOM_POINTCONTROL) };
	NoeudAbstrait* P6{ creerNoeud(NOM_POINTCONTROL) };	NoeudAbstrait* P7{ creerNoeud(NOM_POINTCONTROL) }; NoeudAbstrait* P8{ creerNoeud(NOM_POINTCONTROL) };
	
	P0->assignerPositionRelative(glm::vec3(69, -47, 0.0)); P1->assignerPositionRelative(glm::vec3(69, 0.0, 0.0));
	P2->assignerPositionRelative(glm::vec3(69, 47.0, 0.0));
	P3->assignerPositionRelative(glm::vec3(0.0, 47, 0.0));
	P4->assignerPositionRelative(glm::vec3(-69, 47, 0.0)); P5->assignerPositionRelative(glm::vec3(-69, 0.0, 0.0));
	P6->assignerPositionRelative(glm::vec3(-69, -47, 0.0));
	P7->assignerPositionRelative(glm::vec3(0.0, -47, 0.0)); P8->assignerPositionRelative(glm::vec3(0.0, 0.0, 0.0));
	//NoeudAbstrait* p = chercher("point");
	//for (int i = 0; i < 8; i++) {
	//	listePoint_.push_back(p[i]);
	//	cout << listePoint_[i].obtenirPositionRelative().x << "-----" << listePoint_[i].obtenirPositionRelative().y << endl;
	//}
	zoneJeux_->ajouter(maillet1);
	maillet1->modifierId(2);
	maillet1->assignerPositionRelative(glm::dvec3(zoneJeux_->obtenirSommets()[5].x + 5.0, -2.0, 0.0));
	maillet1->assignerPositionInitial(glm::dvec3(zoneJeux_->obtenirSommets()[5].x + 5.0, -2.0, 0.0));
	zoneJeux_->ajouter(rondelle);
	rondelle->assignerPositionRelative(glm::dvec3(0.0, 0.0, -2.0));
	zoneJeux_->ajouter(mailletVir_);
	mailletVir_->modifierId(3);
	mailletVir_->assignerPositionRelative(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, -2.0, 0.0));
	mailletVir_->assignerPositionInitial(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, -2.0, 0.0));
	zoneJeux_->ajouter(P0);
	zoneJeux_->ajouter(P1); zoneJeux_->ajouter(P2); zoneJeux_->ajouter(P3); zoneJeux_->ajouter(P4);
	zoneJeux_->ajouter(P5); zoneJeux_->ajouter(P6); zoneJeux_->ajouter(P7); zoneJeux_->ajouter(P8);
	//cout << "--------------------------------" << endl;
	
	/*float rayon = utilitaire::calculerSphereEnglobante(*rondelle->obtenirModele()).rayon;
	rondelle->modifierRayon(rayon );*/
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiserPartieAvecVirtuel()
///
/// Initialise une partie avec un joueur virtuel
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiserPartieAvecVirtuel()
{

		zoneJeux_->ajouter(mailletVir_);
		mailletVir_->modifierId(3);
		mailletVir_->assignerPositionRelative(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
		mailletVir_->assignerPositionInitial(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiserPartieAvecHumain()
///
/// Initialise une partie avec un joueur humain
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiserPartieAvecHumain()
{
	zoneJeux_->ajouter(maillet2_);
	maillet2_->modifierId(3);
	maillet2_->assignerPositionRelative(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
	maillet2_->assignerPositionInitial(glm::dvec3(zoneJeux_->obtenirSommets()[1].x - 5.0, 0.0, 0.0));
}
////////////////////////////////////////////////////////////////////////
///
/// @fn int ArbreRenduINF2990::ajouterNouveauElement
///         (const std::string& nomObjet, glm::dvec3 positionR)
///
/// Ajoute un element dans l'arbre
///
/// @param[in] nomObjet : string, positionR : dvec3
///
/// @return le numero de l'objet (int)
///
////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////
///
/// @fn int ArbreRenduINF2990::ajouterNouveauPortail
///				(const std::string& nomObjet, glm::dvec3 positionR)
///
/// Ajoute un portail dans l'arbre
///
/// @param[in] nomObjet : string, positionR : dvec3
///
/// @return le numero du portail (int)
///
////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::marquerSelection(int identifiant, bool enInverse)
///
/// Marque la selection
///
/// @param[in] identifiant : int, enInverse : bool
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::assignerZoneJeux(NoeudAbstrait * zone)
///
/// Assigne la zone de jeux
///
/// @param[in] zone : NoeudAbstrait
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::assignerZoneJeux(NoeudAbstrait * zone)
{
	zoneJeux_ = zone;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
