#pragma once
///////////////////////////////////////////////////////////////////////////
/// @file NoeudMailletVirtuel.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMAILLET_VIRTUEL_H__
#define __ARBRE_NOEUDS_NOEUDMAILLET_VIRTUEL_H__


#include "NoeudComposite.h"
#include "GL/glew.h"
#include "glm/gtx/norm.hpp"

#include "NoeudRondelle.h"
class ArbreRenduINF2990;
class FacadeModele;
///////////////////////////////////////////////////////////////////////////
/// @class NoeudMaillet
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe06
/// @date 2016-09-07
///////////////////////////////////////////////////////////////////////////
class NoeudMailletVirtuel : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudMailletVirtuel(const std::string& typeNoeud);
	/// Destructeur.
	virtual ~NoeudMailletVirtuel();
	///Methode utiliser pour la copie des attributs
	NoeudMailletVirtuel(NoeudMailletVirtuel& destination);

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const;
	void moveY(double temps);
	void moveX(double temps);
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	bool verifierSelection(GLubyte couleurObjet[]);
	void accepterVisiteur(VisiteurAbstrait* visiteur);
	void modifierRayonMaillet(double rayonMaillet);
	double obtenirRayonMailletV();

	void assignerProbabiliteDeJeu(double proba);
	/// assigner Rondelle
	void assignerRondelle(NoeudRondelle* rondelle);
	/// assigner Vitesse
	void assignerVitesse(double vitesse);
	double obtenirVitesse();

	/// assigner la demi largeur des buts
	void assignerLargeurButs(int largeurButs);
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	virtual void redefinirSommets();
	bool estDansLaTable();
	

private:
	/// Angle dans le sinus de l'oscillation
	int nbInstance_;
	double coefRebondissement;
	void attribuerCouleur();
	GLubyte couleurMailletVirtuel_[3];
	static int compteurGreen_;
	double rayonMailletV_;
	/// deplacement du joueur virtuel
	glm::dvec2 deplacement_;
	/// probabilité de rester passif
	double probabilite_;
	/// vitesse du joueur virtuel
	double vitesse_;
	/// largeur du but
	int largeurBut_;
	/// valeur de l'accélération vers la rondelle
	glm::dvec2 forceImpulsion_;
	/// vitesse de frappe du joueur virtuel
	glm::dvec2 vitesseDeFrappe_;
	/// pointeur vers la rondelle
	NoeudRondelle* rondelle_;
	/// indique si le maillet joueur est en mode passif
	bool passif_;
	/// indique si le maillet joueur est en mode offensif
	bool offensif_;

	/// Fonction qui simule le scénario défensif
	void scenarioDefensif(double t);
	/// Fonction qui simule le scénario offensif
	void scenarioOffensif();
	double dx_;
	double dy_;
	double angleDeplacement_;
	glm::dvec3 positionInitial_;
	bool estVirtuel;
};


#endif // __ARBRE_NOEUDS_NOEUDMAILLET_VIRTUEL_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

