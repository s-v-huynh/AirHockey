
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
#include "OpenGL_VBO.h"
#include "FacadeModele.h"
#define VERTEX_LOCATION 0
static opengl::Nuanceur nuanceurSommet_;
static opengl::Nuanceur nuanceurFragment_;

static opengl::Programme programme_;
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
	/*couleurTable_[0] = 0;
	couleurTable_[1] = 100;
	couleurTable_[2] = 120;*/

	friction_ = 0.98;
	coefRebondissement_ = 50;
	acceleration_ = 3.0;
	redefinirSommets();
	definirZone();
	init_ = true;
	//nuanceurSommet_.initialiser(opengl::Nuanceur::Type::NUANCEUR_VERTEX, "nuanceurs/sommet.glsl");
	

	//Programme::Start(programme_);
	
}

//void NoeudTable::assignerUniformMatrix4fv(const GLchar *nom, MatricePipeline &val) { assignerUniformMatrix4fv(nom, glm::value_ptr(val.getMatr())); }
void NoeudTable::point()
{
	/*point_ = dynamic_cast<PointControl*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("point"));
	listePoint_.push_back(point_);
	for (int i = 0; i < 8; i++) {
		cout << listePoint_[i]->obtenirPositionRelative().x << "-----" << listePoint_[i]->obtenirPositionRelative().y << endl;
	}*/
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
void NoeudTable::afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	//// Appel à la version de la classe de base pour l'affichage des enfants.
	///NoeudComposite::afficherConcret(vueProjection, attribuerCouleur);

	//// Révolution autour du centre.
	//auto modele = glm::rotate(transformationRelative_, 35.0f, glm::vec3(0, 0, -1));

	if (!programme_.estInitialise())
	{
		nuanceurSommet_.initialiser(opengl::Nuanceur::Type::NUANCEUR_VERTEX, "nuanceurs/sommetT.glsl");
		nuanceurFragment_.initialiser(opengl::Nuanceur::Type::NUANCEUR_FRAGMENT, "nuanceurs/fragmentT.glsl");
		programme_.initialiser();
		programme_.attacherNuanceur(nuanceurSommet_);
		programme_.attacherNuanceur(nuanceurFragment_);

	}
	Programme::Start(programme_);
	programme_.assignerUniforme("viewProjection", vueProjection);
	glm::mat4x4 const& mV{ vueProjection*glm::inverse(matrProjection) };
	programme_.assignerUniforme("matrVue", matrVue);
	programme_.assignerUniforme("matrProjection", matrProjection);
	programme_.assignerUniforme("matrNormal", glm::mat3(glm::transpose(glm::inverse(mV))));

	glm::vec3 somet0 = glm::vec3(glm::vec4(ptControle_[0], 1));
	glm::vec3 somet1 = glm::vec3(glm::vec4(ptControle_[1], 1));
	glm::vec3 somet2 = glm::vec3(glm::vec4(ptControle_[2], 1));
	glm::vec3 somet3 = glm::vec3(glm::vec4(ptControle_[3], 1));
	glm::vec3 somet4 = glm::vec3(glm::vec4(ptControle_[4], 1));
	glm::vec3 somet5 = glm::vec3(glm::vec4(ptControle_[5], 1));
	glm::vec3 somet6 = glm::vec3(glm::vec4(ptControle_[6], 1));
	glm::vec3 somet7 = glm::vec3(glm::vec4(ptControle_[7], 1));
	glm::vec3 somet8 = glm::vec3(glm::vec4(ptControle_[8], 1));



	glm::vec3 but11 = glm::dvec3(somet5.x,somet5.y+10,0.1);
	glm::vec3 but12 = glm::dvec3(somet5.x, somet5.y - 10, 0.1);
	glm::vec3 but21 = glm::dvec3(somet1.x, somet5.y + 10, 0.1);
	glm::vec3 but22 = glm::dvec3(somet1.x, somet5.y - 10, 0.1);

	glDisable(GL_DEPTH_TEST);

	glPushMatrix();

	glLoadIdentity();

	GLuint indLightSource;
	GLuint indFrontMaterial;
	GLuint indLightModel;
	GLuint indvarsUnif;
	GLuint ubo[4];

	// d�finition des lumi�res
	struct LightSourceParameters
	{
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::vec4 position[2];
		glm::vec3 spotDirection[2];
		float spotExposant;
		float spotAngle;            // ([0.0,90.0] ou 180.0)
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
	} LightSource = { glm::vec4(0.2, 0.2, 0.2, 1.0),
		glm::vec4(0.4, 0.4, 0.4, 1.0),
		glm::vec4(0.6, 0.6, 0.6, 1.0),
		{ glm::vec4(-69, 0.0, 5.0, 1.0), glm::vec4(69, 0.0, 5.0, 1.0) } ,
		{ glm::vec3(35.0, 0.0, 1.0), glm::vec3(-35.0, 0.0, 1.0) },
		0.01,       // l'exposant du c�ne
		5,      // l'angle du c�ne du spot
		1., 0., 0. };
	//ptControle_[5] = glm::vec3(-69, 0.0, 0.0);
	//ptControle_[1] = glm::vec3(69, 0.0, .0);
	// d�finition du mat�riau
	struct MaterialParameters
	{
		glm::vec4 emission;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		float shininess;
	} FrontMaterial = { glm::vec4(0.0, 0.0, 0.0, 1.0),
		glm::vec4(0.2, 0.2, 0.2, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		500.0 };


	struct LightModelParameters
	{
		glm::vec4 ambient; // couleur ambiante
	} LightModel = { glm::vec4(0.2,0.2,0.2,1.0) };

	struct
	{
		int ambianteActive;
		int directionelleActive;
		int spotActive;
	} varsUnif = { FacadeModele::obtenirInstance()->obtenirEtatAmbiante(), FacadeModele::obtenirInstance()->obtenirDirectionnelActive(), FacadeModele::obtenirInstance()->obtenirEtatSpot() };


	// allouer les UBO pour les variables uniformes
	glGenBuffers(4, ubo);

	indLightSource = glGetUniformBlockIndex(programme_.obtenirHandle(), "LightSourceParameters");
	indFrontMaterial = glGetUniformBlockIndex(programme_.obtenirHandle(), "MaterialParameters");
	indLightModel = glGetUniformBlockIndex(programme_.obtenirHandle(), "LightModelParameters");
	indvarsUnif = glGetUniformBlockIndex(programme_.obtenirHandle(), "varsUnif");

	// charger les ubo
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo[0]);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(LightSource), &LightSource, GL_DYNAMIC_COPY);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		const GLuint bindingIndex = 0;
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, ubo[0]);
		glUniformBlockBinding(programme_.obtenirHandle(), indLightSource, bindingIndex);
	}
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo[1]);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(FrontMaterial), &FrontMaterial, GL_DYNAMIC_COPY);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		const GLuint bindingIndex = 1;
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, ubo[1]);
		glUniformBlockBinding(programme_.obtenirHandle(), indFrontMaterial, bindingIndex);
	}
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo[2]);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(LightModel), &LightModel, GL_DYNAMIC_COPY);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		const GLuint bindingIndex = 2;
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, ubo[2]);
		glUniformBlockBinding(programme_.obtenirHandle(), indLightModel, bindingIndex);
	}
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ubo[3]);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(varsUnif), &varsUnif, GL_DYNAMIC_COPY);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		const GLuint bindingIndex = 3;
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, ubo[3]);
		glUniformBlockBinding(programme_.obtenirHandle(), indvarsUnif, bindingIndex);
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureGlace());

	 GLuint sommetID;
	 glGenVertexArrays(1, &sommetID);
	 glBindVertexArray(sommetID);
	 GLfloat sommet_data[] = {
		 somet8.x, somet8.y, somet8.z,//8
		 somet7.x, somet7.y,somet7.z,//7
		 somet0.x, somet0.y, somet0.z,//0
		 somet1.x, somet1.y,somet1.z,//1  
		 somet2.x, somet2.y, somet2.z,//2
		 somet3.x, somet3.y, somet3.z,//3
		 somet4.x, somet4.y, somet4.z,//4
		 somet5.x, somet5.y, somet5.z,//5
		 somet6.x, somet6.y,somet6.z, //6
		 somet7.x, somet7.y, somet7.z,//7


	 };

	 GLuint tamponSommet;
	 glGenBuffers(1, &tamponSommet);
	 glBindBuffer(GL_ARRAY_BUFFER, tamponSommet);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(sommet_data), sommet_data, GL_STATIC_DRAW);

	 glEnableVertexAttribArray(VERTEX_LOCATION);
	 glBindBuffer(GL_ARRAY_BUFFER, tamponSommet);
	 glVertexAttribPointer(VERTEX_LOCATION, 3, GL_FLOAT,GL_FALSE,0,nullptr);
	 glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
	 glDisableVertexAttribArray(0);
	glDisable(GL_TEXTURE_2D);

	 ///ligne du milieu de la table
	glEnable(GL_TEXTURE_2D);
	 glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirLigneMilieu());
	 //glLineWidth(6.0f);
	glBegin(GL_LINES);
	 glVertex3f(somet3.x, somet3.y, 0.0);//0
	 glVertex3f(somet7.x, somet7.y, 0.0);//2
	glEnd();
	glDisable(GL_TEXTURE_2D);

	 ///Bordure de la table
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTextureBordure(0));
	 glLineWidth(8.0f);
	 glBegin(GL_LINE_LOOP);
	 glVertex3f(somet0.x, somet0.y, 0);//0
	 glVertex3f(somet2.x, somet2.y, 0);//2
	 glVertex3f(somet4.x, somet4.y, 0);//4
	 glVertex3f(somet6.x, somet6.y, 0);//6
	 glEnd();
	 glBegin(GL_LINE_LOOP);
	 glVertex3f(somet0.x, somet0.y, 1);//0
	 glVertex3f(somet2.x, somet2.y, 1);//2
	 glVertex3f(somet4.x, somet4.y, 1);//4
	 glVertex3f(somet6.x, somet6.y, 1);//6
	 glEnd();
	 glBegin(GL_LINE_LOOP);
	 glVertex3f(somet0.x, somet0.y, 2);//0
	 glVertex3f(somet2.x, somet2.y, 2);//2
	 glVertex3f(somet4.x, somet4.y, 2);//4
	 glVertex3f(somet6.x, somet6.y, 2);//6
	 glEnd();
	 glBegin(GL_LINE_LOOP);
	 glVertex3f(somet0.x, somet0.y, 3);//0
	 glVertex3f(somet2.x, somet2.y, 3);//2
	 glVertex3f(somet4.x, somet4.y,3);//4
	 glVertex3f(somet6.x, somet6.y, 3);//6
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	 glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirLigneMilieu());
	 ///but de la table
	glBegin(GL_LINES);
	 glVertex3f(but11.x, but11.y, but11.z);//0
	 glVertex3f(but12.x, but12.y, but12.z);//2
	glEnd();
	glBegin(GL_LINES);
	 glVertex3f(but21.x, but21.y, but21.z);//0
	 glVertex3f(but22.x, but22.y, but22.z);//2
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	 glBindTexture(GL_TEXTURE_2D, Texture::obtenirInstance()->obtenirTexturetextureBut());
	 ///but de la table
	 glPointSize(5.0f);
	 glBegin(GL_POINTS);
	 glVertex3f(somet0.x, somet0.y, somet0.z);//0
	 glEnd();
	 glBegin(GL_POINTS);
	 glVertex3f(somet1.x, somet1.y, somet1.z);//1
	 glEnd();
	 glBegin(GL_POINTS);
	 glVertex3f(somet2.x, somet2.y, somet2.z);//2
	glEnd();
	glBegin(GL_POINTS);
	 glVertex3f(somet3.x, somet3.y, somet3.z);//3
	glEnd();
	 glBegin(GL_POINTS);
	 glVertex3f(somet4.x, somet4.y, somet4.z);//4
	glEnd();
	 glBegin(GL_POINTS);
	 glVertex3f(somet5.x, somet5.y, somet5.z);//5
	glEnd();
	 glBegin(GL_POINTS);
	 glVertex3f(somet6.x, somet6.y, somet6.z);//6
	glEnd();
	 glBegin(GL_POINTS);
	 glVertex3f(somet7.x, somet7.y, somet7.z);//7
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// glDeleteBuffers(1, &sommetID);
	 Programme::Stop(programme_);
//	 NoeudComposite::afficherConcret(vueProjection, attribuerCouleur);
	 NoeudComposite::afficherConcret(matrVue, matrProjection, vueProjection, attribuerCouleur);

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
