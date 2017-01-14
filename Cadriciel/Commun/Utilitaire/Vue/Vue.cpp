/////////////////////////////////////////////////////////////////////////////////
/// @file Vue.cpp
/// @author DGI
/// @date 2006-12-18
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
/////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"

#include "Vue.h"
#include "Projection.h"
#include "Plan3D.h"
#include "Droite3D.h"
#include "glm/gtc/type_ptr.hpp"

namespace vue {


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn Vue::Vue(const Camera& camera)
	///
	/// Ce constructeur permet d'assigner la cam�ra de cette vue.
	///
	/// @param[in] camera : La cam�ra associ�e � cette vue.
	///
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////////
	Vue::Vue(const Camera& camera)
		: camera_{ camera }
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool Vue::convertirClotureAVirtuelle(int x, int y, const math::Plan3D& plan, glm::dvec3& point) const
	///
	/// Cette fonction permet de transformer un point (donn� en coordonn�es
	/// d'affichage) en coordonn�es virtuelles �tant donn� un certain plan sur
	/// lequel doit se trouver le point.  Elle utilise les fonction d'OpenGL
	/// donc cette fonction s'applique peu importe la position de la cam�ra.
	///
	/// @param[in]      x     : La position @a X du point en coordonn�e
	///                         d'affichage.
	/// @param[in]      y     : La position @a Y du point en coordonn�e
	///                         d'affichage.
	/// @param[in]      plan  : Le plan sur lequel on veut trouver la position
	///                         correspondante en virtuel.
	/// @param[in, out] point : point transform� @a (x,y) le @a z est le m�me
	///                         que le plan
	///
	/// @return Faux s'il est impossible de convertir le point en virtuel
	///         puisque le plan est parall�le � la direction de la cam�ra, vrai
	///         autrement.
	///
	////////////////////////////////////////////////////////////////////////////
	bool Vue::convertirClotureAVirtuelle(int x, int y, const math::Plan3D& plan, glm::dvec3& point) const
	{
		//Initialisation de variables.
		const GLdouble MinZ{ 0.0 };
		const GLdouble MaxZ{ 1.0 };

		// Obtenir la matrice de projection.
		glm::dmat4 matriceCamera = this->obtenirCamera().obtenirMatrice();

		// Obtenir la matrice de projection.
		glm::dmat4 matriceProjection = this->obtenirProjection().obtenirMatrice();

		// Lire la cl�ture.
		glm::ivec4 cloture;
		glGetIntegerv(GL_VIEWPORT, glm::value_ptr(cloture));

		// Premier point.
		glm::dvec3 point1;
		gluUnProject(
			x, cloture[3] - y, MinZ,
			glm::value_ptr(matriceCamera), glm::value_ptr(matriceProjection), glm::value_ptr(cloture),
			&point1[0], &point1[1], &point1[2]
			);

		// Deuxi�me point.
		glm::dvec3 point2;
		gluUnProject(
			x, cloture[3] - y, MaxZ,
			glm::value_ptr(matriceCamera), glm::value_ptr(matriceProjection), glm::value_ptr(cloture),
			&point2[0], &point2[1], &point2[2]
			);

		// On construit la droite.
		math::Droite3D DroiteCoupe{ point1, point2 };

		return DroiteCoupe.intersection(plan, point);
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool Vue::convertirClotureAVirtuelle(int x, int y, glm::dvec3& point) const
	///
	/// Cette fonction permet de transformer un point (donn� en coordonn�es
	/// d'affichage) en coordonn�es virtuelles dans le plan XY.
	///
	/// @param[in]      x     : La position @a X du point en coordonn�e
	///                         d'affichage.
	/// @param[in]      y     : La position @a Y du point en coordonn�e
	///                         d'affichage.
	/// @param[in, out] point : point transform� @a (x,y) le @a z est le m�me
	///                         que le plan
	///
	/// @return Faux s'il est impossible de convertir le point en virtuel
	///         puisque le plan est parall�le � la direction de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////////
	bool Vue::convertirClotureAVirtuelle(int x, int y, glm::dvec3& point) const
	{
		const math::Plan3D plan{ glm::dvec3(0, 0, 1), glm::dvec3(0, 0, 0) };
		return convertirClotureAVirtuelle(x, y, plan, point);
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Vue::animer(double temps)
	///
	/// Cette fonction permet de faire �voluer la vue en fonction du temps, par
	/// exemple lorsque cette derni�re se d�place par rapport � un objet en
	/// fonction du temps.
	///
	/// @param[in]  temps double : L'intervalle de temps pour lequel r�aliser
	///                            l'animation.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Vue::animer(double temps)
	{
	}

	void Vue::redessiner()
	{
	}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
