//////////////////////////////////////////////////////////////////////////////
/// @file Program.cs
/// @author Equipe 6
/// @date 2016-11-10
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    static class Program
    {
        public struct Joueur
        {
            public string nom;
            public bool estVirtuel;
            public Profil profil;
            public Joueur(string cNom, bool cEstVirtuel, Profil cProfil)
            {
                nom = cNom;
                estVirtuel = cEstVirtuel;
                profil = cProfil;
            }
        }

        private const int NB_IMAGES_PAR_SECONDE = 60;

        public static Object unLock = new Object();
        public static bool peutAfficher = true;
        public static bool tracerRectangle = false;
        public static int nbBut = 0;
        public static bool joueurVirtuel = false;

        public static ModeEdition edition;

        public static ArbreTournoi arbre;
        public static FinPartiRapide finPartiRapide;

        public static bool estDansPartieRapide = false;
        public static bool estDansTournoi = false;
        public static bool estDansModeEdition = false;

        public static string fichierXMLAChargerRapide;
        public static string fichierXMLAChargerTournoi;



        public static List<Joueur> listeJoueursTournoi = new List<Joueur>();        

        public static Profil profilSelectionne;


        public static MenuPrincipal menuPrincipal;
        private static TimeSpan dernierTemps;
        private static TimeSpan tempsAccumule;
        private static Stopwatch chrono = Stopwatch.StartNew();
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / NB_IMAGES_PAR_SECONDE);

        public static Stopwatch tempsJeu = new System.Diagnostics.Stopwatch();
        public static Timer timerJeu = new Timer();

        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length != 0)
                if (args[0] == "testsC++")
                {
                    //if (FonctionsNatives.executerTests())
                    //    System.Console.WriteLine("Échec d'un ou plusieurs tests.");
                    //else
                    //    System.Console.WriteLine("Tests réussis.");

                    //return;
                }

            chrono.Start();
            Application.Idle += ExecuterQuandInactif;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            menuPrincipal = new MenuPrincipal();
            Application.Run(menuPrincipal);

        }

        static public void ExecuterQuandInactif(object sender, EventArgs e)
        {
            FonctionsNatives.Message message;

            while (!FonctionsNatives.PeekMessage(out message, IntPtr.Zero, 0, 0, 0))
            {
                TimeSpan currentTime = chrono.Elapsed;
                TimeSpan elapsedTime = currentTime - dernierTemps;
                dernierTemps = currentTime;

                tempsAccumule += elapsedTime;
                // Console.WriteLine("Ticks per second: " + tempsEcouleVoulu + " Temps:" +  (double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                if (tempsAccumule >= tempsEcouleVoulu)
                {
                    lock (unLock)
                    {
                        if (edition != null && peutAfficher)
                        {
                            edition.MettreAJour((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                           
                        }
                            
                           
                        //Console.WriteLine("Ticks per second: " +  TimeSpan.TicksPerSecond + " Temps:" +  (double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                    }
                    tempsAccumule = TimeSpan.Zero;
                }
            }
        }
    }
}
