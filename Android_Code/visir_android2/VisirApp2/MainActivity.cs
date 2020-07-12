using System;
using Android.App;
using Android.Content;
using Android.Widget;
using Android.OS;
using Android.Util;
using MavLink;
using Android.Runtime;
using Xamarin.Essentials;

namespace VisirApp2
{
    [Activity(Label = "VisirApp2", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Activity
    {
        euler_angles_class rotation_angles;
        euler_angles_class game_rotation_angles;//gyro
        float battery_voltage = 0.0f;

        Intent mapIntent;
        Intent map2Intent;
        Intent telescopeIntent;

        Intent serviceBluetooth;

        PositionClass PositionObj;
        

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2140:TransparentMethodsMustNotReferenceCriticalCodeFxCopRule")]
        protected override void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            Xamarin.Essentials.Platform.Init(this, bundle);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);
            //ActionBar.Hide();

            PositionObj = new PositionClass();

            serviceBluetooth = new Intent(this, typeof(BluetoothClass));
            //serviceBluetooth.SetAction(Constants.ACTION_START_SERVICE);

            Button btnConnect = FindViewById<Button>(Resource.Id.btnConnect);
            btnConnect.Click += btnConnect_Click;

            Button btnSwitchToMap = FindViewById<Button>(Resource.Id.btnSwitchToMap);
            btnSwitchToMap.Click += btnSwitchToMap_Click;

            Button btnSwitchToGoogleMap = FindViewById<Button>(Resource.Id.btnSwitchToGoogleMap);
            btnSwitchToGoogleMap.Click += BtnSwitchToGoogleMap_Click; 

            Button btnTelescopeMode = FindViewById<Button>(Resource.Id.btnTelescopeMode);
            btnTelescopeMode.Click += btnSwitchToTelescope_Click;

            RadioButton rbSourceMap1 = FindViewById<RadioButton>(Resource.Id.rbSourceMap1);
            rbSourceMap1.CheckedChange += ChkSourceMap1_CheckedChange;

            RadioButton rbSourceTelescope = FindViewById<RadioButton>(Resource.Id.rbSourceTelescope);
            rbSourceTelescope.CheckedChange += RbSourceTelescope_CheckedChange;

            RadioButton rbSourceMap2 = FindViewById<RadioButton>(Resource.Id.rbSourceMap2);
            rbSourceMap2.CheckedChange += RbSourceMap2_CheckedChange;

            rotation_angles = new euler_angles_class();
            game_rotation_angles = new euler_angles_class();

            BluetoothClass.MavlinkDataReceived+= MavlinkDataReceivedHandlerMain;
        }

        

        //*****************************
        //Select Activity

        private void BtnSwitchToGoogleMap_Click(object sender, EventArgs e)
        {
            map2Intent = new Intent(this, typeof(ActivityMap2));
            StartActivity(map2Intent);
        }

        private void btnSwitchToTelescope_Click(object sender, EventArgs e)
        {
            telescopeIntent = new Intent(this, typeof(TelescopeActivity));
            StartActivity(telescopeIntent);
        }

        private void btnSwitchToMap_Click(object sender, EventArgs e)
        {
            mapIntent = new Intent(this, typeof(ActivityMap));
            StartActivity(mapIntent);
        }

        //*************************

        private void RbSourceTelescope_CheckedChange(object sender, CompoundButton.CheckedChangeEventArgs e)
        {
            if (FindViewById<RadioButton>(Resource.Id.rbSourceTelescope).Checked)
                BluetoothClass.correction_source = 2;//telescope
        }

        private void ChkSourceMap1_CheckedChange(object sender, CompoundButton.CheckedChangeEventArgs e)
        {
            if (FindViewById<RadioButton>(Resource.Id.rbSourceMap1).Checked)
                BluetoothClass.correction_source = 0;//map1
        }

        private void RbSourceMap2_CheckedChange(object sender, CompoundButton.CheckedChangeEventArgs e)
        {
            if (FindViewById<RadioButton>(Resource.Id.rbSourceMap2).Checked)
                BluetoothClass.correction_source = 1;//map2
        }

        public override void OnRequestPermissionsResult(int requestCode, string[] permissions, [GeneratedEnum] Android.Content.PM.Permission[] grantResults)
        {
            Xamarin.Essentials.Platform.OnRequestPermissionsResult(requestCode, permissions, grantResults);
            base.OnRequestPermissionsResult(requestCode, permissions, grantResults);
        }

        void UpdateMainScreen()
        {
            TextView txtYawGame = FindViewById<TextView>(Resource.Id.txtYawGame);
            TextView txtPitch = FindViewById<TextView>(Resource.Id.txtPitch);
            TextView txtBattery = FindViewById<TextView>(Resource.Id.txtBattery);

            txtYawGame.Text = $"Yaw (Game): {game_rotation_angles.yaw:0.0} deg";
            txtPitch.Text = $"Pitch: {game_rotation_angles.pitch:0.0} deg";
            txtBattery.Text = $"Battery: {battery_voltage:0.0} V";
        }

        

        private void btnConnect_Click(object sender, EventArgs e)
        {
            TextView txtState = FindViewById<TextView>(Resource.Id.txtState);

            txtState.Text = "Connected";
            StartService(serviceBluetooth);
        }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2140:TransparentMethodsMustNotReferenceCriticalCodeFxCopRule")]
        public void MavlinkDataReceivedHandlerMain(MavlinkPacket packet)
        {
            if (packet.Message.GetType() == typeof(MavLink.Msg_mav_game_rotation_vector_euler))
            {
                game_rotation_angles.update_from_mavlink((MavLink.Msg_mav_game_rotation_vector_euler)packet.Message);
                UpdateMainScreen();
            }
            else if (packet.Message.GetType() == typeof(MavLink.Msg_mav_batt_state))
            {
                MavLink.Msg_mav_batt_state battery_state = (MavLink.Msg_mav_batt_state)packet.Message;
                battery_voltage = battery_state.voltage;
            }
        }


    }//end
}

