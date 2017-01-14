////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "ProjectionOrtho.h"
#include <glm/gtc/matrix_transform.inl>


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int largeurCloture, int hauteurCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double largeurFenetre, double hauteurFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] largeurCloture   : dimension en @a X de la cl�ture.
	/// @param[in] hauteurCloture   : dimension en @a Y de la cl�ture.
	/// @param[in] zAvant			: distance du plan avant (en @a z).
	/// @param[in] zArriere			: distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax		: facteur de zoom in maximal.
	/// @param[in] zoomOutMax		: facteur de zoom out maximal.
	/// @param[in] incrementZoom	: distance du plan arri�re (en @a z).
	/// @param[in] largeurFenetre	: dimension en @a X de la fen�tre
	///								  virtuelle.
	/// @param[in] hauteurFenetre	: dimension en @a Y de la fen�tre
	///								  virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrtho::ProjectionOrtho(int largeurCloture, int hauteurCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double largeurFenetre, double hauteurFenetre) :
		Projection{ largeurCloture, hauteurCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
		largeurFenetre_{ largeurFenetre },
		hauteurFenetre_{ hauteurFenetre }
	{
		ajusterRapportAspect();
		xMax_ = largeurFenetre /2;
		xMin_ = -largeurFenetre/2;
		yMax_ = hauteurFenetre /2;
		yMin_  = -hauteurFenetre /2;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		// IMPLANTER.
		double varieLargeur = (1 - 1 / incrementZoom_)*largeurFenetre_ / 2;
		double varieHauteur = (1 - 1 / incrementZoom_)*hauteurFenetre_ / 2;
		largeurFenetre_ += varieLargeur;
		hauteurFenetre_ += varieHauteur;
		obtenirMatrice();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{
		// IMPLANTER.
		double varieLargeur = (incrementZoom_ - 1)*largeurFenetre_ / 2;
		double varieHauteur = (incrementZoom_ - 1)*hauteurFenetre_ / 2;
		largeurFenetre_ -= varieLargeur;
		hauteurFenetre_ -= varieHauteur;
		obtenirMatrice();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::centrerSurPoint( const glm::ivec2& pointCentre )
	///
	/// Permet de centrer la fen�tre virtuelle sur un point de l'�cran. Le
	/// point de l'�cran est convertit en coordonn�es virtuelles et il devient
	/// le centre de la fen�tre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint(const glm::ivec2& pointCentre)
	{
		xMax_ = pointCentre.x + (xMax_ - xMin_) / 2;
		yMax_ = pointCentre.y + (yMax_ - yMin_) / 2;
		xMin_ = pointCentre.x - (xMax_ - xMin_) / 2;
		yMin_ = pointCentre.y - (yMax_ - yMin_) / 2;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in �lastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonn�es du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonn�es du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomIn(const glm::ivec2& coin1,
		const glm::ivec2& coin2)
	{
		centrerSurPoint({ (xMax_ - xMin_) / 2, (yMax_ - yMin_) / 2 });
		double zfacteur = zArriere_ / zAvant_;

		double facteurX;
		double facteurY;

		if (coin2.x > coin1.x) {
			facteurX = (largeurCloture_ / 2) / (coin2.x - coin1.x)*zfacteur;
		}
		else if (coin2.x < coin1.x) {
			facteurX = (largeurCloture_ / 2) / (coin1.x - coin2.x)*zfacteur;
		}
		else {
			facteurX = largeurCloture_;
		}



		if (coin2.y > coin1.y) {
			facteurY = (hauteurCloture_ / 2) / (coin2.y - coin1.y)*zfacteur;
		}

		else if (coin2.y < coin1.y) {
			facteurY = (hauteurCloture_ / 2) / (coin1.y - coin2.y)*zfacteur;
		}
		else
		{
			facteurY = hauteurCloture_;
		}
		
		double variation = zoomOutMax_ - ((facteurX + facteurY) / 2 * incrementZoom_ + zfacteur);
		if (variation >= (facteurX + facteurY) / 2 * incrementZoom_)
		{
			xMax_ *= zfacteur;
			xMin_ *= zfacteur;
			yMax_ *= zfacteur;
			yMin_ *= zfacteur;
			largeurFenetre_ *= zfacteur;
			hauteurFenetre_ *= zfacteur;
			zfacteur = zfacteur + (facteurX + facteurY) / 2 * incrementZoom_;
			xMax_ /= zfacteur;
			xMin_ /= zfacteur;
			yMax_ /= zfacteur;
			yMin_ /= zfacteur;
			largeurFenetre_ /= zfacteur;
			hauteurFenetre_ /= zfacteur;
		}
		appliquer();
		

	}

	

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out �lastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonn�es du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonn�es du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomOut(const glm::ivec2& coin1,
		const glm::ivec2& coin2)
	{
		double zfacteur = zArriere_ / zAvant_;
		double facteurX;
		double facteurY;

		if (coin2.x > coin1.x) {
			facteurX = (largeurCloture_ / 2) / (coin2.x - coin1.x)*zfacteur;
		}
		else if (coin2.x < coin1.x) {
			facteurX = (largeurCloture_ / 2) / (coin1.x - coin2.x)*zfacteur;
		}
		else {
			facteurX = largeurCloture_;
		}



		if (coin2.y > coin1.y) {
			facteurY = (hauteurCloture_ / 2) / (coin2.y - coin1.y)*zfacteur;
		}

		else if (coin2.y < coin1.y) {
			facteurY = (hauteurCloture_ / 2) / (coin1.y - coin2.y)*zfacteur;
		}
		else
		{
			facteurY = hauteurCloture_;
		}
		double variation = zoomInMax_ - ((facteurX + facteurY) / 2 * incrementZoom_ + zfacteur);
		centrerSurPoint({ (xMax_ - xMin_) / 2, (yMax_ - yMin_) / 2 });
		if (variation >= (facteurX + facteurY) / 2 * incrementZoom_)
		{
			zfacteur *= ((facteurX + facteurY) / 2 ) * incrementZoom_;
			xMax_ *= zfacteur;
			xMin_ *= zfacteur;
			yMax_ *= zfacteur;
			yMin_ *= zfacteur;
			largeurFenetre_ *= zfacteur;
			hauteurFenetre_ *= zfacteur;
			////zfacteur = zfacteur + (facteurX + facteurY) / 2 * incrementZoom_;
			//xMax_ /= zfacteur;
			//xMin_ /= zfacteur;
			//yMax_ /= zfacteur;
			//yMin_ /= zfacteur;
			//largeurFenetre_ /= zfacteur;
			//hauteurFenetre_ /= zfacteur;
		}
		centrerSurPoint({ (xMax_ - xMin_) / 2, (yMax_ - yMin_) / 2 });
		appliquer();
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( double largeur, double hauteur )
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// L'agrandissement de la fen�tre virtuelle est proportionnel �
	/// l'agrandissement de la clot�re afin que les objets gardent la m�me
	/// grandeur apparente lorsque la fen�tre est redimensionn�e.
	///
	/// @param[in]  largeur : largeur de la nouvelle cl�ture
	/// @param[in]  hauteur : hauteur de la nouvelle cl�ture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(int largeur, int hauteur)
	{

		GLdouble xMin = -largeurFenetre_ / 2.0;
		GLdouble xMax = largeurFenetre_ / 2.0;
		GLdouble yMin = hauteurFenetre_ / 2.0;
		GLdouble ymax = -hauteurFenetre_ / 2.0;
		GLdouble rapportLargeur = (largeurFenetre_ / largeurCloture_) * (largeur - largeurCloture_);
		GLdouble rapportLongueur = (hauteurFenetre_ / hauteurCloture_) * (hauteur - hauteurCloture_);

		//Ajuster les bordures
		xMin = xMin - rapportLargeur / 2.0;
		xMax = xMax + rapportLargeur / 2.0;
		ymax = ymax - rapportLongueur / 2.0;
		yMin = yMin + rapportLongueur / 2.0;

		largeurFenetre_ = xMax * 2;
		hauteurFenetre_ = yMin * 2;
		largeurCloture_ = largeur;
		hauteurCloture_ = hauteur;

		glOrtho(xMin, xMax, ymax, yMin, zAvant_, zArriere_);
		glViewport(0, 0, largeur, hauteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn glm::mat4 ProjectionOrtho::obtenirMatrice() const
	///
	/// Cette fonction permet de retourner la fen�tre virtuelle en appelant les
	/// fonctions de glm selon le type de projection et les propri�t�s de la
	/// fen�tre.
	///
	/// @return Matrice de projection.
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4 ProjectionOrtho::obtenirMatrice() const
	{
		return glm::ortho(-largeurFenetre_ / 2, largeurFenetre_ / 2,
			-hauteurFenetre_ / 2, hauteurFenetre_ / 2,
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{
		/*double rapportX = 200;
		double rapportY = rapportX*(double)(hauteurCloture_) / (largeurCloture_);
		largeurFenetre_ = 2 * rapportX;
		hauteurFenetre_ = rapportY;*/
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::appliquer()
	///
	/// Permet d'appliquer les changements effectuera la vue 
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::appliquer()
	{
		/*glm::ortho(-largeurFenetre_ / 2, largeurFenetre_ / 2,
			-hauteurFenetre_ / 2, hauteurFenetre_ / 2,
			zAvant_, zArriere_);*/
		glm::ortho(xMin_ / 2, xMax_ / 2,
			yMin_ / 2, yMax_ / 2,
			zAvant_, zArriere_);
	}

	void ProjectionOrtho::appliquer(bool)
	{
		glm::ortho(-largeurFenetre_ / 2, largeurFenetre_ / 2,
		-hauteurFenetre_ / 2, hauteurFenetre_ / 2,
		zAvant_, zArriere_);
		/*glm::ortho(xMin_ / 2, xMax_ / 2,
			yMin_ / 2, yMax_ / 2,
			zAvant_, zArriere_);*/
	}
}; // Fin du namespace vue.


   ///////////////////////////////////////////////////////////////////////////
   /// @}
   ///////////////////////////////////////////////////////////////////////////
