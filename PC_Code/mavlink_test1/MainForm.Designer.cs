/*
 * Created by SharpDevelop.
 * User: User
 * Date: 22.02.2018
 * Time: 17:29
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace mavlink_test1
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		private System.Windows.Forms.Button btnOpen;
		private System.Windows.Forms.ComboBox comboBox_ports;
		private System.Windows.Forms.DataGridView dataGridView1;
		private System.Windows.Forms.DataGridViewTextBoxColumn col_name;
		private System.Windows.Forms.DataGridViewTextBoxColumn Count;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPage1;
		private System.Windows.Forms.TabPage tabPage2;
		private mavlink_test1.AnglesDisplay anglesDisplayRotation;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
            this.components = new System.ComponentModel.Container();
            this.btnOpen = new System.Windows.Forms.Button();
            this.comboBox_ports = new System.Windows.Forms.ComboBox();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.col_name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Count = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.lblBattery = new System.Windows.Forms.Label();
            this.lblRawQuaternion = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.btnSetUserPoint = new System.Windows.Forms.Button();
            this.chkUseGyro = new System.Windows.Forms.CheckBox();
            this.btnStartCalibration = new System.Windows.Forms.Button();
            this.btnSetCalibration = new System.Windows.Forms.Button();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.anglesDisplay1 = new mavlink_test1.AnglesDisplay();
            this.anglesDisplayRotation = new mavlink_test1.AnglesDisplay();
            this.mapControl1 = new mavlink_test1.MapControl();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(13, 15);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(83, 32);
            this.btnOpen.TabIndex = 0;
            this.btnOpen.Text = "Open";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.BtnOpenClick);
            // 
            // comboBox_ports
            // 
            this.comboBox_ports.FormattingEnabled = true;
            this.comboBox_ports.Location = new System.Drawing.Point(116, 22);
            this.comboBox_ports.Name = "comboBox_ports";
            this.comboBox_ports.Size = new System.Drawing.Size(270, 21);
            this.comboBox_ports.TabIndex = 1;
            this.comboBox_ports.DropDown += new System.EventHandler(this.ComboBox_portsDropDown);
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.col_name,
            this.Count});
            this.dataGridView1.Location = new System.Drawing.Point(13, 54);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(357, 155);
            this.dataGridView1.TabIndex = 2;
            // 
            // col_name
            // 
            this.col_name.HeaderText = "Name";
            this.col_name.Name = "col_name";
            this.col_name.Width = 200;
            // 
            // Count
            // 
            this.Count.HeaderText = "Count";
            this.Count.Name = "Count";
            this.Count.Width = 80;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 500;
            this.timer1.Tick += new System.EventHandler(this.Timer1Tick);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(2);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(792, 482);
            this.tabControl1.TabIndex = 4;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.dataGridView1);
            this.tabPage1.Controls.Add(this.btnOpen);
            this.tabPage1.Controls.Add(this.comboBox_ports);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(2);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(2);
            this.tabPage1.Size = new System.Drawing.Size(784, 456);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Connection";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.lblBattery);
            this.tabPage2.Controls.Add(this.lblRawQuaternion);
            this.tabPage2.Controls.Add(this.anglesDisplay1);
            this.tabPage2.Controls.Add(this.anglesDisplayRotation);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Margin = new System.Windows.Forms.Padding(2);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(2);
            this.tabPage2.Size = new System.Drawing.Size(784, 456);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Raw data";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // lblBattery
            // 
            this.lblBattery.AutoSize = true;
            this.lblBattery.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblBattery.Location = new System.Drawing.Point(24, 252);
            this.lblBattery.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblBattery.Name = "lblBattery";
            this.lblBattery.Size = new System.Drawing.Size(64, 20);
            this.lblBattery.TabIndex = 3;
            this.lblBattery.Text = "Battery:";
            // 
            // lblRawQuaternion
            // 
            this.lblRawQuaternion.AutoSize = true;
            this.lblRawQuaternion.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblRawQuaternion.Location = new System.Drawing.Point(24, 220);
            this.lblRawQuaternion.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblRawQuaternion.Name = "lblRawQuaternion";
            this.lblRawQuaternion.Size = new System.Drawing.Size(81, 20);
            this.lblRawQuaternion.TabIndex = 1;
            this.lblRawQuaternion.Text = "Raw quat:";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.btnSetUserPoint);
            this.tabPage3.Controls.Add(this.chkUseGyro);
            this.tabPage3.Controls.Add(this.btnStartCalibration);
            this.tabPage3.Controls.Add(this.btnSetCalibration);
            this.tabPage3.Controls.Add(this.mapControl1);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Margin = new System.Windows.Forms.Padding(2);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(2);
            this.tabPage3.Size = new System.Drawing.Size(784, 456);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Map";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // btnSetUserPoint
            // 
            this.btnSetUserPoint.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSetUserPoint.Location = new System.Drawing.Point(688, 125);
            this.btnSetUserPoint.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetUserPoint.Name = "btnSetUserPoint";
            this.btnSetUserPoint.Size = new System.Drawing.Size(92, 24);
            this.btnSetUserPoint.TabIndex = 4;
            this.btnSetUserPoint.Text = "Set User Point";
            this.btnSetUserPoint.UseVisualStyleBackColor = true;
            this.btnSetUserPoint.Click += new System.EventHandler(this.BtnSetUserPoint_Click);
            // 
            // chkUseGyro
            // 
            this.chkUseGyro.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.chkUseGyro.AutoSize = true;
            this.chkUseGyro.Checked = true;
            this.chkUseGyro.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkUseGyro.Location = new System.Drawing.Point(694, 91);
            this.chkUseGyro.Margin = new System.Windows.Forms.Padding(2);
            this.chkUseGyro.Name = "chkUseGyro";
            this.chkUseGyro.Size = new System.Drawing.Size(79, 17);
            this.chkUseGyro.TabIndex = 3;
            this.chkUseGyro.Text = "Use GYRO";
            this.chkUseGyro.UseVisualStyleBackColor = true;
            // 
            // btnStartCalibration
            // 
            this.btnStartCalibration.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnStartCalibration.Location = new System.Drawing.Point(698, 53);
            this.btnStartCalibration.Margin = new System.Windows.Forms.Padding(2);
            this.btnStartCalibration.Name = "btnStartCalibration";
            this.btnStartCalibration.Size = new System.Drawing.Size(68, 24);
            this.btnStartCalibration.TabIndex = 2;
            this.btnStartCalibration.Text = "Start Calib.";
            this.btnStartCalibration.UseVisualStyleBackColor = true;
            this.btnStartCalibration.Click += new System.EventHandler(this.btnStartCalibration_Click);
            // 
            // btnSetCalibration
            // 
            this.btnSetCalibration.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSetCalibration.Location = new System.Drawing.Point(688, 14);
            this.btnSetCalibration.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetCalibration.Name = "btnSetCalibration";
            this.btnSetCalibration.Size = new System.Drawing.Size(92, 24);
            this.btnSetCalibration.TabIndex = 1;
            this.btnSetCalibration.Text = "Set Calib. Point";
            this.btnSetCalibration.UseVisualStyleBackColor = true;
            this.btnSetCalibration.Click += new System.EventHandler(this.btnSetCalibration_Click);
            // 
            // tabPage4
            // 
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Margin = new System.Windows.Forms.Padding(2);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(2);
            this.tabPage4.Size = new System.Drawing.Size(784, 456);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Telescope";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // anglesDisplay1
            // 
            this.anglesDisplay1.Location = new System.Drawing.Point(217, 21);
            this.anglesDisplay1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.anglesDisplay1.Name = "anglesDisplay1";
            this.anglesDisplay1.Size = new System.Drawing.Size(200, 171);
            this.anglesDisplay1.TabIndex = 2;
            // 
            // anglesDisplayRotation
            // 
            this.anglesDisplayRotation.Location = new System.Drawing.Point(13, 21);
            this.anglesDisplayRotation.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.anglesDisplayRotation.Name = "anglesDisplayRotation";
            this.anglesDisplayRotation.Size = new System.Drawing.Size(200, 171);
            this.anglesDisplayRotation.TabIndex = 0;
            // 
            // mapControl1
            // 
            this.mapControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.mapControl1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.mapControl1.Location = new System.Drawing.Point(4, 5);
            this.mapControl1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.mapControl1.Name = "mapControl1";
            this.mapControl1.Size = new System.Drawing.Size(680, 448);
            this.mapControl1.TabIndex = 0;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(792, 482);
            this.Controls.Add(this.tabControl1);
            this.Name = "MainForm";
            this.Text = "mavlink_test1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.ResumeLayout(false);

		}

        private System.Windows.Forms.Label lblRawQuaternion;
        private AnglesDisplay anglesDisplay1;
        private System.Windows.Forms.TabPage tabPage3;
        private MapControl mapControl1;
        private System.Windows.Forms.Button btnSetCalibration;
        private System.Windows.Forms.Button btnStartCalibration;
        private System.Windows.Forms.CheckBox chkUseGyro;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Label lblBattery;
        private System.Windows.Forms.Button btnSetUserPoint;
    }
}
