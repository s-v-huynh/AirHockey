#include "ProfilVirtuel.h"

ProfilVirtuel::ProfilVirtuel()
{
	nom_ = "";
	vitesse_ = 3;
	passivite_ = 3;
}

ProfilVirtuel::ProfilVirtuel(std::string nom, int vitesse, int passivite)
{
	nom_ = nom;
	vitesse_ = vitesse;
	passivite_ = passivite;
}

const char* ProfilVirtuel::obtenirNom()
{
	return nom_.c_str();
}

int ProfilVirtuel::obtenirVitesse()
{
	return vitesse_;
}

int ProfilVirtuel::obtenirPassivite()
{
	return passivite_;
}

void ProfilVirtuel::modifierNom(char* nom)
{
	nom_ = nom;
}

void ProfilVirtuel::modifierVitesse(int vitesse)
{
	vitesse_ = vitesse;
}

void ProfilVirtuel::modifierPassivite(int passivite)
{
	passivite_ = passivite;
}
