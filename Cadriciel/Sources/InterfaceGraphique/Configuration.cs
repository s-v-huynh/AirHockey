//////////////////////////////////////////////////////////////////////////////
/// @file Configuration.cs
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
    public struct Profil
    {
        public string nom;
        public int vitesse;
        public int passivite;
        public Profil(string cNom, int cVitesse, int cPassivite)
        {
            nom = cNom;
            vitesse = cVitesse;
            passivite = cPassivite;
        }
    }

    public partial class Configuration : Form
    {
        public static bool changerToucheHaut = false;
        public static bool changerToucheBas = false;
        public static bool changerToucheGauche = false;
        public static bool changerToucheDroite = false;
        public static List<Profil> listeProfils = new List<Profil>();
          
        //Profil[];

        //public static bool peutAfficherDebogage = false;
        //public static bool peutAfficherCollision = false;
        //public static bool peutAfficherVitesseRondelle = false;
        //public static bool peutAfficherEclairage = false;
        //public static bool peutAfficherAttractionPortail = false;

        //public static int nbButs = 2;

        //public static string haut = "W";
        //public static string bas = "S";
        //public static string gauche = "A";
        //public static string droite = "D";

        public static bool peutAfficherDebogage;
        public static bool peutAfficherCollision ;
        public static bool peutAfficherVitesseRondelle ;
        public static bool peutAfficherEclairage;
        public static bool peutAfficherAttractionPortail;

        public static int nbButs;

        public static string haut;
        public static string bas;
        public static string gauche ;
        public static string droite ;


        public static bool estVirtuel;


        public Configuration()
        {
            InitializeComponent();
            panel1.BackColor = Color.FromArgb(202, 213, 217);
            groupBox1.BackColor = Color.FromArgb(155, 176, 184);
            groupBox2.BackColor = Color.FromArgb(155, 176, 184);
            groupBox3.BackColor = Color.FromArgb(155, 176, 184);
            groupBox4.BackColor = Color.FromArgb(155, 176, 184);
            tabControl1.BackColor = Color.FromArgb(155, 176, 184);
            listeProfils.Clear();

            haut = "";
            bas = "";
            gauche = "";
            droite = "";

            // Ajouter les donnees dans le combo box de nombre de buts et choisit la valeur par defaut
            comboBox2.Items.Add(1);
            comboBox2.Items.Add(2);
            comboBox2.Items.Add(3);
            comboBox2.Items.Add(4);
            comboBox2.Items.Add(5);
            comboBox2.SelectedIndex = 1;

            // Ajouter les donnees dans le combo box de joueur dans le mode test et choisit la valeur par defaut
            comboBox1.Items.Add("Humain");
            comboBox1.Items.Add("Virtuel");
            comboBox1.SelectedIndex = 1;

            //// Ajouter les donnees dans le combo box de la collision et choisit la valeur par defaut
            //comboBox3.Items.Add("Oui");
            //comboBox3.Items.Add("Non");
            //comboBox3.SelectedIndex = 0;

            //// Ajouter les donnees dans le combo box de la vitesse et choisit la valeur par defaut
            //comboBox4.Items.Add("Oui");
            //comboBox4.Items.Add("Non");
            //comboBox4.SelectedIndex = 0;

            //// Ajouter les donnees dans le combo box de l'eclairage et choisit la valeur par defaut
            //comboBox5.Items.Add("Oui");
            //comboBox5.Items.Add("Non");
            //comboBox5.SelectedIndex = 0;

            //// Ajouter les donnees dans le combo box de l'identification des portails et choisit la valeur par defaut
            //comboBox6.Items.Add("Oui");
            //comboBox6.Items.Add("Non");
            //comboBox6.SelectedIndex = 0;


            // Le profil par defaut
            TabPage profilDefaut = new TabPage("Défaut");
            profilDefaut.Name = "Défaut";

            Label passiveLabel = new Label();
            Label vitesseLabel = new Label();
            TextBox passiveDefaut = new TextBox();
            TextBox vitesseDefaut = new TextBox();

            passiveLabel.Text = "Probabilité d’agir passivement";
            passiveLabel.AutoSize = true;
            vitesseLabel.Text = "Vitesse";
            passiveDefaut.Text = "3";
            vitesseDefaut.Text = "3";

            //Profil defaut = new Profil(profilDefaut.Name, 3, 3);
            FonctionsNatives.ajouterNouveauProfil(profilDefaut.Name, 3, 3);
            

            //Ajout du profil defaut au c++
            //int iPassiveDefaut = 0;
            //int iVitesseDefaut = 0;
            //if(Int32.TryParse(vitesseDefaut.Text, out iVitesseDefaut))
            //{
            //    if (Int32.TryParse(passiveDefaut.Text, out iPassiveDefaut))
            //        FonctionsNatives.ajouterNouveauProfil(profilDefaut.Name, iVitesseDefaut, iPassiveDefaut);
            //}

            passiveDefaut.Location = new System.Drawing.Point(220, 50);
            passiveLabel.Location = new System.Drawing.Point(20, 50);
            vitesseDefaut.Location = new System.Drawing.Point(220, 120);
            vitesseLabel.Location = new System.Drawing.Point(20, 120);

            profilDefaut.Controls.Add(passiveLabel);
            profilDefaut.Controls.Add(passiveDefaut);

            profilDefaut.Controls.Add(vitesseLabel);
            profilDefaut.Controls.Add(vitesseDefaut);

            tabControl1.TabPages.Add(profilDefaut);

            // Ne permet pas de modifier le profil par defaut
            ((Control)tabControl1.TabPages[0]).Enabled = false;

            //Chargement du menu avec la lecture du fichier de sauvegarde et des profils
            FonctionsNatives.chargerConfigurationOptions();
            FonctionsNatives.chargementProfils();
            peutAfficherDebogage = FonctionsNatives.obtenirPeutAfficherDebogage();
            peutAfficherCollision = FonctionsNatives.obtenirPeutAfficherCollision();
            peutAfficherVitesseRondelle = FonctionsNatives.obtenirPeutAfficherVitesse();
            peutAfficherEclairage = FonctionsNatives.obtenirPeutAfficherEclairage();
            peutAfficherAttractionPortail = FonctionsNatives.obtenirPeutAfficherAttractionPortail();

            nbButs = FonctionsNatives.obtenirNbButs();



            /// Conversion char* en string ANSI
            haut = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirHaut());
            bas = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirBas());
            gauche = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirGauche());
            droite = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirDroite());

            estVirtuel = FonctionsNatives.obtenirEstVirtuel();

            /// Ajout des profils de C++ a C#
            //int p = 0;
            //string test = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.nomDuProfil(p));
     
            //Console.WriteLine(test);
            //Console.WriteLine( FonctionsNatives.vitesseDuProfil(0));
            //Console.WriteLine( FonctionsNatives.passiviteDuProfil(0));
            for (int i = 0; i < FonctionsNatives.nombreProfils(); i++)
            {
                Profil tmpProfil = new Profil(System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.nomDuProfil(i)), FonctionsNatives.vitesseDuProfil(i), FonctionsNatives.passiviteDuProfil(i));
                //string t = "avc";
                //int p = 1;
                //int j = 1;
                //Profil tmpProfil = new Profil(t, p, j);
                listeProfils.Add(tmpProfil);
                //Console.WriteLine("Profil " + i + ": " + listeProfils[i].nom + ", "+listeProfils[i].vitesse +", "+listeProfils[i].passivite );

            }
            //Console.WriteLine(listeProfils.Count + "  vs. " + FonctionsNatives.nombreProfils());
            /// Affichage des options qui ont ete sauvegardees
            if (peutAfficherDebogage == true)
            {
                checkBox1.Checked = true;
                groupBox4.Enabled = true;
                if (peutAfficherCollision == true)
                    checkBox2.Checked= true;
                else
                    checkBox2.Checked = false;
                if (peutAfficherVitesseRondelle == true)
                    checkBox3.Checked = true;
                else
                    checkBox3.Checked = false;
                if (peutAfficherEclairage == true)
                    checkBox4.Checked = true;
                else
                    checkBox4.Checked = false;
                if (peutAfficherAttractionPortail == true)
                    checkBox5.Checked = true;
                else
                    checkBox5.Checked = true;
            }


            else
            {
                checkBox1.Checked = false;
                groupBox4.Enabled = false;
                checkBox2.Checked = false;
                checkBox2.Checked = true;
                checkBox2.Checked = true;
                checkBox2.Checked = true;
            }
            
            switch(nbButs)
            {
                case 1:
                    comboBox2.SelectedIndex = 0;
                    break;
                case 2:
                    comboBox2.SelectedIndex = 1;
                    break;
                case 3:
                    comboBox2.SelectedIndex = 2;
                    break;
                case 4:
                    comboBox2.SelectedIndex = 3;
                    break;
                case 5: comboBox2.SelectedIndex = 4;
                    break;
                default:
                    comboBox2.SelectedIndex = 1;
                    break;
            }
            button5.Text = haut;
            button6.Text = bas;
            button7.Text = gauche;
            button8.Text = droite;
            if(estVirtuel)
            {
                comboBox1.SelectedIndex = 1;
            }
            else
            {
                comboBox1.SelectedIndex = 0;
            }
            for (int i = 0; i < listeProfils.Count; i++)
            {
                
                    TabPage myTabPage = new TabPage(listeProfils[i].nom);
                    Label newPassiveLabel = new Label();
                    Label newVitesseLabel = new Label();
                    TextBox passive = new TextBox();
                    TextBox vitesse = new TextBox();

                    newPassiveLabel = new System.Windows.Forms.Label();
                    newPassiveLabel.Text = "Probabilité d’agir passivement";
                    newPassiveLabel.AutoSize = true;
                    newPassiveLabel.Location = new System.Drawing.Point(20, 50);

                    newVitesseLabel = new System.Windows.Forms.Label();
                    newVitesseLabel.Text = "Vitesse";
                    newVitesseLabel.Location = new System.Drawing.Point(20, 120);

                    passive = new System.Windows.Forms.TextBox();
                    passive.Text = listeProfils[i].vitesse.ToString();
                    passive.Location = new System.Drawing.Point(220, 50);

                    vitesse = new System.Windows.Forms.TextBox();
                    vitesse.Text = listeProfils[i].passivite.ToString();
                    vitesse.Location = new System.Drawing.Point(220, 120);

                    myTabPage.Controls.Add(newPassiveLabel);
                    myTabPage.Controls.Add(passive);
                    myTabPage.Controls.Add(newVitesseLabel);
                    myTabPage.Controls.Add(vitesse);

                    myTabPage.Name = listeProfils[i].nom;
                    tabControl1.TabPages.Add(myTabPage);
                
                //passiveLabel.Text = "Probabilité d’agir passivement";
                //passiveLabel.AutoSize = true;
                //passiveLabel.Location = new System.Drawing.Point(20, 50);

                //vitesseLabel.Text = "Vitesse";
                //vitesseLabel.Location = new System.Drawing.Point(20, 120);

                //passive = new System.Windows.Forms.TextBox();
                //passive.Text = "1";
                //passive.Location = new System.Drawing.Point(220, 50);

                //vitesse = new System.Windows.Forms.TextBox();
                //vitesse.Text = "1";
                //vitesse.Location = new System.Drawing.Point(220, 120);

                //myTabPage.Controls.Add(passiveLabel);
                //myTabPage.Controls.Add(passive);
                //myTabPage.Controls.Add(vitesseLabel);
                //myTabPage.Controls.Add(vitesse);

                //myTabPage.Name = profil;
                //tabControl1.TabPages.Add(myTabPage);


            }

        }

        /// Pour activer/desactiver le boite d'affichage de deboguage
        private void checkBox1_CheckedChanged_1(object sender, EventArgs e)
        {
            if (checkBox1.Checked == false)
            {
                groupBox4.Enabled = false;
                checkBox2.Checked = false;
                checkBox3.Checked = false;
                checkBox4.Checked = false;
                checkBox5.Checked = false;
            }
            else
            {
                groupBox4.Enabled = true;
                checkBox2.Checked = true;
                checkBox3.Checked = true;
                checkBox4.Checked = true;
                checkBox5.Checked = true;
            }
        }

        /// Pour ajouter la boite de creation de profile
        private void button2_Click_1(object sender, EventArgs e)
        {
            groupBox5.Visible = true;
        }

        /// Ajouter les profils dans le tableau du bas avec le nom voulu et verifie les doublons
        private void button10_Click_1(object sender, EventArgs e)
        {
            string profil = textBox1.Text;
            TabPage myTabPage = new TabPage(profil);
            
            bool found = false;
            foreach (TabPage tab in tabControl1.TabPages)
            {
                if (profil.Equals(tab.Name))
                {
                    tabControl1.SelectedTab = tab;
                    found = true;
                }
            }
            if (!found && profil != "")
            {
                Label passiveLabel = new Label();
                Label vitesseLabel = new Label();
                TextBox passive = new TextBox();
                TextBox vitesse = new TextBox();


                passiveLabel.Text = "Probabilité d’agir passivement";
                passiveLabel.AutoSize = true;
                passiveLabel.Location = new System.Drawing.Point(20, 50);

                vitesseLabel.Text = "Vitesse";
                vitesseLabel.Location = new System.Drawing.Point(20, 120);

                passive = new System.Windows.Forms.TextBox();
                passive.Text = "1";
                passive.Location = new System.Drawing.Point(220, 50);

                vitesse = new System.Windows.Forms.TextBox();
                vitesse.Text = "1";
                vitesse.Location = new System.Drawing.Point(220, 120);

                myTabPage.Controls.Add(passiveLabel);
                myTabPage.Controls.Add(passive);
                myTabPage.Controls.Add(vitesseLabel);
                myTabPage.Controls.Add(vitesse);
                
                myTabPage.Name = profil;
                tabControl1.TabPages.Add(myTabPage);
  

            }
            else if (profil == "")
            {
                MessageBox.Show("Il faut un nom au profil !");
            }
            else
                MessageBox.Show("Le profil existe déjà !");

        }

        /// Pour cacher la boite de creation de profile
        private void button11_Click_1(object sender, EventArgs e)
        {
            textBox1.Text = "";
            groupBox5.Visible = false;
        }

        /// Supprimer un profil
        private void button4_Click(object sender, EventArgs e)
        {
            if (tabControl1.SelectedIndex != 0)
            {
                tabControl1.TabPages.Remove(tabControl1.SelectedTab);
            }
        }

        /// Pour modifier la touche du haut
        private void button5_Click(object sender, EventArgs e)
        {
            changerToucheHaut = true;
        }

        /// Pour modifier la touche du bas
        private void button6_Click(object sender, EventArgs e)
        {
            changerToucheBas = true;
        }

        /// Pour modifier la touche du gauche
        private void button7_Click(object sender, EventArgs e)
        {
            changerToucheGauche = true;
        }

        /// Pour modifier la touche du droite
        private void button8_Click(object sender, EventArgs e)
        {
            changerToucheDroite = true;
        }

        /// Pour mettre les touches par defaut
        private void button9_Click(object sender, EventArgs e)
        {
            button5.Text = "W";
            button6.Text = "S";
            button7.Text = "A";
            button8.Text = "D";
        }

        /// Pour modifier les touches selon le bouton de l'usager
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if(changerToucheHaut)
            {
                changerToucheBas = false;
                changerToucheGauche = false;
                changerToucheDroite = false;
                if (button6.Text != keyData.ToString() && button7.Text != keyData.ToString() && button8.Text != keyData.ToString())
                    button5.Text = keyData.ToString();
                else
                    MessageBox.Show(keyData.ToString() + " est déjà utilisé !");
                changerToucheHaut = false;
            }

            if (changerToucheBas)
            {
                changerToucheHaut = false;
                changerToucheGauche = false;
                changerToucheDroite = false;
                if (button5.Text != keyData.ToString() && button7.Text != keyData.ToString() && button8.Text != keyData.ToString())
                    button6.Text = keyData.ToString();
                else
                    MessageBox.Show(keyData.ToString() + " est déjà utilisé !");
                changerToucheBas = false;
            }

            if (changerToucheGauche)
            {
                changerToucheBas = false;
                changerToucheHaut = false;
                changerToucheDroite = false;
                if (button5.Text != keyData.ToString() && button6.Text != keyData.ToString() && button8.Text != keyData.ToString())
                    button7.Text = keyData.ToString();
                else
                    MessageBox.Show(keyData.ToString() + " est déjà utilisé !");
                changerToucheGauche = false;
            }

            if (changerToucheDroite)
            {
                changerToucheBas = false;
                changerToucheHaut = false;
                changerToucheGauche = false;
                if (button5.Text != keyData.ToString() && button6.Text != keyData.ToString() && button7.Text != keyData.ToString())
                    button8.Text = keyData.ToString();
                else
                    MessageBox.Show(keyData.ToString() + " est déjà utilisé !");
                changerToucheDroite = false;
            }

            return base.ProcessCmdKey(ref msg, keyData);
        }

        /// Pour le enable/disable le bouton supprimer
        private void tabControl1_Selected(object sender, TabControlEventArgs e)
        {
            if (tabControl1.SelectedIndex == 0)
            {
                button4.Enabled = false;
            }
            else
            {
                button4.Enabled = true;
            }
        }

        /// Pour la sauvegarde
        private void Configuration_FormClosing(object sender, FormClosingEventArgs e)
        {
            //Console.WriteLine("Haut " + button5.Text);

            //Console.WriteLine("Bas " + button6.Text);

            //Console.WriteLine("Gauche " + button7.Text);

            //Console.WriteLine("Droite " + button8.Text);

            //Console.WriteLine("Nombre de but: " + comboBox2.SelectedItem.ToString());
            
            //Console.WriteLine("Joueur: " + comboBox1.SelectedItem.ToString());

            //Console.WriteLine("Collision: " + comboBox3.SelectedItem.ToString());

            //Console.WriteLine("Vitesse: " + comboBox4.SelectedItem.ToString());

            //Console.WriteLine("Eclairage: " + comboBox5.SelectedItem.ToString());

            //Console.WriteLine("Portail: " + comboBox6.SelectedItem.ToString());

            miseAJourSauvegardeInterface();

            FonctionsNatives.miseAJourSauvegardeConfiguration(peutAfficherDebogage, peutAfficherCollision, peutAfficherVitesseRondelle, peutAfficherEclairage, peutAfficherAttractionPortail,
                nbButs, haut, bas, gauche, droite, estVirtuel);

            FonctionsNatives.sauvegarderConfigurationOptions(button5.Text, button6.Text, button7.Text, button8.Text);


            ajouterTabProfils();

            //for (int i = 0; i < listeProfils.Count(); i++)
            //{
            //    Console.WriteLine(listeProfils[i].nom + " :" + listeProfils[i].vitesse + " " + listeProfils[i].passivite + "C#");
            //}

            

            //Console.WriteLine("Nombre de but: " + comboBox2.SelectedItem.ToString() + "\n" +
            //        "Index: " + comboBox2.SelectedIndex.ToString());

            //Console.WriteLine("Joueur: " + comboBox1.SelectedItem.ToString() + "\n" +
            //        "Index: " + comboBox1.SelectedIndex.ToString());

            //Console.WriteLine("Collision: " + comboBox3.SelectedItem.ToString() + "\n" +
            //        "Index: " + comboBox3.SelectedIndex.ToString());

            //Console.WriteLine("Vitesse: " + comboBox4.SelectedItem.ToString() + "\n" +
            //        "Index: " + comboBox4.SelectedIndex.ToString());

            //Console.WriteLine("Eclairage: " + comboBox5.SelectedItem.ToString() + "\n" +
            //        "Index: " + comboBox5.SelectedIndex.ToString());

            //Console.WriteLine("Portail: " + comboBox6.SelectedItem.ToString() + "\n" +
            //        "Index: " + comboBox6.SelectedIndex.ToString());

            //Console.WriteLine("Profil defaut: " + "\n" + "Passive: " + passiveDefaut.Text
            //    + "\n" + "Vitesse: " + vitesseDefaut.Text);

            //foreach (TabPage tab in tabControl1.TabPages)
            //{

               // tabControl1.SelectedTab = tab;
                // 0 et 2 sont les labels
               // string tmp = tab.Controls[0].Text + " " + tab.Controls[1].Text + " " + tab.Controls[2].Text + " " + tab.Controls[3].Text;
                //Console.WriteLine(tab.Name + " " + tmp + "Tabs");

            //}
            FonctionsNatives.sauvegardeProfils();
            FonctionsNatives.reinitialiserProfils();
            listeProfils.Clear();
        }

        private void miseAJourSauvegardeInterface()
        {
            if (checkBox1.Checked)
            {
                peutAfficherDebogage = true;
                if (checkBox2.Checked)
                    peutAfficherCollision = true;
                else
                    peutAfficherCollision = false;
                if (checkBox3.Checked)
                    peutAfficherVitesseRondelle = true;
                else
                    peutAfficherVitesseRondelle = false;
                if (checkBox4.Checked)
                    peutAfficherEclairage = true;
                else
                    peutAfficherEclairage = false;
                if (checkBox5.Checked)
                    peutAfficherAttractionPortail = true;
                else
                    peutAfficherAttractionPortail = false;
            }
            else
            {
                peutAfficherDebogage = false;
                peutAfficherCollision = false;
                peutAfficherVitesseRondelle = false;
                peutAfficherDebogage = false;
                peutAfficherEclairage = false;
                peutAfficherAttractionPortail = false;
            }
            switch(comboBox2.SelectedIndex)
            {
                case 0:
                    nbButs = 1;
                    break;
                case 1:
                    nbButs = 2;
                    break;
                case 2:
                    nbButs = 3;
                    break;
                case 3:
                    nbButs = 4;
                    break;
                case 4:
                    nbButs = 5;
                    break;
                default:
                    nbButs = 2;
                    break;
            }

            haut = button5.Text;
            bas = button6.Text;
            gauche = button7.Text;
            droite = button8.Text;

            if (comboBox1.SelectedIndex == 1)
                estVirtuel = true;
            else
                estVirtuel = false;
        }
        private void ajouterTabProfils()
        {
            // bool found = false; 
            FonctionsNatives.reinitialiserProfils();
            foreach (TabPage tab in tabControl1.TabPages)
            {
                //for (int i = 0; i < FonctionsNatives.nombreProfils(); i++)
                //{
                //    if (tab.Name.Equals(FonctionsNatives.nomDuProfil(i)))
                //    {
                //        found = true;
                //    }
                //}
                tabControl1.SelectedTab = tab;
                if (tab.Name != "Défaut")
                {
                    // 0 et 2 sont les labels
                   // string tmp = tab.Controls[0].Text + " " + tab.Controls[1].Text + " " + tab.Controls[2].Text + " " + tab.Controls[3].Text;
                    //Console.WriteLine(tab.Name + " " + tmp);
                    int tmpVitesse = Int32.Parse(tab.Controls[1].Text);
                    int tmpPassivite = Int32.Parse(tab.Controls[3].Text);
                    FonctionsNatives.ajouterNouveauProfil(tab.Name, tmpVitesse, tmpPassivite);
                }

            }
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            Program.nbBut = (int) comboBox2.SelectedItem;
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
