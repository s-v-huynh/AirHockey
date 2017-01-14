///////////////////////////////////////////////////////////////////////////////
/// @file PointControl.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "PointControl.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include "FacadeModele.h"
#include "../Arbre/Texture.h"

#include "Modele3D.h"
#include "OpenGL_VBO.h"

int PointControl::pControl_ = 0;
int NoeudAbstrait::compteurPControl_ = 0;
 
////////////////////////////////////////////////////////////////////////
///
/// @fn PointControl::PointControl(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
PointControl::PointControl(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	NoeudAbstrait::compteurPControl_++;
	couleurPointControl_[0] = 255;
	couleurPointControl_[1] = 255;
	couleurPointControl_[2] = 0;
	couleurPointControl_[1] = 0;
	attribuerCouleur();

}


////////////////////////////////////////////////////////////////////////
///
/// @fn PointControl::~PointControl()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
PointControl::~PointControl()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void PointControl::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le modèle à sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void PointControl::afficherConcret(const glm::mat4& matrVue, const glm::mat4& matrProjection, const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	glPushName(id_);
	glPushMatrix();
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(matrVue, matrProjection, vueProjection, attribuerCouleur);
	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurPointControl_[0];
	couleurObjet[1] = couleurPointControl_[1];
	couleurObjet[2] = couleurPointControl_[2];
	GLubyte couleurSelection[3];
	couleurSelection[0] = couleurSelection_[0];
	couleurSelection[1] = couleurSelection_[1];
	couleurSelection[2] = couleurSelection_[2];
	// Révolution autour du centre.
	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(sqrtf(2), sqrtf(2), 0));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0.0f, 0.0f, -1.0f));
	modele = glm::translate(modele, centreRotation_);
	glm::dvec3 po = obtenirPositionRelative();
	//cout << po[0] << "	" << po[1] << endl;
	//glPointSize(9.0f);
	glm::vec4 Position = glm::vec4(obtenirPositionRelative(), 0.1f);
	glm::mat4 Model = glm::translate(transformationRelative_, glm::vec3(1.0f));
	glm::vec4 Transformed =vueProjection* Model * Position;
	/*glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(Transformed.x, Transformed.y, 0.0);//0
	glVertex3f(-Transformed.x, Transformed.y, 0.0);//2
	glVertex3f(Transformed.x, -Transformed.y, 0.0);//4
	glVertex3f(-Transformed.x, -Transformed.y, 0.0);//6
	glEnd();*/
	/*std::vector<glm::dvec3>listePoint;
	//listePoint.push_back(obtenirPositionRelative());
	glm::vec3 sommet0 = listePoint[0];
	glm::vec3 sommet1 = listePoint[1];
	glm::vec3 sommet2 = listePoint[2];
	glm::vec3 sommet3 = listePoint[3];
	glm::vec3 sommet4 = listePoint[4];
	glm::vec3 sommet5 = listePoint[5];
	glm::vec3 sommet6 = listePoint[6];
	glm::vec3 sommet7 = listePoint[7];
	glm::vec3 sommet8 = listePoint[8];*/
	//glm::vec3 sommet8 = listePoint[9];
	/*glm::vec3 baz[8] = { obtenirPositionRelative() };
	for (int i = 0; i < 7; i++)
	{
		cout << baz[i].x << "	" << baz[i].y << endl;
	}*/
	//vbo_->dessiner(estSelectionne(), attribuerCouleur, couleurObjet, couleurSelection, modele, matrVue, matrProjection, vueProjection*modele);

	glPopMatrix();
	glPopName();
}

void PointControl::obtenirPoint()
{
	//table_ = dynamic_cast <NoeudTable*>(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table"));
	//listePoints_.push_back(dynamic_cast <PointControl*>(table_->chercher("point")));

	//for (int i = 0; i < 8; i++)
	//{
	//	   // Sommet P8
	//	cout << listePoints_[i]->obtenirPositionRelative().x << listePoints_[i]->obtenirPositionRelative().y << endl;
	//}
}



////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PointControl::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araignée oscille selon une période de 4 secondes.
	/*angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	glm::vec3 position(0.0f);
	position[0] = 5.0f * static_cast<float>(cos(utilitaire::DEG_TO_RAD(angle_)));
	position[1] = 40.0f * static_cast<float>(sin(utilitaire::DEG_TO_RAD(angle_)));

	assignerPositionRelative(position);*/
}
void PointControl::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void PointControl::attribuerCouleur()
///
/// Cette fonction attribut une couleur.
///
///
////////////////////////////////////////////////////////////////////////
void PointControl::attribuerCouleur()
{
	if (NoeudAbstrait::compteurPControl_ < 180)
	{
		couleurPointControl_[0] = 255;
		couleurPointControl_[1] = 255 - NoeudAbstrait::compteurPControl_ + 1;
		couleurPointControl_[2] = PointControl::pControl_;
		//std::cout << "couleur attribuée: " << (int)couleurPortail_[0] << ";" << (int)couleurPortail_[1] << ";" << (int)couleurPortail_[2] << std::endl;

	}
	else
	{
		NoeudAbstrait::compteurPControl_ = 1;
		PointControl::pControl_++;
		couleurPointControl_[0] = PointControl::pControl_;
		couleurPointControl_[1] = 0;
		couleurPointControl_[2] = 155;
	}
}
bool PointControl::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;
	//cout << "couleur objet selection: " << (int)couleurSelection_[2] << endl;

	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;

	}
	else if (couleurObjet[0] == couleurPointControl_[0] && couleurObjet[1] == couleurPointControl_[1] && couleurObjet[2] == couleurPointControl_[2])
	{
		estPointe = true;
		if (couleurSelection_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			attribuerCouleurSelection();

		}
	}
	obtenirPoint();

	return estPointe;
}
void PointControl::deplacementPointControl(double x, double y)
{
	glm::dvec3 deplacement;
	deplacement += obtenirPositionRelative();
	assignerPositionRelative(deplacement);

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
