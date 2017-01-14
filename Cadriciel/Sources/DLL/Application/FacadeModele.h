//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__


#include <windows.h>
#include <string>
#include "../VisiteurSelection.h"
#include "../VisiteurDuplication.h"
#include "../VisiteurDeplacement.h"
#include "../VisiteurRotation.h"
#include "../VisiteurSuppression.h"
#include "../VisiteurEcritureXML.h"
#include "../VisiteurEchelle.h"
#include "../VisiteurRotation.h"
#include "../VisiteurCollision.h"
#include "Partie.h"
#include "Tournoi.h"
#include "../ProfilVirtuel.h"
// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, �t� 2011
#include "../../tinyxml2/include/tinyxml2.h"
#include "../Externe/FMOD/include/fmod.hpp"

#include "BoiteEnvironnement.h"

//#include "../Externe/FTGL/include/FTGL/ftgl.h"

class NoeudAbstrait;
class ArbreRenduINF2990;
class NoeudTable;

namespace vue {
   class Vue;
}


///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une fa�ade) sur l'ensemble
///        du mod�le et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.
   static FacadeModele* obtenirInstance();
   /// Lib�re l'instance unique de la classe.
   static void libererInstance();

   /// Cr�e un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration � partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Lib�re le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du mod�le.
   void afficher() const;
   /// Affiche la base du contenu du mod�le.
   void afficherBase() const;
   /// initialier le rectangle elastique
   void initialiserRectangleElas(int x, int y);

   /// mettre a jour le rectangle elastique
   void mettreAJourRectangleElas(int x1, int y1);

   /// finalise le rectangle elastique
   void terminerRectangleElas();

   ///Zoom in grace au rectangle elestique
   void zoomInElas();

   ///Zoom in grace au rectangle elestique
   void zoomOutElas();
	void zoomOut();
	void zoomIn();
   ///Selection avec rectangle elastique
   void selectionRectangle();
 
   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();
    /// Permet d'ajouter un noeud sans transformation sur la scene
   int ajouterNouveauElement(char* nomObjet, int x, int y);
   int ajouterNouveauPortail(char* nomObjet, int x, int y);
   /// R�initialise la sc�ne.
   void reinitialiser();

   /// Anime la sc�ne.
   void animer(float temps);
   void redessiner();
   void determinerCouleurPixel(int posX, int posY, GLubyte  couleurPixel[]);
   void selectionObjet(int posX, int posY, bool selectionUnique);


   void mettreAEchelle(int x, int y);

   ///Initialise la rotation en prenant le point initial de la souris
   void initialiserRotation(int pointY);
   ///Initialise le deplacement en prenant le point initial de la souris
   void initialiserDeplacement(int pointX, int pointY);

   ///Effectuer la rotation sur les objets selectionnes
   void effectuerRotation(int pointY);

   ///Effectuer le deplacement des objets
   void effectuerDeplacement(float x, float y);

   double obtenirFrictionTable();
	void deplacer(double deplacementX, double deplacementY);
   double obtenirAccelerationBonus();
   double obtenirCoefRebondissement();

   int obtenirPositionObjetX();
   int obtenirPositionObjetY();
   int obtenirPositionObjetZ();

   int obtenirAngleRotationObjet();

   double obtenirFacteurEchelleObjet();

   void mettreEchelleObjetBouton(double facteur);

   void rotationObjetBouton(int angle);

   void deplacementObjetBouton(float pointX, float pointY);

   void frictionTableBouton(double frictionTable);
   void accelerationBonusBouton(double accelerationBonus);
   void coefRebondissementBouton(double coefRebondissement);
	glm::dvec3 obtenirPositionSouris();
	void sauverSouris();
	//void obtenirPositionSouris(int x, int y);

	void deplacerSouris(int x, int y);

   //Permet de selectionner un objet ou plusieurs sur la scene
   void selectionner(int x, int y, bool selectionUnique);
   //Permettre la selection avec le rectangle elastique
   void selectionnerRectangle(int x, int y, int hauteur, int largeur, bool selectionUnique);
   //Modification de boutton CTRL
   void modifierEtatCTRL(bool etatCTRL);
   /// Efface les enfants sélectionnés.
   void effacerSelection();
   /// Sélectionne tous les enfants de même que le noeud.
   void selectionnerTout();
   /// Désélectionne tous les enfants de même que le noeud.
   void deselectionnerTout();

   //Permet de dupliquer un element de la scene
   void dupliquerSelection(int x, int y);

   //Permet la suppresion d'un objet ou plusieurs objets de la scene
   void supprimerSelection();

   //Permet le deplacement de la selection
   void deplacerSelection(int x, int y);

   //Sauvegarde de l'arbre
   void sauvegardeParDefaut();
   void sauvegarderArbre(std::string nomFichier);

   //Chargement de l'arbre
   void initialisationParDefaut();
   void initialiserChargement(std::string nomFichier);
   void chargerArbre(ArbreRenduINF2990 * arbre, NoeudAbstrait* noeudCourant, tinyxml2::XMLNode * parent);
   //Chargement des options de configuration
   void chargerConfigurationOptions();
   void miseAJourSauvegardeConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
	   int nbButs, char* haut, char* bas, char* gauche, char* droite, bool estVirtuel);
   void miseAJourChargementConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
	   int nbButs, char* haut, char* bas, char* gauche, char* droite, bool estVirtuel);
   void sauvegarderConfigurationOptions(char* haut, char* bas, char* gauche, char* droite);

   void initialiserSauvegardeTournoi();

   void sauvegarderTournoi();

   void chargementTournoi();

   void assignerJoueur1Tournoi(const char* nom, bool estVirtuel, int index);
   void assignerJoueur2Tournoi(const char* nom, bool estVirtuel, int index);
   void assignerJoueur3Tournoi(const char* nom, bool estVirtuel, int index);
   void assignerJoueur4Tournoi(const char* nom, bool estVirtuel, int index);

	const char * obtenirNomJoueur1Tournoi();

	const char * obtenirNomJoueur2Tournoi();

	const char * obtenirNomJoueur3Tournoi();

	const char * obtenirNomJoueur4Tournoi();

   bool obtenirTypeJoueur1Tournoi();

   bool obtenirTypeJoueur2Tournoi();

   bool obtenirTypeJoueur3Tournoi();

   bool obtenirTypeJoueur4Tournoi();

   int obtenirProfilJoueur1Tournoi();

   int obtenirProfilJoueur2Tournoi();

   int obtenirProfilJoueur3Tournoi();

   int obtenirProfilJoueur4Tournoi();

   //Obtention des options de configuration
   bool obtenirPeutAfficherDebogage();
   bool obtenirPeutAfficherCollision();
   bool obtenirPeutAfficherVitesse();
   bool obtenirPeutAfficherEclairage();
   bool obtenirPeutAfficherAttractionPortail();

   int obtenirNbButs();
   const char*  obtenirHaut();
   const char* obtenirBas();
   const char* obtenirGauche();
   const char* obtenirDroite();

   bool obtenirEstVirtuel();
	void deplacerClavier(double x, double y);
   //Gestion des profils
   void creerProfil(char* nom, int vitesse, int passivite);
   void ajouterProfil(ProfilVirtuel profil);
   void ajouterNouveauProfil(char* nom, int vitesse, int passivite);
   void ajouterNouveauProfil(std::string nom, int vitesse, int passivite);
   int nombreProfils();
   const char* nomDuProfil(int profilChoisi);
   int vitesseDuProfil(int profilChoisi);
   int passiviteDuProfil(int profilChoisi);

   void sauvegardeProfils();
   void chargementProfils();
   void clearXML();

   void supprimerProfil(std::string nom);

   void reinitialiserProfils();
   //Initialisation de la partie
   void initialiserPartie(int, bool);
   void lancerPartieRapide();
   void lancerPartieTournoi(std::string nom1, std::string nom2);
   void assignerBut(bool joueur1);
   void initialiserPartieTournoi();
   void arreterPartie();
   void arreterPartie(std::string);
   void arreterTournoi();
	void initialiserTournoi(int, bool, string, bool, string, bool, string, bool, string);
   void joueurMaillet1(int x, int y);
   void joueurMaillet2(double x, double y);
   bool estDansTable(glm::dvec3 point);
   bool estDanTable(NoeudAbstrait* noeud);
   void reinitialiserTest();

   void ajouterNomProfil(std::string nom);

   void nextPartie();
   bool afficherPanelRapide();
   int scoreFinalPerdant();
   bool nomVainqueurPartieRapide();

   bool getJoueur1Passe();
   bool getJoueur3Passe();
   bool getVainqueur1Passe();
   bool getActualiser1();
   bool getActualiser2();
   bool getActualiser3();
   void reinitialiserPartie();
   bool butsActifs();

   void adversaireVirtuel(bool virtuel);
   bool adversaireEstVirtuel();

   void enModeEdition(bool modeEdition);
   bool modeEdition() { return modeEdition_; }

   bool joueurVirtuelDansPartieCourante();
	void setTypeValue(bool value);
	bool getTypeValue();
	void activationVueOrbite();
	void activationVueOrtho();
	
	////Sauvegarde de l'arbre
	//void sauvegardeParDefaut();
	//void sauvegarderArbre(std::string nomFichier);

	////Chargement de l'arbre
	//void initialisationParDefaut();
	//void initialiserChargement(std::string nomFichier);
	//void chargerArbre(ArbreRenduINF2990 * arbre, NoeudAbstrait* noeudCourant, tinyxml2::XMLNode * parent);
	////Chargement des options de configuration
	//void chargerConfigurationOptions();
	//void miseAJourSauvegardeConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
	//	int nbButs, char* haut, char* bas, char* gauche, char* droite, bool estVirtuel);
	//void miseAJourChargementConfiguration(bool peutAfficherDebogage, bool peutAfficherCollision, bool peutAfficherVitesseRondelle, bool peutAfficherEclairage, bool peutAfficherAttractionPortail,
	//	int nbButs, char* haut, char* bas, char* gauche, char* droite, bool estVirtuel);
	//void sauvegarderConfigurationOptions(char* haut, char* bas, char* gauche, char* droite);
	//void initialiserSauvegardeTournoi();
	//void sauvegarderTournoi();
	//void chargementTournoi();

	//void assignerJoueur1Tournoi(const char* nom, bool estVirtuel, int index);
	//void assignerJoueur2Tournoi(const char* nom, bool estVirtuel, int index);
	//void assignerJoueur3Tournoi(const char* nom, bool estVirtuel, int index);
	//void assignerJoueur4Tournoi(const char* nom, bool estVirtuel, int index);

	//const char* obtenirNomJoueur1Tournoi();
	//const char* obtenirNomJoueur2Tournoi();
	//const char* obtenirNomJoueur3Tournoi();
	//const char* obtenirNomJoueur4Tournoi();

	//bool obtenirTypeJoueur1Tournoi();
	//bool obtenirTypeJoueur2Tournoi();
	//bool obtenirTypeJoueur3Tournoi();
	//bool obtenirTypeJoueur4Tournoi();

	//int obtenirProfilJoueur1Tournoi();
	//int obtenirProfilJoueur2Tournoi();
	//int obtenirProfilJoueur3Tournoi();
	//int obtenirProfilJoueur4Tournoi();

	////Obtention des options de configuration
	//bool obtenirPeutAfficherDebogage();
	//bool obtenirPeutAfficherCollision();
	//bool obtenirPeutAfficherVitesse();
	//bool obtenirPeutAfficherEclairage();
	//bool obtenirPeutAfficherAttractionPortail();

	//int obtenirNbButs();
	//const char*  obtenirHaut();
	//const char* obtenirBas();
	//const char* obtenirGauche();
	//const char* obtenirDroite();

   void initaliserSono();
   void jouerSonMaillet();
   void jouerSonMur();
   void jouerSonDeFond();
   void jouerSonPortail();
   void jouerSonBut();
   void mettreEnPause();
   void relacherMusique();

   void sizeFenetre(int x, int y);

   void tempsJouer(char* tempsJouer);
   bool obtenirEtatAmbiante() { return ambianteEstActive_; }
   bool obtenirDirectionnelActive() { return utiliserDirectionnelle_; }
   bool obtenirEtatSpot() { return spotActive_; }
   void modifierEtatAmbiante(bool etat) {
	   ambianteEstActive_ = etat;
	   string eta;
	   if (etat)
		   eta = "ouverte";
	   else
		   eta = "fermee";
	   cout << collision_->afficherTemps() << " - Lumiere(s) ambiantes " << eta << endl;
   }
   void modifierEtatDirectionnelle(bool etat) {
	   utiliserDirectionnelle_ = etat;
	   string eta;
	   if (etat)
		   eta = "ouverte";
	   else
		   eta = "fermee";
	   cout << collision_->afficherTemps() << " - Lumiere(s) directionnnelle " << eta << endl;
   }
   void modifierEtatSpot(bool etat) {
	   spotActive_ = etat;
	   string eta;
	   if (etat)
		   eta = "ouvertes";
	   else
		   eta = "fermees";
	   cout << collision_->afficherTemps() << " - Lumieres spot " << eta << endl;
   }

   void enModeTest(bool modeTest);

private:
   /// Constructeur par d�faut.
   FacadeModele() = default;
   /// Destructeur.
   ~FacadeModele();
   /// Constructeur copie d�sactiv�.
   FacadeModele(const FacadeModele&) = delete;
   /// Op�rateur d'assignation d�sactiv�.
   FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele* instance_;

   /// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poign�e ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poign�e ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la sc�ne.
   vue::Vue* vue_{ nullptr };

	/// Vue courante ortho
	vue::Vue* vueOrtho_{ nullptr };
	/// Vue courante orbite
	vue::Vue* vueOrbite_{ nullptr };
   /// Arbre de rendu contenant les diff�rents objets de la sc�ne.
   ArbreRenduINF2990* arbre_{ nullptr };
   ///La table du jeu
   NoeudTable* table_{ nullptr };
   char modeApplication_{ 'R' };
   //VIsiteur de duplication
   VisiteurDuplication* duplicateur_;
   //Visiteur de Deplacement
   VisiteurDeplacement* deplacement_;
   //Visiteur de suppression
   VisiteurSuppression* supprimeur_;
   //Visiteur de rotation
   VisiteurRotation* rotateur_;
   //Visiteur pour la mise a l'echelle
   VisiteurEchelle* visiteurEchelle_;
   //Etat du boutton ctrl
   bool etatCTRL_;
   //Visiteur pour les collisions
   VisiteurCollision* collision_;

   /// Point d'ancrage rectangle elastique
   int pointAncrageX_;
   int pointAncrageY_;
   ///Point final du rectangle elastique
   int pointFinalX_;
   int pointFinalY_;
	int pointInitialX_;
	int pointInitialY_;
   // Options du menu configuration
   /// Permet l'affichage de debogage
   bool peutAfficherDebogage_;
   /// Permet l'affichage du type d'objet qui entre en collision avec la rondelle
   bool peutAfficherCollision_;
   ///Permet l'affichage de la vitesse de la rondelle suite a une collision
   bool peutAfficherVitesseRondelle_;
   ///Permet l'affichage de l'etat de l'eclairage
   bool peutAfficherEclairage_;
   ///Permet l'affichage de la delimitation de l'attraction des portails est affichee
   bool peutAfficherAttractionPortail_;
   ///Permet de savoir si la lumiere ambiante du modele est activer
   bool ambianteEstActive_;
   ///Permet de savoir si on utilise la lumiere directionnel ou pas
   bool utiliserDirectionnelle_;
   ///Permet de savoir le spot est activer
   bool spotActive_;
   /// Nombre de buts necessaires pour gagner une partie
   int nbButs_;

   ///Touches de controle 
  char*  haut_;
   char* bas_;
   char* gauche_;
   char*  droite_;

   string sHaut_;
   string sBas_;
   string sGauche_;
   string sDroite_;

   /// Vecteur des profils virtuels qui ont ete crees
   std::vector<ProfilVirtuel> listeProfils;
   std::vector<std::string> nomProfils;
   std::vector<char*> charProfils;
   NoeudJoueur listeJoueursTournoi[4];
   int indexTournoi[4];
   std::string listeNomTournoi[4];
	///Determine si le deuxieme joueur est virtuel ou non pour le mode test
	bool estVirtuel_;


   ///Donnees du mode partie rapide

   ///Partie en train d'etre jouer 
   Partie* partieEnCours_;
   Tournoi* tournoiEnCours_;
   int nbMaxPartieTournoi_ = 3;
   
   NoeudJoueur tableauJoueurPartie[4];
   bool enTournoi_ = false;

   bool j1_ = false;
   std::string nom1_ = "Joueur 1";
   bool j2_ = true;
   std::string nom2_ = "Joueur 2";
   bool j3_ = true;
   std::string nom3_ = "Joueur 3";
   bool j4_ = true;
   std::string nom4_ = "Joueur 4";

   bool vainqueur1_;
   std::string nomVainqueur1_;

   bool vainqueur2_;
   std::string nomVainqueur2_;

   std::string gagnant_;
   std::string gagnantPartieRapide_;

   bool afficherPanelRapide_ = false;
	glm::dvec3 positionSouris_;
   bool leVainqueur_ = false;
   int scoreFinalLooser_ = 0;
   //public void miseAJourArbre(bool joueur1Passe, bool joueur3Passe, bool vainqueur1Passe, bool actualiser1, bool actualiser2, bool actualiser3)
   bool joueur1Passe_ = false; 
   bool joueur3Passe_ = false;
   bool vainqueur1Passe_ = false;
   bool actualiser1_ = false;
   bool actualiser2_ = false;
   bool actualiser3_ = false;

   bool modeEdition_ = true;
   bool modeTest_ = false;
   bool activerBut_ = true;
   bool adversaireVirtuel_;
   bool joueurVirtuelDansPartieCourante_;
   FMOD_SYSTEM *leSysteme_;
   FMOD_SOUND *collisionMur_ = NULL;
   FMOD_SOUND *but_ = NULL;
   FMOD_SOUND *collisionMaillet_ = NULL;
   FMOD_SOUND *collisionPortail_ = NULL;
   FMOD_SOUND *sonDeFond_ = NULL;
   FMOD_CHANNEL *chaine_ = NULL;

   utilitaire::BoiteEnvironnement* boite_;

   

   int fenetreX_ = 0;
   int fenetreY_ = 0;

   string afficherNom1_ = "Joueur 1";
   string afficherNom2_ = "Joueur 2";
   int butJoueur1_ = 0;
   int butJoueur2_ = 0;
   string tempsJouer_ = "00:00";
   //bool modeTest_ = false;

	bool typeVue_=false;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est pr�sentement utilis�e pour
/// voir la sc�ne.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
