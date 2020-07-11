/*
 * Created by SharpDevelop.
 * User: NO
 * Date: 17.03.2019
 * Time: 19:05
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace mavlink_test1
{
	partial class AnglesDisplay
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		private System.Windows.Forms.Label lblState;
		private System.Windows.Forms.Label lblAccur;
		private System.Windows.Forms.Label lblYaw;
		private System.Windows.Forms.Label lblPitch;
		private System.Windows.Forms.Label lblRoll;
		private System.Windows.Forms.GroupBox groupBox1;
		
		/// <summary>
		/// Disposes resources used by the control.
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
			this.lblRoll = new System.Windows.Forms.Label();
			this.lblPitch = new System.Windows.Forms.Label();
			this.lblYaw = new System.Windows.Forms.Label();
			this.lblAccur = new System.Windows.Forms.Label();
			this.lblState = new System.Windows.Forms.Label();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// lblRoll
			// 
			this.lblRoll.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.lblRoll.Location = new System.Drawing.Point(6, 18);
			this.lblRoll.Name = "lblRoll";
			this.lblRoll.Size = new System.Drawing.Size(219, 33);
			this.lblRoll.TabIndex = 0;
			this.lblRoll.Text = "ROLL: N/A";
			// 
			// lblPitch
			// 
			this.lblPitch.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.lblPitch.Location = new System.Drawing.Point(6, 64);
			this.lblPitch.Name = "lblPitch";
			this.lblPitch.Size = new System.Drawing.Size(237, 33);
			this.lblPitch.TabIndex = 1;
			this.lblPitch.Text = "PITCH: N/A";
			// 
			// lblYaw
			// 
			this.lblYaw.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.lblYaw.Location = new System.Drawing.Point(6, 107);
			this.lblYaw.Name = "lblYaw";
			this.lblYaw.Size = new System.Drawing.Size(237, 33);
			this.lblYaw.TabIndex = 2;
			this.lblYaw.Text = "YAW: N/A";
			// 
			// lblAccur
			// 
			this.lblAccur.Location = new System.Drawing.Point(18, 149);
			this.lblAccur.Name = "lblAccur";
			this.lblAccur.Size = new System.Drawing.Size(100, 23);
			this.lblAccur.TabIndex = 3;
			this.lblAccur.Text = "Accuracy: N/A";
			// 
			// lblState
			// 
			this.lblState.Location = new System.Drawing.Point(18, 175);
			this.lblState.Name = "lblState";
			this.lblState.Size = new System.Drawing.Size(100, 23);
			this.lblState.TabIndex = 4;
			this.lblState.Text = "State: N/A";
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.lblState);
			this.groupBox1.Controls.Add(this.lblRoll);
			this.groupBox1.Controls.Add(this.lblAccur);
			this.groupBox1.Controls.Add(this.lblPitch);
			this.groupBox1.Controls.Add(this.lblYaw);
			this.groupBox1.Location = new System.Drawing.Point(3, 6);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(249, 204);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Angles";
			// 
			// AnglesDisplay
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.groupBox1);
			this.Name = "AnglesDisplay";
			this.Size = new System.Drawing.Size(269, 215);
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);

		}
	}
}
