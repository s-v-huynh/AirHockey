////////////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacementTest.cpp
/// @author Equipe 6
/// @date 2016-11-04
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "VisiteurDeplacementTest.h"
#include "NoeudPortail.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(VisiteurDeplacementTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacementTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacementTest::setUp()
{
	noeud = std::make_unique<NoeudPortail>(ArbreRenduINF2990::NOM_PORTAIL);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacementTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacementTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDeplacementTest::testDeplacement()
///
/// Cas de test: écriture/lecture de la position relative
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDeplacementTest::testDeplacement()
{

	glm::dvec3 vecteur{ noeud->obtenirPositionRelative() };

	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2]));

	VisiteurDeplacement* visiteur = new VisiteurDeplacement();
	visiteur->modifierPosition(glm::dvec3{ 1.0, 2.0, 3.0 });

	noeud->accepterVisiteur(visiteur);

	vecteur = noeud->obtenirPositionRelative();

	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] - 1.0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] - 2.0));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2] - 3.0));

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
