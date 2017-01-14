//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_TOURNOI_H__
#define __APPLICATION_TOURNOI_H__



#include <string>
#include "Partie.h"


///////////////////////////////////////////////////////////////////////////
/// @class Tournoi
/// @brief Classe qui regroupe les parametres du tournoi
///
/// @author equipe06
/// @date 2016-10-20
///////////////////////////////////////////////////////////////////////////
//class NoeudJoueur;

class Tournoi
{
private:
	NoeudJoueur* joueur1_;
	NoeudJoueur* joueur2_;
	NoeudJoueur* joueur3_;
	NoeudJoueur* joueur4_;

	

	int vainqueur1_;
	int vainqueur2_;
	int vainqueurFinal_;

	bool suppJ4 = false;
	bool suppJ1 = false;
	bool suppJ2 = false;
	bool suppJ3 = false; 

	int nbButMax_;
	bool arreterPartie;
	Partie partie_;
	int partieRestante_ = 3;

public:
	

	//Tournoi(bool joueurVirtuel1, string nomJ1, bool joueurVirtuel2, string nomJ2, bool joueurVirtuel3, string nomJ3, bool joueurVirtuel4, string nomJ4 );
	Tournoi() = default;
	~Tournoi() {};
	void assignerJoueur(int a, NoeudJoueur* b) 
	{
		switch (a)
		{
		case 1:
			joueur1_ = b;
			break;
		case 2:
			joueur2_ = b;
			break;
		case 3:
			joueur3_ = b;
			break;
		case 4:
			joueur4_ = b;
			break;
		default:
			break;
		}
	};
	Partie* getPartie() { return &partie_; };
	NoeudJoueur* joueurNom();
	void setvainqueur1(int a) { vainqueur1_ = a; };
	void setvainqueur2(int a) { vainqueur2_ = a; };
	void nextPartie() 
	{
		joueur1_->reinitialiserBut();
		joueur2_->reinitialiserBut();
		joueur3_->reinitialiserBut();
		joueur4_->reinitialiserBut();

		if (partieRestante_ > 0)
		{
			switch (partieRestante_)
			{
			case 3:
				partie_.assignerJoueur1(joueur1_);
				partie_.assignerJoueur2(joueur2_);
				break;
			case 2:
				partie_.assignerJoueur1(joueur3_);
				partie_.assignerJoueur2(joueur4_);
				break;
			case 1:
				if (vainqueur1_ == 1)
					partie_.assignerJoueur1(joueur1_);

				if (vainqueur1_ == 2)
					partie_.assignerJoueur1(joueur2_);

				if (vainqueur2_ == 3)
					partie_.assignerJoueur2(joueur3_);

				if (vainqueur2_ == 4)
					partie_.assignerJoueur2(joueur4_);
				break;
			default:
				break;
			}
		}
		
	};
};






#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
