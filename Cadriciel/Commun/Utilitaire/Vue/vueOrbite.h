//////////////////////////////////////////////////////////////////////////////
/// @file VueOrbite.h
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VueOrbite_H__
#define __UTILITAIRE_VueOrbite_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionOrbite.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class VueOrbite
	/// @brief Classe concrète de vue orthogonale.
	///
	/// Cette classe implante le comportement attendu d'une vue orthogonale.
	///
	/// @author equipe06
	/// @date 2016-11-17
	////////////////////////////////////////////////////////////////////////
	class VueOrbite : public Vue
	{
	public:
		// Constructeur.
		VueOrbite(Camera const& camera, ProjectionOrbite const& projection);

		/// Obtention de la projection.
		virtual const ProjectionOrbite& obtenirProjection() const;

		/// Modification de la clotûre.
		virtual void redimensionnerFenetre(int largeur, int hauteur);

		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Zoom in élastique.
		virtual void zoomerInElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);
		/// Zoom out élastique.
		virtual void zoomerOutElastique(const glm::ivec2& coin1,
			const glm::ivec2& coin2);

		/// Déplacement dans le plan XY par rapport à la vue.
		virtual void deplacerXY(double deplacementX, double deplacementY, int x, int y);
		/// Déplacement dans le plan XY par rapport à la vue.
		virtual void deplacerXY(const glm::ivec2& deplacement, int x, int y);
		/// Déplacement selon l'axe des Z par rapport à la vue.
		virtual void deplacerZ(double deplacement);
		/// Rotation selon les axes des X et des Y par rapport à la vue.
		virtual void rotaterXY(double rotationX, double rotationY);
		/// Rotation selon les axes des X et des Y par rapport à la vue.
		virtual void rotaterXY(const glm::ivec2& rotation);
		/// Rotation selon l'axe des Z par rapport à la vue.
		virtual void rotaterZ(double rotation);
		virtual void definirProjection()const;
		/// Application de la caméra
		virtual void appliquerCamera() const;
		/// Deplacement de la fenetre virtuelle avec la touche haut.
		virtual void deplacerClavier(double x, double y) ;
		/// Deplacement de la fenetre virtuelle avec la touche Bas.
		virtual void deplacerClavierBas(double x, double y) ;
		/// Deplacement de la fenetre virtuelle avec la touche Droite.
		virtual void deplacerClavierDroite(double x, double y) ;
		/// Deplacement de la fenetre virtuelle avec la touche Gauche.
		virtual void deplacerClavierGauche(double x, double y) ;
		///Deplacement de la vue avec la souris
		virtual void deplacerSouris(glm::dvec3 dSouris);

	private:
		/// Projection utilisée pour cette vue.
		ProjectionOrbite projection_;

	};


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VueOrbite_H__


   ///////////////////////////////////////////////////////////////////////////
   /// @}
   ///////////////////////////////////////////////////////////////////////////
