//////////////////////////////////////////////////////////////////////////////
/// @file ProfilVirtuel.h
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef	PROFIL_VIRTUEL_H
#define PROFIL_VIRTUEL_H

#include <string>

#include "../../tinyxml2/include/tinyxml2.h"

class ProfilVirtuel
{
public:
	///Constructeur par defaut
	ProfilVirtuel::ProfilVirtuel();
	///Constructeur par parametres qui prend le nom, la vitesse et le degre de passivite
	ProfilVirtuel::ProfilVirtuel(std::string nom, int vitesse, int passivite);

	/// Methode pour obtenir les attributs
	const char* obtenirNom();
	int obtenirVitesse();
	int obtenirPassivite();

	/// Modificateur
	void modifierNom(char* nom);
	void modifierVitesse(int vitesse);
	void modifierPassivite(int passivite);

private:
	///Nom du profil
	std::string nom_;
	///Vitesse du maillet
	int vitesse_;
	/// Degre de passivite
	int passivite_;
};

#endif PROFIL_VIRTUEL_H