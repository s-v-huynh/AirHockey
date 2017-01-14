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
    public partial class ModeTest : Form
    {
        public ModeTest()
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

        /// Aller dans le menu princpal avec ctrl + Q
        private void ModeTest_KeyDown(object sender, KeyEventArgs e)
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

        /// Retourner dans le mode edition
        private void vueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.activationVueOrbite();
        }

        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.activationVueOrtho();
        }
    }
}
