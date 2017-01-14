///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.h
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDTABLE_H__
#define __ARBRE_NOEUDS_NOEUDTABLE_H__


#include "NoeudComposite.h"
#include "GL/glew.h"
#include "NoeudMaillet.h"
#include "NoeudMailletVirtuel.h"
#include "PointControl.h"
#include "NoeudPortail.h"
#include "Utilitaire.h"
#include "../VisiteurCollision.h"
#include <vector>
#include "../../../Commun/Utilitaire/OpenGL/OpenGL_Nuanceur.h"
#include "../../Commun/Utilitaire/OpenGL/OpenGL_Programme.h"

using namespace opengl;
using namespace std;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudTable
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Equipe06
/// @date 2016-09-07
///////////////////////////////////////////////////////////////////////////
class NoeudTable : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudTable(const std::string& typeNoeud);
	//void assignerUniformMatrix4fv(const GLchar * nom, MatricePipeline & val);
	void point();
	/// Destructeur.
	~NoeudTable();

	/// Affiche le cube.
	virtual void afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const;



	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	virtual void redessiner();

	virtual double obtenirFriction() const;
	void modifierFriction(double friction);
	double obtenirCoefRebondissement();
	void modifierCoefRebondissement(double coefRebondissement);
	double obtenirAcceleration();
	void modifierAcceleration(double acceleration);
	vector <NoeudPortail*>& obtenirListePortails() { return listePortails_; };
	virtual void redefinirSommets();
	virtual bool curseurEstDansTable(glm::dvec3 pos);
	virtual bool curseurEstDansZone(glm::dvec3 pos);
	void chercherCollisions();

	void assignerRondelle(NoeudRondelle * rond);
	void definirZone();
	NoeudRondelle * obtenirRondelle();

	int getGauche();
	int getDroite();
	void incrementerGauche();
	void incrementerDroite();
	void reinitialiserBut();
private:
	//static opengl::Programme programme;
	/// Angle dans le sinus de l'oscillation
	float angle_{ 0 };
	/// Liste d'affichage pour l'affichage de ce noeud.
	static GLuint liste_;
	/// nombre d'objet de cette classe
	static int nbObjet_;
	GLint locVertex;
	GLint locColor;
	/// Fonction qui affiche la surface de la table
	GLubyte couleurTable_[3];

	/// position des 8 points de controle
	glm::dvec3  ptControle_[13];
	glm::dvec3 sommetT_[13];
	/// indique le point appuy�, -1 si aucun point ne l'est
	int Appuye_;
	/// indique s'il faut afficher les points de controle
	bool afficherPtControle_;
	/// propri�t�s d'affichage de la table
	// La demi largeur des chacun des points de controle
	int demiLargeurPtControle_;
	// La demi largeur des chacun des buts
	int demiLargeurBut_;
	// hauteur de la table en Z
	int hauteur_;
	// epaisseur de la table
	int epaisseur_;
	// epaisseur de la bordure de la table
	int epaisseurBordure_;
	// hauteur de la bordure de la table
	int hauteurBordure_;
	// epaisseur des buts
	int epaisseurButs_;
	// epaisseur de la ligne du milieu
	int epaisseurLigneMilieu_;
	/// propri�t�s de jeu
	/*double rebondissement_; // coefficient de rebondissement des murs*/
	double friction_;	//coefficient de friction de la table
	double acceleration_; //coefficient d'acceleration des bonus accelerateurs
	double coefRebondissement_;/// limites que les points de controle ne peuvent franchir

	int limiteDistanceBarreRouge_;
	int limiteHorizontaleBut_;
	int limiteAxeHorizontal_;
	int limiteHorizontalBut_;
	/// maillet du premier joueur
	NoeudMaillet* mailletPrincipal_;
	/// maillet de l'adversaire
	NoeudAbstrait* mailletAdversaire_;
	/// rondelle
	NoeudRondelle* rondelle_;
	//liste des portails dans la table
	std::vector<NoeudPortail*> listePortails_;
//	std::vector<PointControl*> listePoint_;

	VisiteurCollision* collision_;
	VisiteurCollision* collisionM_;
	vector<glm::dvec3> sommetsZone_;
//	PointControl* point_;
	int nbButGauche_ = 0;
	int nbButDroite_ = 0;
//	PointControl* test;
	int init_;
	 GLuint prog_;
	//opengl::Nuanceur nuanceurSommet_;
	//opengl::Programme programme_;
};


#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__

//
/////////////////////////////////////////////////////////////////////////////////
///// @}
/////////////////////////////////////////////////////////////////////////////////
//
//	NoeudRondelle * obtenirRondelle();
//
//	//Partie* partie_ = nullptr;
//private:
//	/// Angle dans le sinus de l'oscillation
//	float angle_{ 0 };
//	/// Liste d'affichage pour l'affichage de ce noeud.
//	static GLuint liste_;
//	/// nombre d'objet de cette classe
//	static int nbObjet_;
//	GLint locVertex;
//	GLint locColor;
//	/// Fonction qui affiche la surface de la table
//
//	void dessinerPointsDeControle() const;
//	bool deplacerPointDeControle(double x, double y);
//	/// Fonction qui v�rifie si les points de contr�le sont include dans la zone d'�dition
//	bool pointsDansZoneEdition() const;
//
//	/// position des 8 points de controle
//	glm::dvec3  ptControle_[13];
//	glm::dvec3 sommetT_[13];
//	/// indique le point appuy�, -1 si aucun point ne l'est
//	int Appuye_;
//	/// indique s'il faut afficher les points de controle
//	bool afficherPtControle_;
//	/// propri�t�s d'affichage de la table
//	// La demi largeur des chacun des points de controle
//	int demiLargeurPtControle_;
//	// La demi largeur des chacun des buts
//	int demiLargeurBut_;
//	// hauteur de la table en Z
//	int hauteur_;
//	// epaisseur de la table
//	int epaisseur_;
//	// epaisseur de la bordure de la table
//	int epaisseurBordure_;
//	// hauteur de la bordure de la table
//	int hauteurBordure_;
//	// epaisseur des buts
//	int epaisseurButs_;
//	// epaisseur de la ligne du milieu
//	int epaisseurLigneMilieu_;
//	/// propri�t�s de jeu
//	/*double rebondissement_; // coefficient de rebondissement des murs*/
//	double friction_;	//coefficient de friction de la table
//	double acceleration_; //coefficient d'acceleration des bonus accelerateurs
//	double coefRebondissement_;/// limites que les points de controle ne peuvent franchir
//
//	int limiteDistanceBarreRouge_;
//	int limiteHorizontaleBut_;
//	int limiteAxeHorizontal_;
//	int limiteHorizontalBut_;
//	/// maillet du premier joueur
//	NoeudMaillet* mailletPrincipal_;
//	/// maillet de l'adversaire
//	NoeudMaillet* mailletAdversaire_;
//	/// rondelle
//	NoeudRondelle* rondelle_;
//	//liste des portails dans la table
//	std::vector<NoeudPortail*> listePortails_;
//	VisiteurCollision* collision_;
//
//	
//	
//};
//
//
//#endif // __ARBRE_NOEUDS_NOEUDTABLE_H__
//
//
/////////////////////////////////////////////////////////////////////////////////
///// @}
///////////////////////////////////////////////////////////////////////////////
