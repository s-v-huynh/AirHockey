//////////////////////////////////////////////////////////////////////////////
/// @file FinPartiRapide.cs
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
    public partial class FinPartiRapide : Form
    {
        public FinPartiRapide()
        {
            InitializeComponent();
            this.BackColor = Color.FromArgb(202, 213, 217);
            button1.BackColor = Color.FromArgb(17, 102, 17);
            button2.BackColor = Color.FromArgb(175, 39, 35);
        }
        public void nomVainqueur(bool vainqueur)
        {
            if (vainqueur)
            {
                label3.Text = "Joueur 1";
                label5.Text = "Joueur 2";
            }
            else
            {
                label3.Text = "Joueur 2";
                label5.Text = "Joueur 1";
            }
        }

        public void scoreFinal(int perdant)
        {
            label6.Text = Configuration.nbButs.ToString();
            label7.Text = perdant.ToString();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
            Program.menuPrincipal.Show();
            FonctionsNatives.mettreEnPause();
            Program.edition.Hide();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
            Program.menuPrincipal.Hide();
            Program.edition.Show();
            FonctionsNatives.reinitialiserPartie();
            FonctionsNatives.jouerSonDeFond();
            Program.tempsJeu.Reset();
            
        }

        private void FinPartiRapide_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Close();
            Program.menuPrincipal.Show();
            Program.edition.Hide();
        }
        private void button1_MouseEnter(object sender, EventArgs e)
        {
            button1.BackColor = Color.FromArgb(30, 158, 30);
        }

        private void button1_MouseLeave(object sender, EventArgs e)
        {
            button1.BackColor = Color.FromArgb(17, 102, 17);
        }

        private void button2_MouseEnter(object sender, EventArgs e)
        {
            button2.BackColor = Color.FromArgb(215, 40, 25);
        }

        private void button2_MouseLeave(object sender, EventArgs e)
        {
            button2.BackColor = Color.FromArgb(160, 39, 35);
        }
    }
}
