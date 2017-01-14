////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigSceneTest.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigSceneTest.h"
#include "ConfigScene.h"
#include "FacadeModele.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ConfigSceneTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigSceneTest::setUp()
{
	// Nous pourrions initialiser l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune initialisation n'est requise.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigSceneTest::tearDown()
{
	// Nous pourrions lib�rer l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune lib�ration n'est requise.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::testSauvegardeChargement()
///
/// Cas de test: sauvegarde et chargement XML de la configuration
/// Modifier la valeur CALCULS_PAR_IMAGE, enregistrer la configuration,
/// restaurer la valeur CALCULS_PAR_IMAGE, charger la configuration,
/// s'assurer que la valeur sauvegard�e a bien �t� restaur�e du fichier
/// XML, restaurer la valeur par d�faut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigSceneTest::testSauvegardeChargement()
{
	// On d�finit une autre valeur pour les attributs
	ConfigScene::CALCULS_PAR_IMAGE = 20;

	// On sauvegarde le XML...
	FacadeModele::obtenirInstance()->enregistrerConfiguration();

	// On remet les valeurs par d�faut
	ConfigScene::CALCULS_PAR_IMAGE = 50;

	// On charge le XML...
	FacadeModele::obtenirInstance()->chargerConfiguration();

	// On v�rifie si les valeurs de test sont celles qui ont bien �t� charg�es
	CPPUNIT_ASSERT(ConfigScene::CALCULS_PAR_IMAGE == 20);

	// On r�affecte les valeurs par d�faut
	ConfigScene::CALCULS_PAR_IMAGE = 50;

	// On resauvegarde le XML
	FacadeModele::obtenirInstance()->enregistrerConfiguration();
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
