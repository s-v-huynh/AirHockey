//////////////////////////////////////////////////////////////////////////////
/// @file ConfigurationTournoi.cs
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
    public partial class ConfigurationTournoi : Form
    {
        public static bool joueur1EstVirtuel = false;
        public static bool joueur2EstVirtuel = false;
        public static bool joueur3EstVirtuel = false;
        public static bool joueur4EstVirtuel = false;
        public static string joueur1 = "joueur1";
        public static string joueur2 = "joueur2";
        public static string joueur3 = "joueur3";
        public static string joueur4 = "joueur4";

        public ConfigurationTournoi()
        {
            InitializeComponent();
            panel1.BackColor = Color.FromArgb(202, 213, 217);
            button2.BackColor = Color.FromArgb(17, 102, 17);
            button3.BackColor = Color.FromArgb(175, 39, 35);
            Program.fichierXMLAChargerTournoi = "../Exe/zones/default.xml";
            label7.Text = Program.fichierXMLAChargerTournoi;
            Configuration.listeProfils.Clear();

            comboBox1.Visible = false;
            comboBox2.Visible = false;
            comboBox3.Visible = false;
            comboBox4.Visible = false;
            //FonctionsNatives.ajouterNouveauProfil("Défaut", 3, 3);
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
            for (int i = 0; i < Configuration.listeProfils.Count; i++)
            {
                comboBox2.Items.Add(Configuration.listeProfils[i].nom);
            }
            for (int i = 0; i < Configuration.listeProfils.Count; i++)
            {
                comboBox3.Items.Add(Configuration.listeProfils[i].nom);
            }
            for (int i = 0; i < Configuration.listeProfils.Count; i++)
            {
                comboBox4.Items.Add(Configuration.listeProfils[i].nom);
            }
            comboBox1.SelectedIndex = 0 ;
            comboBox2.SelectedIndex = 0;
            comboBox3.SelectedIndex = 0;
            comboBox4.SelectedIndex = 0;
            FonctionsNatives.chargementTournoi();
            textBox1.Text = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirNomJoueur1Tournoi());
            textBox2.Text = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirNomJoueur2Tournoi());
            textBox3.Text = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirNomJoueur3Tournoi());
            textBox4.Text = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirNomJoueur4Tournoi());

           if(FonctionsNatives.obtenirTypeJoueur1Tournoi())
            {
                radioButton2.Checked = true;
                radioButton1.Checked = false;
            }
            else
            {
                radioButton2.Checked = false;
                radioButton1.Checked = true;
            }
            if (FonctionsNatives.obtenirTypeJoueur2Tournoi())
            {
                radioButton3.Checked = true;
                radioButton4.Checked = false;
            }
            else
            {
                radioButton3.Checked = false;
                radioButton4.Checked = true;
            }
            if (FonctionsNatives.obtenirTypeJoueur3Tournoi())
            {
                radioButton5.Checked = true;
                radioButton6.Checked = false;
            }
            else
            {
                radioButton5.Checked = false;
                radioButton6.Checked = true;
            }
            if (FonctionsNatives.obtenirTypeJoueur4Tournoi())
            {
                radioButton7.Checked = true;
                radioButton8.Checked = false;
            }
            else
            {
                radioButton7.Checked = false;
                radioButton8.Checked = true;
            }
            comboBox1.SelectedIndex = FonctionsNatives.obtenirProfilJoueur1Tournoi();
            comboBox2.SelectedIndex = FonctionsNatives.obtenirProfilJoueur2Tournoi();
            comboBox3.SelectedIndex = FonctionsNatives.obtenirProfilJoueur3Tournoi();
            comboBox4.SelectedIndex = FonctionsNatives.obtenirProfilJoueur4Tournoi();

        }

        /// Choisir le joueur humain et ne pas pouvoir choisir un joueur virtuel
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            comboBox1.Visible = false;
            joueur1EstVirtuel = false;
        }

        /// Choisir un joueur virtuel et ne pas pouvoir choisir un joueur humain
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            comboBox1.Visible = true;
            joueur1EstVirtuel = true;
        }

        /// Choisir le joueur humain et ne pas pouvoir choisir un joueur virtuel
        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            comboBox2.Visible = false;
            joueur2EstVirtuel = false;
        }

        /// Choisir un joueur virtuel et ne pas pouvoir choisir un joueur humain
        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            comboBox2.Visible = true;
            joueur2EstVirtuel = true;
        }

        /// Choisir le joueur humain et ne pas pouvoir choisir un joueur virtuel
        private void radioButton6_CheckedChanged(object sender, EventArgs e)
        {
            comboBox3.Visible = false;
            joueur3EstVirtuel = false;
        }

        /// Choisir un joueur virtuel et ne pas pouvoir choisir un joueur humain
        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            comboBox3.Visible = true;
            joueur3EstVirtuel = true;
        }

        /// Choisir le joueur humain et ne pas pouvoir choisir un joueur virtuel
        private void radioButton8_CheckedChanged(object sender, EventArgs e)
        {
            comboBox4.Visible = false;
            joueur4EstVirtuel = false;
        }

        /// Choisir un joueur virtuel et ne pas pouvoir choisir un joueur humain
        private void radioButton7_CheckedChanged(object sender, EventArgs e)
        {
            comboBox4.Visible = true;
            joueur4EstVirtuel = true;
        }

        /// Pour retourner au menu principal
        private void button3_Click(object sender, EventArgs e)
        {
            FonctionsNatives.assignerJoueur1Tournoi(textBox1.Text, radioButton2.Checked, comboBox1.SelectedIndex);
            FonctionsNatives.assignerJoueur2Tournoi(textBox2.Text, radioButton3.Checked, comboBox2.SelectedIndex);
            FonctionsNatives.assignerJoueur3Tournoi(textBox3.Text, radioButton5.Checked, comboBox3.SelectedIndex);
            FonctionsNatives.assignerJoueur4Tournoi(textBox4.Text, radioButton7.Checked, comboBox4.SelectedIndex);
            FonctionsNatives.sauvegarderTournoi();
            this.Close();
            Program.menuPrincipal.Show();
        }

        /// Pour demarrer le tournoi
        private void button2_Click(object sender, EventArgs e)
        {
            if (joueur1EstVirtuel && joueur2EstVirtuel && joueur3EstVirtuel && joueur4EstVirtuel)
            {
                MessageBox.Show("Il faut au moins un joueur humain !");
            }
            else if(textBox1.Text == textBox2.Text || textBox1.Text == textBox3.Text || textBox1.Text == textBox4.Text ||
                textBox2.Text == textBox3.Text || textBox2.Text == textBox4.Text || textBox3.Text == textBox4.Text)
            {
                MessageBox.Show("Chaque joueur doit avoir un nom unique!");
            }
            else if(Program.fichierXMLAChargerTournoi=="")
            {
                MessageBox.Show("Aucune zone de jeu n'est chargée!");
            }
            else if (!((radioButton1.Checked || radioButton2.Checked)&& (radioButton3.Checked || radioButton4.Checked)&& 
                (radioButton5.Checked || radioButton6.Checked)&& (radioButton7.Checked || radioButton8.Checked)))
            {
                MessageBox.Show("Le type de joueur doit être choisi pour chaque joueur.");
            }
            else if (radioButton2.Checked && comboBox1.SelectedItem == null)
            {
                MessageBox.Show("Un profil doit être choisi pour le joueur virtuel 1.");
            }
            else if (radioButton3.Checked && comboBox2.SelectedItem == null)
            {
                MessageBox.Show("Un profil doit être choisi pour le joueur virtuel 2.");
            }
            else if (radioButton5.Checked && comboBox3.SelectedItem == null)
            {
                MessageBox.Show("Un profil doit être choisi pour le joueur virtuel 3.");
            }
            else if (radioButton7.Checked && comboBox4.SelectedItem == null)
            {
                MessageBox.Show("Un profil doit être choisi pour le joueur virtuel 4.");
            }
            else
            {
                
                ///Stockage de la liste des joueurs du tournoi
                Program.Joueur joueur1 = new Program.Joueur();
                Program.Joueur joueur2 = new Program.Joueur();
                Program.Joueur joueur3 = new Program.Joueur();
                Program.Joueur joueur4 = new Program.Joueur();
                joueur1.nom = textBox1.Text;
                joueur2.nom = textBox2.Text;
                joueur3.nom = textBox3.Text;
                joueur4.nom = textBox4.Text;
                if (radioButton1.Checked)
                {
                    joueur1.estVirtuel = false;
                }
                else if (radioButton2.Checked)
                {
                    int selected = comboBox1.SelectedIndex;
                    joueur1.estVirtuel = true;
                    joueur1.profil = Configuration.listeProfils[selected];
                }
                if (radioButton3.Checked)
                {
                    joueur2.estVirtuel = false;
                }
                else if (radioButton4.Checked)
                {
                    int selected = comboBox2.SelectedIndex;
                    joueur2.estVirtuel = true;
                    joueur2.profil = Configuration.listeProfils[selected];
                }
                if (radioButton5.Checked)
                {
                    joueur3.estVirtuel = false;
                }
                else if (radioButton6.Checked)
                {
                    int selected = comboBox4.SelectedIndex;
                    joueur3.estVirtuel = true;
                    joueur3.profil = Configuration.listeProfils[selected];
                }
                if (radioButton6.Checked)
                {
                    joueur4.estVirtuel = false;

                }
                else if (radioButton7.Checked)
                {
                    int selected = comboBox4.SelectedIndex;
                    joueur4.estVirtuel = true;
                    joueur4.profil = Configuration.listeProfils[selected];
                }
                Program.listeJoueursTournoi.Add(joueur1);
                Program.listeJoueursTournoi.Add(joueur2);
                Program.listeJoueursTournoi.Add(joueur3);
                Program.listeJoueursTournoi.Add(joueur4);
                //for (int i = 0; i < Program.listeJoueursTournoi.Count; i++)
                //{
                //    Console.WriteLine("Profil :" + Program.listeJoueursTournoi[i].nom + Program.listeJoueursTournoi[i].estVirtuel);
                //}

                this.Hide();
                //Program.edition = new ModeEdition();
                //Program.edition.lancerModeEdition();
                //Program.edition = null;
                Program.edition.Show();

                Program.tempsJeu.Reset();
                Program.tempsJeu.Start();
                Program.timerJeu.Interval = 500;
                Program.timerJeu.Start();
                Program.timerJeu.Tick += new EventHandler(timerJeuTick);

                FonctionsNatives.initialiserChargement(Program.fichierXMLAChargerTournoi);

                this.Close();
                Program.arbre.Show();
                Program.menuPrincipal.Hide();
                //FonctionsNatives.initialiserPartie(Configuration.nbButs, Program.joueurVirtuel);
                if (!joueur1EstVirtuel || !joueur2EstVirtuel|| !joueur3EstVirtuel|| !joueur4EstVirtuel)
                {

                    Program.joueurVirtuel = false;

                }
                FonctionsNatives.initialiserTournoi(Configuration.nbButs,joueur1EstVirtuel,joueur1.nom, joueur2EstVirtuel,joueur2.nom, joueur3EstVirtuel, joueur3.nom, joueur4EstVirtuel,joueur4.nom);
                Program.arbre.initialisationNomsJoueur(joueur1.nom, joueur2.nom, joueur3.nom, joueur4.nom);
                FonctionsNatives.nextPartie();
                FonctionsNatives.enModeTest(false);
                FonctionsNatives.jouerSonDeFond();


            }
        }

        private void timerJeuTick(object sender, EventArgs e)
        {
            string tempsJouer = Program.tempsJeu.Elapsed.Minutes.ToString("00") + ":" + Program.tempsJeu.Elapsed.Seconds.ToString("00");
            Console.WriteLine(tempsJouer);
            FonctionsNatives.tempsJouer(tempsJouer);
        }

        private void button1_Click(object sender, EventArgs e)
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
                Program.fichierXMLAChargerTournoi = nomFichier;
                if (!(System.IO.Path.GetDirectoryName(openDialog.FileName) == fichierZones))
                {
                    MessageBox.Show("Le fichier doit être dans le dossier zones.");
                }
            }
            label7.Text = System.IO.Path.GetFileName(Program.fichierXMLAChargerTournoi);
        }

        private void ConfigurationTournoi_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Close();
            Program.menuPrincipal.Show();
        }
        private void button2_MouseEnter(object sender, EventArgs e)
        {
            button2.BackColor = Color.FromArgb(30, 158, 30);
        }

        private void button2_MouseLeave(object sender, EventArgs e)
        {
            button2.BackColor = Color.FromArgb(17, 102, 17);
        }

        private void button3_MouseEnter(object sender, EventArgs e)
        {
            button3.BackColor = Color.FromArgb(215, 40, 25);
        }

        private void button3_MouseLeave(object sender, EventArgs e)
        {
            button3.BackColor = Color.FromArgb(160, 39, 35);
        }
    }
}
