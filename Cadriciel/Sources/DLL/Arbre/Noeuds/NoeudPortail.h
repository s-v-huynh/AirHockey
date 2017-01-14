///////////////////////////////////////////////////////////////////////////
/// @file NoeudPortail.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPORTAIL_H__
#define __ARBRE_NOEUDS_NOEUDPORTAIL_H__

#include "NoeudComposite.h"
#include "NoeudCercle.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBonusAccelerateur
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe06
/// @date 2016-09-07
///////////////////////////////////////////////////////////////////////////
class NoeudPortail : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudPortail(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPortail();
    void copierAttributs(NoeudPortail& destination);
	/// Affiche le cube.
	//virtual void afficherConcret(const glm::mat4& vueProjection) const;
	virtual void afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur) const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	virtual void redessiner();
	bool obtenirAttraction() { return attraction_; };
	///Permet d'obtenir le rayon d'attraction des portails
	float obtenirRayonAttraction() { return rayonAttraction_; };
	virtual bool verifierSelection(GLubyte couleurObjet[]);
	NoeudPortail* getFrere();
	void setFrere(NoeudPortail* noeud);
	///indique si le portail est dans la table
	virtual bool estDansLaTable();
	///activer l'atraction des objets
	void activerAttraction() { attraction_ = true; };
	///desactiver l'attraction des objets
	void desactiverAttraction() { attraction_ = false; };
	virtual void modifierRayon(float rayonPortail);
	void modifierVitesseRotation(float vitesse);
	virtual float obtenirRayon();
	virtual void redefinirSommets();
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	void afficherRayonAttraction(bool afficher);
	void assignerCercle(NoeudCercle* noeud);
private:
	/// Angle dans le sinus de l'oscillation
	static int nbInstances_;
	bool attraction_;
	void attribuerCouleur();
	GLubyte couleurPortail_[3];
	GLfloat vitesseRotation_;
	static int compteurRed_;
	float rayonPortail_;
	float rayonAttraction_;
	NoeudPortail* portailFrere_;
	bool estLier_;
	bool afficherRayonAttraction_;
	NoeudCercle* cercle_;
};


#endif // __ARBRE_NOEUDS_NOEUDBONUSACCELERATEUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
