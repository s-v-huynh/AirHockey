//////////////////////////////////////////////////////////////////////////////
/// @file NoeudJoueur.h
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_JOUEUR_H__
#define __ARBRE_NOEUD_JOUEUR_H__


#include "NoeudComposite.h"
#include "NoeudRondelle.h"
//#include "GL/glew.h"

class NoeudJoueur : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudJoueur() {};
	NoeudJoueur(bool virtuel, std::string nom);
	/// Destructeur.
	virtual ~NoeudJoueur();
	//Methode utiliser pour la copie des attributs
	//NoeudMailletVirtuel(NoeudMailletVirtuel& destination);

	void assignerMaillet(NoeudAbstrait* node);
	int getBut() const; 
	NoeudAbstrait* getMaillet() { return maillet_; };
	NoeudMailletVirtuel* getMailletVirtuel() { return dynamic_cast<NoeudMailletVirtuel*>(maillet_); };
	void incrementerBut();
	void reinitialiserBut();
	void setBut(int);
	bool estVirtuel() { return estVirtuel_; };
	void setVirtuel( bool virtuel) { estVirtuel_ = virtuel; };
	void assignerNom(std::string nom) { nomJoueur_ = nom; };
	std::string getNom() { return nomJoueur_; };
private:
	NoeudAbstrait* maillet_;
	int nbBut_;
	bool estVirtuel_;
	std::string nomJoueur_;
};
#endif // __ARBRE_NOEUD_JOUEUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
