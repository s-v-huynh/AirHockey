#include "OpenGL_VBO.h"

///////////////////////////////////////////////////////////////////////////////
/// @file ModeleStorage_VBO.cpp
/// @author Martin Paradis
/// @date 2015-08-28
/// @version 1.0
///
/// @addtogroup modele Modele
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Modele3D.h"
#include "AideGL.h"
#include "Utilitaire.h"

/// Position de l'attribut de location dans le nuanceur de sommet
#define VERTEX_LOCATION 0
#define TEXCOORD_LOCATION 1

namespace opengl{

	Programme VBO::programme_;
	Nuanceur VBO::nuanceurFragment_;
	Nuanceur VBO::nuanceurSommet_;

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VBO::VBO(modele::Modele3D const* modele)
	///
	/// Assigne le mod�le 3D.
	///
	/// @param[in] modele : le modele 3D � dessiner.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	VBO::VBO(modele::Modele3D const* modele)
		: modele_{ modele }
	{}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VBO::~VBO()
	///
	/// Destructeur, rel�che le VBO.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	VBO::~VBO()
	{
		liberer();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::charger()
	///
	/// Charge les donn�es du mod�les 3D sur la m�moire de la carte graphique
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::charger()
	{
		if(!programme_.estInitialise())
		{
			// Initialisation des nuanceurs
			nuanceurFragment_.initialiser(Nuanceur::Type::NUANCEUR_FRAGMENT, "nuanceurs/fragment.glsl");
			nuanceurSommet_.initialiser(Nuanceur::Type::NUANCEUR_VERTEX, "nuanceurs/sommet.glsl");
			programme_.initialiser();
			programme_.attacherNuanceur(nuanceurFragment_);
			programme_.attacherNuanceur(nuanceurSommet_);
		}
		creerVBO(modele_->obtenirNoeudRacine());
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::creerVBO(modele::Noeud const& noeud)
	///
	/// Cr�ation des VBO selon les donn�es propres � chaque Mesh. L'ordre 
	/// des identifiants OpenGL se calque sur le mod�le 3D, en prenant pour
	/// acquis que la hi�rarchie interne des noeuds internes n'est pas 
	/// modifi�e.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::creerVBO(modele::Noeud const& noeud)
	{
		for (auto const& mesh : noeud.obtenirMeshes())
		{
			enregistrerTampon(mesh.obtenirSommets());
			if (mesh.possedeNormales())
				enregistrerTampon(mesh.obtenirNormales());
			if (mesh.possedeTexCoords())
				enregistrerTampon(mesh.obtenirTexCoords());
			if (mesh.possedeFaces())
				enregistrerTampon(mesh.obtenirFaces());
		}
		/// Cr�ation r�cursive.
		for (auto const& n : noeud.obtenirEnfants())
		{
			creerVBO(n);
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessiner() const
	///
	/// Appelle le dessin du mod�le � partir des VBO.  Utilise le mod�le 3D
	/// pour obtenir la mat�riau propre � chaque Mesh.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessiner(bool estSelectionne, bool attribCouleur, GLubyte couleurObjet[], GLubyte couleurSelection[], const glm::mat4& vueProjection) const
	{
		unsigned int bufferIndex = 0;
		dessiner(modele_->obtenirNoeudRacine(), bufferIndex, estSelectionne, attribCouleur, couleurObjet, couleurSelection, vueProjection);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex) const
	///
	/// Dessin r�cursif du mod�le 3D.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::dessiner(modele::Noeud const& noeud, unsigned int& bufferIndex, bool estSelectionne, bool attribCouleur, GLubyte couleurObjet[], GLubyte couleurSelection[], const glm::mat4& vueProjection) const
	{
		// Matrice de transformation
		glm::mat4x4 const& m{ vueProjection * noeud.obtenirTransformation() };

		Programme::Start(programme_);
		programme_.assignerUniforme("modelViewProjection", m);
		/// Empiler la transformation courante
		glPushMatrix();
		glMultMatrixf(glm::value_ptr(m));
		//glLoadIdentity();

		for (auto const& mesh : noeud.obtenirMeshes())
		{
			// Appliquer le mat�riau pour le mesh courant
			appliquerMateriau(mesh.obtenirMateriau());
			//std::cout << "j'y suis" << std::endl;

			bool possedeNormales{ mesh.possedeNormales() };
			bool possedeCouleurs{ mesh.possedeCouleurs() };
			bool possedeTexCoords{ mesh.possedeTexCoords() };
			bool possedeSommets{ mesh.possedeSommets() };
			bool possedeFaces{ mesh.possedeFaces() };

			//std::cout <<"attribue" <<attribCouleur << std::endl;
			//std::cout << "selection" <<estSelectionne << std::endl;

			if (estSelectionne)
			{
				glVertexAttrib3f(3, couleurSelection[0], couleurSelection[1], couleurSelection[2]);		// Couleur de l'objet s�lectionn� (vert)
			//std::cout << "j'y suis"<< (int)couleurSelection[0]<< (int)couleurSelection[1]<< (int)couleurSelection[2] << std::endl;

			}

			else if (attribCouleur)
			{
				glVertexAttrib3f(3, couleurObjet[0] / 255.0, couleurObjet[1] / 255.0, couleurObjet[2] / 255.0);
				//std::cout << "j'y suis"<< (int)couleurObjet[0]<< (int)couleurObjet[1]<< (int)couleurObjet[2] << std::endl;

			}
			else
			{
				possedeCouleurs ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL);
				possedeNormales ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
			}

			if (possedeSommets)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, 0, nullptr);
			}
			if (possedeNormales)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, 0, nullptr);
			}
			if (possedeTexCoords)
			{
				glBindBuffer(GL_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
			}
			if (possedeFaces)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handles_[bufferIndex]); ++bufferIndex;
				glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(3 * mesh.obtenirFaces().size()), GL_UNSIGNED_INT, nullptr);
			}



			/// Pour une raison ou une autre, il faut la d�sactiver apr�s le dessin 
			/// si le mod�le poss�de des couleurs de vertex.
			if (possedeCouleurs)
				glDisable(GL_COLOR_MATERIAL);
			if (possedeNormales)
				glDisable(GL_LIGHTING);

			glMatrixMode(GL_TEXTURE);
			//glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}



		Programme::Stop(programme_);
		/// Dessin r�cursif.
		for (auto const& n : noeud.obtenirEnfants())
		{
			dessiner(n, bufferIndex, estSelectionne, attribCouleur, couleurObjet, couleurSelection, m);
		}

		/// Pop de la transformation du noeud courant
		glPopMatrix();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::liberer()
	///
	/// Rel�che la m�moire sur la carte graphique.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::liberer()
	{
		for (auto const& handle : handles_)
		{
			glDeleteBuffers(static_cast<GLsizei>(handles_.size()), handles_.data());
		}
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VBO::appliquerMateriau(modele::Materiau const& materiau) const
	///
	/// Assigne un mat�riau OpenGL selon la m�thode d�pr�ci�e d'illumination
	/// d'OpenGL
	///
	/// @param[in] materiau : le materiau � assigner
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VBO::appliquerMateriau(modele::Materiau const& materiau) const
	{
		/// V�rifier si texture existe
		if (modele_->possedeTexture(materiau.nomTexture_)) {
			// Activer le texturage OpenGL et lier la texture appropri�e
			glEnable(GL_TEXTURE_2D);
			glScalef(1.0, -1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, modele_->obtenirTextureHandle(materiau.nomTexture_));
		}
		else {
			// D�sactiver le texturage OpenGL puisque cet objet n'a aucune texture
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

		/// Assigner le mat�riau
		/// � Faire : Envoyez les valeurs du mat�riau aux nuanceurs
		/*materiau.diffuse_
		materiau.speculaire_
		materiau.ambiant_
		materiau.emission_
		Shininess = materiau.shininess_ * materiau.shininessStrength_*/

		glPolygonMode(
			GL_FRONT_AND_BACK,
			materiau.filDeFer_ ? GL_LINE : GL_FILL);

		materiau.afficherDeuxCotes_ ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

	}
}