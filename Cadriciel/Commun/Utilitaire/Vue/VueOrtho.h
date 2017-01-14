//////////////////////////////////////////////////////////////////////////////
/// @file VueOrtho.h
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUEORTHO_H__
#define __UTILITAIRE_VUEORTHO_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionOrtho.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class VueOrtho
	/// @brief Classe concr�te de vue orthogonale.
	///
	/// Cette classe implante le comportement attendu d'une vue orthogonale.
	///
	/// @author Martin Bisson
	/// @date 2006-12-16
	////////////////////////////////////////////////////////////////////////
	class VueOrtho : public Vue
	{
	public:
		// Constructeur.
		VueOrtho(Camera const& camera, ProjectionOrtho const& projection);

		/// Obtention de la projection.
		virtual const ProjectionOrtho& obtenirProjection() const;

		/// Modification de la clot�re.
		virtual void redimensionnerFenetre(int largeur, int hauteur);

		/// Zoom in, c'est-�-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-�-dire un rapetissement.
		virtual void zoomerOut();
		/// Zoom in �lastique.
		virtual void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);
		/// Zoom out �lastique.
		virtual void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);

		/// D�placement dans le plan XY par rapport � la vue.
		virtual void deplacerXY(double deplacementX, double deplacementY);
		/// D�placement dans le plan XY par rapport � la vue.
		virtual void deplacerXY(const glm::ivec2& deplacement);
		/// D�placement selon l'axe des Z par rapport � la vue.
		virtual void deplacerZ(double deplacement);
		/// Rotation selon les axes des X et des Y par rapport � la vue.
		virtual void rotaterXY(double rotationX, double rotationY);
		/// Rotation selon les axes des X et des Y par rapport � la vue.
		virtual void rotaterXY(const glm::ivec2& rotation);
		/// Rotation selon l'axe des Z par rapport � la vue.
		virtual void rotaterZ(double rotation);


	private:
		/// Projection utilis�e pour cette vue.
		ProjectionOrtho projection_;

	};


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUEORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
