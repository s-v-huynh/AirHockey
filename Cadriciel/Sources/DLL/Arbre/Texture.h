///////////////////////////////////////////////////////////////////////////////
/// @file Textures.h
/// @author equipe06
/// @date 2016-09-08
/// @version 1.0
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Utilitaire.h"
#include "AideGL.h"

///////////////////////////////////////////////////////////////////////////
/// @class Textures
/// @brief cette classe nous permet de charger toutes les textures en une fois
///@author equipe06
/// @date 2016-09-08
///////////////////////////////////////////////////////////////////////////
class Texture
{
public:
	/// Obtient l'instance unique de la classe.
	static Texture* obtenirInstance();

	/// Libère l'instance unique de la classe.
	static void libererInstance();
	void chargerTexture();
	/// retourne la texture des murets
	unsigned int obtenirTextureMuret() const;
	/// retourne la texture de la glace
	unsigned int obtenirTextureGlace() const;
	unsigned int obtenirLigneMilieu() const;

	unsigned int obtenirTexturetextureBut() const;

	/// retourne la texture de la bordure
	unsigned int obtenirTextureBordure(int index) const;

private:
	Texture();
	~Texture() {}

	/// Instance unique de la classe.
	static Texture* instance_;
	/// charge les textures du jeu
	void chargerTextures();
	/// texture 1 des murets
	unsigned int textureMuret_;
	/// texture de la surface de la glace
	unsigned int textureGlace_;
	/// texture du fond avec l'explosion bleu
	unsigned int textureBut_;
	unsigned int textureLigne_;
	/// textures des bordures
	unsigned int textureBordures_[3];
};

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////