///////////////////////////////////////////////////////////////////////////
/// @file BoiteEnvironnement.h
/// @author Nicolas Cloutier
/// @date 2016-07-02
/// @version 1.1
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_BOITEENVIRONNEMENT_H__
#define __UTILITAIRE_BOITEENVIRONNEMENT_H__


#include <string>
#include "glm\fwd.hpp"
#include "OpenGL_Programme.h"
#include "OpenGL_Nuanceur.h"

struct FIBITMAP;

namespace utilitaire {
      
   ///////////////////////////////////////////////////////////////////////////
   /// @class BoiteEnvironnement
   /// @brief Classe repr�sentant une bo�te d'environnement ("skybox").
   ///
   ///        Elle s'occupe de charger 6 images du cube formant la bo�te.  Elle
   ///        utilise la convention de sens de CubeMapGen (de ATI), lorsque les
   ///        images sont export�es avec le mapping OpenGL (plut�t que DirectX).
   ///
   /// @author Martin Bisson
   /// @date 2007-05-28
   ///////////////////////////////////////////////////////////////////////////
   class BoiteEnvironnement
   {
   public:
      /// Constructeur � partir des noms des fichiers d'images de la bo�te.
      BoiteEnvironnement(
         const std::string& fichierXpos, const std::string& fichierXneg,
         const std::string& fichierYpos, const std::string& fichierYneg,
         const std::string& fichierZpos, const std::string& fichierZneg,
		 unsigned int dimension);
      /// Destructeur.
      ~BoiteEnvironnement();

      /// Affiche la bo�te d'environnement.
	  void afficher(glm::mat4 const& projection, glm::mat4 const& modeleVue);


   private:
      /// Donn�es des images de la bo�te d'environnement.
      FIBITMAP* imagesEnvironnement_[6];
	  /// Identificateur de la texture
	  unsigned int textureId_;
	  /// Identificateur de la VAO
	  unsigned int vaoId_;
	  /// Identificateur de la VBO contenant les sommes
	  unsigned int vboId_;

	  /// Nuanceurs g�rant l'affichage des VBO
	  opengl::Programme programme_;
	  opengl::Nuanceur nuanceurFragment_;
	  opengl::Nuanceur nuanceurSommet_;


	  /// Tableau des sommets de la bo�te
	  static const float sommets_[18];

   };


} // Fin de l'espace de nom utilitaire.


#endif // __UTILITAIRE_BOITEENVIRONNEMENT_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
