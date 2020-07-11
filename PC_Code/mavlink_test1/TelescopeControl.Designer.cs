namespace mavlink_test1
{
    partial class TelescopeControl
    {
        /// <summary> 
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором компонентов

        /// <summary> 
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.lblRA = new System.Windows.Forms.Label();
            this.lblDEC = new System.Windows.Forms.Label();
            this.lblStellarium = new System.Windows.Forms.Label();
            this.lblLSTTime = new System.Windows.Forms.Label();
            this.btnStop = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lblRA
            // 
            this.lblRA.AutoSize = true;
            this.lblRA.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblRA.Location = new System.Drawing.Point(20, 21);
            this.lblRA.Name = "lblRA";
            this.lblRA.Size = new System.Drawing.Size(97, 29);
            this.lblRA.TabIndex = 0;
            this.lblRA.Text = "RA: N/A";
            // 
            // lblDEC
            // 
            this.lblDEC.AutoSize = true;
            this.lblDEC.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblDEC.Location = new System.Drawing.Point(20, 57);
            this.lblDEC.Name = "lblDEC";
            this.lblDEC.Size = new System.Drawing.Size(115, 29);
            this.lblDEC.TabIndex = 1;
            this.lblDEC.Text = "DEC: N/A";
            // 
            // lblStellarium
            // 
            this.lblStellarium.AutoSize = true;
            this.lblStellarium.Location = new System.Drawing.Point(22, 144);
            this.lblStellarium.Name = "lblStellarium";
            this.lblStellarium.Size = new System.Drawing.Size(101, 17);
            this.lblStellarium.TabIndex = 2;
            this.lblStellarium.Text = "Stellarium: N/A";
            // 
            // lblLSTTime
            // 
            this.lblLSTTime.AutoSize = true;
            this.lblLSTTime.Location = new System.Drawing.Point(22, 100);
            this.lblLSTTime.Name = "lblLSTTime";
            this.lblLSTTime.Size = new System.Drawing.Size(100, 17);
            this.lblLSTTime.TabIndex = 3;
            this.lblLSTTime.Text = "LST Time: N/A";
            // 
            // btnStop
            // 
            this.btnStop.Location = new System.Drawing.Point(25, 195);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(92, 27);
            this.btnStop.TabIndex = 4;
            this.btnStop.Text = "Stop";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // TelescopeControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.lblLSTTime);
            this.Controls.Add(this.lblStellarium);
            this.Controls.Add(this.lblDEC);
            this.Controls.Add(this.lblRA);
            this.Name = "TelescopeControl";
            this.Size = new System.Drawing.Size(448, 236);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblRA;
        private System.Windows.Forms.Label lblDEC;
        private System.Windows.Forms.Label lblStellarium;
        private System.Windows.Forms.Label lblLSTTime;
        private System.Windows.Forms.Button btnStop;
    }
}
