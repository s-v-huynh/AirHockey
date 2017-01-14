////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author Jean-Fran�ois P�russe
/// @date 2007-01-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigScene.h"
#include <iostream>


SINGLETON_DECLARATION_CPP(ConfigScene);

/// Nombre de calculs par image.
int ConfigScene::CALCULS_PAR_IMAGE{ 50 };


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::creerDOM ( TiXmlNode& node ) const
///
/// Cette fonction �crit les valeurs de la configuration dans un �l�ment XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::creerDOM ( tinyxml2::XMLDocument& document ) const
{
	// Cr�er le noeud 'configuration'
	tinyxml2::XMLElement* elementConfiguration{ document.NewElement("configuration") };
	
	// Cr�er le noeud scene et d�finir ses attributs
	tinyxml2::XMLElement* elementScene{ document.NewElement("CScene") };
	elementScene->SetAttribute("CALCULS_PAR_IMAGE", ConfigScene::CALCULS_PAR_IMAGE);
	
	// Adjoindre le noeud 'elementScene'
	elementConfiguration->LinkEndChild(elementScene);

	// Adjoindre le noeud 'configuration' au noeud principal
	// (Rappel : pas besoin de lib�rer la m�moire de elementConfiguration
	// puisque toutes les fonctions Link... le font pour nous)
	document.LinkEndChild(elementConfiguration);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::lireDOM( const TiXmlNode& node )
///
/// Cette fonction lit les valeurs de la configuration � partir d'un �l�ment
/// XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::lireDOM( const tinyxml2::XMLDocument& document )
{
	// Tenter d'obtenir le noeud 'Configuration'
	const tinyxml2::XMLElement* elementConfiguration{ document.FirstChildElement("configuration") };
	if (elementConfiguration != nullptr) {
		// Tenter d'obtenir l'�l�ment CScene, puis l'attribut CALCULS_PAR_IMAGE
		const tinyxml2::XMLElement* elementScene{ elementConfiguration->FirstChildElement("CScene") };
		if (elementScene != nullptr) {
			if (elementScene->QueryIntAttribute("CALCULS_PAR_IMAGE", &ConfigScene::CALCULS_PAR_IMAGE) != tinyxml2::XML_SUCCESS){
				std::cerr << "Erreur : CALCULS_PAR_IMAGE : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
