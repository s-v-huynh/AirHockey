namespace InterfaceGraphique
{
    partial class MenuPrincipal
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MenuPrincipal));
            this.PartieRapide = new System.Windows.Forms.Button();
            this.Tournoi = new System.Windows.Forms.Button();
            this.Configuration = new System.Windows.Forms.Button();
            this.Editeur = new System.Windows.Forms.Button();
            this.Quitter = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // PartieRapide
            // 
            this.PartieRapide.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.PartieRapide.BackColor = System.Drawing.Color.LightSlateGray;
            this.PartieRapide.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PartieRapide.ForeColor = System.Drawing.Color.White;
            this.PartieRapide.Location = new System.Drawing.Point(476, 286);
            this.PartieRapide.Margin = new System.Windows.Forms.Padding(2);
            this.PartieRapide.Name = "PartieRapide";
            this.PartieRapide.Size = new System.Drawing.Size(200, 52);
            this.PartieRapide.TabIndex = 0;
            this.PartieRapide.Text = "Partie Rapide";
            this.PartieRapide.UseVisualStyleBackColor = false;
            this.PartieRapide.Click += new System.EventHandler(this.PartieRapide_Click);
            this.PartieRapide.MouseEnter += new System.EventHandler(this.PartieRapide_MouseEnter);
            this.PartieRapide.MouseLeave += new System.EventHandler(this.PartieRapide_MouseLeave);
            // 
            // Tournoi
            // 
            this.Tournoi.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.Tournoi.BackColor = System.Drawing.Color.LightSlateGray;
            this.Tournoi.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Tournoi.ForeColor = System.Drawing.Color.White;
            this.Tournoi.Location = new System.Drawing.Point(476, 342);
            this.Tournoi.Margin = new System.Windows.Forms.Padding(2);
            this.Tournoi.Name = "Tournoi";
            this.Tournoi.Size = new System.Drawing.Size(200, 52);
            this.Tournoi.TabIndex = 1;
            this.Tournoi.Text = "Tournoi";
            this.Tournoi.UseVisualStyleBackColor = false;
            this.Tournoi.Click += new System.EventHandler(this.Tournoi_Click);
            this.Tournoi.MouseEnter += new System.EventHandler(this.Tournoi_MouseEnter);
            this.Tournoi.MouseLeave += new System.EventHandler(this.Tournoi_MouseLeave);
            // 
            // Configuration
            // 
            this.Configuration.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.Configuration.BackColor = System.Drawing.Color.LightSlateGray;
            this.Configuration.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Configuration.ForeColor = System.Drawing.Color.White;
            this.Configuration.Location = new System.Drawing.Point(476, 398);
            this.Configuration.Margin = new System.Windows.Forms.Padding(2);
            this.Configuration.Name = "Configuration";
            this.Configuration.Size = new System.Drawing.Size(200, 52);
            this.Configuration.TabIndex = 2;
            this.Configuration.Text = "Configuration";
            this.Configuration.UseVisualStyleBackColor = false;
            this.Configuration.Click += new System.EventHandler(this.Configuration_Click);
            this.Configuration.MouseEnter += new System.EventHandler(this.Configuration_MouseEnter);
            this.Configuration.MouseLeave += new System.EventHandler(this.Configuration_MouseLeave);
            // 
            // Editeur
            // 
            this.Editeur.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.Editeur.BackColor = System.Drawing.Color.LightSlateGray;
            this.Editeur.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Editeur.ForeColor = System.Drawing.Color.White;
            this.Editeur.Location = new System.Drawing.Point(476, 454);
            this.Editeur.Margin = new System.Windows.Forms.Padding(2);
            this.Editeur.Name = "Editeur";
            this.Editeur.Size = new System.Drawing.Size(200, 52);
            this.Editeur.TabIndex = 3;
            this.Editeur.Text = "Éditeur";
            this.Editeur.UseVisualStyleBackColor = false;
            this.Editeur.Click += new System.EventHandler(this.Editeur_Click);
            this.Editeur.MouseEnter += new System.EventHandler(this.Editeur_MouseEnter);
            this.Editeur.MouseLeave += new System.EventHandler(this.Editeur_MouseLeave);
            // 
            // Quitter
            // 
            this.Quitter.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.Quitter.BackColor = System.Drawing.Color.Maroon;
            this.Quitter.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Quitter.ForeColor = System.Drawing.Color.White;
            this.Quitter.Location = new System.Drawing.Point(455, 524);
            this.Quitter.Margin = new System.Windows.Forms.Padding(2);
            this.Quitter.Name = "Quitter";
            this.Quitter.Size = new System.Drawing.Size(243, 59);
            this.Quitter.TabIndex = 4;
            this.Quitter.Text = "Quitter";
            this.Quitter.UseVisualStyleBackColor = false;
            this.Quitter.Click += new System.EventHandler(this.Quitter_Click);
            this.Quitter.MouseEnter += new System.EventHandler(this.Quitter_MouseEnter);
            this.Quitter.MouseLeave += new System.EventHandler(this.Quitter_MouseLeave);
            // 
            // MenuPrincipal
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Menu_Principal;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1136, 609);
            this.Controls.Add(this.Quitter);
            this.Controls.Add(this.Editeur);
            this.Controls.Add(this.Configuration);
            this.Controls.Add(this.Tournoi);
            this.Controls.Add(this.PartieRapide);
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "MenuPrincipal";
            this.Text = "MenuPrincipal";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button PartieRapide;
        private System.Windows.Forms.Button Tournoi;
        private System.Windows.Forms.Button Configuration;
        private System.Windows.Forms.Button Editeur;
        private System.Windows.Forms.Button Quitter;
    }
}