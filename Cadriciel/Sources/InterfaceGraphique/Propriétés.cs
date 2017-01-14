//////////////////////////////////////////////////////////////////////////////
/// @file Proprietes.cs
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
    public partial class Propriétés : Form
    {
        public Propriétés()
        {
            InitializeComponent();

            string frictionTable = FonctionsNatives.obtenirFrictionTable().ToString();
            string accelerationBonus = FonctionsNatives.obtenirAccelerationBonus().ToString();
            string coefRebondissement = FonctionsNatives.obtenirCoefRebondissement().ToString();

            textBox1.Text = frictionTable;
            textBox3.Text = accelerationBonus;
            textBox2.Text = coefRebondissement;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            double frictionTable = -1;
            Double.TryParse(textBox1.Text, out frictionTable);
            if (frictionTable < 1 || frictionTable > 5)
            {
                MessageBox.Show("Entrer une valeur entre 1 et 5 pour la friction.");
                frictionTable = 1;
                textBox1.Text = "1";
            }
            else
                FonctionsNatives.frictionTableBouton(frictionTable);

            double accelerationBonus = -1;
            Double.TryParse(textBox3.Text, out accelerationBonus);
            if (accelerationBonus < 1 || accelerationBonus > 5)
            {
                MessageBox.Show("Entrer une valeur entre 1 et 5 pour l'accélération.");
                accelerationBonus = 3;
                textBox3.Text = "3";
            }
            else
                FonctionsNatives.accelerationBonusBouton(accelerationBonus);

            double coefRebondissement = -1;
            Double.TryParse(textBox2.Text, out coefRebondissement);
            if (coefRebondissement < 1 || coefRebondissement > 5)
            {
                MessageBox.Show("Entrer une valeur entre 1 et 5 pour le coefficient de rebondissement.");
                coefRebondissement = 3;
                textBox2.Text = "3";
            }
            else
                FonctionsNatives.coefRebondissementBouton(coefRebondissement);
        }
    }
}
