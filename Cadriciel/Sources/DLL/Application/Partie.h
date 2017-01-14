//////////////////////////////////////////////////////////////////////////////
/// @file Parti.h
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_PARTIE_H__
#define __APPLICATION_PARTIE_H__



#include <string>
#include "../Arbre/Noeuds/NoeudJoueur.h"
#include "../Arbre/Noeuds/NoeudRondelle.h"
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////
/// @class Partie
/// @brief Classe qui regroupe les parametres de de la partie
///
/// @author equipe06
/// @date 2016-10-20
///////////////////////////////////////////////////////////////////////////
//class NoeudJoueur;

class FacadeModele;
class Partie
{
private:
	//bool joueurVirtuel_;
	NoeudJoueur* joueur1_;
	NoeudJoueur* joueur2_;
	NoeudAbstrait* rondelle_;
	int nbButMax_;
	bool arreterPartie_;
	bool partieClassique_;
	NoeudJoueur* vainqueur_;
	bool partieFinie_ = false;
	int nbButJoueurGauche_ = 0;
	int nbButJoueurDroite_ = 0;
	std::string nomJoueurGauche_ = "Joueur 1";
	std::string nomJoueurDroite_ = "Joueur 2";
	std::string nomVainqueur_;
	bool joueurGaucheVirtuel_;
	bool joueurDroiteVirtuel_;

public:
	Partie() {};
	///Constructueur pour une partie standard
	Partie(int nbBut, bool joueurVirtuel);

	Partie(int nbBut, bool joueurGVirtuel, std::string nomjoueurG, bool joueurDVirtuel, std::string nomjoueurD);
	///Constructueur pour une partie dans un tournoi
	Partie(int nbBut, NoeudJoueur*, NoeudJoueur*);
	///Destructeur
	~Partie();
	int obtenirButJoueur1() const;
	int obtenirButJoueur2() const;
	void assignerJoueur1(NoeudJoueur*);
	void assignerJoueur1(std::string);
	void assignerJoueur2(std::string);
	//std::string obtenirVainqueur();
	void assignerJoueur2(NoeudJoueur*);
	void assignerbutJ1();
	void assignerbutJ2();
	void miseEnPlaceMaillet(bool estVirtuel);
	std::string obtenirVainqueur(); // { return vainqueur_; };
	//bool joueurVirtuel() { return joueurVirtuel_; };
	void reinitialiser();
	void arreter();
	void chargerZone(string nomZone);
	bool getEtatPartie() { return partieFinie_; };
	void setEtatPartie(bool a) { partieFinie_ = a; };
	FacadeModele* facade;
	const string obtenirJoueur1() { return nomJoueurGauche_; };
	const string obtenirJoueur2() { return nomJoueurDroite_; };
};






#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
