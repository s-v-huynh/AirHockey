//////////////////////////////////////////////////////////////////////////////
/// @file MenuPrincipal.cs
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
    public partial class MenuPrincipal : Form
    {
        public MenuPrincipal()
        {
            InitializeComponent();
            Program.edition = new ModeEdition();
            Program.arbre = new ArbreTournoi();
            Program.finPartiRapide = new FinPartiRapide();
            PartieRapide.BackColor = Color.FromArgb(76, 103, 139);
            Editeur.BackColor = Color.FromArgb(76, 103, 139);
            Tournoi.BackColor = Color.FromArgb(76, 103, 139);
            Configuration.BackColor = Color.FromArgb(76, 103, 139);
            Quitter.BackColor = Color.FromArgb(160, 41, 49);
            FonctionsNatives.initaliserSono();
        }

        private void PartieRapide_Click(object sender, EventArgs e)
        {
            //FonctionsNatives.jouerSonDeFond();
            FonctionsNatives.enModeEdition(false);
            //Console.WriteLine("PR");
            Program.estDansPartieRapide = true;
            Program.estDansModeEdition = false;
            Program.estDansTournoi = false;
            this.Hide();
            ConfigurationPartieRapide configurationPartieRapide = new ConfigurationPartieRapide();
            configurationPartieRapide.ShowDialog();
            //configurationPartieRapide = null;
            //this.Show();    
        }

        private void Tournoi_Click(object sender, EventArgs e)
        {
            FonctionsNatives.enModeEdition(false);
            //Console.WriteLine("Tour");
            Program.estDansPartieRapide = false;
            Program.estDansModeEdition = false;
            Program.estDansTournoi = true;
            this.Hide();
            ConfigurationTournoi configurationTournoi = new ConfigurationTournoi();
            configurationTournoi.ShowDialog();
            //configurationTournoi = null;
            //this.Show();
            
        }

        private void Configuration_Click(object sender, EventArgs e)
        {
            Configuration configuration = new Configuration();
            configuration.ShowDialog();
        }

        private void Editeur_Click(object sender, EventArgs e)
        {
            FonctionsNatives.enModeEdition(true);
            Program.estDansPartieRapide = false;
            Program.estDansModeEdition = true;
            Program.estDansTournoi = false;
            this.Hide();
            //Program.edition = new ModeEdition();
            Program.edition.Show();
            //Program.edition = null;
            //this.Show();

            //Console.WriteLine("ED");

        }

        private void Quitter_Click(object sender, EventArgs e)
        {
            FonctionsNatives.relacherMusique();
            Application.Exit();
        }

        private void PartieRapide_MouseEnter(object sender, EventArgs e)
        {
            PartieRapide.BackColor = Color.FromArgb(0, 68, 153);
            this.BackgroundImage = InterfaceGraphique.Properties.Resources.Menu_Principal_PartieRapide;
        }

        private void PartieRapide_MouseLeave(object sender, EventArgs e)
        {
            PartieRapide.BackColor = Color.FromArgb(76, 103, 139);
            this.BackgroundImage = InterfaceGraphique.Properties.Resources.Menu_Principal;
        }

        private void Tournoi_MouseEnter(object sender, EventArgs e)
        {
            Tournoi.BackColor = Color.FromArgb(0, 68, 153);
            this.BackgroundImage = InterfaceGraphique.Properties.Resources.Menu_Principal_tournoi;
        }

        private void Tournoi_MouseLeave(object sender, EventArgs e)
        {
            Tournoi.BackColor = Color.FromArgb(76, 103, 139);
            this.BackgroundImage = InterfaceGraphique.Properties.Resources.Menu_Principal;
        }

        private void Configuration_MouseEnter(object sender, EventArgs e)
        {
            Configuration.BackColor = Color.FromArgb(0, 68, 153);
            this.BackgroundImage = InterfaceGraphique.Properties.Resources.Menu_Principal_configuration;
        }

        private void Configuration_MouseLeave(object sender, EventArgs e)
        {
            Configuration.BackColor = Color.FromArgb(76, 103, 139);
            this.BackgroundImage = InterfaceGraphique.Properties.Resources.Menu_Principal;
        }

        private void Editeur_MouseEnter(object sender, EventArgs e)
        {
            Editeur.BackColor = Color.FromArgb(0, 68, 153);
            this.BackgroundImage = InterfaceGraphique.Properties.Resources.Menu_Principal_editeur;
        }

        private void Editeur_MouseLeave(object sender, EventArgs e)
        {
            Editeur.BackColor = Color.FromArgb(76, 103, 139);
            this.BackgroundImage = InterfaceGraphique.Properties.Resources.Menu_Principal;
        }

        private void Quitter_MouseEnter(object sender, EventArgs e)
        {
            Quitter.BackColor = Color.FromArgb(225, 0, 0);
        }

        private void Quitter_MouseLeave(object sender, EventArgs e)
        {
            Quitter.BackColor = Color.FromArgb(160, 41, 49);
        }
    }
}
