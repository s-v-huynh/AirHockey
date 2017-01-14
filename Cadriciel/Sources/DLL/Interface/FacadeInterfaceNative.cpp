////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"

#include "BancTests.h"

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fen�tre
	/// identifi�e par le handle pass� en param�tre.  Cette fonction doit
	/// �tre la premi�re � �tre appel�e, car la cr�ation de l'objet du mod�le
	/// C++ s'attend � avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND) handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction lib�re le contexte OpenGL. Cette fonction doit �tre la
	/// derni�re � �tre appel�e, car elle lib�re �galement l'objet du mod�le
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// D�sinitialisation de la fa�ade.  Le fait de le faire apr�s la
		// d�sinitialisation du contexte OpenGL aura pour cons�quence que la
		// lib�ration des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la sc�ne.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la sc�ne.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour d�tecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit �tre appel�e lorsque la fen�tre est
	/// redimensionn�e afin d'ajuster les param�tres de la machine � �tats
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fen�tre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fen�tre.
	/// @param[in] hauteur : La nouvelle hauteur de la fen�tre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(largeur, hauteur);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
	///
	/// Cette fonction effectue les diff�rents calculs d'animations
	/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
	/// physique du jeu.
	///
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float) temps);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl redessiner
	///
	/// Cette fonction effectue les diff�rents calculs d'animations
	/// n�cessaires pour le mode jeu, tel que les diff�rents calculs de
	/// physique du jeu.
	///
	/// @param[in] aucun.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redessiner()
	{
		FacadeModele::obtenirInstance()->redessiner();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le pr�sent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arri�re sur le pr�sent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'ex�cuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont r�ussi, 1 si au moins un test a �chou�
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void ajouterNouveauElement(char* nom, int x, int y)
	///
	/// Cette fonction permet d'ajouter un noeud quelconque sur la scene de jeu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int ajouterNouveauElement(char* nom, int x, int y)
	{
		return FacadeModele::obtenirInstance()->ajouterNouveauElement(nom, x, y);
	}

	__declspec(dllexport) int ajouterNouveauPortail(char* nom, int x, int y)
	{
		return FacadeModele::obtenirInstance()->ajouterNouveauPortail(nom, x, y);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserRectangleElas(int x, int y)
	{
		FacadeModele::obtenirInstance()->initialiserRectangleElas(x, y);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void mettreAJourRectangleElas(int x1, int y1)
	{
		FacadeModele::obtenirInstance()->mettreAJourRectangleElas(x1, y1);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void terminerRectangleElas()
	{
		FacadeModele::obtenirInstance()->terminerRectangleElas();
	}	

	__declspec(dllexport) void selectionObjet(int posX, int posY, bool attribuer)
	{
		FacadeModele::obtenirInstance()->selectionObjet(posX, posY, attribuer);
	}
	__declspec(dllexport) void miseAEchelle(int x, int y)
	{
		FacadeModele::obtenirInstance()->mettreAEchelle(x, y);
	}
	__declspec(dllexport) void initialiserRotation(int pointY)
	{
		FacadeModele::obtenirInstance()->initialiserRotation(pointY);
	}

	__declspec(dllexport) void initialiserDeplacement(int pointX, int pointY)
	{
		FacadeModele::obtenirInstance()->initialiserDeplacement(pointX, pointY);
	}

	__declspec(dllexport) void effectuerRotation(int pointY)
	{
		FacadeModele::obtenirInstance()->effectuerRotation(pointY);
	}

	__declspec(dllexport) void sauverSouris()
	{
		FacadeModele::obtenirInstance()->sauverSouris();
	}
	__declspec(dllexport) void deplacerSouris(int x, int y)
	{
		FacadeModele::obtenirInstance()->deplacerSouris(x, y);
	}

	__declspec(dllexport) void effectuerDeplacement(float pointX, float pointY)
	{
		FacadeModele::obtenirInstance()->effectuerDeplacement(pointX, pointY);
	}

	__declspec(dllexport) double obtenirFrictionTable()
	{
		return FacadeModele::obtenirInstance()->obtenirFrictionTable();
	}

	__declspec(dllexport) double obtenirAccelerationBonus()
	{
		return FacadeModele::obtenirInstance()->obtenirAccelerationBonus();
	}

	__declspec(dllexport) double obtenirCoefRebondissement()
	{
		return FacadeModele::obtenirInstance()->obtenirCoefRebondissement();
	}

	__declspec(dllexport) int obtenirPositionObjetX()
	{
		return FacadeModele::obtenirInstance()->obtenirPositionObjetX();
	}

	__declspec(dllexport) int obtenirPositionObjetY()
	{
		return FacadeModele::obtenirInstance()->obtenirPositionObjetY();
	}

	__declspec(dllexport) int obtenirPositionObjetZ()
	{
		return FacadeModele::obtenirInstance()->obtenirPositionObjetZ();
	}

	__declspec(dllexport) int obtenirAngleRotationObjet()
	{
		return FacadeModele::obtenirInstance()->obtenirAngleRotationObjet();
	}

	__declspec(dllexport) double obtenirFacteurEchelleObjet()
	{
		return FacadeModele::obtenirInstance()->obtenirFacteurEchelleObjet();
	}

	__declspec(dllexport) void mettreEchelleObjetBouton(double facteur)
	{
		FacadeModele::obtenirInstance()->mettreEchelleObjetBouton(facteur);
	}

	__declspec(dllexport) void rotationObjetBouton(int angle)
	{
		FacadeModele::obtenirInstance()->rotationObjetBouton(angle);
	}
	__declspec(dllexport) void deplacementObjetBouton(float pointX, float pointY)
	{
		FacadeModele::obtenirInstance()->deplacementObjetBouton(pointX, pointY);
	}
	__declspec(dllexport) void deplacer(int pointX, int pointY)
	{
		//FacadeModele::obtenirInstance()->deplacer()
	}
	__declspec(dllexport) void frictionTableBouton(double frictionTable)
	{
		FacadeModele::obtenirInstance()->frictionTableBouton(frictionTable);
	}

	__declspec(dllexport) void accelerationBonusBouton(double accelerationBonus)
	{
		FacadeModele::obtenirInstance()->accelerationBonusBouton(accelerationBonus);
	}

	__declspec(dllexport) void coefRebondissementBouton(double coefRebondissement)
	{
		FacadeModele::obtenirInstance()->coefRebondissementBouton(coefRebondissement);
	}
	////////////////////////////////////////////////////////////////////////
	///
	///
	///
	/// 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void dupliquerSelection(int x, int y) {
		FacadeModele::obtenirInstance()->dupliquerSelection(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	///
	///
	/// 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void supprimerSelection() {
		FacadeModele::obtenirInstance()->supprimerSelection();
	}
	////////////////////////////////////////////////////////////////////////
	///
	///
	///
	/// 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void deplacerSelection(int x, int y) {
		FacadeModele::obtenirInstance()->deplacerSelection(x, y);
	}
	////////////////////////////////////////////////////////////////////////
	///
	///
	///
	/// 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void selectionner(int x, int y, bool selectionUnique) {
		FacadeModele::obtenirInstance()->selectionner(x, y, selectionUnique);
	}
	////////////////////////////////////////////////////////////////////////
	///
	///
	///
	/// 
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void selectionnerRectangle(int x, int y, int hauteur, int largeur, bool selectionUnique) {
		FacadeModele::obtenirInstance()->selectionnerRectangle(x, y, hauteur, largeur, selectionUnique);
	}
    __declspec(dllexport) void deselectionnerTout(){
        FacadeModele::obtenirInstance()->deselectionnerTout();
    }
    __declspec(dllexport) void selectionnerTout(){
        FacadeModele::obtenirInstance()->selectionnerTout();
    }
    __declspec(dllexport) void effacerSelection(){
        FacadeModele::obtenirInstance()->effacerSelection();
    }
    __declspec(dllexport) void modifierEtatCTRL(bool etatCTRL){
        FacadeModele::obtenirInstance()->modifierEtatCTRL(etatCTRL);
    }
    
    __declspec(dllexport)  void sauvegardeParDefaut()
	{
		FacadeModele::obtenirInstance()->sauvegardeParDefaut();
	}

	__declspec(dllexport)  void initialisationParDefaut()
	{
		FacadeModele::obtenirInstance()->initialisationParDefaut();
	}

	__declspec(dllexport) void sauvegarderArbre(char* nomFichier)
	{
		FacadeModele::obtenirInstance()->sauvegarderArbre(nomFichier);
	}

	__declspec(dllexport) void initialiserChargement(char* nomFichier)
	{
		FacadeModele::obtenirInstance()->initialiserChargement(nomFichier);
	}
	__declspec(dllexport) void deplacerXY(double deplacementX, double deplacementY, int x, int y)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY,x,y);
	}
	__declspec(dllexport) void deplacerClavier(double x, double y)
	{
		FacadeModele::obtenirInstance()->deplacerClavier(x, y);
	}
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void zoomInElas()
	///
	/// Cette fonction permet de faire un zoom in avec le rectangle elastique
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void zoomInElas()
	{
		FacadeModele::obtenirInstance()->zoomInElas();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void zoomOutElas()
	///
	/// Cette fonction permet de faire un zoom out  avec le rectangle elastique
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void zoomOutElas()
	{
		FacadeModele::obtenirInstance()->zoomOutElas();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void selectionElastique()
	{
		FacadeModele::obtenirInstance()->selectionRectangle();
	}
	void chargerConfigurationOptions()
	{
		FacadeModele::obtenirInstance()->chargerConfigurationOptions();
	}
	void miseAJourSauvegardeConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
		int nbButs, char * haut, char * bas, char * gauche, char * droite, bool estVirtuel)
	{
		FacadeModele::obtenirInstance()->miseAJourSauvegardeConfiguration(peutAfficherDebogage, peutAfficherCollision, peutAfficherVitesseRondelle, peutAfficherEclairage, peutAfficherAttractionPortail, nbButs,
			haut, bas, gauche, droite, estVirtuel);
	}
	void miseAJourChargementConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
		int nbButs, char * haut, char * bas, char * gauche, char * droite, bool estVirtuel)
	{
		FacadeModele::obtenirInstance()->miseAJourChargementConfiguration(peutAfficherDebogage, peutAfficherCollision, peutAfficherVitesseRondelle, peutAfficherEclairage, peutAfficherAttractionPortail, nbButs,
			haut, bas, gauche, droite, estVirtuel);
	}
	void sauvegarderConfigurationOptions(char* haut, char* bas, char* gauche, char* droite)
	{
		FacadeModele::obtenirInstance()->sauvegarderConfigurationOptions(haut,  bas,  gauche, droite);
	}
	bool obtenirPeutAfficherDebogage()
	{
		return FacadeModele::obtenirInstance()->obtenirPeutAfficherDebogage();
	}
	bool obtenirPeutAfficherCollision()
	{
		return FacadeModele::obtenirInstance()->obtenirPeutAfficherCollision();
	}
	bool obtenirPeutAfficherVitesse()
	{
		return FacadeModele::obtenirInstance()->obtenirPeutAfficherVitesse();
	}
	bool obtenirPeutAfficherEclairage()
	{
		return FacadeModele::obtenirInstance()->obtenirPeutAfficherEclairage();
	}
	bool obtenirPeutAfficherAttractionPortail()
	{
		return FacadeModele::obtenirInstance()->obtenirPeutAfficherAttractionPortail();
	}
	int obtenirNbButs()
	{
		return FacadeModele::obtenirInstance()->obtenirNbButs();
	}
	const char* obtenirHaut()
	{
		return FacadeModele::obtenirInstance()->obtenirHaut();
	}
	const char* obtenirBas()
	{
		return FacadeModele::obtenirInstance()->obtenirBas();
	}

	const char* obtenirGauche()
	{
		return FacadeModele::obtenirInstance()->obtenirGauche();
	}

	const char* obtenirDroite()
	{
		return FacadeModele::obtenirInstance()->obtenirDroite();
	}

	void creerProfil(char * nom, int vitesse, int passivite)
	{
		FacadeModele::obtenirInstance()->creerProfil(nom, vitesse, passivite);
	}

	void ajouterNouveauProfil(char * nom, int vitesse, int passivite)
	{
		FacadeModele::obtenirInstance()->ajouterNouveauProfil(nom, vitesse, passivite);
	}

	void sauvegardeProfils()
	{
		FacadeModele::obtenirInstance()->sauvegardeProfils();
	}

	void chargementProfils()
	{
		FacadeModele::obtenirInstance()->chargementProfils();
	}

	void supprimerProfil(std::string nom)
	{
		FacadeModele::obtenirInstance()->supprimerProfil(nom);
	}

	int nombreProfils()
	{
		return FacadeModele::obtenirInstance()->nombreProfils();
	}

	const char* nomDuProfil(int profilChoisi)
	{
		return FacadeModele::obtenirInstance()->nomDuProfil(profilChoisi);
	}

	int vitesseDuProfil(int profilChoisi)
	{
		return FacadeModele::obtenirInstance()->vitesseDuProfil(profilChoisi);
	}

	int passiviteDuProfil(int profilChoisi)
	{
		return FacadeModele::obtenirInstance()->passiviteDuProfil(profilChoisi);
	}

	void reinitialiserProfils()
	{
		return FacadeModele::obtenirInstance()->reinitialiserProfils();
	}

	void ajouterNomProfil(char* nom)
	{
		return FacadeModele::obtenirInstance()->ajouterNomProfil(nom);
	}

	void sauvegarderTournoi()
	{
		FacadeModele::obtenirInstance()->sauvegarderTournoi();
	}

	void chargementTournoi()
	{
		FacadeModele::obtenirInstance()->chargementTournoi();
	}

	void assignerJoueur1Tournoi(char* nom, bool estVirtuel, int index)
	{
		FacadeModele::obtenirInstance()->assignerJoueur1Tournoi(nom, estVirtuel, index);
	}

	void assignerJoueur2Tournoi(char* nom, bool estVirtuel, int index)
	{
		FacadeModele::obtenirInstance()->assignerJoueur2Tournoi(nom, estVirtuel, index);
	}

	void assignerJoueur3Tournoi(char* nom, bool estVirtuel, int index)
	{
		FacadeModele::obtenirInstance()->assignerJoueur3Tournoi(nom, estVirtuel, index);
	}

	void assignerJoueur4Tournoi(char* nom, bool estVirtuel, int index)
	{
		FacadeModele::obtenirInstance()->assignerJoueur4Tournoi(nom, estVirtuel, index);
	}

	const char * obtenirNomJoueur1Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirNomJoueur1Tournoi();
	}

	const char * obtenirNomJoueur2Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirNomJoueur2Tournoi();
	}

	const char * obtenirNomJoueur3Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirNomJoueur3Tournoi();
	}

	const char * obtenirNomJoueur4Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirNomJoueur4Tournoi();
	}

	bool obtenirTypeJoueur1Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirTypeJoueur1Tournoi();
	}

	bool obtenirTypeJoueur2Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirTypeJoueur2Tournoi();
	}

	bool obtenirTypeJoueur3Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirTypeJoueur3Tournoi();
	}

	bool obtenirTypeJoueur4Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirTypeJoueur4Tournoi();
	}

	int obtenirProfilJoueur1Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirProfilJoueur1Tournoi();
	}

	int obtenirProfilJoueur2Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirProfilJoueur2Tournoi();
	}

	int obtenirProfilJoueur3Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirProfilJoueur3Tournoi();
	}

	int obtenirProfilJoueur4Tournoi()
	{
		return FacadeModele::obtenirInstance()->obtenirProfilJoueur4Tournoi();
	}



	bool obtenirEstVirtuel()
	{
		return FacadeModele::obtenirInstance()->obtenirEstVirtuel();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport)void initialiserPartie(int a, bool b)
	{
		FacadeModele::obtenirInstance()->initialiserPartie(a, b);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void lancerPartieRapide()
	{
		FacadeModele::obtenirInstance()->lancerPartieRapide();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void lancerPartieTournoi(char* nom1, char* nom2)
	{
		FacadeModele::obtenirInstance()->lancerPartieTournoi(nom1,nom2);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void assignerBut(bool joueur1)
	{
		FacadeModele::obtenirInstance()->assignerBut(joueur1);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserPartieTournoi()
	{
		FacadeModele::obtenirInstance()->initialiserPartieTournoi();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void arreterPartie()
	{
		FacadeModele::obtenirInstance()->arreterPartie();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void arreterTournoi() 
	{
		FacadeModele::obtenirInstance()->arreterTournoi();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void initialiserTournoi(int nbBut,bool j1, char* nom1, bool j2, char* nom2, bool j3, char* nom3, bool j4, char* nom4)
	{
		FacadeModele::obtenirInstance()->initialiserTournoi(nbBut,j1, nom1, j2, nom2, j3, nom3, j4, nom4);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void joueurMaillet1(int x, int y)
	{
		FacadeModele::obtenirInstance()->joueurMaillet1(x, y);
	}

	void joueurMaillet2(double x, double y)
	{
		FacadeModele::obtenirInstance()->joueurMaillet2(x, y);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	_declspec(dllexport) void nextPartie()
	{
		
		FacadeModele::obtenirInstance()->nextPartie();
		
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool afficherPanelRapide()
	{
		return FacadeModele::obtenirInstance()->afficherPanelRapide();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool nomVainqueurPartieRapide()
	{
		return FacadeModele::obtenirInstance()->nomVainqueurPartieRapide();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int scoreFinalPerdant()
	{
		return FacadeModele::obtenirInstance()->scoreFinalPerdant();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool getJoueur1Passe()
	{
		return FacadeModele::obtenirInstance()->getJoueur1Passe();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool getJoueur3Passe()
	{
		return FacadeModele::obtenirInstance()->getJoueur3Passe();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool getVainqueur1Passe()
	{
		return FacadeModele::obtenirInstance()->getVainqueur1Passe();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool getActualiser1()
	{
		return FacadeModele::obtenirInstance()->getActualiser1();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool getActualiser2()
	{
		return FacadeModele::obtenirInstance()->getActualiser2();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool getActualiser3()
	{
		return FacadeModele::obtenirInstance()->getActualiser3();
	}
	void enModeEdition(bool modeEdition)
	{
		FacadeModele::obtenirInstance()->enModeEdition(modeEdition);
	}

	__declspec(dllexport) void reinitialiserPartie()
	{
		FacadeModele::obtenirInstance()->reinitialiserPartie();
	}

	__declspec(dllexport) void adversaireVirtuel(bool virtuel)
	{
		FacadeModele::obtenirInstance()->adversaireVirtuel(virtuel);
	}

	__declspec(dllexport) bool joueurVirtuelDansPartieCourante()
	{
		return FacadeModele::obtenirInstance()->joueurVirtuelDansPartieCourante();
	}

	__declspec(dllexport) bool obtenirEtatAmbiante()
	{
		return FacadeModele::obtenirInstance()->obtenirEtatAmbiante();
	}

	__declspec(dllexport) bool obtenirDirectionnelActive()
	{
		return FacadeModele::obtenirInstance()->obtenirDirectionnelActive();
	}

	__declspec(dllexport) bool obtenirEtatSpot()
	{
		return FacadeModele::obtenirInstance()->obtenirEtatSpot();
	}

	__declspec(dllexport) void modifierEtatAmbiante(bool etat)
	{
		FacadeModele::obtenirInstance()->modifierEtatAmbiante(etat);
	}

	__declspec(dllexport) void modifierEtatDirectionnelle(bool etat)
	{
		FacadeModele::obtenirInstance()->modifierEtatDirectionnelle(etat);
	}

	__declspec(dllexport) void modifierEtatSpot(bool etat)
	{
		FacadeModele::obtenirInstance()->modifierEtatSpot(etat);
	}

	__declspec(dllexport) void reinitialiserTest()
	{
		FacadeModele::obtenirInstance()->reinitialiserTest();
	}

	__declspec(dllexport) void initaliserSono() 
	{
		FacadeModele::obtenirInstance()->initaliserSono();
	}
	__declspec(dllexport) void jouerSonDeFond()
	{
		FacadeModele::obtenirInstance()->jouerSonDeFond();
	}
	__declspec(dllexport) void jouerSonMaillet() 
	{
		FacadeModele::obtenirInstance()->jouerSonMaillet();
	}
	__declspec(dllexport) void jouerSonPortail() 
	{
		FacadeModele::obtenirInstance()->jouerSonPortail();
	}
	__declspec(dllexport) void jouerSonBut() 
	{
		FacadeModele::obtenirInstance()->jouerSonBut();
	}
	__declspec(dllexport) void mettreEnPause() 
	{
		FacadeModele::obtenirInstance()->mettreEnPause();
	}
	__declspec(dllexport) void relacherMusique() 
	{
		FacadeModele::obtenirInstance()->relacherMusique();
	}
	__declspec(dllexport) void enModeTest(bool modeEdition)
	{
		FacadeModele::obtenirInstance()->enModeTest(modeEdition);
	}

	__declspec(dllexport) void sizeFenetre(int x, int y)
	{
		FacadeModele::obtenirInstance()->sizeFenetre(x, y);
	}


	__declspec(dllexport) void tempsJouer(char* tempsJouer)
	{
		FacadeModele::obtenirInstance()->tempsJouer(tempsJouer);
	}

	__declspec(dllexport) void activationVueOrtho()
	{
		FacadeModele::obtenirInstance()->activationVueOrtho();
	}
	__declspec(dllexport) void activationVueOrbite()
	{
		FacadeModele::obtenirInstance()->activationVueOrbite();
	}
}




///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
