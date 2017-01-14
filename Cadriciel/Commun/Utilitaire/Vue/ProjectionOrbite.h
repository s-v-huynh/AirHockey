#pragma once
////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrbite.h
/// @author equipe06
/// @date 2016-11-17
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTIONPESPECTIVE_H__
#define __UTILITAIRE_ProjectionOrbite_H__


#include "Projection.h"
#include <glm/fwd.hpp>

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class ProjectionOrbite
	/// @brief Classe implantant une projection orthogonale.
	///
	/// Cette classe implante l'interface de projection définie par la
	/// classe de base Projection et ajoute certaines fonctionnalitées
	/// spécifiques à la projection orthogonale, comme le zoom autour d'un
	/// point en particulier et le zoom élastique.
	///
	/// @author equipe06
	/// @date 2016-11-17
	////////////////////////////////////////////////////////////////////////
	class ProjectionOrbite : public Projection
	{
	public:
		/// Constructeur.
		ProjectionOrbite(int largeurCloture, int hauteurCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom,double largeurFenetre, double hauteurFenetre);


		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomerOut();
		/// Modification de la clôture.
		virtual void redimensionnerFenetre(int largeur, int hauteur);
		/// Obtention de la matrice de projection.
		virtual glm::mat4 obtenirMatrice() const;

		/// Obtenir les coordonnées de la fenêtre virtuelle.
		inline glm::dvec2 obtenirDimensionFenetreVirtuelle() const;

		/// Zoom in, c'est-à-dire un agrandissement.
		virtual void zoomIn(const glm::ivec2& coin1,
			const glm::ivec2& coin2);
		/// Zoom out, c'est-à-dire un rapetissement.
		virtual void zoomOut(const glm::ivec2& coin1,
			const glm::ivec2& coin2);

		void setLargeurFenetre(double x) { largeurFenetre_ = x; };
		void setHauteurFenetre(double x) { hauteurFenetre_ = x; };
		virtual void appliquer()const;
		void centrerSurPoint(const glm::ivec2& pointCentre);

	private:
		/// Ajuste la fenêtre virtuelle pour respecter le rapport d'aspect.
		void ajusterRapportAspect();

		/// Largeur de la fenêtre virtuelle.
		double largeurFenetre_;
		/// Hauteur de la fenêtre virtuelle.
		double hauteurFenetre_;

		double xMax_;
		double yMax_;
		double xMin_;
		double yMin_;

	};

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void ProjectionOrbite::obtenirCoordonneesFenetreVirtuelle(double& xMin, double& xMax, double& yMin, double& yMax) const
	///
	/// Cette fonction retourne les coordonnées de la fenêtre virtuelle
	/// associée à cette projection.
	///
	/// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
	/// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
	/// @param[out]  yMin : La variable qui contiendra l'ordonnée minimale.
	/// @param[out]  yMax : La variable qui contiendra l'ordonnée maximale.
	///
	/// @return Les coordonnées de la fenêtre virtuelle.
	///
	////////////////////////////////////////////////////////////////////////
	inline glm::dvec2 ProjectionOrbite::obtenirDimensionFenetreVirtuelle() const
	{
		return glm::dvec2(largeurFenetre_, hauteurFenetre_);
	}


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_ProjectionOrbite_H__


   ///////////////////////////////////////////////////////////////////////////
   /// @}
   ///////////////////////////////////////////////////////////////////////////
