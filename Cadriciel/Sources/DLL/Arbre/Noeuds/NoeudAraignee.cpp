///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAraignee.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudAraignee.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAraignee::NoeudAraignee(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAraignee::NoeudAraignee(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAraignee::~NoeudAraignee()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAraignee::~NoeudAraignee()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAraignee::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le mod�le � sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAraignee::afficherConcret(const glm::mat4& vueProjection) const
{
	// Appel � la version de la classe de base pour l'affichage des enfants.
//	NoeudComposite::afficherConcret(vueProjection);

	// R�volution autour du centre.
	auto modele = glm::rotate(transformationRelative_, 35.0f, glm::vec3(sqrtf(2), sqrtf(2), 0));
	// Affichage du mod�le.
	//vbo_->dessiner(vueProjection * modele);
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
void NoeudAraignee::animer(float temps)
{
	// Appel � la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araign�e oscille selon une p�riode de 4 secondes.
	angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	glm::vec3 position(0.0f);
	position[0] = 5.0f * static_cast<float>(cos(utilitaire::DEG_TO_RAD(angle_)));
	position[1] = 40.0f * static_cast<float>(sin(utilitaire::DEG_TO_RAD(angle_)));

	assignerPositionRelative(position);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
