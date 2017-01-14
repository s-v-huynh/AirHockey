using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Xml;

namespace InterfaceGraphique
{
    class EtatEditionRondelle : EtatEdition
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterClic(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithmes lors d'un clic d'une
        /// touche quelconque.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @param[in] k : Represente la touche appuyer.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpretationClic(int x, int y, Keys k)
        {
            if (curseurValide_)
            {
                FonctionsNatives.ajouterNoeud(NOM_RONDELLE, x, y);
                /*Program.edition.marquerModificationDansLaScene();*/
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool verifierCurseur(int x, int y)
        ///
        /// Methode permettant la verification de la position du curseur pour
        /// l'edition du poteau
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Vrai lorsque le curseur est dans la bonne position pour editer
        /// un poteau, faux autrement.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool verifierClic(int x, int y)
        {
            curseurValide_ = FonctionsNatives.verifierClicRondelle(x, y);
            return curseurValide_;
        }
    }
}
