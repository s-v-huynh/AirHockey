//////////////////////////////////////////////////////////////////////////////
/// @file Parti.cpp
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "Partie.h"
#include "../Application/FacadeModele.h"
 
Partie::Partie(int nbBut, bool virtuel):
	nbButMax_(nbBut)
{
	arreterPartie_ = false;
	joueur1_ = new NoeudJoueur(false, "joueur 1");
	joueur2_ = new NoeudJoueur(virtuel, "joueur 2");
	partieClassique_ = true;
	vainqueur_ = nullptr;
}

Partie::Partie(int nbBut, bool joueurGVirtuel, std::string nomjoueurG, bool joueurDVirtuel, std::string nomjoueurD)
{
	nbButMax_ = nbBut;
	joueurGaucheVirtuel_ = joueurGVirtuel;
	joueurDroiteVirtuel_ = joueurDVirtuel;
	nomJoueurGauche_ = nomjoueurG;
	nomJoueurDroite_ = nomjoueurD;
	arreterPartie_ = false;
	nbButJoueurDroite_ = 0;
	nbButJoueurGauche_ = 0;
	if (joueurDroiteVirtuel_ && joueurGaucheVirtuel_)
	{
		
		bool vainqueur = rand() % 2;
		
		if (vainqueur)
		{
			nomVainqueur_ = nomJoueurDroite_;
		}
		else
		{
			nomVainqueur_ = nomJoueurGauche_;
		}
		arreter();
	}
}

Partie::Partie(int nbBut, NoeudJoueur* j1, NoeudJoueur* j2):
	nbButMax_(nbBut)
{
	arreterPartie_ = false;
	partieClassique_ = false;
	joueur1_ = j1;
	joueur2_ = j2;
}
Partie::~Partie() 
{
	if (partieClassique_) 
	{
		delete joueur1_;
		delete joueur2_;
	}
}


int Partie::obtenirButJoueur1() const
{
	return nbButJoueurGauche_;
	//return joueur1_->getBut();

}

int Partie::obtenirButJoueur2() const
{
	return nbButJoueurDroite_;
	//return joueur2_->getBut();
}

void Partie::assignerJoueur1(NoeudJoueur* node)
{
	joueur1_ = node;
}

void Partie::assignerJoueur1(std::string node)
{
	nomJoueurGauche_ = node;
}


void Partie::assignerJoueur2(std::string node)
{
	nomJoueurDroite_ = node;
}

void Partie::assignerJoueur2(NoeudJoueur* node)
{
	joueur2_ = node;
}

void Partie::assignerbutJ1()
{
	if (arreterPartie_ == false)
	{
		//joueur1_->incrementerBut();
		nbButJoueurGauche_++;
		//&&arreterpartie = false
		if (nbButJoueurGauche_ == nbButMax_)
		{
			nomVainqueur_ = nomJoueurGauche_;
			arreterPartie_ = true;
			//vainqueur_ = joueur1_;
			arreter();
			

		}
	}
}

void Partie::assignerbutJ2()
{
	if (arreterPartie_ == false)
	{
		//joueur2_->incrementerBut();
		nbButJoueurDroite_++;
		if (nbButJoueurDroite_ == nbButMax_)
		{
			nomVainqueur_ = nomJoueurDroite_;
			arreterPartie_ = true;
			//vainqueur_ = joueur2_;
			arreter();
			
		}
	}
}



//void Partie::miseEnPlaceMaillet(bool estVirtuel)
//{
//	/*maillet1->assignerPositionRelative(glm::dvec3(-66.0, 0.0, 0.0));
//	maillet2->assignerPositionRelative(glm::dvec3(62.0, 0.0, 0.0));
//	rondelle->assignerPositionRelative(glm::dvec3(0.0, 0.0, 0.0));*/
//	joueur1_->getMaillet()->assignerPositionRelative(glm::dvec3(-66.0, 0.0, 0.0));
//	//if(!estVirtuel)
//		joueur2_->getMaillet()->assignerPositionRelative(glm::dvec3(62.0, 0.0, 0.0));
//	/*else
//		joueur2_->getMailletVirtuel()->assignerPositionRelative(glm::dvec3(62.0, 0.0, 0.0));
//*/
//	rondelle_->assignerPositionRelative(glm::dvec3(0.0, 0.0, 0.0));
//}

void Partie::arreter()
{
	
	
	partieFinie_ = true;
	facade = facade->obtenirInstance();
	facade->arreterPartie(nomVainqueur_);
}

void Partie::reinitialiser()
{
	joueur1_->setBut(0);
	joueur2_->setBut(0);
	partieFinie_ = false;
	arreterPartie_ = false;
	nbButJoueurDroite_ = 0;
	nbButJoueurGauche_ = 0;
	//miseEnPlaceMaillet();
}


//void Partie::reinitialiser() 
//{
//	joueur1_->setBut(0);
//	joueur2_->setBut(0);
//	miseEnPlaceMaillet();
//}