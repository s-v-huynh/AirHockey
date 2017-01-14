////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__

#include <string>

extern "C" {

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();
	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void animer(double temps);
	__declspec(dllexport) void redessiner();
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();
	__declspec(dllexport) int obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
    __declspec(dllexport) int ajouterNouveauElement(char* nom, int x, int y);
	__declspec(dllexport) int ajouterNouveauPortail(char* nom, int x, int y);
	__declspec(dllexport) void initialiserRectangleElas(int x, int y);
	__declspec(dllexport) void mettreAJourRectangleElas(int x1, int y1);
	__declspec(dllexport) void terminerRectangleElas();
	__declspec(dllexport) void selectionObjet(int posX, int posY,bool attribuer);
	__declspec(dllexport) void miseAEchelle(int x, int y);
	__declspec(dllexport) void initialiserRotation(int pointY);
	__declspec(dllexport) void initialiserDeplacement(int pointX, int pointY);
	__declspec(dllexport) void effectuerRotation(int pointY);
	__declspec(dllexport) void sauverSouris();
	__declspec(dllexport) void deplacerSouris(int x, int y);
	__declspec(dllexport) void effectuerDeplacement(float pointX, float pointY);
	__declspec(dllexport) double obtenirFrictionTable();
	__declspec(dllexport) double obtenirAccelerationBonus();
	__declspec(dllexport) double obtenirCoefRebondissement();
	__declspec(dllexport) int obtenirPositionObjetX();
	__declspec(dllexport) int obtenirPositionObjetY();
	__declspec(dllexport) int obtenirPositionObjetZ();
	__declspec(dllexport) int obtenirAngleRotationObjet();
	__declspec(dllexport) double obtenirFacteurEchelleObjet();
	__declspec(dllexport) void mettreEchelleObjetBouton(double facteur);
	__declspec(dllexport) void rotationObjetBouton(int angle);
	__declspec(dllexport) void deplacementObjetBouton(float pointX, float pointY);
	__declspec(dllexport) void deplacer(int pointX, int pointY);
	__declspec(dllexport) void frictionTableBouton(double frictionTable);
	__declspec(dllexport) void accelerationBonusBouton(double accelerationBonus);
	__declspec(dllexport) void coefRebondissementBouton(double coefRebondissement);
	__declspec(dllexport) void dupliquerSelection(int x, int y);
	__declspec(dllexport) void supprimerSelection();
    __declspec(dllexport) void deselectionnerTout();
    __declspec(dllexport) void selectionnerTout();
    __declspec(dllexport) void effacerSelection();
    __declspec(dllexport) void modifierEtatCTRL(bool etatCTRL);
    __declspec(dllexport) void deplacerSelection(int x, int y);
	//__declspec(dllexport) void selectionner(int x, int y, bool selectionUnique);
	__declspec(dllexport) void selectionnerRectangle(int x, int y, int hauteur, int largeur, bool selectionUnique);
	__declspec(dllexport) void sauvegarderArbre(char* nomFichier);
	__declspec(dllexport) void initialiserChargement(char* nomFichier);
	__declspec(dllexport) void sauvegardeParDefaut();
	__declspec(dllexport) void initialisationParDefaut();
	__declspec(dllexport) void deplacerXY(double deplacementX, double deplacementY, int x, int y);
	__declspec(dllexport) void zoomInElas();
	__declspec(dllexport) void zoomOutElas();
	__declspec(dllexport) void selectionElastique();
	__declspec(dllexport) void chargerConfigurationOptions();
	__declspec(dllexport) void miseAJourSauvegardeConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
		int nbButs, char* haut, char* bas, char* gauche, char* droite, bool estVirtuel);
	__declspec(dllexport) void miseAJourChargementConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
		int nbButs, char* haut, char* bas, char* gauche, char* droite, bool estVirtuel);
	__declspec(dllexport) void sauvegarderConfigurationOptions(char* haut, char* bas, char* gauche, char* droite);
	__declspec(dllexport) bool obtenirPeutAfficherDebogage();
	__declspec(dllexport) bool obtenirPeutAfficherCollision();
	__declspec(dllexport) bool obtenirPeutAfficherVitesse();
	__declspec(dllexport) bool obtenirPeutAfficherEclairage();
	__declspec(dllexport) bool obtenirPeutAfficherAttractionPortail();
	__declspec(dllexport) int obtenirNbButs();
	__declspec(dllexport) const char* obtenirHaut();
	__declspec(dllexport) const char* obtenirBas();
	__declspec(dllexport) const char* obtenirGauche();
	__declspec(dllexport) const char* obtenirDroite();
	__declspec(dllexport) void creerProfil(char* nom, int vitesse, int passivite);
	__declspec(dllexport) void ajouterNouveauProfil(char* nom, int vitesse, int passivite);
	__declspec(dllexport) void sauvegardeProfils();
	__declspec(dllexport) void chargementProfils();
	__declspec(dllexport) void supprimerProfil(std::string nom);
	__declspec(dllexport) int nombreProfils();
	__declspec(dllexport) const char* nomDuProfil(int profilChoisi);
	__declspec(dllexport) int vitesseDuProfil(int profilChoisi);
	__declspec(dllexport) int passiviteDuProfil(int profilChoisi);
	__declspec(dllexport) void reinitialiserProfils();
	__declspec(dllexport) void ajouterNomProfil(char* nom);

	__declspec(dllexport) void sauvegarderTournoi();
	__declspec(dllexport) void chargementTournoi();

	__declspec(dllexport) void assignerJoueur1Tournoi(char* nom, bool estVirtuel, int index);
	__declspec(dllexport) void assignerJoueur2Tournoi(char* nom, bool estVirtuel, int index);
	__declspec(dllexport) void assignerJoueur3Tournoi(char* nom, bool estVirtuel, int index);
	__declspec(dllexport) void assignerJoueur4Tournoi(char* nom, bool estVirtuel, int index);

	__declspec(dllexport) const char* obtenirNomJoueur1Tournoi();
	__declspec(dllexport) const char* obtenirNomJoueur2Tournoi();
	__declspec(dllexport) const char* obtenirNomJoueur3Tournoi();
	__declspec(dllexport) const char* obtenirNomJoueur4Tournoi();

	__declspec(dllexport) bool obtenirTypeJoueur1Tournoi();
	__declspec(dllexport) bool obtenirTypeJoueur2Tournoi();
	__declspec(dllexport) bool obtenirTypeJoueur3Tournoi();
	__declspec(dllexport) bool obtenirTypeJoueur4Tournoi();

	__declspec(dllexport) int obtenirProfilJoueur1Tournoi();
	__declspec(dllexport) int obtenirProfilJoueur2Tournoi();
	__declspec(dllexport) int obtenirProfilJoueur3Tournoi();
	__declspec(dllexport) int obtenirProfilJoueur4Tournoi();

	__declspec(dllexport) bool obtenirEstVirtuel();

	__declspec(dllexport) bool obtenirEstVirtuel();
	//__declspec(dllexport) void joeurMaillet1(int x, int y);

	__declspec(dllexport) bool obtenirEstVirtuel();
	__declspec(dllexport) void joueurMaillet1(int x, int y);
	__declspec(dllexport) void joueurMaillet2(double x, double y);

	__declspec(dllexport) void initialiserPartie(int, bool);
	__declspec(dllexport) void lancerPartieRapide();
	__declspec(dllexport) void lancerPartieTournoi(char* nom1, char* nom2);
	__declspec(dllexport) void assignerBut(bool joueur1);
	__declspec(dllexport) void initialiserPartieTournoi();
	__declspec(dllexport) void arreterPartie();
	__declspec(dllexport) void arreterTournoi();
	__declspec(dllexport) void initialiserTournoi(int nbBut,bool j1, char* nom1, bool j2, char* nom2, bool j3, char* nom3, bool j4, char* nom4);
	__declspec(dllexport) void nextPartie();
	__declspec(dllexport) void reinitialiserTest();

	__declspec(dllexport) bool afficherPanelRapide();
	__declspec(dllexport) bool nomVainqueurPartieRapide();
	__declspec(dllexport) int scoreFinalPerdant();


	__declspec(dllexport) bool getJoueur1Passe();
	__declspec(dllexport) bool getJoueur3Passe();
	__declspec(dllexport) bool getVainqueur1Passe();
	__declspec(dllexport) bool getActualiser1();
	__declspec(dllexport) bool getActualiser2();
	__declspec(dllexport) bool getActualiser3();

	__declspec(dllexport) void enModeEdition(bool modeEdition);

	__declspec(dllexport) void reinitialiserPartie();

	__declspec(dllexport) void adversaireVirtuel(bool virtuel);
	__declspec(dllexport) bool joueurVirtuelDansPartieCourante();

	__declspec(dllexport) void initaliserSono();
	//__declspec(dllexport) void jouerSonMaillet();
	__declspec(dllexport) void jouerSonDeFond();
	//__declspec(dllexport) void jouerSonPortail();
	//__declspec(dllexport) void jouerSonBut();
	__declspec(dllexport) void mettreEnPause();
	__declspec(dllexport) void relacherMusique();
	__declspec(dllexport) void enModeTest(bool modeEdition);
	__declspec(dllexport) void sizeFenetre(int x, int y);

	__declspec(dllexport) void tempsJouer(char* tempsJouer);

	__declspec(dllexport) void enModeTest(bool modeTest);

	__declspec(dllexport) void setTypeValue(bool value);
	__declspec(dllexport) void activationVueOrbite();
	__declspec(dllexport) void activationVueOrtho();
	__declspec(dllexport) bool obtenirEtatAmbiante();
	__declspec(dllexport) bool obtenirDirectionnelActive();
	__declspec(dllexport) bool obtenirEtatSpot();
	__declspec(dllexport) void modifierEtatAmbiante(bool etat);
	__declspec(dllexport) void modifierEtatDirectionnelle(bool etat);
	__declspec(dllexport) void modifierEtatSpot(bool etat);

	__declspec(dllexport) void setTypeValue(bool value);
	__declspec(dllexport) void activationVueOrtho();
	__declspec(dllexport) void activationVueOrbite();
}

#endif // __FACADE_INTERFACE_NATIVE_H__
