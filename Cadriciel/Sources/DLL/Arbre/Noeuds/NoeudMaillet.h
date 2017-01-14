///////////////////////////////////////////////////////////////////////////
/// @file NoeudMaillet.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMAILLET_H__
#define __ARBRE_NOEUDS_NOEUDMAILLET_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMaillet
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe06
/// @date 2016-09-07
///////////////////////////////////////////////////////////////////////////
class NoeudMaillet : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudMaillet(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudMaillet();
    ///Methode utiliser pour la copie des attributs
    void copierAttributs(NoeudMaillet& destination);

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	virtual void redessiner();
	bool verifierSelection(GLubyte couleurObjet[]);
	void accepterVisiteur(VisiteurAbstrait* visiteur);
	void modifierRayonMaillet(double rayonMaillet);
	double obtenirRayonMaillet();
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste) override;
	virtual void redefinirSommets();
	virtual bool estDansLaTable();

private:
	/// Angle dans le sinus de l'oscillation
	int nbInstance_;
	double coefRebondissement;
	void attribuerCouleur();
	GLubyte couleurMaillet_[3];
	static int compteurGreen_;
	double rayonMaillet_;
	

};


#endif // __ARBRE_NOEUDS_NOEUDMAILLET_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
