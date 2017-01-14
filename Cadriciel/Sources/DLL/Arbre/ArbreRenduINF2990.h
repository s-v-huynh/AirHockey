///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"
#include "../VisiteurSuppression.h"
#include <map>
#include <string>

class FacadeModele;

///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui représente l'arbre de rendu spécifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilisés par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public :
	/// Constructeur par défaut.
	ArbreRenduINF2990();
	/// Destructeur.
	virtual ~ArbreRenduINF2990();

	/// Initialise l'arbre de rendu à son état initial.
	void initialiser();
	void initialiserPartieAvecVirtuel();
	void initialiserPartieAvecHumain();
	int ajouterNouveauElement(const std::string& nomObjet, glm::dvec3 positionR);
    int ajouterNouveauPortail(const std::string& nomObjet, glm::dvec3 positionR);
	void ajouterPairePortails(NoeudAbstrait* portail);

	/// La chaîne représentant le type des araignées.
	static const std::string NOM_ARAIGNEE;
	/// La chaîne représentant le type des cones-cubes.
	static const std::string NOM_CONECUBE;
	/// La chaîne représentant le type des table.
	static const std::string NOM_TABLE;
	/// La chaîne représentant le type des rondelle.
	static const std::string NOM_RONDELLE;
	/// La chaîne représentant le type des maillet.
	static const std::string NOM_MAILLET_1;
	static const std::string NOM_MAILLET_V;
	static const std::string NOM_MAILLET_2;
	static const std::string NOM_POINTCONTROL_0; static const std::string NOM_POINTCONTROL_1; static const std::string NOM_POINTCONTROL_2;
	static const std::string NOM_POINTCONTROL_3; static const std::string NOM_POINTCONTROL_4; static const std::string NOM_POINTCONTROL_5;
	static const std::string NOM_POINTCONTROL_6; static const std::string NOM_POINTCONTROL_7; static const std::string NOM_POINTCONTROL_8;
	static const std::string NOM_POINTCONTROL;
	static const std::string NOM_CERCLE;
	/// La chaîne représentant le type des bonus.
	static const std::string NOM_BONUS;
	static const std::string NOM_PORTAIL;
	static const std::string NOM_MURET;

	void modifierProchainId(int id) { prochainId_ = id; }
	int obtenirProchainId() { return prochainId_; }
	void marquerSelection(int identifiant, bool enInverse);
	void assignerZoneJeux(NoeudAbstrait * zone);


private:
	NoeudAbstrait* zoneJeux_;
	int prochainId_ = 1 - 1;
	std::map < std::string, const opengl::VBO* > listObjetSelecitonne;
    std::vector<pair<NoeudPortail*, NoeudPortail*>> listePortail_;
	std::vector<NoeudAbstrait> listePoint_;
	VisiteurSuppression* supprimer_;
	bool continuer_;
	NoeudAbstrait* maillet2_;
	NoeudAbstrait* mailletVir_;
};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
