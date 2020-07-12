using System;
using System.Threading;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Views.InputMethods;
using Android.Widget;
using MavLink;

namespace VisirApp2
{
    [Activity(Label = "TelescopeActivity")]
    public class TelescopeActivity : Activity
    {
        MeadeClass sky_viwer_obj = new MeadeClass();
        AstronomyClass astronomy_obj = new AstronomyClass();
        SettingsClass SettingsSaver = new SettingsClass();

        Timer timer;

        double CurrentRAHours = 0.0;
        double CurrentDecDeg = 0.0;
        double VertCorrection = 0.0;
        double TeleCalibAzimuth = 0.0;//deg

        protected override void OnDestroy()
        {
            base.OnDestroy();
            sky_viwer_obj.Close();
        }

        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            SetContentView(Resource.Layout.TelescopeLayout);
            //ActionBar.Hide();
            LoadSettings();
            BluetoothClass.MavlinkDataReceived += MavlinkDataReceivedHandlerMap;

            int num = 0;
            TimerCallback tm = new TimerCallback(TimerEvent);
            timer = new Timer(tm, num, 0, 1000);

            BluetoothClass.telescope_correction_yaw = TeleCalibAzimuth;

            EditText editTextVertCorr = FindViewById<EditText>(Resource.Id.editTextVertCorr);
            editTextVertCorr.Text = VertCorrection.ToString();
            editTextVertCorr.EditorAction += (sender, e) =>
            {
                if (e.ActionId == ImeAction.Done)
                {
                    InputMethodManager imm = (InputMethodManager)GetSystemService(Context.InputMethodService);
                    imm.HideSoftInputFromWindow(editTextVertCorr.WindowToken, HideSoftInputFlags.None);
                    string strNumber = editTextVertCorr.Text;
                    strNumber = strNumber.Replace('.', ',');
                    if (strNumber.Length == 0)
                        VertCorrection = 0;
                    else
                        VertCorrection = Convert.ToDouble(strNumber);
                    SettingsSaver.SaveVertCorrection(VertCorrection);
                }
            };

            EditText editTextCalibAzimuth = FindViewById<EditText>(Resource.Id.editTextCalibAzimuth);
            editTextCalibAzimuth.Text = TeleCalibAzimuth.ToString();
            editTextCalibAzimuth.EditorAction += (sender, e) =>
            {
                if (e.ActionId == ImeAction.Done)
                {
                    InputMethodManager imm = (InputMethodManager)GetSystemService(Context.InputMethodService);
                    imm.HideSoftInputFromWindow(editTextCalibAzimuth.WindowToken, HideSoftInputFlags.None);
                    string strNumber = editTextCalibAzimuth.Text;
                    strNumber = strNumber.Replace('.', ',');
                    if (strNumber.Length == 0)
                        TeleCalibAzimuth = 0;
                    else
                        TeleCalibAzimuth = Convert.ToDouble(strNumber);
                    SettingsSaver.SaveTeleCalibAzimuth(TeleCalibAzimuth);
                    BluetoothClass.telescope_correction_yaw = TeleCalibAzimuth;
                }
            };
        }

        private void TimerEvent(object state)
        {
            TextView txtServerState = FindViewById<TextView>(Resource.Id.txtServerState);
            txtServerState.Text = $"Sever State: {sky_viwer_obj.State}";
        }

        void LoadSettings()
        {
            double SavedUserLat;
            double SavedUserLon;
            double vertCorr;
            double teleCalibAzimuth;

            bool UserSavedOk = SettingsSaver.GetUserPos(out SavedUserLat, out SavedUserLon);
            SettingsSaver.GetVertCorr(out vertCorr);
            VertCorrection = vertCorr;

            SettingsSaver.GetTeleCalibAzimuth(out teleCalibAzimuth);
            TeleCalibAzimuth = teleCalibAzimuth;

            astronomy_obj.SetUserPosition(SavedUserLat, SavedUserLon);
        }

        public void UpdateCurrentPosition(double altitude_deg, double azimuth_deg)
        {
            altitude_deg += VertCorrection;
            astronomy_obj.CalculateEquatorialFromHorizontal(altitude_deg, azimuth_deg, out double ra_hours, out double dec_deg);
            CurrentRAHours = ra_hours;
            CurrentDecDeg = dec_deg;

            TextView txtRaHours = FindViewById<TextView>(Resource.Id.txtRaHours);
            txtRaHours.Text = $"RA: {CurrentRAHours:0.00} h";

            TextView txtDECDeg = FindViewById<TextView>(Resource.Id.txtDECDeg);
            txtDECDeg.Text = $"DEC: {CurrentDecDeg:0.00} deg";

            sky_viwer_obj.UpdateCurrentPos(CurrentRAHours, CurrentDecDeg);
        }

        private void MavlinkDataReceivedHandlerMap(MavlinkPacket packet)
        {
            if (packet.Message.GetType() == typeof(MavLink.Msg_mav_game_rotation_vector_euler))
            {
                Msg_mav_game_rotation_vector_euler game_angle = (MavLink.Msg_mav_game_rotation_vector_euler)packet.Message;
                UpdateCurrentPosition(game_angle.pitch, game_angle.yaw);
            }
        }
    }//end of class
}