//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacementTest.h
/// @author Equipe 6
/// @date 2016-01-04
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VISITEURDEPLACEMENT_H
#define _TESTS_VISITEURDEPLACEMENT_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "VisiteurDeplacement.h"

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe NoeudAbstrait
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class VisiteurDeplacementTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurDeplacementTest);
	CPPUNIT_TEST(testDeplacement);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================

	/// Cas de test: écriture/lecture de la position relative
	void testDeplacement();

private:
	/// Instance d'un noeud abstrait
	std::unique_ptr<NoeudAbstrait> noeud;
};

#endif // _TESTS_VISITEURDEPLACEMENT_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

