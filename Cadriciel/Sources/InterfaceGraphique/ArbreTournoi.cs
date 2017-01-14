//////////////////////////////////////////////////////////////////////////////
/// @file ArbreTournoi.cs
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class ArbreTournoi : Form
    {
        public ArbreTournoi()
        {
            InitializeComponent();
            label1.Text = "Joueur 1";
            label2.Text = "Joueur 2";
            label5.Text = "Joueur 3";
            label6.Text = "Joueur 4";
            label3.Text = "";
            label7.Text = "";
            label4.Text = "";
        }

        public void miseAJourArbre(bool joueur1Passe, bool joueur3Passe, bool vainqueur1Passe, bool actualiser1, bool actualiser2, bool actualiser3)
        {
            if (actualiser1)
            {
                if (joueur1Passe)
                {
                    label3.Text = label1.Text;
                }
                else
                {
                    label3.Text = label2.Text;
                }
            }

            if (actualiser2)
            {
                if (joueur3Passe)
                {
                    label4.Text = label5.Text;
                }
                else
                {
                    label4.Text = label6.Text;
                }
            }
            if (actualiser3)
            {
                if (vainqueur1Passe)
                {
                    label7.Text = label3.Text;
                }
                else
                {
                    label7.Text = label4.Text;
                }
            }
        }

        public void initialisationNomsJoueur(string nom1, string nom2, string nom3, string nom4)
        {
            label1.Text = nom1;
            label2.Text = nom2;
            label5.Text = nom3;
            label6.Text = nom4;

        }
        private void label1_TextChanged(object sender, EventArgs e)
        {
            //label1.Text = "Hardy";
        }

        private void label2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label3_TextChanged(object sender, EventArgs e)
        {

        }

        private void label7_TextChanged(object sender, EventArgs e)
        {

        }

        private void label4_TextChanged(object sender, EventArgs e)
        {

        }

        private void label5_TextChanged(object sender, EventArgs e)
        {

        }

        private void label6_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
