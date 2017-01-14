//////////////////////////////////////////////////////////////////////////////
/// @file ConfigurationPartieRapide.cs
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

//using System;
//using System.Collections.Generic;
//using System.ComponentModel;
//using System.Data;
//using System.Drawing;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using System.Windows.Forms;

//namespace InterfaceGraphique
//{
//    public partial class ConfigurationPartieRapide : Form
//    {
//        public ConfigurationPartieRapide()
//        {
//            InitializeComponent();
//        }

//        /// Choisir le joueur humain et ne pas pouvoir choisir un joueur virtuel
//        private void radioButton1_CheckedChanged(object sender, EventArgs e)
//        {
//            comboBox1.Visible = false;
//            Program.joueurVirtuel = false;
//        }

//        /// Choisir un joueur virtuel et ne pas pouvoir choisir un joueur humain
//        private void radioButton2_CheckedChanged(object sender, EventArgs e)
//        {
//            comboBox1.Visible = true;
//            Program.joueurVirtuel = true;
//        }

//        /// Pour retourner au menu principal
//        private void button2_Click(object sender, EventArgs e)
//        {
//            this.Close();
//            Program.menuPrincipal.Show();
//        }

//        /// Pour demarrer une partie
//        private void button1_Click(object sender, EventArgs e)
//        {
//            //this.Hide();
//            //PartieRapide partieRapide = new PartieRapide();
//            //partieRapide.ShowDialog();
//            //partieRapide = null;
//            //this.Show();

//            //this.Hide();
//            //Program.edition = new ModeEdition();
//            //Program.edition.lancerModeEdition();
//            //Program.edition = null;
//            //this.Show();
//            FonctionsNatives.initialiserPartie(Configuration.nbButs, Program.joueurVirtuel);

//            this.Close();
//            Program.edition.Show();
//        }
//    }
//}
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

    public partial class ConfigurationPartieRapide : Form
    {
        public ConfigurationPartieRapide()
        {
            InitializeComponent();
            panel1.BackColor = Color.FromArgb(202, 213, 217);
            button1.BackColor = Color.FromArgb(17, 102, 17);
            button2.BackColor = Color.FromArgb(175, 39, 35);
            Program.fichierXMLAChargerRapide = "../Exe/zones/default.xml";
            label4.Text = Program.fichierXMLAChargerRapide;
            Configuration.listeProfils.Clear();

            Profil defaut = new Profil("Défaut", 3, 3);
            Configuration.listeProfils.Add(defaut);
            FonctionsNatives.chargementProfils();
            for (int i = 0; i < FonctionsNatives.nombreProfils(); i++)
            {
                Profil tmpProfil = new Profil(System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.nomDuProfil(i)), FonctionsNatives.vitesseDuProfil(i), FonctionsNatives.passiviteDuProfil(i));
                Configuration.listeProfils.Add(tmpProfil);
               // Console.WriteLine("Profil " + i + ": " + listeProfils[i].nom + ", " + listeProfils[i].vitesse + ", " + listeProfils[i].passivite);

            }
            for (int i = 0; i < Configuration.listeProfils.Count; i++)
            {
                comboBox1.Items.Add(Configuration.listeProfils[i].nom);
            }
        }

        /// Choisir le joueur humain et ne pas pouvoir choisir un joueur virtuel
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            comboBox1.Visible = false;
            Program.joueurVirtuel = false;
            //FonctionsNatives.adversaireVirtuel(false);

        }

        /// Choisir un joueur virtuel et ne pas pouvoir choisir un joueur humain
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            comboBox1.Visible = true;
            Program.joueurVirtuel = true;
            //FonctionsNatives.adversaireVirtuel(true);

        }

        /// Pour retourner au menu principal
        private void button2_Click(object sender, EventArgs e)
        {
            Configuration.listeProfils.Clear();
            this.Close();
            Program.menuPrincipal.Show();
        }

        /// Pour demarrer une partie
        private void button1_Click(object sender, EventArgs e)
        {
            //this.Hide();
            //PartieRapide partieRapide = new PartieRapide();
            //partieRapide.ShowDialog();
            //partieRapide = null;
            //this.Show();
         
            if (!(radioButton1.Checked || radioButton2.Checked))
            {
                MessageBox.Show("Le type de joueur doit être choisi.");
            }
            else if (radioButton2.Checked && comboBox1.SelectedItem == null)
            {
                MessageBox.Show("Un profil doit être choisi pour le joueur virtuel.");
            }
            else
            {
                this.Close();
                //Program.edition = new ModeEdition();
                //Program.edition.lancerModeEdition();
                //Program.edition = null;
                Program.edition.Show();
                Program.menuPrincipal.Hide();
                //exectction fonction partie rapide
                FonctionsNatives.initialiserChargement(Program.fichierXMLAChargerRapide);
                FonctionsNatives.initialiserPartie(Program.nbBut, Program.joueurVirtuel);

                //FonctionsNatives.initialiserChargement(Program.fichierXMLAChargerRapide);
                //FonctionsNatives.lancerPartieRapide();\
               // FonctionsNatives.adversaireVirtuel(Program.joueurVirtuel);

                Program.tempsJeu.Reset();
                Program.tempsJeu.Start();
                Program.timerJeu.Interval = 500;
                Program.timerJeu.Start();
                Program.timerJeu.Tick += new EventHandler(timerJeuTick);
                // FonctionsNatives.adversaireVirtuel(Program.joueurVirtuel);
                FonctionsNatives.enModeTest(false);
                FonctionsNatives.jouerSonDeFond();
                
            }
        }

        private void timerJeuTick(object sender, EventArgs e)
        {
            string tempsJouer = Program.tempsJeu.Elapsed.Minutes.ToString("00") + ":" + Program.tempsJeu.Elapsed.Seconds.ToString("00");
            //Console.WriteLine(tempsJouer);
            FonctionsNatives.tempsJouer(tempsJouer);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            int selected = comboBox1.SelectedIndex;
            Program.profilSelectionne = Configuration.listeProfils[selected];
        }
        
        private void button3_Click(object sender, EventArgs e)
        {
            string nomFichier = "";
            OpenFileDialog openDialog = new OpenFileDialog();
            string currentPath = System.IO.Directory.GetCurrentDirectory();
            System.Text.StringBuilder builder = new System.Text.StringBuilder();
            string sousFichierZones = @"\zones";
            string fichierZones = currentPath + sousFichierZones;
            openDialog.InitialDirectory = fichierZones;
            
            openDialog.Filter = "XML Files| *.xml";
            DialogResult result = openDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                nomFichier = openDialog.FileName;
            }
            if (nomFichier != "")
            {
                Program.fichierXMLAChargerRapide = nomFichier;
                if (!(System.IO.Path.GetDirectoryName(nomFichier) == fichierZones))
                {
                    MessageBox.Show("Le fichier doit être dans le dossier zones.");
                }
            }
            label4.Text = System.IO.Path.GetFileName(Program.fichierXMLAChargerRapide);
        }

        private void ConfigurationPartieRapide_FormClosing(object sender, FormClosingEventArgs e)
        {
            Configuration.listeProfils.Clear();
            this.Close();
            Program.menuPrincipal.Show();
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
