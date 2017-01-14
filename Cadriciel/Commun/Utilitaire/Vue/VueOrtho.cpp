////////////////////////////////////////////////////////////////////////////////////
/// @file VueOrtho.cpp
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "VueOrtho.h"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VueOrtho::VueOrtho(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une vue orthogonale.  Ne fait que créer les objets
	/// Projection et Camera correspondant.
	///
	/// @param[in] camera        : Caméra à utiliser au départ pour cette vue.
	/// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arrière (en @a z).
	/// @param[in] xMinFenetre   : coordonnée minimale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonnée maximale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonnée minimale en @a y de la fenêtre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonnée maximale en @a y de la fenêtre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	VueOrtho::VueOrtho(Camera const& camera, ProjectionOrtho const& projection) :
		Vue{ camera },
		projection_{projection}
	{
		//definirProjection();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn const ProjectionOrtho& VueOrtho::obtenirProjection() const
	///
	/// Retourne la projection orthogonale associée à cette vue.
	///
	/// @return La projection orthogonale associée à cette vue.
	///
	////////////////////////////////////////////////////////////////////////
	const ProjectionOrtho& VueOrtho::obtenirProjection() const
	{
		return projection_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::redimensionnerFenetre( int largeur, int hauteur )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// @param[in]  hauteur : Dimension en X de la nouvelle clôture.
	/// @param[in]  largeur : Dimension en Y de la nouvelle clôture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::redimensionnerFenetre(int largeur, int hauteur)
	{
		projection_.redimensionnerFenetre(largeur, hauteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::zoomerIn()
	{
		projection_.zoomerIn();
		camera_.repositionner();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::zoomerOut()
	{
		projection_.zoomerOut();
		camera_.repositionner();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in élastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonnées du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonnées du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::zoomerInElastique(const glm::ivec2& coin1,
		const glm::ivec2& coin2)
	{
		/// À Faire: Redimensionner la projection et déplacer la caméra
		projection_.zoomIn(coin1, coin2);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out élastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonnées du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonnées du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::zoomerOutElastique(const glm::ivec2& coin1,
		const glm::ivec2& coin2)
	{
		/// À Faire: Redimensionner la projection et déplacer la caméra
		//projection_.zoomOut(coin1, coin2);


		glm::dvec3 point1;// (coin1.x, coin1.y, 0);
		point1.x = coin1.x;
		point1.y = coin1.y;
		glm::dvec3 point2; // (coin2.x, coin2.y, 0);
		point2.x = coin2.x;
		point2.y = coin2.y;
		glm::dvec3 centreRectangle;
		if (coin2.x >= coin1.x) {
			centreRectangle.x = coin2.x - ((coin2[0] - coin1[0]) / 2);
		}
		else {
			centreRectangle.x = coin1.x - ((coin1[0] - coin2[0]) / 2);
		}


		if (coin2.y >= coin1.y) {
			centreRectangle.y = coin2.y - ((coin2[1] - coin1[1]) / 2);
		}

		else {
			centreRectangle.y = coin1.y - ((coin1[1] - coin2[1]) / 2);
		}


		glm::dvec2 dimensionCloture = projection_.obtenirDimensionCloture();
		glm::dvec2 dimensionFenetreVirtuelle = projection_.obtenirDimensionFenetreVirtuelle();

		//centreRectangle.y = -1 * (centreRectangle.y - (dimensionCloture.y / 2));

		glm::dvec3 centreRectangleEnFenetre;
		convertirClotureAVirtuelle(centreRectangle.x, centreRectangle.y, centreRectangleEnFenetre);

		double facteurZoom = projection_.getZArriere() / projection_.getZAvant();
		double facteurX;
		double facteurY;

		if (coin2.x > coin1.x) {
			facteurX = (dimensionCloture.x) / ((coin2[0] - coin1[0])/*facteurZoom*/);
		}
		else if (coin2.x < coin1.x) {
			facteurX = (dimensionCloture.x) / ((coin1[0] - coin2[0])/*facteurZoom*/);
		}
		else {
			facteurX = dimensionCloture.x;
		}



		if (coin2.y > coin1.y) {
			facteurY = (dimensionCloture.y) / ((coin2[1] - coin1[1])/*facteurZoom*/);
		}

		else if (coin2.y < coin1.y) {
			facteurY = (dimensionCloture.y) / ((coin1[1] - coin2[1])/*facteurZoom*/);
		}
		else
		{
			facteurY = dimensionCloture.y;
		}

		//double facteurX = (dimensionCloture.x / 2) / ((coin2[0] - coin1[0])/*facteurZoom*/);
		//double facteurY = (dimensionCloture.y / 2) / ((coin1[1] - coin2[1])/*facteurZoom*/);

		int moyenneZoom = (facteurX + facteurY) / 2;

		double variation = projection_.getZoomOutMax() - (moyenneZoom * projection_.getIncrementZoom() + facteurZoom);


		if (variation > (moyenneZoom * projection_.getIncrementZoom() + facteurZoom))
		{
			if (facteurZoom > projection_.getZoomInMax())
			{
				facteurZoom = projection_.getZoomInMax();
			}
			
			facteurZoom *= moyenneZoom * projection_.getIncrementZoom();

			dimensionFenetreVirtuelle.x *= (facteurZoom);
			dimensionFenetreVirtuelle.y *= (facteurZoom);
			/*dimensionFenetreVirtuelle.x /= facteurZoom;
			dimensionFenetreVirtuelle.y /= facteurZoom;*/
			//printf("")
			projection_.setLargeurFenetre(dimensionFenetreVirtuelle.x);
			projection_.setHauteurFenetre(dimensionFenetreVirtuelle.y);
			//deplacerXY(centreRectangle.x, centreRectangle.y);
			projection_.appliquer(true);
		}

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::deplacerXY(double deplacementX, double deplacementY)
	///
	/// @param[in]  deplacementX : Déplacement en pourcentage de la largeur.
	/// @param[in]  deplacementY : Déplacement en pourcentage de la hauteur.
	///
	/// Permet de faire un "pan" d'un certain pourcentage.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::deplacerXY(double deplacementX, double deplacementY, int x, int y)
	{
		camera_.deplacerXY(deplacementX * projection_.obtenirDimensionCloture()[0], 
			deplacementY * projection_.obtenirDimensionCloture()[1],x,y);
		/*projection_.deplacer(deplacementX,
			deplacementY );*/
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::deplacerXY(const glm::ivec2& deplacement)
	///
	/// Permet de faire un "pan" équivalent à la distance du déplacement
	/// spécifié en coordonnées de clôture.
	///
	/// @param[in]  deplacement : Déplacement en coordonnées de clôture
	///                           (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::deplacerXY(const glm::ivec2& deplacement, int x, int y)
	{
		camera_.deplacerXY(deplacement[0], deplacement[1],x,y);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::deplacerZ(double deplacement)
	///
	/// Ne fait rien, car se déplacer dans l'axe de la profondeur n'a pas
	/// vraiment de signification avec une vue orthogonale.
	///
	/// @param[in]  deplacement : Déplacement selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::deplacerZ(double deplacement)
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::rotaterXY(double rotationX, double rotationY)
	///
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Une rotation de 100% correspondant à 360 degrés en X (angle de
	/// rotation) ou 180 degrés en Y (angle d'élévation).
	///
	/// @param[in]  rotationX : Rotation en pourcentage de la largeur.
	/// @param[in]  rotationY : Rotation en pourcentage de la hauteur.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::rotaterXY(double rotationX, double rotationY)
	{
		camera_.orbiterXY(rotationX * 360, rotationY * 180);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::rotaterXY(const glm::ivec2& rotation)
	///
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Un déplacement de la taille de la fenêtre correspond à 100%.
	///
	/// @param[in]  rotation : Rotation en coordonnées de clotûre (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::rotaterXY(const glm::ivec2& rotation)
	{
		const glm::ivec2 dimensions{ projection_.obtenirDimensionCloture() };
		rotaterXY(rotation[0] / (double) dimensions[0],
			rotation[1] / (double) dimensions[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrtho::rotaterZ(double rotation)
	///
	/// Ne fait rien, car tourner autour de l'axe de la profondeur
	/// correspondrait à un rouli et n'est pas souhaitable pour cette vue.
	///
	/// @param[in]  rotation : Rotation selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrtho::rotaterZ(double rotation)
	{
	}

	void VueOrtho::definirProjection() const
	{
		projection_.actualisationProjection();
	}

	void VueOrtho::appliquerCamera() const
	{
		camera_.repositionner();
	}

	void VueOrtho::deplacerClavier(double x, double y)
	{
		glm::dvec3 position = camera_.obtenirPosition();
		glm::dvec3 pointVise = camera_.obtenirPointVise();
		position.x += x;
		position.y += y;
		camera_.assignerPosition(position);
		camera_.assignerPointVise(pointVise);
		
	}

	void VueOrtho::deplacerClavierBas(double x, double y)
	{
		glm::dvec3 position = camera_.obtenirPosition();
		glm::dvec3 pointVise = camera_.obtenirPointVise();
		position.x += x;
		position.y += y;
		camera_.assignerPosition(position);
		camera_.assignerPointVise(pointVise);

	}

	void VueOrtho::deplacerClavierDroite(double x, double y)
	{
		glm::dvec3 position = camera_.obtenirPosition();
		glm::dvec3 pointVise = camera_.obtenirPointVise();
		position.x += x;
		position.y += y;
		camera_.assignerPosition(position);
		camera_.assignerPointVise(pointVise);
	}

	void VueOrtho::deplacerClavierGauche(double x, double y)
	{
		glm::dvec3 position = camera_.obtenirPosition();
		glm::dvec3 pointVise = camera_.obtenirPointVise();
		position.x += x;
		position.y += y;
		pointVise.x += x;
		pointVise.y += y;
		camera_.assignerPosition(position);
		camera_.assignerPointVise(pointVise);
	}

	void VueOrtho::deplacerSouris(glm::dvec3 dSouris)
	{
		camera_.assignerPosition(camera_.obtenirPosition() - dSouris);
		camera_.assignerPointVise(camera_.obtenirPointVise() - dSouris);
	}

	//void VueOrtho::appliquerCamera() const
	//{
	//	camera_.repositionner();
	//}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
