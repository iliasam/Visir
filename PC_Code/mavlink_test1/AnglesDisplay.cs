using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace mavlink_test1
{
	public partial class AnglesDisplay : UserControl
	{
		euler_angles_class rotation_angles;
		
		public AnglesDisplay()
		{
			InitializeComponent();
			
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
			rotation_angles = new euler_angles_class();
		}
		
		public void update_angles(euler_angles_class new_angles)
		{
			rotation_angles = new_angles;
			
			lblRoll.Text = "ROLL: " + rotation_angles.roll.ToString("0.0") + " deg";
			lblPitch.Text = "PITCH: " + rotation_angles.pitch.ToString("0.0") + " deg";
			lblYaw.Text  = "YAW: " + rotation_angles.yaw.ToString("0.0") + " deg";
			
			lblAccur.Text = "Accuracy: " + rotation_angles.accuracy.ToString("0.0");
			lblState.Text = "State: " + rotation_angles.state.ToString();
		}
		
		public void update_name(string new_name)
		{
			groupBox1.Text = new_name;
		}
	}
}
