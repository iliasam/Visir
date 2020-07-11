using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using MavLink;
using System.Numerics;
using GMap.NET;


namespace mavlink_test1
{
	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class MainForm : Form
	{
        const float SQR2 = 0.7071067812f;
        
	    int rx_cnt = 0;

        enum VisirState_t
        {
            IDLE = 0,
            YAW_CALIBRATION,
        }

        struct type_item
		{
			public int count;
			public string name;
		};

        SerialWorkerClass2 serial_worker;
        Mavlink mavlink_obj;
        euler_angles_class rotation_angles;
        euler_angles_class game_rotation_angles;//gyro

        euler_angles_class rotation_angles_t1;
        Quaternion raw_quaternion;

        List<type_item> mav_types = new List<type_item>();

        VisirState_t visir_state = VisirState_t.IDLE;

        NMEAPublisherClass NMEAPublisherObj;

        //$GPHDT,123.456,T*00

        public MainForm()
		{
			InitializeComponent();
			
			comboBox_ports.Items.Clear();
			serial_worker = new SerialWorkerClass2(Application.StartupPath + @"\config.ini");
			serial_worker.AnswerReceived = SerialPortReceivedHandler;
			serial_worker.SerialFailSignal = SerialFailSignal_function;
			
			string serial = serial_worker.settings_holder.GetSetting("SERIAL_SETTINGS", "serial");
			if (comboBox_ports.Items.Count == 0) {
				comboBox_ports.Items.Add(serial);
				comboBox_ports.SelectedItem = comboBox_ports.Items[0];//нашелся хотя бы один порт
			}
			
			rotation_angles = new euler_angles_class();
            game_rotation_angles = new euler_angles_class();
            rotation_angles_t1 = new euler_angles_class();

            mavlink_obj = new Mavlink();
			mavlink_obj.PacketReceived+= new PacketReceivedEventHandler(ProcessRxMavlinkPacket);
			
			anglesDisplayRotation.update_name("Rotation vector");
            anglesDisplay1.update_name("Gyro vector");

            NMEAPublisherObj = new NMEAPublisherClass();
            NMEAPublisherObj.Start();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        public void SerialPortReceivedHandler(byte[] received_data)
		{
			mavlink_obj.ParseBytes(received_data);
		}
		
		void SerialFailSignal_function(bool state)
		{
		
		}
		
		public void ProcessRxMavlinkPacket(object sender, MavlinkPacket e)
		{
			//System.Diagnostics.Debug.WriteLine("number", e.SequenceNumber.ToString());
			
			if (e.Message.GetType() == typeof(MavLink.Msg_mav_rotation_vector_euler)) 
			{
				Invoke((MethodInvoker)delegate()
				{
				    rx_cnt++;
				    rotation_angles.update_from_mavlink((MavLink.Msg_mav_rotation_vector_euler)e.Message);
				    anglesDisplayRotation.update_angles(rotation_angles);
                    if (chkUseGyro.Checked == false)
                        mapControl1.draw_direction(rotation_angles.yaw);
                });
			}
			if (e.Message.GetType() == typeof(MavLink.Msg_mav_quaternion)) 
			{
				Invoke((MethodInvoker)delegate()
				{
				    rx_cnt++;
				    MavLink.Msg_mav_quaternion m_quaternion = (MavLink.Msg_mav_quaternion)e.Message;
                    raw_quaternion = new Quaternion(m_quaternion.x, m_quaternion.y, m_quaternion.z, m_quaternion.w);
                    lblRawQuaternion.Text = $"Raw Quat: X={raw_quaternion.X:0.0000} Y={raw_quaternion.Y:0.0000} Z={raw_quaternion.Z:0.0000}  W={raw_quaternion.W:0.0000}";

                    rotation_angles_t1.update_from_quaternion(raw_quaternion);
                    //anglesDisplay1.update_angles(rotation_angles_t1);
                });
			}
            if (e.Message.GetType() == typeof(MavLink.Msg_mav_game_rotation_vector_euler))
            {
                Invoke((MethodInvoker)delegate ()
                {
                    rx_cnt++;
                    game_rotation_angles.update_from_mavlink((MavLink.Msg_mav_game_rotation_vector_euler)e.Message);
                    anglesDisplay1.update_angles(game_rotation_angles);
                    if (chkUseGyro.Checked == true)
                        mapControl1.draw_direction(game_rotation_angles.yaw);
                    NMEAPublisherObj.CurrentAngle = game_rotation_angles.yaw;
                });
            }
            if (e.Message.GetType() == typeof(MavLink.Msg_mav_button_event))
            {
                Invoke((MethodInvoker)delegate ()
                {
                    rx_cnt++;
                    parse_keys_event((MavLink.Msg_mav_button_event)e.Message);
                });
            }
            if (e.Message.GetType() == typeof(MavLink.Msg_mav_batt_state))
            {
                Invoke((MethodInvoker)delegate ()
                {
                    rx_cnt++;
                    MavLink.Msg_mav_batt_state msg = (MavLink.Msg_mav_batt_state)e.Message;
                    lblBattery.Text = $"Battery: {msg.voltage:0.00} V";
                });
            }

            statistic_analyse(e.Message.GetType().ToString());
		}

        void parse_keys_event(MavLink.Msg_mav_button_event msg)
        {
            //if (visir_state == VisirState_t.YAW_CALIBRATION)
            if (true)
            {
                if ((msg.button_code == 2) && (msg.event_code == 2))
                {
                    //menu button pressed
                    calculate_yaw_correction();
                }
            }
        }
		
		void statistic_analyse(string str)
		{
			bool found = false;
			for( int i = 0; i < mav_types.Count; i++ )
			{
				if (mav_types[i].name == str)
				{
					type_item tmp_item = mav_types[i];
					tmp_item.count++;
					mav_types[i] = tmp_item;
					found = true;
				}
			}
			if (found == false)
			{
				type_item new_item;
				new_item.name = str;
				new_item.count = 1;
				mav_types.Add(new_item);
			}
		}
		
		void update_table()
		{
			if (dataGridView1.Rows.Count < mav_types.Count)
			{
				dataGridView1.Rows.Clear();
				
				int i = 0;
				for(i = 0; i < mav_types.Count; i++ )
				{
					dataGridView1.Rows.Add();
					dataGridView1.Rows[i].Cells[0].Value = mav_types[i].name;
					dataGridView1.Rows[i].Cells[1].Value = mav_types[i].count.ToString();
				}
			}
			else
			{
				int i = 0;
				for(i = 0; i < mav_types.Count; i++ )
				{
					dataGridView1.Rows[i].Cells[0].Value = mav_types[i].name;
					dataGridView1.Rows[i].Cells[1].Value = mav_types[i].count.ToString();
				}
			}
		}
		
		void BtnOpenClick(object sender, EventArgs e)
		{
			// If we have opened port - just close it and make necessary things
			if (serial_worker.ConnectionState == true) {
				serial_worker.ClosePort();
				
				btnOpen.Text = "Open";
				// Exit
				return;
			}

			// Try to open selected COM port
			string port_name = serial_worker.GetSerialName(comboBox_ports.Text);
			int result = serial_worker.OpenSerialPort(port_name, 9600);
			if (result == 1)
			{
				btnOpen.Text = "Close";
			}
		}
		
		void update_port_list()
		{
			comboBox_ports.Items.Clear();
			List<String> port_names = serial_worker.GetSerialPortInfo();
			foreach (string s in port_names)
			{
				comboBox_ports.Items.Add(s);
			}
			
			if (port_names.Count == 0) {
				MessageBox.Show("No serial ports in system!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			} else {
				comboBox_ports.SelectedItem = comboBox_ports.Items[0];//нашелся хотя бы один порт
			}
		}
		
		void ComboBox_portsDropDown(object sender, EventArgs e)
		{
			update_port_list();
		}
		
		void Timer1Tick(object sender, EventArgs e)
		{
			update_table();
		}
		
		
		void BtnRequestInfoClick(object sender, EventArgs e)
		{
			/*
			MavLink.Msg_mav_curtains_cmd mav_msg = new MavLink.Msg_mav_curtains_cmd();
			
			mav_msg.command = (byte)MavLink.MAV_CURTAINS_DRIVE_STATE.CLOSE;
			
			var mvp = new MavlinkPacket
                  {
                      ComponentId = 1,
                      SystemId = 1,//PC
                      Message = mav_msg
                  };
			send_mavlink_paket(mvp);
			*/
		}

        void sent_mavlink_yaw_correction(byte vect_type, float correction)
        {
            MavLink.Msg_mav_set_yaw_correction mav_msg = new MavLink.Msg_mav_set_yaw_correction();

            mav_msg.vector_type = vect_type;
            mav_msg.value = correction;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            send_mavlink_paket(mvp);
        }

        void send_mavlink_paket(MavlinkPacket packet)
		{
			byte[] data_to_send = mavlink_obj.Send(packet);
			serial_worker.send_bin_data_to_serial(data_to_send);
		}

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
        }

        private void btnSetCalibration_Click(object sender, EventArgs e)
        {
            mapControl1.start_set_calibration_pos();
        }

        private void btnStartCalibration_Click(object sender, EventArgs e)
        {
            visir_state = VisirState_t.YAW_CALIBRATION;
            sent_mavlink_yaw_correction(0, 0.0f);
            sent_mavlink_yaw_correction(1, 0.0f);
        }

        void calculate_yaw_correction()
        {
            double real_angle = mapControl1.CalibYaw;

            double rot_vect_yaw = rotation_angles.yaw;
            double game_vect_yaw = game_rotation_angles.yaw;

            double rot_vect_corr = real_angle - rot_vect_yaw;
            double game_vect_corr = real_angle - game_vect_yaw;

            //sent_mavlink_yaw_correction(0, (float)rot_vect_corr);
            //sent_mavlink_yaw_correction(1, (float)game_vect_corr);

            sent_mavlink_yaw_correction(255, (float)real_angle);
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            serial_worker.Destroy();
            NMEAPublisherObj.Stop();
        }

        private void BtnSetUserPoint_Click(object sender, EventArgs e)
        {
            mapControl1.start_set_user_pos();
        }
    }//end of class
}
