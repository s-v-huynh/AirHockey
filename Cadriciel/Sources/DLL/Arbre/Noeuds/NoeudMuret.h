///////////////////////////////////////////////////////////////////////////
/// @file NoeudMuret.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMURET_H__
#define __ARBRE_NOEUDS_NOEUDMURET_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBonusAccelerateur
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe06
/// @date 2016-09-07
///////////////////////////////////////////////////////////////////////////
class NoeudMuret : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudMuret(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMuret();
	void copierAttributs(NoeudMuret& destination);
	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	bool verifierSelection(GLubyte couleurObjet[]);
	void accepterVisiteur(VisiteurAbstrait* visiteur);

	void modifierLongueurMuret(double longueurMuret);

	//void assignerPositionRelative(const glm::dvec3& positionRelative);
	/// Assigne la position initiale du noeud.
	inline void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;

	//const glm::dvec3& obtenirPositionRelative();
	//void modifierFacteurEchelle(double facteurEchelle);
	//bool estDansLaZoneDeJeu();
	// inline void modifierEchelle(const glm::fvec3 scale) { scale_.y = scale.y; };
	virtual void redefinirSommets();
	//bool estDansLaTable();
	virtual bool estDansLaTable();
	//void mettreAJourPosition();

	double obtenirLongueurMuret();
	/// Points du mur
	struct point_muret
	{
		glm::dvec3 debut, fin;
		point_muret() {};
		point_muret(const glm::dvec3& p1, const glm::dvec3& p2)
			: debut(p1), fin(p2) {};
	};
	inline point_muret obtenirPoints() const;

	//	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
protected:
	/// Fonction qui permet de recalculer les sommets du noeud
	//virtual void recalculerSommets() {};
private:

	double hauteurMuret_;
	double epaisseurMuret_;
	double longueurMuret_;
	void attribuerCouleur();
	GLubyte couleurMuret_[3];
	static int compteurBleu_;
	glm::dvec2 tranlastion_;
	int nbInstances_;
	glm::dvec3 debut_, fin_;
	glm::dvec3 debutInit_, finInit_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudMuret::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
///
/// Cette fonction retourne l'ensemble des deux points de début et de fin du muret
///
/// @param[in] modele : Modele3D
///			   liste : VBO
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
inline void NoeudMuret::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	//	debutInit_ = utilitaire::calculerBoiteEnglobante(*modele).coinMin;
	//finInit_ = utilitaire::calculerBoiteEnglobante(*modele).coinMax;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudMuret::point_muret NoeudMuret::obtenirPoints() const
///
/// Cette fonction retourne l'ensemble des deux points de début et de fin du muret
///
/// @return L'ensemble de points
///
////////////////////////////////////////////////////////////////////////
inline NoeudMuret::point_muret NoeudMuret::obtenirPoints() const
{
	return point_muret(debut_, fin_);
}
#endif // __ARBRE_NOEUDS_NOEUDBONUSACCELERATEUR_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
