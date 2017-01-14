//////////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.cs
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
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;


namespace InterfaceGraphique
{
    public partial class ModeEdition : Form
    {
        /*pri ate static EtatEdition etat_ = null;*/
        private int xMouseDown_ = int.MaxValue;
        private int yMouseDown_ = int.MinValue;
        private Keys modificateur_ = Keys.None;
        private static int hauteurPanel1_ = 0;
        private static int largeurPanel1_ = 0;
        int idSelectionner;
        int idCreer;
        bool enSelection = false;
        bool vue = false;
        public static bool zoomInElas = false;
        public static bool zoomOutElas = false;
        private int valeurY = 0;
        public static bool enEchelle = false;
        public static bool enRotation = false;
        public static bool enDeplacement = false;
        public static bool enModeTest = false;
        string nomObjet;
        string fichierCourant = "";
        Etat etatEdition;
        enum Etat
        {
            initial,
            selection,
            selectionRect,
            ajout,
            ajoutPortail,
            deplacement,
            zoom,
            duplication,
            rotation,
            echelle,
            orthographique,
            orbite,

        }
        Timer timer = new Timer();
        public ModeEdition()
        {
            InitializeComponent();
            panel2.BackColor = Color.FromArgb(202, 213, 217);
            groupBox3.BackColor = Color.FromArgb(155, 176, 184);
            groupBox4.BackColor = Color.FromArgb(155, 176, 184);
            toolStrip1.BackColor = Color.FromArgb(202, 213, 217);
            InitialiserAnimation();
            FonctionsNatives.chargerConfigurationOptions();
            Configuration.haut = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirHaut());
            Configuration.bas = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirBas());
            Configuration.gauche = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirGauche());
            Configuration.droite = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(FonctionsNatives.obtenirDroite());
            Configuration.nbButs = FonctionsNatives.obtenirNbButs();
            Configuration.peutAfficherDebogage = FonctionsNatives.obtenirPeutAfficherDebogage();
            Configuration.peutAfficherCollision = FonctionsNatives.obtenirPeutAfficherCollision();
            Configuration.peutAfficherEclairage = FonctionsNatives.obtenirPeutAfficherEclairage();
            Configuration.peutAfficherVitesseRondelle = FonctionsNatives.obtenirPeutAfficherVitesse();
            Configuration.peutAfficherAttractionPortail = FonctionsNatives.obtenirPeutAfficherAttractionPortail();
            //Configuration du timer
            timer.Tick += new EventHandler(timer_Tick);
            timer.Interval = 16;//1000ms  1s
            timer.Enabled = true;
            timer.Start();
            this.MouseWheel += new MouseEventHandler(Panel1_MouseWheel);
            panel1.Height = panel1.Width / 2;

            etatEdition = Etat.initial;

            string frictionTable = FonctionsNatives.obtenirFrictionTable().ToString();
            string accelerationBonus = FonctionsNatives.obtenirAccelerationBonus().ToString();
            string coefRebondissement = FonctionsNatives.obtenirCoefRebondissement().ToString();

            textBox1.Text = frictionTable;
            textBox3.Text = accelerationBonus;
            textBox2.Text = coefRebondissement;

            //string positionX = FonctionsNatives.obtenirPositionObjetX().ToString();
            //string positionY = FonctionsNatives.obtenirPositionObjetY().ToString();
            //string positionZ = FonctionsNatives.obtenirPositionObjetZ().ToString();
            //string angleRotationObjet = FonctionsNatives.obtenirAngleRotationObjet().ToString();
            //string facteurEchelleObjet = FonctionsNatives.obtenirFacteurEchelleObjet().ToString();

            //textBox4.Text = positionX;
            //textBox5.Text = positionY;
            //textBox6.Text = positionZ;
            //textBox7.Text = angleRotationObjet;
            //textBox8.Text = facteurEchelleObjet;

            this.ActiveControl = panel1;

            if (Program.estDansPartieRapide)
            {
                panel2.Visible = false;
                toolStrip1.Visible = false;
                menuStrip1.Visible = false;
                FonctionsNatives.initialiserChargement(Program.fichierXMLAChargerRapide);
                this.Text = "Partie Rapide";
            }
            
            if (Program.estDansModeEdition)
            {
                this.Text = "Mode Édition";
                FonctionsNatives.mettreEnPause();
            }

            if (Program.estDansTournoi)
            {
                panel2.Visible = false;
                toolStrip1.Visible = false;
                menuStrip1.Visible = false;
                FonctionsNatives.initialiserChargement(Program.fichierXMLAChargerTournoi);
                this.Text = "Tournoi";
            }


        }
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        /// Affiche les barre menu selon ce qui est choisi dans le menu principal
        private void ModeEdition_Shown(object sender, EventArgs e)
        {
            if (Program.estDansPartieRapide)
            {
                panel2.Visible = false;
                toolStrip1.Visible = false;
                menuStrip1.Visible = false;
                this.Text = "Partie Rapide";
                //Console.WriteLine("PR");
            }

            if (Program.estDansModeEdition)
            {
                this.Text = "Mode Édition";
                //Console.WriteLine("EDition");
            }

            if (Program.estDansTournoi)
            {
                panel2.Visible = false;
                toolStrip1.Visible = false;
                menuStrip1.Visible = false;
                this.Text = "Tournoi";
                //Console.WriteLine("Tour");
            }
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

        private void timer_Tick(object sender, EventArgs e)
        {
            if (!Program.tracerRectangle)
            {
                //Console.WriteLine("Tick");
                FonctionsNatives.redessiner();
                FonctionsNatives.dessinerOpenGL();
            }
        }
        public void lancerModeEdition()
        {
            this.ShowDialog();
        }

        private void sélectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.selection;
            
        }
        private void portailToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.ajoutPortail;
            nomObjet = "portail";
        }
        private void muretToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.ajout;
            nomObjet = "muret";
        }
        private void bonusAccélérateurToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.ajout;
            nomObjet = "bonus";
        }
        private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.duplication;
        }
        private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //etatEdition = Etat.suppression;
            FonctionsNatives.supprimerSelection();
        }
        private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.rotation;
        }

        private void déplacementToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.deplacement;
        }

        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.initialisationParDefaut();
        }

        private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string nomFichier = "";
            OpenFileDialog openDialog = new OpenFileDialog();
            openDialog.Filter = "XML Files| *.xml";
            DialogResult result = openDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                nomFichier = openDialog.FileName;
            }
            if (nomFichier != "")
                FonctionsNatives.initialiserChargement(nomFichier);
            fichierCourant = nomFichier;
        }

        private void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fichierCourant == "")
            {
                string nomFichier = "";
                SaveFileDialog saveDialog = new SaveFileDialog();
                saveDialog.Filter = "XML Files| *.xml";
                DialogResult result = saveDialog.ShowDialog();
                if (result == DialogResult.OK)
                {
                    nomFichier = saveDialog.FileName;
                }
                if (nomFichier == "default.xml")
                {
                    MessageBox.Show("Impossible d'enregistrer dans le fichier par defaut.");
                }
                if (nomFichier != "")
                    FonctionsNatives.sauvegarderArbre(nomFichier);
                fichierCourant = nomFichier;
            }
            else
            {
                FonctionsNatives.sauvegarderArbre(fichierCourant);
            }
        }

        private void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string nomFichier = "";
            string nomFichierSansChemin = "";
            SaveFileDialog saveDialog = new SaveFileDialog();
            saveDialog.Filter = "XML Files| *.xml";
            DialogResult result = saveDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                nomFichier = saveDialog.FileName;
                nomFichierSansChemin = System.IO.Path.GetFileName(nomFichier);
            }
            if (nomFichierSansChemin == "default.xml")
            {
                MessageBox.Show("Impossible d'ecrire dans le fichier par défaut.");
            }
            else if (nomFichier != "")
                FonctionsNatives.sauvegarderArbre(nomFichier);
            fichierCourant = nomFichier;
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            
            if (e.Button == MouseButtons.Left)
            {
                FonctionsNatives.sauverSouris();
               // FonctionsNatives.deplacerSouris(e.X, e.Y);
                
                switch (etatEdition)
                {
                    case Etat.initial:
                        enDeplacement = false;
                        enEchelle = false;
                        enRotation = false;
                        FonctionsNatives.deselectionnerTout();
                        
                        break;
                    case Etat.selection:
                        if (!Program.tracerRectangle)
                        {
                            // FonctionsNatives.initialiserOpenGL(panel1.Handle);
                            //Console.WriteLine("   Debut");
                            Program.tracerRectangle = true;
                            FonctionsNatives.initialiserRectangleElas(e.X, e.Y);
                            if (e.Button == MouseButtons.Left)
                            {
                                //int nombreSelection =FonctionsNatives.obtenirNombreNoeudsSelectionnes();
                                // Console.WriteLine("NombreNoeudsSelectionnes"+ nombreSelection);
                                enSelection = !enSelection;
                                FonctionsNatives.selectionObjet(e.X, e.Y, true);
                               // if(e.Button == .Left)
                                string positionX = FonctionsNatives.obtenirPositionObjetX().ToString();
                                string positionY = FonctionsNatives.obtenirPositionObjetY().ToString();
                                string positionZ = FonctionsNatives.obtenirPositionObjetZ().ToString();
                                string angleRotationObjet = FonctionsNatives.obtenirAngleRotationObjet().ToString();
                                string facteurEchelleObjet = FonctionsNatives.obtenirFacteurEchelleObjet().ToString();
                                textBox4.Text = positionX;
                                textBox5.Text = positionY;
                                textBox6.Text = positionZ;
                                textBox7.Text = angleRotationObjet;
                                textBox8.Text = facteurEchelleObjet;
                            }
                            // etatEdition = Etat.selection;

                        }
                        break;
                    case Etat.ajout:
                        {
                            
                            if (e.Button == MouseButtons.Left)
                            {
                                //a modifier
                                if (nomObjet == "muret")
                                {

                                    //FonctionsNatives.sauvegarderPositionSouris(e.X, e.Y);
                                    FonctionsNatives.ajouterNouveauElement(nomObjet, e.Location.X, e.Location.Y);
                                }
                                else if(nomObjet == "portail")
                                {
                                    etatEdition = Etat.ajoutPortail;
                                }
                               else
                                {

                                    //FonctionsNatives.sauvegarderPositionSouris(e.X, e.Y);
                                    FonctionsNatives.ajouterNouveauElement(nomObjet, e.Location.X, e.Location.Y);
                                }

                            }
                        }
                        break;
                        case Etat.ajoutPortail:
                        {
                            FonctionsNatives.ajouterNouveauElement(nomObjet, e.Location.X, e.Location.Y);
                            FonctionsNatives.ajouterNouveauPortail(nomObjet, e.Location.X, e.Location.Y);
                            FonctionsNatives.initialiserDeplacement(e.X, e.Y);
                            enDeplacement = true;
                            etatEdition = Etat.initial;
                        }
                        break;
                    case Etat.echelle:
                        {
                            if (e.Button == MouseButtons.Left)
                            {
                                enEchelle = true;
                                valeurY = e.Y;
                            }
                        }
                        break;
                    case Etat.rotation:
                        if (e.Button == MouseButtons.Left)
                        {
                            FonctionsNatives.initialiserRotation(e.Y);
                            enRotation = true;
                        }
                        break;
                    case Etat.deplacement:
                        if (e.Button == MouseButtons.Left)
                        {
                            FonctionsNatives.initialiserDeplacement(e.X, e.Y);
                            enDeplacement = true;
                        }
                        break;
                    case Etat.duplication:
                        {
                            if (e.Button == MouseButtons.Left)
                            {
                                FonctionsNatives.dupliquerSelection(e.Location.X, e.Location.Y);
                                FonctionsNatives.initialiserDeplacement(e.X, e.Y);
                                enDeplacement = true;
                                etatEdition = Etat.initial;
                            }

                        }
                        break;
                    case Etat.zoom:
                        if (!Program.tracerRectangle)
                        {
                            // FonctionsNatives.initialiserOpenGL(panel1.Handle);
                            //Console.WriteLine("   Debut");
                            zoomInElas = true;
                            zoomOutElas = false;
                            Program.tracerRectangle = true;
                            FonctionsNatives.initialiserRectangleElas(e.X, e.Y);
                        }
                        break;
                }
            }
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {

            if(keyData == Keys.J)
            {
                if (FonctionsNatives.obtenirEtatAmbiante()) {
                    FonctionsNatives.modifierEtatAmbiante(false);
                    //FonctionsNatives.modifierEtatDirectionnelle(true);
                }
                else
                {
                    FonctionsNatives.modifierEtatAmbiante(true);
                    FonctionsNatives.modifierEtatDirectionnelle(false);

                }

            }

            if (keyData == Keys.K)
            {
                if (FonctionsNatives.obtenirDirectionnelActive())
                {
                    FonctionsNatives.modifierEtatDirectionnelle(false);
                    //FonctionsNatives.modifierEtatAmbiante(true);
                }
                else
                {
                    FonctionsNatives.modifierEtatDirectionnelle(true);
                    FonctionsNatives.modifierEtatAmbiante(false);
                    FonctionsNatives.modifierEtatSpot(false);
                }

            }
            if (keyData == Keys.L)
            {
                if (FonctionsNatives.obtenirEtatSpot())
                {
                    FonctionsNatives.modifierEtatSpot(false);
                }
                else
                {
                    FonctionsNatives.modifierEtatSpot(true);
                    //FonctionsNatives.modifierEtatAmbiante(false);
                    FonctionsNatives.modifierEtatDirectionnelle(false);
                }

            }

            if (keyData == Keys.Up)
            {
                FonctionsNatives.deplacerXY(0.0, -0.005,0,-5);
               // FonctionsNatives.deplacerClavier(0.0, -5.0);
            }
            if (keyData == Keys.Down)
            {
                FonctionsNatives.deplacerXY(0.0, 0.005, 0, 5);
                //FonctionsNatives.deplacerClavier(0.0, 50.0);
            }
            if (keyData == Keys.Left)
            {
                FonctionsNatives.deplacerXY(0.005, 0.0, 5, 0);
                //FonctionsNatives.deplacerClavier(0.005, 0.0);
            }
            if (keyData == Keys.Right)
            {
                FonctionsNatives.deplacerXY(-0.005, 0.0, -5, 0);
                //FonctionsNatives.deplacerClavier(-0.005, 0.0);

            }
            if (keyData == Keys.OemMinus || keyData == Keys.Subtract)
            {
                FonctionsNatives.zoomIn();
            }

            if (keyData == Keys.Oemplus || keyData == Keys.Add)

            {
                FonctionsNatives.zoomOut();
            }
            if (keyData == Keys.Control && enSelection)
            {

            }
            if (keyData == Keys.Alt && etatEdition == Etat.zoom)
            {
                
                zoomOutElas = true;
                zoomInElas = false;

            }
			
			if(keyData == Keys.Escape)
            {
                if (enDeplacement)
                {
                    FonctionsNatives.supprimerSelection();
                    enDeplacement = false;
                }
            }

            if (keyData == Keys.Delete)
            {
                 FonctionsNatives.supprimerSelection();
            }

			if (keyData == Keys.Control)
            {
                 FonctionsNatives.supprimerSelection();
            }

            if (keyData == Keys.Escape)
            {
                if (enModeTest)
                {
                    if (menuStrip2.Visible == false)
                    {   


                        Program.peutAfficher = false;
                        menuStrip2.Visible = true;
                        label12.Visible = true;
                    }
                    else
                    {
                        Program.peutAfficher = true;
                        menuStrip2.Visible = false;
                        label12.Visible = false;
                    }
                }

                if(Program.estDansPartieRapide || Program.estDansTournoi)
                {
                    
                    if (menuStrip3.Visible == false)
                    {
                        Program.peutAfficher = false;
                        Program.tempsJeu.Stop();
                        menuStrip3.Visible = true;
                        label12.Visible = true;
                    }
                    else
                    {
                        Program.peutAfficher = true;
                        Program.tempsJeu.Start();
                        menuStrip3.Visible = false;
                        label12.Visible = false;
                    }
                }
            }
            if(keyData == Keys.Space)
            {
                if (Program.estDansModeEdition && enModeTest)
                {
                    FonctionsNatives.reinitialiserTest();
                }
                if(Program.estDansPartieRapide)
                {
                    FonctionsNatives.reinitialiserPartie();
                    Program.tempsJeu.Reset();
                    Program.tempsJeu.Start();
                }
                
            }
            //if (keyData == Keys.P)
            //{
            //    if (Program.estDansModeEdition)
            //        Console.WriteLine("MODE EDITION !");

            //if (keyData == Keys.P)
            //{
            //    if (Program.estDansModeEdition)
            //        Console.WriteLine("MODE EDITION !");

            //    if (Program.estDansPartieRapide)
            //        Console.WriteLine("PARTIE RAPIDE !");

            //    if (Program.estDansTournoi)
            //        Console.WriteLine("TOURNOI !");
            //}
            if(keyData == Keys.D)
            {
                if (Program.estDansModeEdition)
                    etatEdition = Etat.deplacement;
            }
            if (keyData == Keys.S)
            {
                if (Program.estDansModeEdition)
                    etatEdition = Etat.selection;
            }
            if (keyData == Keys.R)
            {
                if (Program.estDansModeEdition)
                    etatEdition = Etat.rotation;
            }
            if (keyData == Keys.E)
            {
                if (Program.estDansModeEdition)
                    etatEdition = Etat.echelle;
            }
            if (keyData == Keys.C)
            {
                if (Program.estDansModeEdition)
                    etatEdition = Etat.duplication;
            }
            if (keyData == Keys.Z)
            {
                if (Program.estDansModeEdition)
                    etatEdition = Etat.zoom;
            }
            if (keyData == Keys.M)
            {
                if (Program.estDansModeEdition)
                {
                    etatEdition = Etat.ajout;
                    nomObjet = "muret";
                }
            }
            if (keyData == Keys.P)
            {
                if (Program.estDansModeEdition)
                {
                    etatEdition = Etat.ajout;
                    nomObjet = "portail";
                }
            }
            if (keyData == Keys.B)
            {
                if (Program.estDansModeEdition)
                {
                    etatEdition = Etat.ajout;
                    nomObjet = "bonus";
                }
            }
            if (keyData == Keys.T)
            {
                if (!enModeTest)
                {
                    FonctionsNatives.enModeEdition(false);
                    panel2.Visible = false;
                    toolStrip1.Visible = false;
                    menuStrip1.Visible = false;
                    enModeTest = true;
                    //Configuration.estVirtuel;
                    this.Text = "Mode Test";
                }
                else
                {
                    FonctionsNatives.enModeEdition(true);
                    Program.peutAfficher = true;
                    panel2.Visible = true;
                    toolStrip1.Visible = true;
                    menuStrip1.Visible = true;

                    menuStrip2.Visible = false;
                    label12.Visible = false;

                    enModeTest = false;
                    this.Text = "Mode Édition";
                }
            }
            if(keyData == Keys.D1 || keyData == Keys.NumPad1)
            {
                FonctionsNatives.activationVueOrtho();
            }
            if (keyData == Keys.D2 || keyData == Keys.NumPad2)
            {
                FonctionsNatives.activationVueOrbite();
            }
            if (!Program.joueurVirtuel)
            {
                if (Configuration.haut == keyData.ToString())
                {
                    //Console.WriteLine("haut");
                    FonctionsNatives.joueurMaillet2(0, 5);
                }

                if (Configuration.bas == keyData.ToString())
                {
                    //Console.WriteLine("bas");
                    FonctionsNatives.joueurMaillet2(0, -5);
                }

                if (Configuration.gauche == keyData.ToString())
                {
                    //Console.WriteLine("gauche");
                    FonctionsNatives.joueurMaillet2(-5, 0);
                }

                if (Configuration.droite == keyData.ToString())
                {
                    //Console.WriteLine("droite");
                    FonctionsNatives.joueurMaillet2(5, 0);
                }

            }
            if (Program.estDansTournoi && FonctionsNatives.joueurVirtuelDansPartieCourante() )
            {
                if (Configuration.haut == keyData.ToString())
                {
                    //Console.WriteLine("haut");
                    FonctionsNatives.joueurMaillet2(0, 5);
                }

                if (Configuration.bas == keyData.ToString())
                {
                    //Console.WriteLine("bas");
                    FonctionsNatives.joueurMaillet2(0, -5);
                }

                if (Configuration.gauche == keyData.ToString())
                {
                    //Console.WriteLine("gauche");
                    FonctionsNatives.joueurMaillet2(-5, 0);
                }

                if (Configuration.droite == keyData.ToString())
                {
                    //Console.WriteLine("droite");
                    FonctionsNatives.joueurMaillet2(5, 0);
                }
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void ModeEdition_KeyDown(object sender, KeyEventArgs e)
        {
           
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            //FonctionsNatives.enModeEdition(e)
           // FonctionsNatives.deplacerSouris(e.X,e.Y);
            if (Program.estDansPartieRapide)
            {
                panel2.Visible = false;
                toolStrip1.Visible = false;
                menuStrip1.Visible = false;
                this.Text = "Partie Rapide";
                //Console.WriteLine("PR");

                if (FonctionsNatives.afficherPanelRapide())
                {
                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    FonctionsNatives.mettreEnPause();
                    Program.tempsJeu.Reset();
                    Program.timerJeu.Stop();
                    Program.finPartiRapide.nomVainqueur(FonctionsNatives.nomVainqueurPartieRapide());
                    Program.finPartiRapide.scoreFinal(FonctionsNatives.scoreFinalPerdant());
                    Program.finPartiRapide.ShowDialog();
                    Program.tempsJeu.Start();
                    Program.timerJeu.Start();
                }

            }

            if (Program.estDansModeEdition && !enModeTest)
            {
                panel2.Visible = true;
                toolStrip1.Visible = true;
                menuStrip1.Visible = true;
                this.Text = "Mode Édition";
                //Console.WriteLine("EDition");
            }

            if (Program.estDansTournoi)
            {
                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                panel2.Visible = false;
                toolStrip1.Visible = false;
                menuStrip1.Visible = false;
                this.Text = "Tournoi";
                //Console.WriteLine("Tour");

                //Program.menuPrincipal.Hide();
                Program.arbre.miseAJourArbre(FonctionsNatives.getJoueur1Passe(), FonctionsNatives.getJoueur3Passe(), FonctionsNatives.getVainqueur1Passe(), FonctionsNatives.getActualiser1(), FonctionsNatives.getActualiser2(), FonctionsNatives.getActualiser3());
            }

            if (enModeTest || Program.estDansPartieRapide || Program.estDansTournoi)
            {
                //Console.WriteLine("im moving");
                if(Program.peutAfficher == true)
                    FonctionsNatives.joueurMaillet1(e.X, e.Y);
            }

            if (Program.tracerRectangle && (etatEdition == Etat.selection || etatEdition == Etat.zoom))
            {
                FonctionsNatives.mettreAJourRectangleElas(e.X, e.Y);
            }

            if (enEchelle && etatEdition == Etat.echelle)
            {
                int depY = valeurY - e.Y;
                valeurY = e.Y;
                FonctionsNatives.miseAEchelle(e.Location.X, depY);

                string facteurEchelleObjet = FonctionsNatives.obtenirFacteurEchelleObjet().ToString();
                textBox8.Text = facteurEchelleObjet;
            }
            if ((etatEdition == Etat.deplacement && enDeplacement) || (etatEdition == Etat.duplication && enDeplacement))
            {
                FonctionsNatives.effectuerDeplacement(e.X, e.Y);

                string positionX = FonctionsNatives.obtenirPositionObjetX().ToString();
                string positionY = FonctionsNatives.obtenirPositionObjetY().ToString();
                string positionZ = FonctionsNatives.obtenirPositionObjetZ().ToString();

                textBox4.Text = positionX;
                textBox5.Text = positionY;
                textBox6.Text = positionZ;
            }
            if (etatEdition == Etat.rotation && enRotation)
            {
                FonctionsNatives.effectuerRotation(e.Y);

                string angleRotationObjet = FonctionsNatives.obtenirAngleRotationObjet().ToString();
                textBox7.Text = angleRotationObjet;
            }
            if(enDeplacement)
            {
                FonctionsNatives.effectuerDeplacement(e.X, e.Y);
            }

        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {

            if (Program.tracerRectangle && etatEdition == Etat.selection)
            {
                Program.tracerRectangle = false;
                FonctionsNatives.terminerRectangleElas();
                FonctionsNatives.selectionElastique();
            }

            if (Program.tracerRectangle && etatEdition == Etat.zoom)
            {
                Program.tracerRectangle = false;
                FonctionsNatives.terminerRectangleElas();
                if (zoomInElas)
                {
                    FonctionsNatives.zoomInElas();
                }
                else if (zoomOutElas)
                {
                    FonctionsNatives.zoomOutElas();
                }

            }

            enEchelle = false;
            enRotation = false;
            if (etatEdition == Etat.deplacement && enDeplacement)
            {
                enDeplacement = false;
            }
        }

        private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.zoom;
        }

        private void Panel1_MouseWheel(object sender, MouseEventArgs e)
        {
            etatEdition = Etat.zoom;
            if (etatEdition == Etat.zoom)
            {
                
                int nombreDeZoom = e.Delta / 120;
                //Console.WriteLine(nombreDeZoom);
                for (int i = 0; i < Math.Abs(nombreDeZoom); i++)
                {
                    if (nombreDeZoom < 0)
                        FonctionsNatives.zoomOut();
                    else
                        FonctionsNatives.zoomIn();
                }
            }
        }
       

        private void miseÀLéchelleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            etatEdition = Etat.echelle;
        }

        //Bouton mettre a jour
        private void button1_Click(object sender, EventArgs e)
        {
            double facteur = -1;
            Double.TryParse(textBox8.Text, out facteur);
            if (facteur <= 0)
            {
                MessageBox.Show("Entrer une valeur strictement positive pour le facteur.");
                facteur = 1;
            }
            else
            {
                FonctionsNatives.mettreEchelleObjetBouton(facteur);
            }

            int angle = -1;
            Int32.TryParse(textBox7.Text, out angle);
            FonctionsNatives.rotationObjetBouton(angle);

            float pointX = -1;
            float pointY = -1;
            float.TryParse(textBox4.Text, out pointX);
            float.TryParse(textBox5.Text, out pointY);
            FonctionsNatives.deplacementObjetBouton(pointX, pointY);


        }

        private void button2_Click(object sender, EventArgs e)
        {
            double frictionTable = -1;
            Double.TryParse(textBox1.Text, out frictionTable);
            if (frictionTable < 0 || frictionTable >= 1)
            {
                MessageBox.Show("Entrer une valeur entre 0 et 1 pour la friction.");
                frictionTable = 0.5;
                textBox1.Text = "0.5";
            }
            else
                FonctionsNatives.frictionTableBouton(frictionTable);

            double accelerationBonus = -1;
            Double.TryParse(textBox3.Text, out accelerationBonus);
            if (accelerationBonus < 0 || accelerationBonus > 15)
            {
                MessageBox.Show("Entrer une valeur entre 0 et 15 pour l'accélération.");
                accelerationBonus = 3;
                textBox3.Text = "3";
            }
            else
                FonctionsNatives.accelerationBonusBouton(accelerationBonus);

            double coefRebondissement = -1;
            Double.TryParse(textBox2.Text, out coefRebondissement);
            if (coefRebondissement < 0 || coefRebondissement > 20)
            {
                MessageBox.Show("Entrer une valeur entre 0 et 20 pour le coefficient de rebondissement.");
                coefRebondissement = 3;
                textBox2.Text = "3";
            }
            else
                FonctionsNatives.coefRebondissementBouton(coefRebondissement);
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void propriétésToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Propriétés propriete = new Propriétés();
            propriete.ShowDialog();

            string frictionTable = FonctionsNatives.obtenirFrictionTable().ToString();
            string accelerationBonus = FonctionsNatives.obtenirAccelerationBonus().ToString();
            string coefRebondissement = FonctionsNatives.obtenirCoefRebondissement().ToString();

            textBox1.Text = frictionTable;
            textBox3.Text = accelerationBonus;
            textBox2.Text = coefRebondissement;
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = true;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            FonctionsNatives.initialisationParDefaut();
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = true;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;


            string nomFichier = "";
            OpenFileDialog openDialog = new OpenFileDialog();
            openDialog.Filter = "XML Files| *.xml";
            DialogResult result = openDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                nomFichier = openDialog.FileName;
            }
            if (nomFichier != "")
                FonctionsNatives.initialiserChargement(nomFichier);
            fichierCourant = nomFichier;
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = true;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            if (fichierCourant == "")
            {
                string nomFichier = "";
                SaveFileDialog saveDialog = new SaveFileDialog();
                saveDialog.Filter = "XML Files| *.xml";
                DialogResult result = saveDialog.ShowDialog();
                if (result == DialogResult.OK)
                {
                    nomFichier = saveDialog.FileName;
                }
                if (nomFichier == "default.xml")
                {
                    MessageBox.Show("Impossible d'enregistrer dans le fichier par defaut.");
                }
                if (nomFichier != "")
                    FonctionsNatives.sauvegarderArbre(nomFichier);
                fichierCourant = nomFichier;
            }
            else
            {
                FonctionsNatives.sauvegarderArbre(fichierCourant);
            }
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = true;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.ajout;
            nomObjet = "bonus";
        }

        private void toolStripButton5_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = true;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.ajoutPortail;
            nomObjet = "portail";
        }

        private void toolStripButton6_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = true;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.ajout;
            nomObjet = "muret";
        }

        private void toolStripButton7_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = true;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.selection;
        }

        private void toolStripButton8_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = true;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.echelle;
        }

        private void toolStripButton9_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = true;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.duplication;
        }

        private void toolStripButton10_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = true;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.zoom;
        }


        private void toolStripButton12_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = true;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.deplacement;
        }

        private void toolStripButton13_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = true;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;

            etatEdition = Etat.rotation;
        }

        private void toolStripButton14_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = true;
            toolStripButton15.Checked = false;
        }

        private void toolStripButton15_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = true;

            FonctionsNatives.supprimerSelection();
        }

        private void toolStripButton16_Click(object sender, EventArgs e)
        {
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
            toolStripButton4.Checked = false;
            toolStripButton5.Checked = false;
            toolStripButton6.Checked = false;
            toolStripButton7.Checked = false;
            toolStripButton8.Checked = false;
            toolStripButton9.Checked = false;
            toolStripButton10.Checked = false;
            toolStripButton12.Checked = false;
            toolStripButton13.Checked = false;
            toolStripButton14.Checked = false;
            toolStripButton15.Checked = false;
        }

        private void aideToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string textAide = System.IO.File.ReadAllText("aide.txt");
            MessageBox.Show(textAide);
        }

        /// Le bouton pour retourner dans le menu principal
        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Hide();
            Program.menuPrincipal.Show();
            FonctionsNatives.mettreEnPause();
        }

        /// Ctrl + Q pour retourner dans le menu principal
        private void ModeEdition_KeyDown_1(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.Q)
            {
                this.Hide();
                Program.menuPrincipal.Show();
                FonctionsNatives.mettreEnPause();
            }
            if (e.Control && e.KeyCode == Keys.S)
            {
                if (fichierCourant == "")
                {
                    string nomFichier = "";
                    SaveFileDialog saveDialog = new SaveFileDialog();
                    saveDialog.Filter = "XML Files| *.xml";
                    DialogResult result = saveDialog.ShowDialog();
                    if (result == DialogResult.OK)
                    {
                        nomFichier = saveDialog.FileName;
                    }
                    if (nomFichier == "default.xml")
                    {
                        MessageBox.Show("Impossible d'enregistrer dans le fichier par defaut.");
                    }
                    if (nomFichier != "")
                        FonctionsNatives.sauvegarderArbre(nomFichier);
                    fichierCourant = nomFichier;
                }

                else
                {
                    FonctionsNatives.sauvegarderArbre(fichierCourant);
                }
            }
            if (e.Control && e.KeyCode == Keys.N)
            {
                FonctionsNatives.initialisationParDefaut();
            }
            if (e.Control && e.KeyCode == Keys.O)
            {
                string nomFichier = "";
                OpenFileDialog openDialog = new OpenFileDialog();
                openDialog.Filter = "XML Files| *.xml";
                DialogResult result = openDialog.ShowDialog();
                if (result == DialogResult.OK)
                {
                    nomFichier = openDialog.FileName;
                }
                if (nomFichier != "")
                    FonctionsNatives.initialiserChargement(nomFichier);
                fichierCourant = nomFichier;
            }
        }

        /// Pour aller dans le mode test
        private void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //this.Hide();
            //ModeTest modeTest = new ModeTest();
            //modeTest.ShowDialog();
            //modeTest = null;
            //this.Show();

            FonctionsNatives.enModeEdition(false);
            FonctionsNatives.enModeTest(true);
            panel2.Visible = false;
            toolStrip1.Visible = false;
            menuStrip1.Visible = false;
            enModeTest = true;
           //Configuration.estVirtuel;
            this.Text = "Mode Test";
        }

        /// Retourner dans le menu principal
        private void menuPrincipalCtrlQToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //foreach (Form f in Application.OpenForms)
            //{
            //    if (f.Name != "MenuPrincipal")
            //    {
            //        f.Close();
            //    }
            //}
            FonctionsNatives.enModeTest(false);
            this.Hide();
            Program.menuPrincipal.Show();
            FonctionsNatives.mettreEnPause();
            panel2.Visible = true;
            toolStrip1.Visible = true;
            menuStrip1.Visible = true;

            menuStrip2.Visible = false;
            menuStrip3.Visible = false;
            label12.Visible = false;
            enModeTest = false;
                }

        /// Pour retourner dans le mode edition de mode test
        private void modeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.enModeEdition(true);
            FonctionsNatives.enModeTest(false);
            Program.peutAfficher = true;
            panel2.Visible = true;
            toolStrip1.Visible = true;
            menuStrip1.Visible = true;

            menuStrip2.Visible = false;
            label12.Visible = false;

            enModeTest = false;
            this.Text = "Mode Édition";
        }

        /// Pour aller dans le menu principal de partie rapide
        private void menuPrincipalCtrlQToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            //foreach (Form f in Application.OpenForms)
            //{
            //    if (f.Name != "MenuPrincipal")
            //    {
            //        f.Close();
            //    }
            //}
            FonctionsNatives.enModeTest(false);
            menuStrip3.Visible = false;
            label12.Visible = false;
            this.Hide();
            Program.menuPrincipal.Show();
            FonctionsNatives.mettreEnPause();
        }

        /// Pour fermer le form de edition
        private void ModeEdition_FormClosing(object sender, FormClosingEventArgs e)
            {
            //this.Hide();
            //Program.menuPrincipal.Show();

            enModeTest = false;
            FonctionsNatives.enModeTest(true);
            menuStrip3.Visible = false;
            label12.Visible = false;
            if (e.CloseReason == CloseReason.UserClosing)
                {
                e.Cancel = true;
                this.Hide();
                Program.menuPrincipal.Show();
                FonctionsNatives.mettreEnPause();
            }
            }

        /// Pour fermer le form de edition
        private void ModeEdition_FormClosed(object sender, FormClosedEventArgs e)
        {
            menuStrip3.Visible = false;
            label12.Visible = false;
            this.Hide();
            Program.menuPrincipal.Show();
            FonctionsNatives.mettreEnPause();
        }

        private void ModeEdition_SizeChanged(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height);
            FonctionsNatives.sizeFenetre(panel1.Width, panel1.Height);
        }

        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.activationVueOrbite();
        }

        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.activationVueOrtho();
        }

        private void panel1_Move(object sender, EventArgs e)
        {
            //FonctionsNatives.deplacerSouris(this.Location.X, this.Location.Y);
        }

        private void orbiteToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            FonctionsNatives.activationVueOrbite();
        }

        private void orthographiqueToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            FonctionsNatives.activationVueOrtho();
        }
        //Partie Rapide et Tournoi
        private void orbiteToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            FonctionsNatives.activationVueOrbite();

        }

        private void orthographiqueToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            FonctionsNatives.activationVueOrtho();
        
    }
}
}
