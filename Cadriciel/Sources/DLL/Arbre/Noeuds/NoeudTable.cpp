
///////////////////////////////////////////////////////////////////////////
/// @file NoeudTable.cpp
 /// @author equipe06
 /// @date 2016-09-07
 /// @version 1.0
 ///
 /// @addtogroup inf2990 INF2990
 /// @{
 ///////////////////////////////////////////////////////////////////////////
#include "NoeudTable.h"
#include "../Arbre/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::NoeudTable(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres. Il permet
/// d'assigner les attributs par des valeurs de base.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::NoeudTable(const std::string& typeNoeud) : NoeudComposite{ typeNoeud }
{
	ptControle_[0] = glm::vec3(69, -47, 0.0);            // Sommet P0
	ptControle_[1] = glm::vec3(69, 0.0, 0.0);            // Sommet P1
	ptControle_[2] = glm::vec3(69, 47, 0.0);            // Sommet P2
	ptControle_[3] = glm::vec3(0.0, 47, 0.0);          // Sommet P3 ptControle_[7] = glm::vec3(-69, 47, 0.0);          // Sommet P7
	ptControle_[4] = glm::vec3(-69, 47, 0.0);           // Sommet P4 ptControle_[3] = glm::vec3(0.0, -47, 0.0);          // Sommet P3 
	ptControle_[5] = glm::vec3(-69, 0.0, 0.0);			// Sommet P5 ptControle_[6] = glm::vec3(-69, 0.0, 0.0);         // Sommet P6
	ptControle_[6] = glm::vec3(-69, -47, 0.0);         // Sommet P6 ptControle_[5] = glm::vec3(-69, -47, 0.0);			// Sommet P5
	ptControle_[7] = glm::vec3(0.0, -47, 0.0);          // Sommet P7 ptControle_[4] = glm::vec3(0.0, 47, 0.0);           // Sommet P4
	ptControle_[8] = glm::vec3(0.0, 0.0, 0.0);        // Sommet P8


	sommetT_[0] = glm::vec3(ptControle_[0].x , ptControle_[0].y , ptControle_[0].z);
	sommetT_[1] = glm::vec3(ptControle_[1].x , ptControle_[1].y, ptControle_[1].z);
	sommetT_[2] = glm::vec3(ptControle_[2].x , ptControle_[2].y, ptControle_[2].z);
	sommetT_[3] = glm::vec3(ptControle_[3].x, ptControle_[3].y, ptControle_[3].z);
	sommetT_[4] = glm::vec3(ptControle_[4].x, ptControle_[4].y , ptControle_[4].z);
	sommetT_[5] = glm::vec3(ptControle_[5].x , ptControle_[5].y, ptControle_[5].z);
	sommetT_[6] = glm::vec3(ptControle_[6].x , ptControle_[6].y, ptControle_[6].z);
	sommetT_[7] = glm::vec3(ptControle_[7].x , ptControle_[7].y, ptControle_[7].z);
	sommetT_[8] = glm::vec3(ptControle_[8].x , ptControle_[8].y , ptControle_[8].z);

	//Definition des sommets pour les buts
	sommetT_[9] =  glm::vec3(sommetT_[5].x, sommetT_[5].y+10, 0);
	sommetT_[10] = glm::vec3(sommetT_[5].x, sommetT_[5].y-10, 0);
	sommetT_[11] = glm::vec3(sommetT_[1].x, sommetT_[1].y+10, 0);
	sommetT_[12] = glm::vec3(sommetT_[1].x, sommetT_[1].y-10, 0);

	
	friction_ = 0.98;
	coefRebondissement_ = 50;
	acceleration_ = 3.0;
	redefinirSommets();
	definirZone();
	init_ = true;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTable::~NoeudTable()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTable::~NoeudTable()
{
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::afficherConcret(const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	//// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(vueProjection, attribuerCouleur);
	//// Révolution autour du centre.
	//auto modele = glm::rotate(transformationRelative_, 35.0f, glm::vec3(sqrtf(2), sqrtf(2), 0));
	//// Affichage du modèle.
	//vbo_->dessiner(vueProjection * modele);
#define pos0 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[0],1)))
#define pos1 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[1],1)))
#define pos2 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[2],1)))
#define pos3 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[3],1)))
#define pos4 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[4],1)))
#define pos5 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[5],1)))
#define pos6 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[6],1)))
#define pos7 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[7],1)))
#define pos8 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[8],1)))

#define BUT11 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[5].x, sommetT_[5].y+10, 0, 1)))
#define BUT12 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[5].x, sommetT_[5].y-10, 0, 1)))
#define BUT21 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[1].x, sommetT_[1].y+10, 0, 1)))
#define BUT22 glm::value_ptr(glm::vec3(vueProjection * glm::vec4(sommetT_[1].x, sommetT_[1].y-10, 0, 1)))


	/*glBegin(GL_POINTS);
	for (int i = 0;i<1000;++i)
	{
	glVertex3f(cos(2 * 3.14159*i / 1000.0), sin(2 * 3.14159*i / 1000.0), 0);
	}
	glEnd();*/
	///////points de controle///////////////////////////////
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	glPointSize(9.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	glPointSize(9.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos1);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos3);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos4);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos6);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	glPointSize(8.0f);
	glBegin(GL_POINTS);
	glVertex3fv(pos7);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	/////////////////////////////////////////////////////




	///Buts
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirLigneMilieu());
	glLineWidth(8.0f);
	///But de gauche
	glBegin(GL_LINES); glVertex3fv(pos5); glVertex3fv(BUT11); glEnd();
	glBegin(GL_LINES); glVertex3fv(pos5); glVertex3fv(BUT12); glEnd();

	///But de droite
	glBegin(GL_LINES); glVertex3fv(pos1); glVertex3fv(BUT21); glEnd();
	glBegin(GL_LINES); glVertex3fv(pos1); glVertex3fv(BUT22); glEnd();
	glDisable(GL_TEXTURE_2D);

	//glDisable(GL_TEXTURE_2D);
	///////////////////////bordure/////////////////////////////
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordure(0));
	glLineWidth(6.0f);
	glBegin(GL_LINES);
	glVertex3fv(pos0);
	glVertex3fv(pos2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordure(0));
	glLineWidth(6.0f);
	glBegin(GL_LINES);
	glVertex3fv(pos2);
	glVertex3fv(pos4);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordure(0));
	glLineWidth(6.0f);
	glBegin(GL_LINES);
	glVertex3fv(pos4);
	glVertex3fv(pos6);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordure(0));
	glLineWidth(6.0f);
	glBegin(GL_LINES);
	glVertex3fv(pos6);
	glVertex3fv(pos0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	///////////////Ligne mediane///////////////////////////////////

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirLigneMilieu());
	glLineWidth(4.0f);
	glBegin(GL_LINES);
	glVertex3fv(pos3);
	glVertex3fv(pos7);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirLigneMilieu());
	glBegin(GL_POINTS);
		for (int i = 0;i<1000;++i)
		{
			//glVertex3f(rayonAttraction_*cos(2 * utilitaire::PI*i / 1000.0), rayonAttraction_*sin(2 * utilitaire::PI*i / 1000.0), 0);
			glVertex3f(5*cos(2 * utilitaire::PI*i / 1000.0), 5*sin(2 * utilitaire::PI*i / 1000.0), 0);
		}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//////////////surface Table//////////////////////////////////
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureGlace());
	glBegin(GL_QUADS);
	glVertex3fv(pos1);
	glVertex3fv(pos2);
	glVertex3fv(pos3);
	glVertex3fv(pos8);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(pos8);
	glVertex3fv(pos3);
	glVertex3fv(pos4);
	glVertex3fv(pos5);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(pos5);
	glVertex3fv(pos6);
	glVertex3fv(pos7);
	glVertex3fv(pos8);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(pos8);
	glVertex3fv(pos1);
	glVertex3fv(pos0);
	glVertex3fv(pos7);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	///////////////////////////////////////////////////////////////////////////

	glEnable(GL_NORMALIZE);
	// Affichage du modèle 
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}
///////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::accepter()
///
/// @return Aucune.
///
///////////////////////////////////////////////////////////////////////////
//void NoeudTable::accepter(VisiteurAbstrait& visiteur)
//{
//	visiteur.visiter(*this);
//}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::animer(float temps)
{
	if (init_) {
		for (auto enfant : enfants_) {
			if (enfant->obtenirType() == "portail") {
				listePortails_.push_back(dynamic_cast<NoeudPortail*>(enfant));
			}
			if ((enfant->obtenirType() == "rondelle"))
				rondelle_ = dynamic_cast<NoeudRondelle*>(enfant);
			if ((enfant->obtenirType() == "maillet"))
				mailletPrincipal_ = dynamic_cast<NoeudMaillet*>(enfant);
			if ((enfant->obtenirType() == "mailletV"))
				mailletAdversaire_ = dynamic_cast<NoeudMailletVirtuel*>(enfant);
			if ((enfant->obtenirType() == "maillet"))
				mailletAdversaire_ = dynamic_cast<NoeudMaillet*>(enfant);
		}
		collision_ = new VisiteurCollision(rondelle_, coefRebondissement_, listePortails_, acceleration_);
		collision_->initialiserScores();
		definirZone();
		init_ = false;
	}
	if (estModifier_) {
		redefinirSommets();
		estModifier_ = false;
	}
	NoeudComposite::animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::redessiner()
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::redessiner() {
	NoeudComposite::redessiner();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudTable::obtenirFriction()
///
/// Cette fonction permet d'obtenir la friction.
///
/// @return La friction
///
////////////////////////////////////////////////////////////////////////
double NoeudTable::obtenirFriction() const
{
	return friction_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::modifierFriction(double friction)
///
/// Cette fonction permet de modifier la friction
///
/// @param[in] friction : la friction
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::modifierFriction(double friction)
{
	friction_ = friction;
	//std::cout << friction_  << std::endl;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudTable::obtenirCoefRebondissement()
///
/// Cette fonction permet d'obtenir le coefficient de rebondissement.
///
/// @return Le coefficient de rebondissement
///
////////////////////////////////////////////////////////////////////////
double NoeudTable::obtenirCoefRebondissement()
{
	return coefRebondissement_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::modifierCoefRebondissement
///										(double coefRebondissement)
///
/// Cette fonction permet de modifier le coefficient de rebondissement.
///
/// @param[in] coefRebondissement : le coefficient de rebondissement.
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::modifierCoefRebondissement(double coefRebondissement)
{
	coefRebondissement_ = coefRebondissement;
	//std::cout << coefRebondissement_ << std::endl;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudTable::obtenirAcceleration()
///
/// Cette fonction permet d'obtenir l'acceleration des bonus.
///
/// @return L'acceleration des bonus
///
////////////////////////////////////////////////////////////////////////
double NoeudTable::obtenirAcceleration()
{
	return acceleration_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::modifierAcceleration(double acceleration)
///
/// Cette fonction permet de modifier l'acceleration.
///
/// @param[in] acceleration : l'acceleration.
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::modifierAcceleration(double acceleration)
{
	acceleration_ = acceleration;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::redefinirSommets()
///
/// Cette fonction permet de modifier redefinir les sommets apres une modification.
///
/// @param[in] Aucun.
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::redefinirSommets()
{
	unsigned int nbSommets = 13;
	for (unsigned int i = 0; i < nbSommets; i++) {
		sommets_.push_back(sommetT_[i]);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTable::definirZone()
///
/// Cette fonction permet de modifier dire dans quel zone la souri doit 
///se trouver pour modifier la position d'un objet.
///
/// @param[in] Aucun.
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudTable::definirZone() {
	for (unsigned int i = 0; i < 8; i++) {

		sommetsZone_.push_back(sommetT_[i]);
	}
}

//Verifie si le curseur st toujour dans la table
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudTable::curseurEstDansTable(glm::dvec3 pos)
///
/// Cette fonction permet de savoir si la souris est dans la table
///
/// @param[in] pos : la position de la souris.
///
/// @return true si oui, false sinon
///
////////////////////////////////////////////////////////////////////////
bool NoeudTable::curseurEstDansTable(glm::dvec3 pos)
{
	return utilitaire::pointsDansPolygone2D(pos, sommets_);
}

bool NoeudTable::curseurEstDansZone(glm::dvec3 pos)
{	
	return utilitaire::pointsDansPolygone2D(pos, sommetsZone_);
}

void NoeudTable::chercherCollisions()
{
	collision_->visiter(this);
}

void NoeudTable::assignerRondelle(NoeudRondelle * rond)
{
	rondelle_ = rond;
}

NoeudRondelle * NoeudTable::obtenirRondelle()
{
	return rondelle_;
}

void NoeudTable::incrementerGauche()
{
	nbButGauche_++;
}
void NoeudTable::incrementerDroite()
{
	nbButDroite_++;
}
int NoeudTable::getGauche()
{
	return nbButGauche_;
}
int NoeudTable::getDroite()
{
	return nbButDroite_;
}

void NoeudTable::reinitialiserBut()
{
	nbButGauche_ = 0;
	nbButDroite_ = 0;
}

/////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
