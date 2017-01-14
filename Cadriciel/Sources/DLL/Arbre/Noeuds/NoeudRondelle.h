///////////////////////////////////////////////////////////////////////////
/// @file NoeudRondelle.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDRONDELLE_H__
#define __ARBRE_NOEUDS_NOEUDRONDELLE_H__


#include "NoeudComposite.h"
#include "GL/glew.h"
#include "NoeudTable.h"
#include "Utilitaire.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudRondelle
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe06
/// @date 2016-09-07
///////////////////////////////////////////////////////////////////////////
class NoeudRondelle : public NoeudComposite
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudRondelle(const std::string& typeNoeud);
	///Constructeur de copie
	NoeudRondelle(const NoeudRondelle&);
	/// Destructeur.
	~NoeudRondelle();
    ///Methode pour copier les attributs de copie
    void copierAttributs(NoeudRondelle& destination);
	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	virtual void redessiner();
	///modificateurs 
	void modifierRayonRondelle(double rayonRondelle);
	virtual void redefinirSommets();
	virtual bool estDansLaTable();
	///recuperateurs
	double obtenirRayonRondelle();
	void modifierVitesse(glm::dvec2 vitesse);
	glm::dvec2 obtenirVitesse();
	double obtenirVitesseMax() { return vitesseMax_; }
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:
	/// Angle dans le sinus de l'oscillation
	GLubyte couleurRondelle_[3];
	double rayonRondelle_;
	glm::dvec2 vitesseRondelle_;
	double vitesseMax_;
	double coefRebondissement_;
	double angleDeplacement_;
	double dx_, dy_;
	bool enMouvement_;
	bool estModifier_;
	double vx, vy;
	utilitaire::SphereEnglobante sphere_;
};


#endif // __ARBRE_NOEUDS_NOEUDRONDELLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
