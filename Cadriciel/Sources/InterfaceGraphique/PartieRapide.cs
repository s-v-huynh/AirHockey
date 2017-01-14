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
    public partial class PartieRapide : Form
    {
        public PartieRapide()
        {
            InitializeComponent();
            InitialiserAnimation();
        }

        /// Initialiser les animations
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        public void MettreAJour(double tempsInterAffichage)
        {
            if (!Program.tracerRectangle && Visible)
            {
                try
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                        FonctionsNatives.dessinerOpenGL();
                    });
                }
                catch (Exception)
                {
                }

            }
        }

        /// Pour afficher la barre de menu avec le bouton ESC
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Escape)
            {
                if (menuStrip1.Visible == false)
                {
                    menuStrip1.Visible = true;
                    label1.Visible = true;
                }
                else
                {
                    menuStrip1.Visible = false;
                    label1.Visible = false;
                }
            }

            return base.ProcessCmdKey(ref msg, keyData);
        }

        /// Aller dans le menu principal avec le menu
        private void menuPrincipalCtrlQToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (Form f in Application.OpenForms)
            {
                if (f.Name != "MenuPrincipal")
                {
                    f.Close();
                }
            }
        }

        /// Aller dans le menu princpal avec ctrl + Q
        private void PartieRapide_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.Q)
            {
                foreach (Form f in Application.OpenForms)
                {
                    if (f.Name != "MenuPrincipal")
                    {
                        f.Close();
                    }
                }

            }
        }

        /// Retourne dans le menu principal quand on appuie sur le x en haut a droite
        private void PartieRapide_FormClosing(object sender, FormClosingEventArgs e)
        {
            foreach (Form f in Application.OpenForms)
            {
                if (f.Name != "MenuPrincipal")
                {
                    f.Close();
                }
            }
        }
    }
}
