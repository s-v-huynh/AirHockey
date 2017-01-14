///////////////////////////////////////////////////////////////////////////
/// @file NoeudMaillet.cpp
/// @author equipe06
/// @date 2016-09-07
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "NoeudMaillet.h"
#include "Utilitaire.h"
#include "FacadeModele.h"
#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

int NoeudMaillet::compteurGreen_ = 0;
int NoeudAbstrait::compteurMaillet_ = 0;
////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::NoeudRondelle(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMaillet::NoeudMaillet(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	NoeudAbstrait::compteurMaillet_++;
	couleurMaillet_[0] = 0;
	couleurMaillet_[1] = 0;
	couleurMaillet_[2] = 255;
	couleurSelection_[1] = 0;
	//rayonMaillet_ = 1.0;
	attribuerCouleur();
	assignerEstSelectionnable(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRondelle::~NoeudTable()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMaillet::~NoeudMaillet()
{
}

void NoeudMaillet::copierAttributs(NoeudMaillet & destination)
{
    destination.angleRotation_ = angleRotation_;
    destination.facteurEchelle_ = facteurEchelle_;
    destination.rayonMaillet_ = rayonMaillet_;
    destination.coefRebondissement = coefRebondissement;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRondelle::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @param[in] vueProjection : La matrice qui permet de 
///					transformer le mod�le � sa position voulue.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMaillet::afficherConcret(const glm::mat4& vueProjection, const bool& attribuerCouleur)const
{
	glPushName(id_);
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret(vueProjection, attribuerCouleur);

	// R�volution autour du centre.
	GLubyte couleurObjet[3];
	couleurObjet[0] = couleurMaillet_[0];
	couleurObjet[1] = couleurMaillet_[1];
	couleurObjet[2] = couleurMaillet_[2];
	GLubyte couleurSelection[3];
	couleurSelection[0] = couleurSelection_[0];
	couleurSelection[1] = couleurSelection_[1];
	couleurSelection[2] = couleurSelection_[2];

	auto modele = glm::rotate(transformationRelative_, 0.0f, glm::vec3(1.0, 0.0, .0));
	modele = glm::translate(modele, glm::vec3(0.0, 0.0, 0.0));

	modele = glm::translate(modele, centreRotation_);
	modele = glm::rotate(modele, angleRotation_, glm::vec3(0, 0, 1.0));
	modele = glm::translate(modele, centreRotation_);
	modele = glm::scale(modele, glm::vec3(rayonMaillet_, rayonMaillet_, rayonMaillet_));
	// Affichage du mod�le.
	if(!FacadeModele::obtenirInstance()->modeEdition())
	vbo_->dessiner(estSelectionne(), attribuerCouleur, couleurObjet, couleurSelection, vueProjection*modele);

	glPopName();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMaillet::animer(float temps)
{
	// Appel � la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araign�e oscille selon une p�riode de 4 secondes.
	/*angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	glm::vec3 position(0.0f);
	position[0] = 5.0f * static_cast<float>(cos(utilitaire::DEG_TO_RAD(angle_)));
	position[1] = 40.0f * static_cast<float>(sin(utilitaire::DEG_TO_RAD(angle_)));

	assignerPositionRelative(position);*/
}
void NoeudMaillet::redessiner()
{
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMaillet::attribuerCouleur()
///
/// Cette fonction attribut une couleur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMaillet::attribuerCouleur()
{
	if (NoeudAbstrait::compteurPortail_ < 180)
	{
		couleurMaillet_[0] = NoeudMaillet::compteurGreen_;
		couleurMaillet_[1] = 100 - NoeudAbstrait::compteurMaillet_ + 1;
		couleurMaillet_[2] = 0;
		//std::cout << "couleur attribu�e: " << (int)couleurPortail_[0] << ";" << (int)couleurPortail_[1] << ";" << (int)couleurPortail_[2] << std::endl;

	}
	else
	{
		NoeudAbstrait::compteurMaillet_ = 1;
		NoeudMaillet::compteurGreen_++;
		couleurMaillet_[0] = NoeudMaillet::compteurGreen_;
		couleurMaillet_[1] = 255;
		couleurMaillet_[2] = 0;
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudMaillet::verifierSelection(GLubyte couleurObjet[])
///
/// Cette fonction verifie si le noeud est selectionne.
///
/// @param[in] couleurObjet : Le code RGB de l'objet
///
/// @return Faux si le noeud n'est pas selectione et vice-versa.
///
////////////////////////////////////////////////////////////////////////
bool NoeudMaillet::verifierSelection(GLubyte couleurObjet[])
{
	bool estPointe = false;
	//cout << "couleur objet selection: " << (int)couleurSelection_[2] << endl;
	if (couleurObjet[0] == couleurSelection_[0] && couleurObjet[1] == couleurSelection_[1] && couleurObjet[2] == couleurSelection_[2])
	{
		estPointe = true;
	}
	else if (couleurObjet[0] == couleurMaillet_[0] && couleurObjet[1] == couleurMaillet_[1] && couleurObjet[2] == couleurMaillet_[2])
	{
		estPointe = true;
		if (couleurSelection_[1] == 0)
		{
			NoeudAbstrait::compteurSelection_++;
			attribuerCouleurSelection();
		}
	}
	return estPointe;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMaillet::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Accepte le visiteur.
///
/// @param[in] visiteur : le type visiteur
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudMaillet::accepterVisiteur(VisiteurAbstrait* visiteur) {
	visiteur->visiter(this);
}
//void NoeudMaillet::accepterVisiteur(VisiteurAbstrait* visiteur)
//{
//	visiteur->visiter(this);
//}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMaillet::modifierRayonMaillet(double rayonMaillet)
///
/// Modifie le rayon du maillet
///
/// @param[in] rayonMaillet : le rayon du maillet
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudMaillet::modifierRayonMaillet(double rayonMaillet)
{
	rayonMaillet_ = rayonMaillet;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudMaillet::obtenirRayonMaillet()
///
/// Obtenir le rayon du maillet
///
/// @return le rayon du maillet
///
////////////////////////////////////////////////////////////////////////
double NoeudMaillet::obtenirRayonMaillet()
{
	return rayonMaillet_;
}
void NoeudMaillet::assignerObjetRendu(modele::Modele3D const * modele, opengl::VBO const * liste)
{
	NoeudAbstrait::assignerObjetRendu(modele, liste);
	rayonMaillet_ = utilitaire::calculerSphereEnglobante(*modele_).rayon/2;
	redefinirSommets();
}
void NoeudMaillet::redefinirSommets()
{
	rayonMaillet_ *= facteurEchelle_;
	sommets_.erase(sommets_.begin(), sommets_.end());
	sommets_.push_back(glm::dvec3(rayonMaillet_ + obtenirPositionRelative().x, rayonMaillet_ + obtenirPositionRelative().y, obtenirPositionRelative().z));
	utilitaire::BoiteEnglobante modeleMaillet = utilitaire::calculerBoiteEnglobante(*modele_);
	//std::cout << modeleMaillet.coinMin.x << std::endl;
	//sommets_.push_back(glm::dvec3(modeleMaillet.coinMin.x, modeleMaillet.coinMax.y, modeleMaillet.coinMin.z));
	//sommets_.push_back(glm::dvec3(modeleMaillet.coinMax.x, modeleMaillet.coinMax.y, modeleMaillet.coinMin.z));
	//sommets_.push_back(glm::dvec3(modeleMaillet.coinMax.x, modeleMaillet.coinMin.y, modeleMaillet.coinMin.z));
	//sommets_.push_back(glm::dvec3(modeleMaillet.coinMin.x, modeleMaillet.coinMin.y, modeleMaillet.coinMin.z));

}
bool NoeudMaillet::estDansLaTable()
{
	if (estModifier_) {
		redefinirSommets();
	}
	std::vector<glm::dvec3> sommetsTable = this->obtenirParent()->obtenirSommets();
	return utilitaire::pointsDansPolygone2D(obtenirSommets(), sommetsTable);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
