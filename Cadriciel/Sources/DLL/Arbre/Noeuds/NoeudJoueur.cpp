///////////////////////////////////////////////////////////////////////////////
/// @file NoeudJoueur.cpp
/// @author equipe06
/// @date 2016-10-21
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#include "NoeudJoueur.h"

NoeudJoueur::NoeudJoueur(bool virtuel, std::string nom)
{ 
	nomJoueur_ = nom;
	estVirtuel_ = virtuel;
	maillet_ = nullptr;
	nbBut_ = 0;
}

NoeudJoueur::~NoeudJoueur()
{

}

void NoeudJoueur::assignerMaillet(NoeudAbstrait* maillet)
{
	maillet_ = maillet;
}

int NoeudJoueur:: getBut() const
{
	return nbBut_;
}

void NoeudJoueur::setBut(int but)
{
	nbBut_ = but;
}

void NoeudJoueur::incrementerBut()
{
	nbBut_++;
}

void NoeudJoueur::reinitialiserBut()
{
	nbBut_ = 0;
}