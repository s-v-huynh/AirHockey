///////////////////////////////////////////////////////////////////////////
/// @file NoeudBonusAccelerateur.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBONUSACCELERATEUR_H__
#define __ARBRE_NOEUDS_NOEUDBONUSACCELERATEUR_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBonusAccelerateur
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe06
/// @date 2016-09-07
///////////////////////////////////////////////////////////////////////////
class NoeudBonusAccelerateur : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudBonusAccelerateur(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudBonusAccelerateur();
    void copierAttributs(NoeudBonusAccelerateur& destination);

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const;

	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	void accepterVisiteur(VisiteurAbstrait* visiteur);
	bool verifierSelection(GLubyte couleurObjet[]);
	virtual bool estDansLaTable();
	virtual void redefinirSommets();
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)override;
	void modifierRayonBonusAccelerateur(double rayon);
	double obtenirRayonBonusAccelerateur() { return rayonBonusAccelerateur_; }

private:
	/// Angle dans le sinus de l'oscillation
	int nbInstances_;
	void attribuerCouleur();
	GLubyte couleurBonus_[3];
	static int compteurYellow_;
	double rayonBonusAccelerateur_;
};


#endif // __ARBRE_NOEUDS_NOEUDBONUSACCELERATEUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
