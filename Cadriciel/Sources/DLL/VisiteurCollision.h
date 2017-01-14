//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCollision.h
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef	VISITEUR_COLLISION_H
#define VISITEUR_COLLISION_H
#include "VisiteurAbstrait.h"
#include "AideCollision.h"
#include "Utilitaire.h"
#include <vector>
#include <iomanip>

//afin d'eviter l'erreur de classe imcomplete 
class FacadeModele;

class VisiteurCollision : public VisiteurAbstrait {
public:
	//Constructeur par defaut
	VisiteurCollision();
	//Constructeur avec parametres
	VisiteurCollision(NoeudRondelle* rondelle, double coefRebon, std::vector<NoeudPortail*> portails, double acceleration);
	//VisiteurCollision(NoeudMailletVirtuel* maillet, double coefRebon, double acceleration);

	//Destructeur
	~VisiteurCollision();
	void definirPosition(glm::dvec3);
	void definirTable(NoeudTable*);

	//visites des differents noeuds
	virtual void visiter(NoeudComposite*);
	virtual void visiter(NoeudMaillet*);
	virtual void visiter(NoeudMailletVirtuel*);
	virtual void visiter(NoeudMuret*);
	virtual	void visiter(NoeudPortail*);
	virtual void visiter(NoeudRondelle*);
	virtual void visiter(NoeudTable*);
	virtual void visiter(NoeudBonusAccelerateur*);
	void reinitialiserPartie();
	void quitterPortail();
	int obtenirButsJoueur1() { return butsJoueur1_; }
	int obtenirButsJoueur2() { return butsJoueur2_; }
	void initialiserScores();
	int getButJoueurG();
	int getButJoueurD();
	void gererDebogage(string objet);
	string afficherTemps();
private:
	NoeudTable * zoneJeu_;
	glm::dvec3 position_;
	NoeudRondelle* rondelle_;
	NoeudAbstrait* maillet;
	std::vector<NoeudPortail*> listePortails_;
	double coefRebon_;
	double acceleration_;
	bool debugObjet_;
	bool debugVitesse_;
	int butsJoueur1_;
	int butsJoueur2_;
	NoeudAbstrait* maillet1_;
	NoeudAbstrait* maillet2_;

	int nbButGauche_ = 0;
	int nbButDroite_ = 0;
	FacadeModele* facade;
};

#endif
