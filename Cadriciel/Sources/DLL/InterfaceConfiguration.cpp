///////////////////////////////////////////////////////////////////////////
/// @file InterfaceConfiguration
/// @author equipe06
/// @date 2016-10-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "InterfaceConfiguration.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn InterfaceConfiguration::InterfaceConfiguration()
///
/// Ce constructeur met des valeurs par defaut pour les options generales
/// de la configuration
///
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
InterfaceConfiguration::InterfaceConfiguration()
{
	peutAfficherDebogage_ = false;
	peutAfficherCollision_ = false;
	peutAfficherVitesseRondelle_ = false;
	peutAfficherEclairage_ = false;
	peutAfficherAttractionPortail_ = false;

	nbButs_ = 2;

	estVirtuel_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool InterfaceConfiguration::obtenirPeutAfficherDebogage()
///
/// Permet de determiner s'il est possible d'afficher a la console pour
/// debogage
///
/// @return retourne vrai si l'affichage a la console est permise
///
////////////////////////////////////////////////////////////////////////
bool InterfaceConfiguration::obtenirPeutAfficherDebogage()
{
	return peutAfficherDebogage_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool InterfaceConfiguration::obtenirPeutAfficherCollision()
///
/// Permet de determiner s'il est possible d'afficher le type d'objet
/// qui entre en contact avec la rondelle lors d'une collision
///
/// @return retourne vrai si l'affichage du type d'objet qui entre
///		en collision avec la rondelle est permise
///
////////////////////////////////////////////////////////////////////////
bool InterfaceConfiguration::obtenirPeutAfficherCollision()
{
	return peutAfficherCollision_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool InterfaceConfiguration::obtenirPeutAfficherVitesseRondelle()
///
/// Permet de determiner s'il est possible d'afficher la vitesse d'une
/// rondelle a la console suite a une collision
///
/// @return retourne vrai si l'affichage du type d'objet qui entre
///		en collision avec la rondelle est permise
///
////////////////////////////////////////////////////////////////////////
bool InterfaceConfiguration::obtenirPeutAfficherVitesseRondelle()
{
	return peutAfficherVitesseRondelle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool InterfaceConfiguration::obtenirPeutAfficherEclairage()
///
/// Permet de determiner s'il est possible d'afficher l'etat de
/// l'eclairage a la console
///
/// @return retourne vrai si l'affichage de l'etat de l'eclairage est 
///		permise
///
////////////////////////////////////////////////////////////////////////
bool InterfaceConfiguration::obtenirPeutAfficherEclairage()
{
	return peutAfficherEclairage_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool InterfaceConfiguration::obtenirPeutAfficherAttractionPortail()
///
/// Permet de determiner s'il est possible d'afficher la delimitation 
/// de l'attraction des portails
///
/// @return retourne vrai si l'affichage de la delimitation de l'attraction
///		des portails
///
////////////////////////////////////////////////////////////////////////
bool InterfaceConfiguration::obtenirPeutAfficherAttractionPortail()
{
	return peutAfficherAttractionPortail_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int InterfaceConfiguration::obtenirNbButs()
///
/// Retourne le nombre de buts necessaire pour gagner une partie
///
/// @return le nombre de buts necessaire pour gagner une partie
///
////////////////////////////////////////////////////////////////////////
int InterfaceConfiguration::obtenirNbButs()
{
	return nbButs_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool InterfaceConfiguration::obtenirEstVirtuel()
///
/// Permet de determiner si le deuxieme joueur est virtuel ou humain
///
/// @return retourne vrai le deuxieme joueur est virtuel
///
////////////////////////////////////////////////////////////////////////
bool InterfaceConfiguration::obtenirEstVirtuel()
{
	return estVirtuel_;
}


void InterfaceConfiguration::modifierPeutAfficherDebogage(bool peutAfficherDebogage)
{
	peutAfficherDebogage_ = peutAfficherDebogage;
}

void InterfaceConfiguration::modifierPeutAfficherCollision(bool peutAfficherCollision)
{
	peutAfficherCollision_ = peutAfficherCollision;
}

void InterfaceConfiguration::modifierPeutAfficherVitesseRondelle(bool peutAfficherVitesse)
{
	peutAfficherVitesseRondelle_ = peutAfficherVitesse;
}

void InterfaceConfiguration::modifierPeutAfficherEclairage(bool peutAfficherEclairage)
{
	peutAfficherEclairage_ = peutAfficherEclairage;
}

void InterfaceConfiguration::modifierPeutAfficherAttractionPortail(bool peutAfficherAttractionPortail)
{
	peutAfficherAttractionPortail_ = peutAfficherAttractionPortail;
}

void InterfaceConfiguration::modifierNbButs(int nbButs)
{
	nbButs_ = nbButs;
}

void InterfaceConfiguration::modifierEstVirtuel(bool estVirtuel)
{
	estVirtuel_ = estVirtuel;
}

