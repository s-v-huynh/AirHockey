//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCollision.cpp
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "VisiteurCollision.h"
#include "Utilitaire.h"
#include "AideGL.h"
#include "GL\gl.h"
#include "GL\glew.h"
#include "GL\glew.h"
#include "GL\wglew.h"

#include "NoeudTypes.h"
#include "NoeudMailletVirtuel.h"
#include "../Application/FacadeModele.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCollision::VisiteurCollision()
///
/// Constructeur par defaut, ne fait rien de special
///
/// @param[in] Aucun : Rein defaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
VisiteurCollision::VisiteurCollision() {

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCollision::VisiteurCollision(NoeudRondelle* rondelle, double coefRebon, std::vector<NoeudPortail*> portails, double acceleration)
///
/// Constructeur par parametres
///
/// @param[in] rondelle : la rondelle du jeux, coefRebon : le coefficient de rebon de la table,  portails : la liste de portails 
///			   acceleration : l'acceleration de la table
///
/// @return Aucune : constructeur.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VisiteurCollision::VisiteurCollision(NoeudRondelle* rondelle, double coefRebon, std::vector<NoeudPortail*> portails, double acceleration) :
rondelle_(rondelle), coefRebon_(coefRebon), acceleration_(acceleration){
	for (unsigned int i = 0; i < portails.size(); i++) {
		listePortails_.push_back(portails[i]);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCollision::~VisiteurCollision()
///
/// Destructeur : desalloue la memoire
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
VisiteurCollision::~VisiteurCollision(){
	delete rondelle_;
	for (unsigned int i = 0; i < listePortails_.size(); i++) {
		delete listePortails_[i];
	}
	listePortails_.clear();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::definirTable(NoeudTable* table)
///
/// Cette fonction permet de definir la table de jeu.
///
/// @param[in] table : la table du jeu.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::definirTable(NoeudTable* table) {
	zoneJeu_ = table;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudComposite* noeud)
///
/// Cette fonction permet de visiter un noeud composite.
///
/// @param[in] noeud : Le noeud a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudComposite* noeud) {


}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudMaillet* noeud)
///
/// Cette fonction permet de verifier si il y a eu collision entre le 
///maillet et un autre objet.
///
/// @param[in] noeud : Le noeud a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudMaillet* noeud) {
	glm::dvec2 force;
	vector<glm::dvec3> sommetsT = noeud->obtenirParent()->obtenirSommets();
	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(noeud->obtenirPositionRelative(), noeud->obtenirRayonMaillet()*2, rondelle_->obtenirPositionRelative(), rondelle_->obtenirRayonRondelle()*2);
	force = aidecollision::calculerForceRebondissement2D(collision, coefRebon_);
	//On verifie si la collision a bien eu lieu
	if (force.x != 0 || force.y != 0) {
		rondelle_->modifierVitesse(glm::dvec2(rondelle_->obtenirVitesse().x + force.x, rondelle_->obtenirVitesse().y + force.y));
		FacadeModele::obtenirInstance()->jouerSonMaillet();
		gererDebogage("Maillet");
	}
	collision = aidecollision::calculerCollisionSegment(sommetsT[3], sommetsT[7], noeud->obtenirPositionRelative(),
		noeud->obtenirRayonMaillet()*4,
		false);
	if (collision.enfoncement > 0) {
		//Arreter le deplacement du maillet
		//noeud->toucherMedian(true);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurCollision::visiter(NoeudMailletVirtuel* noeud)
///
/// Cette fonction permet de verifier si il y a eu collision entre le 
///maillet virtuelle et un autre objet.
///
/// @param[in] noeud : Le noeud a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudMailletVirtuel* noeud) {
	glm::dvec2 force;
	vector<glm::dvec3> sommetsT = noeud->obtenirParent()->obtenirSommets();
	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(noeud->obtenirPositionRelative(), noeud->obtenirRayonMailletV() * 2, rondelle_->obtenirPositionRelative(), rondelle_->obtenirRayonRondelle() * 2);
	force = aidecollision::calculerForceRebondissement2D(collision, coefRebon_);
	//On verifie si la collision a bien eu lieu
	if (force.x != 0 || force.y != 0) {
		rondelle_->modifierVitesse(glm::dvec2(rondelle_->obtenirVitesse().x + force.x, rondelle_->obtenirVitesse().y + force.y));
		FacadeModele::obtenirInstance()->jouerSonMaillet();
		gererDebogage("Maillet Adversaire");
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudMuret* noeud)
///
/// Cette fonction permet de verifier si il y a eu collision entre le 
///muret et un autre objet.
///
/// @param[in] noeud : Le noeud a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudMuret* noeud) {
	glm::dvec2 force;
	vector<glm::dvec3> sommetsMur = noeud->obtenirSommets();
	//std::cout << sommetsMur[0].x << "  " << sommetsMur[0].y  <<"  "<< sommetsMur[0].z << " Y " <<sommetsMur[1].x << "  " << sommetsMur[1].y << "  " << sommetsMur[1].z << std::endl;
	aidecollision::DetailsCollision collision;
	collision = aidecollision::calculerCollisionSegment(sommetsMur[1], sommetsMur[0], rondelle_->obtenirPositionRelative(),
		rondelle_->obtenirRayonRondelle() * 2,
		true);
	force = aidecollision::calculerForceRebondissement2D(collision, 2.0);
	if (force.x != 0 || force.y != 0) {
		rondelle_->modifierVitesse(glm::dvec2((rondelle_->obtenirVitesse().x + force.x), (rondelle_->obtenirVitesse().y + force.y)));
		FacadeModele::obtenirInstance()->jouerSonPortail();
		gererDebogage("Muret");
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudPortail* noeud)
///
/// Cette fonction permet de verifier si il y a eu collision entre le 
///portail et un autre objet.
///
/// @param[in] noeud : Le noeud a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudPortail* noeud) {
	glm::dvec2 vitesseInitial = rondelle_->obtenirVitesse();
	if(noeud->obtenirAttraction()){
		aidecollision::DetailsCollision collision1 = aidecollision::calculerCollisionSphere(noeud->obtenirPositionRelative(), noeud->obtenirRayonAttraction()*2, rondelle_->obtenirPositionRelative(),
			rondelle_->obtenirRayonRondelle()*2);
		if (collision1.enfoncement > 0) {		
			//rondelle_->modifierVitesse(vitesseInitial*1.002);
			gererDebogage("Rayon d'attraction Portail");
			rondelle_->assignerPositionRelative(noeud->obtenirPositionRelative());
			//noeud->modifierVitesseRotation(-0.5f);
		}

		aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(noeud->obtenirPositionRelative(), noeud->obtenirRayon()*2, rondelle_->obtenirPositionRelative(),
			rondelle_->obtenirRayonRondelle()*2);
		//verifier si il y a eu collision avec la rondelle
		if (collision.enfoncement > 0) {
			//desactiver l'attraction de la destination
			noeud->getFrere()->desactiverAttraction();
			rondelle_->assignerPositionRelative(noeud->getFrere()->obtenirPositionRelative());
			rondelle_->modifierVitesse(glm::dvec2((rondelle_->obtenirVitesse().x), (rondelle_->obtenirVitesse().y)));
			FacadeModele::obtenirInstance()->jouerSonPortail();
			gererDebogage("Portail");
		}
	}
	else {
		aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(noeud->obtenirPositionRelative(), noeud->obtenirRayonAttraction()*2, rondelle_->obtenirPositionRelative(),
			rondelle_->obtenirRayonRondelle());
		//verifier si il y a eu collision avec la rondelle
		if (!(collision.enfoncement > 0)) {
			//std::cout << "Re-activation attraction" << std::endl;
			quitterPortail();
			noeud->activerAttraction();
		}

		
		
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudRondelle* noeud)
///
/// Cette fonction permet de verifier si il y a eu collision entre la
///rondelle et un autre objet.
///
/// @param[in] noeud : Le noeud a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudRondelle* noeud) {
	//Rien faire
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudTable* noeud)
///
/// Cette fonction permet de verifier si il y a eu collision entre la
///table et un autre objet, elle permet aussi de visiter ses enfants.
///
/// @param[in] noeud : Le noeud a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudTable* noeud) {
	facade = FacadeModele::obtenirInstance();
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
	glm::dvec2 force;
	aidecollision::DetailsCollision collision;
	vector<glm::dvec3> sommetsT = noeud->obtenirSommets();
	int nbSommets = sommetsT.size();
	for(unsigned int i = 0; i < nbSommets - 1; i++){
	
		if (i == 0) {
			collision = aidecollision::calculerCollisionSegment(sommetsT[i], sommetsT[12], rondelle_->obtenirPositionRelative(),
				rondelle_->obtenirRayonRondelle() * 2,
				false);
		}
		else if (i == 11) {
			collision = aidecollision::calculerCollisionSegment(sommetsT[i], sommetsT[2], rondelle_->obtenirPositionRelative(),
				rondelle_->obtenirRayonRondelle() * 2,
				false);
		}
		else if (i == 4) {
			collision = aidecollision::calculerCollisionSegment(sommetsT[i], sommetsT[9], rondelle_->obtenirPositionRelative(),
				rondelle_->obtenirRayonRondelle() * 2,
				false);
		}
		else if (i == 10) {
			collision = aidecollision::calculerCollisionSegment(sommetsT[i], sommetsT[6], rondelle_->obtenirPositionRelative(),
				rondelle_->obtenirRayonRondelle() * 2,
				false);
		}
		else if (i == 7) {
			collision = aidecollision::calculerCollisionSegment(sommetsT[7], sommetsT[0], rondelle_->obtenirPositionRelative(),
				rondelle_->obtenirRayonRondelle() * 2,
				false);
		}
		else if( i == 2 || i == 3 || i == 6){
			collision = aidecollision::calculerCollisionSegment(sommetsT[i], sommetsT[i + 1], rondelle_->obtenirPositionRelative(),
				rondelle_->obtenirRayonRondelle()*2,
				false);
		}
		

		force = aidecollision::calculerForceRebondissement2D(collision, 2.0);
		if(force.x != 0 || force.y != 0){
			rondelle_->modifierVitesse(glm::dvec2((rondelle_->obtenirVitesse().x + force.x), (rondelle_->obtenirVitesse().y + force.y)));
			FacadeModele::obtenirInstance()->jouerSonMur();
			gererDebogage("Table");
		}
	}
	//Collision pour les buts	
	for (unsigned int i = 9; i < nbSommets - 1; i++) {
		collision = aidecollision::calculerCollisionSegment(sommetsT[i], sommetsT[i + 1], rondelle_->obtenirPositionRelative(),
			rondelle_->obtenirRayonRondelle(),
			false);
		if (collision.enfoncement > 0) {
			if (i == 9) {
				gererDebogage("But Gauche");
				butsJoueur1_++;
				//if (FacadeModele::obtenirInstance()->modeEdition()) ///////pb
				//{
					FacadeModele::obtenirInstance()->assignerBut(false);
					FacadeModele::obtenirInstance()->jouerSonBut();
				//}
				//FacadeModele::obtenirInstance()->assignerBut(false);
				reinitialiserPartie();
			}
			if (i == 11) {
				gererDebogage("But Droite");
				butsJoueur2_++;
				//if (FacadeModele::obtenirInstance()->modeEdition()) ///////pb
				//{
					FacadeModele::obtenirInstance()->assignerBut(true);
					FacadeModele::obtenirInstance()->jouerSonBut();
				//}
				//FacadeModele::obtenirInstance()->assignerBut(true);
				reinitialiserPartie();
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visiter(NoeudBonusAccelerateur* noeud)
///
/// Cette fonction permet de verifier si il y a eu collision entre le 
///bonus d'acceleration et un autre objet.
///
/// @param[in] noeud : Le noeud a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visiter(NoeudBonusAccelerateur* noeud) {
	aidecollision::DetailsCollision c = aidecollision::calculerCollisionSphere(noeud->obtenirPositionRelative(), noeud->obtenirRayonBonusAccelerateur()*2, rondelle_->obtenirPositionRelative(),
		rondelle_->obtenirRayonRondelle()*2);
	//verifier si il y a eu collision avec la rondelle
	if (c.enfoncement > 0) {
		rondelle_->modifierVitesse(rondelle_->obtenirVitesse()*acceleration_);
		FacadeModele::obtenirInstance()->jouerSonPortail();
		gererDebogage("Bonus d'acceleration");
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::reinitialiserPartie()
///
/// Cette fonction permet de reinintialiser la la partie.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::reinitialiserPartie()
{
	rondelle_->assignerPositionRelative(glm::dvec3(0.0, 0.0, 0.0));
	rondelle_->modifierVitesse(glm::dvec2(0.0, 0.0));
	maillet1_ = rondelle_->obtenirParent()->chercher(0);
	maillet2_ = rondelle_->obtenirParent()->chercher(1);
	maillet1_->assignerSelection(false); 
	maillet1_->assignerPositionRelative(maillet1_->obtenirPositionInitial());
	maillet2_->assignerPositionRelative(maillet2_->obtenirPositionInitial());

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::quitterPortail()
///
/// Cette fonction permet de pousser la rondelle a quitter le portail
///pour ne pas etre reabsorber.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::quitterPortail()
{
	glm::dvec2 position;
	if (rondelle_->obtenirVitesse().x > 0)
		position[0] = rondelle_->obtenirPositionRelative().x + 0.8;
	if (rondelle_->obtenirVitesse().x < 0)
		position[0] = rondelle_->obtenirPositionRelative().x - 0.8;
	if (rondelle_->obtenirVitesse().y > 0)
		position[1] = rondelle_->obtenirPositionRelative().y + 0.8;
	if (rondelle_->obtenirVitesse().y < 0)
		position[1] = rondelle_->obtenirPositionRelative().y - 0.8;
	rondelle_->assignerPositionRelative(glm::dvec3(position, rondelle_->obtenirPositionRelative().z));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::initialiserScores()
///
/// Cette fonction permet de reinitialiser le scores pour les deux joueurs.
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::initialiserScores()
{
	butsJoueur1_ = 0;
	butsJoueur2_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int  VisiteurCollision::getButJoueurG()
///
/// Cette fonction retourne le nombre de but gauche.
///
/// @param[in] Aucun.
///
/// @return le nombre de but du joueur gauche.
///
////////////////////////////////////////////////////////////////////////
int  VisiteurCollision::getButJoueurG()
{
	return nbButDroite_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int  VisiteurCollision::getButJoueurD()
///
/// Cette fonction retourne le nombre de but droite.
///
/// @param[in] Aucun.
///
/// @return le nombre de but du joueur droite.
///
////////////////////////////////////////////////////////////////////////
int  VisiteurCollision::getButJoueurD() 
{
	return nbButGauche_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::gererDebogage(string objet)
///
/// Cette fonction affiche le debogage selon les booleans de l'utilisateur, 
///
/// @param[in] objet : l'objet avec qui la rondelle entre en collision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::gererDebogage(string objet)
{
	if (!FacadeModele::obtenirInstance()->modeEdition()) {
		if (FacadeModele::obtenirInstance()->obtenirPeutAfficherCollision())
			std::cout << afficherTemps() << " - Collision : " << objet << std::endl;
		if (FacadeModele::obtenirInstance()->obtenirPeutAfficherVitesse())
			std::cout << afficherTemps() << " - Vitesse : " << sqrt(pow(rondelle_->obtenirVitesse().x, 2) + pow(rondelle_->obtenirVitesse().y, 2)) << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn string VisiteurCollision::afficherTemps()
///
/// Cette fonction permet de calculer le temps.
///
/// @param[in] Aucun.
///
/// @return string : le temps dans le bon format.
///
////////////////////////////////////////////////////////////////////////
string VisiteurCollision::afficherTemps()
{
	SYSTEMTIME st, lt;
	GetSystemTime(&st);
	GetLocalTime(&lt);
	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << lt.wHour << ':' << std::setw(2) << std::setfill('0') << lt.wMinute << ':' << lt.wSecond << ':' << std::setw(3) << lt.wMilliseconds;
	string s = ss.str();
	return s;
}
