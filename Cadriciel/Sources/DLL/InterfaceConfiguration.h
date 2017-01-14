///////////////////////////////////////////////////////////////////////////
/// @file InterfaceConfiguration.h
/// @author equipe06
/// @date 2016-10-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef	INTERFACE_CONFIGURATION_H
#define INTERFACE_CONFIGURATION_H

#include <string>

#include <tinyxml2.h>

class InterfaceConfiguration
{


public:
	///Constructeur par defaut
	InterfaceConfiguration();
	///Retourne s'il est possible d'afficher a la console
	bool obtenirPeutAfficherDebogage();
	///Retourne s'il est possible d'afficher le type d'objet entre en collision avec la rondelle
	bool obtenirPeutAfficherCollision();
	///Retourne s'il est possible d'afficher la vitesse d'une rondelle apres collision
	bool obtenirPeutAfficherVitesseRondelle();
	///Retourne si l'etat de l'eclairage est afficher
	bool obtenirPeutAfficherEclairage();
	///Retourne si la delimitation de l'attraction du portail est affichee
	bool obtenirPeutAfficherAttractionPortail();
	///Retourne le nombre de buts necessaire pour gagner
	int obtenirNbButs();
	///Retourne si le deuxieme joueur est virtuel ou non
	bool obtenirEstVirtuel();

	///Modifie l'etat de l'affichage a la console
	void modifierPeutAfficherDebogage(bool peutAfficherDebogage);
	///Modifie l'affichage des collisions
	void modifierPeutAfficherCollision(bool peutAfficherCollision);
	///Modifie l'affichage de la vitesse de la rondelle
	void modifierPeutAfficherVitesseRondelle(bool peutAfficherVitesse);
	///Modifie l'affichage de l'eclairage
	void modifierPeutAfficherEclairage(bool peutAfficherEclairage);
	///Modifie l'affichage de l'attraction des portails
	void modifierPeutAfficherAttractionPortail(bool peutAfficherAttractionPortail);
	///Modifie le nombre de buts necessaires pour gagner
	void modifierNbButs(int nbButs);
	///Modifie le type de joueur (virtuel ou non)
	void modifierEstVirtuel(bool estVirtuel);

private:
	///Permet l'affichage a la console
	bool peutAfficherDebogage_;
	///Affiche le type d'objet que la rondelle est entree en collision a la console avec si vrai
	bool peutAfficherCollision_;
	///Affiche la vitesse de la rondelle apres une collision avec un objet a la console si vrai
	bool peutAfficherVitesseRondelle_;
	///Affiche l'etat de l'eclairage a la console si vrai
	bool peutAfficherEclairage_;
	///La delimitation de l'attraction des portails est affichee si vrai
	bool peutAfficherAttractionPortail_;

	///Nombre de buts necessaires pour gagner une partie
	int nbButs_;

	///Determine si le deuxieme joueur est virtuel ou non pour le mode de test
	bool estVirtuel_;



};

#endif
