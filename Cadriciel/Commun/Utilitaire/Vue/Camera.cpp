///////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "Utilitaire.h"
#include "Camera.h"
#include "glm\gtc\matrix_transform.hpp"
#include <algorithm>

using namespace std;

namespace vue {


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn Camera::Camera(const glm::dvec3& position, const glm::dvec3& pointVise, const glm::dvec3& directionHautCamera, const glm::dvec3& directionHautMonde)
	///
	/// Constructeur de la cam�ra � partir des coordonn�es cart�siennes.
	///
	/// @param[in]  position            : position de la cam�ra.
	/// @param[in]  pointVise           : point vis�.
	/// @param[in]  directionHautCamera : direction du haut de la cam�ra.
	/// @param[in]  directionHautMonde  : direction du haut du monde de la
	///                                   cam�ra.
	///
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////////
	Camera::Camera(const glm::dvec3& position,
		const glm::dvec3& pointVise,
		const glm::dvec3& directionHautCamera,
		const glm::dvec3& directionHautMonde, bool vueOrbite)
		: position_{ position },
		pointVise_{ pointVise },
		directionHaut_{ directionHautCamera },
		directionHautMonde_{ directionHautMonde },
		pointViseDepart_{ pointVise },
		positionDepart_{ position },
		vueOrbite_{ vueOrbite }
	{
		anglePhi_ = 75;
		angleTheta_ = 0;
		lastX_=0;
		lastY_=0;
		directionVueDistance_ = sqrt(pow(position.x,2)+pow(position.y,2)+pow(position.z,2));
		//std::cout << directionVueDistance_ << std::endl;
		//std::cout << vueOrbite << std::endl;
		if (vueOrbite)
		{
			
			//actualiserPosition();
			repositionner();
		}
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerXY( double deplacementX, double deplacementY )
	///
	/// D�place la cam�ra dans le plan perpendiculaire � la direction vis�e
	///
	/// @param[in]  deplacementX : D�placement sur l'axe horizontal du plan de
	///                            la cam�ra.
	/// @param[in]  deplacementY : D�placement sur l'axe vertical du plan de la
	///                            cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerXY(double deplacementX, double deplacementY, int x, int y)
	{
		if (vueOrbite_==true)
		{

			anglePhi_ += y;
			angleTheta_ += x;
			//cout << anglePhi_ << endl;
			if (anglePhi_ > 84.0)
				anglePhi_ = 85.0;
			else if (anglePhi_ < 5.0)
				anglePhi_ = 5.0;

			/*if (angleTheta_ > 299.0)
				angleTheta_ = 299.0;
			else if (angleTheta_ < -299.0)
				angleTheta_ = 0.0;*/
				//angleTheta_ = 0;
			if (x >= 0 && y >= 0)
			{
				
				/*if (lastX_ > x)
					orbiterXY(5.0, 0.0, true);
				if (lastX_ < x)
					orbiterXY(-5.0, 0.0, true);
				if (lastY_ > y)
					orbiterXY(0.0, 5.0, true);
				if (lastY_ < y)
					orbiterXY(0.0, -5.0, true);*/
				lastX_ = x;
				lastY_ = y;
				/*x += x;
				y += y;*/
				
			}
		}
		if (vueOrbite_ == false)
		{
			position_[0] += deplacementX;
			position_[1] += deplacementY;
			pointVise_[0] += deplacementX;
			pointVise_[1] += deplacementY;
		}

	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::deplacerZ( double deplacement, bool bougePointVise )
	///
	/// D�place la cam�ra dans l'axe de la direction vis�e.
	///
	/// @param[in]  deplacement    : D�placement sur l'axe de la direction vis�e
	/// @param[in]  bougePointVise : Si vrai, le point de vis� est �galement
	///                              d�plac�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::deplacerZ(double deplacement, bool bougePointVise)
	{
	}

	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::repositionner()
	///
	/// repostionne la cam�ra dans l'axe de la direction vis�e
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::repositionner()const
	{
		//position_ = positionDepart_;
		//pointVise_ = pointViseDepart_;
	
		gluLookAt(position_.x, position_.y, position_.z,
				pointVise_.x, pointVise_.y, pointVise_.z, directionHaut_.x,
				directionHaut_.y, directionHaut_.z);
	}

	void Camera::zoomInCamera()
	{

		if (directionVueDistance_ < 900)
		{
			directionVueDistance_ += 5;
		}
		//actualiserPosition();
		repositionner();
	}

	void Camera::zoomOutCamera()
	{
		if (directionVueDistance_ > 100)
		{
			directionVueDistance_ -= 5;
		}
		//actualiserPosition();
		repositionner();
	}

	void Camera::actualiserPosition()
	{

		position_.x = directionVueDistance_*cos(utilitaire::DEG_TO_RAD(anglePhi_))*sin(utilitaire::DEG_TO_RAD(angleTheta_));
		position_.y = directionVueDistance_*sin(utilitaire::DEG_TO_RAD(anglePhi_));
		position_.z = directionVueDistance_*cos(utilitaire::DEG_TO_RAD(anglePhi_))*cos(utilitaire::DEG_TO_RAD(angleTheta_));

	}

	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::tournerXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de sa position (et donc d�placement du
	/// point vis� en gardant la position fixe.
	///
	/// @param[in] rotationX        : Modification de l'angle de rotation du
	///                               point vis� par rapport � la position.
	/// @param[in] rotationY        : Modification de l'angle d'�l�vation du
	///                               point vis� par rapport � la position.
	/// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectu�e
	///                               si elle am�nerait une inversion de la
	///                               cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::tournerXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
	}


	////////////////////////////////////////////////////////////////////////////
	///
	/// @fn void Camera::orbiterXY( double rotationX, double rotationY, bool empecheInversion )
	///
	/// Rotation de la cam�ra autour de son point de vis� (et donc d�placement
	/// de la position en gardant le point de vis� fixe.
	///
	/// @param[in]  rotationX        : Modification de l'angle de rotation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  rotationY        : Modification de l'angle d'�l�vation de la
	///                                position par rapport au point de vis�.
	/// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectu�
	///                                si elle am�nerait une inversion de la
	///                                cam�ra.
	///
	///  @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////////
	void Camera::orbiterXY(double rotationX,
		double rotationY,
		bool   empecheInversion //=true
		)
	{
		anglePhi_ += rotationY;
		angleTheta_ += rotationX;
		//cout << anglePhi_ << endl;
		if (anglePhi_ > 89.0)
			anglePhi_ = 89.0;
		else if (anglePhi_ < 0.0)
			anglePhi_ = 0.0;

		if (angleTheta_ > 299.0)
			angleTheta_ = 0.0;
		else if (angleTheta_ < -299.0)
			angleTheta_ = -299.0;
		//actualiserPosition();
		repositionner();
	}
	///
	/// @fn glm::mat4 Camera::obtenirMatrice() const
	///
	/// Calcule la matrice aidant � positionner la cam�ra dans la sc�ne.
	///
	/// @return Matrice de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////
	glm::mat4 Camera::obtenirMatrice() const
	{
		if (vueOrbite_==false)
			return glm::lookAt(position_, pointVise_, directionHaut_);
		if (vueOrbite_ == true)
		{
			
			return glm::lookAt(glm::dvec3(directionVueDistance_*cos(utilitaire::DEG_TO_RAD(angleTheta_))*sin(utilitaire::DEG_TO_RAD(anglePhi_)),
				directionVueDistance_*sin(utilitaire::DEG_TO_RAD(angleTheta_))*sin(utilitaire::DEG_TO_RAD(anglePhi_)),
				directionVueDistance_*cos(utilitaire::DEG_TO_RAD(anglePhi_))),
				glm::dvec3(0, 0, 0),
				glm::dvec3(directionHaut_.x, directionHaut_.z, directionHaut_.y));
		}
		//return glm::lookAt(glm::vec3(position_.x, position_.y, position_.z), // camera position
		//	glm::vec3(0, 0, 0), // look at origin
		//	glm::vec3(0, 1, 0));
	}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
