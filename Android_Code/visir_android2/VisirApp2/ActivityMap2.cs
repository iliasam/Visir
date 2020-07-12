
using Android.App;
using Android.Content;
using Android.Gms.Maps;
using Android.Gms.Maps.Model;
using Android.Graphics;
using Android.OS;

using Android.Widget;
using Geodesy;
using MavLink;
using System;
using System.Reflection;

namespace VisirApp2
{
    [Activity(Label = "ActivityMap2")]
    public class ActivityMap2 : Activity, IOnMapReadyCallback, GoogleMap.IOnMapClickListener
    {
        double line_length = 10000;//meters

        double currVisirDirDegMap2 = 0.0;//current visir direction
        double VisirTargetDirDegMap2 = 0.0;//visir target direction

        const double DEG_IN_RAD = 57.295779;

        public GlobalCoordinates UserPosition;
        public GlobalCoordinates CalibPosition;
        public GlobalCoordinates TargetPosition;

        private System.Timers.Timer UpdateTimer;

        GeodeticCalculator geo_calc = new GeodeticCalculator(Ellipsoid.WGS84);

        bool is_initialized = false;
        bool TimerFirstStart = true;
        bool DirectionChanged = false;

        private GoogleMap googleMap;
        Polyline MainLine;
        Marker UserMarker;
        Marker CalibMarker;
        Marker TargetMarker;
        SettingsClass SettingsSaver = new SettingsClass();

        public static Action<double> SetTargetAngleEvent;//callback - new set target event

        //*********************************************************8

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2140:TransparentMethodsMustNotReferenceCriticalCodeFxCopRule")]
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            SetContentView(Resource.Layout.Map2Layout);
            //ActionBar.Hide();

            UserPosition = new GlobalCoordinates(55.83231, 37.29907);
            CalibPosition = new GlobalCoordinates(55.832, 37.29907);
            LoadSettins();

            InitMap();

             is_initialized = true;
            //***********************************

            BluetoothClass.MavlinkDataReceived += MavlinkDataReceivedHandlerMap2;

            PositionClass.NewGPSPosition += NewGPSPositionEvent;

            Button btnUseGPS = FindViewById<Button>(Resource.Id.btnUseGPS);
            btnUseGPS.Click += BtnUseGPS_Click;

            CheckBox chkTarget = FindViewById<CheckBox>(Resource.Id.chkTarget);
            chkTarget.CheckedChange += ChkTarget_CheckedChange;

            BluetoothClass.map2_correction_yaw = get_direction(CalibPosition);
        }

        private void ChkTarget_CheckedChange(object sender, CompoundButton.CheckedChangeEventArgs e)
        {
            if (e.IsChecked == false)
            {
                UpdateTargetPoint(false);
            }
            else
            {
                UpdateTargetPoint(true);
            }
        }

        private void NewGPSPositionEvent(double accuracy)
        {
            Button btnUseGPS = FindViewById<Button>(Resource.Id.btnUseGPS);
            btnUseGPS.Text = $"GPS: {accuracy}";
        }

        private void BtnUseGPS_Click(object sender, EventArgs e)
        {
            if (PositionClass.CurrentGPSAccuracy < 100)
            {
                UserPosition.Latitude = PositionClass.UserGPSPosition.Latitude.Degrees;
                UserPosition.Longitude = PositionClass.UserGPSPosition.Longitude.Degrees;
                UpdateUserPosPoints();
                DrawDirection(currVisirDirDegMap2);
            }
        }

        public void OnMapReady(GoogleMap map)
        {
            googleMap = map;
            googleMap.MyLocationEnabled = true;
            googleMap.AnimateCamera(CameraUpdateFactory.NewLatLngZoom(ConvertPos(UserPosition), 16));
            googleMap.UiSettings.RotateGesturesEnabled = false;
            googleMap.UiSettings.ZoomControlsEnabled = true;
            googleMap.SetOnMapClickListener(this);

            RunOnUiThread(() => {
                DrawDirection(45);
            });

            UpdateUserPosPoints();
            UpdateCalibPoints();

            UpdateTimer = new System.Timers.Timer(3000);
            UpdateTimer.Elapsed += UpdateTimer_Elapsed;
            UpdateTimer.AutoReset = true;
            UpdateTimer.Enabled = true;
            TimerFirstStart = true;
        }

        private void UpdateTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            if (TimerFirstStart)
            {
                TimerFirstStart = false;
                UpdateTimer.Interval = 200;
                UpdateTimer.Enabled = false;
                UpdateTimer.Enabled = true;
            }
            else if (DirectionChanged)
            {
                UpdateTimer.Enabled = false;
                RunOnUiThread(() => {
                    DrawDirection(currVisirDirDegMap2);
                });
                DirectionChanged = false;
                UpdateTimer.Enabled = true;
            }
        }

        void InitMap()
        {
            var mapFragment = (MapFragment)FragmentManager.FindFragmentById(Resource.Id.map);
            mapFragment.GetMapAsync(this);
        }

        /// <summary>
        /// Event generated by map
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void OnMapClick(LatLng point)
        {
            CheckBox chkCalibOn = FindViewById<CheckBox>(Resource.Id.chkCalibOn);
            CheckBox chkUserOn = FindViewById<CheckBox>(Resource.Id.chkUserOn);
            CheckBox chkTarget = FindViewById<CheckBox>(Resource.Id.chkTarget);

            if (chkCalibOn.Checked)
            {
                //recalculate calib point position
                CalibPosition = new GlobalCoordinates(point.Latitude, point.Longitude);
                UpdateCalibPoints();
                SaveSettings();
            }
            else if (chkUserOn.Checked)
            {
                //set user position
                UserPosition = new GlobalCoordinates(point.Latitude, point.Longitude);
                UpdateUserPosPoints();
                SettingsSaver.SaveUserPos(UserPosition.Latitude.Degrees, UserPosition.Longitude.Degrees);
            }
            else if (chkTarget.Checked)
            {
                TargetPosition = new GlobalCoordinates(point.Latitude, point.Longitude);
                UpdateTargetPoint(true);
            }
        }

        /// <summary>
        /// Event from bluetooth device
        /// </summary>
        /// <param name="packet"></param>
        private void MavlinkDataReceivedHandlerMap2(MavlinkPacket packet)
        {
            if (packet.Message.GetType() == typeof(MavLink.Msg_mav_game_rotation_vector_euler))
            {
                Msg_mav_game_rotation_vector_euler game_angle = (MavLink.Msg_mav_game_rotation_vector_euler)packet.Message;
               UpdateVisirDirection(game_angle.yaw);
            }
            /*
            if (packet.Message.GetType() == typeof(MavLink.Msg_mav_rotation_vector_euler))
            {
                Msg_mav_rotation_vector_euler rotation_angle = (MavLink.Msg_mav_rotation_vector_euler)packet.Message;
            }
            */
            else if (packet.Message.GetType() == typeof(MavLink.Msg_mav_button_event))
            {
                parse_keys_event((MavLink.Msg_mav_button_event)packet.Message);
            }
        }

        void parse_keys_event(MavLink.Msg_mav_button_event msg)
        {

        }

        void UpdateVisirDirection(double angle)
        {
            currVisirDirDegMap2 = angle;
            DirectionChanged = true;
        }

        /// <summary>
        /// Draw main direction line
        /// </summary>
        /// <param name="angle"></param>
        public void DrawDirection(double angle)
        {
            if (is_initialized == false)
                return;

            GlobalCoordinates stop_geo = get_line_position(angle);
            try
            {
                if (MainLine != null)
                {
                    MainLine.Remove();
                    PolylineOptions linePoints = new PolylineOptions();
                    linePoints.Add(ConvertPos(UserPosition));
                    linePoints.Add(ConvertPos(stop_geo));
                    MainLine = googleMap.AddPolyline(linePoints);
                }
                else
                {
                    PolylineOptions linePoints = new PolylineOptions();
                    linePoints.Add(ConvertPos(UserPosition));
                    linePoints.Add(ConvertPos(stop_geo));
                    MainLine = googleMap.AddPolyline(linePoints);
                }
            }
            catch (Exception e)
            {

            }

            
        }

       

        void UpdateUserPosPoints()
        {
            if (UserMarker != null)
                UserMarker.Remove();

            var icon = BitmapDescriptorFactory.DefaultMarker(BitmapDescriptorFactory.HueRed);
            var markerOptions = new MarkerOptions()
                                .SetPosition(ConvertPos(UserPosition))
                                .SetIcon(icon)
                                .SetSnippet($"User")
                                .SetTitle($"User");
            UserMarker = googleMap.AddMarker(markerOptions);
        }

        void UpdateCalibPoints()
        {
            if (CalibMarker != null)
                CalibMarker.Remove();

            var icon = BitmapDescriptorFactory.DefaultMarker(BitmapDescriptorFactory.HueBlue);
            var markerOptions = new MarkerOptions()
                                .SetPosition(ConvertPos(CalibPosition))
                                .SetIcon(icon)
                                .SetSnippet($"Calib")
                                .SetTitle($"Calib");
            CalibMarker = googleMap.AddMarker(markerOptions);

            //update direction
            BluetoothClass.map2_correction_yaw = get_direction(CalibPosition);
        }

        void UpdateTargetPoint(bool Visible)
        {
            if (TargetMarker != null)
                TargetMarker.Remove();

            if (Visible == false)
            {
                SetTargetAngleEvent?.Invoke(-1);
                return; //markey removed
            }
                

            var icon = BitmapDescriptorFactory.DefaultMarker(BitmapDescriptorFactory.HueOrange);
            var markerOptions = new MarkerOptions()
                                .SetPosition(ConvertPos(TargetPosition))
                                .SetIcon(icon)
                                .SetSnippet($"Target")
                                .SetTitle($"Target");
            TargetMarker = googleMap.AddMarker(markerOptions);

            VisirTargetDirDegMap2 = get_direction(TargetPosition);
            SetTargetAngleEvent?.Invoke(VisirTargetDirDegMap2);
        }





        /// <summary>
        /// Прямая геодезическая задача
        /// </summary>
        /// <param name="angle">Азимут визира</param>
        /// <returns></returns>
        GlobalCoordinates get_line_position(double angle)
        {
            GlobalCoordinates start = UserPosition;
            GlobalCoordinates end = geo_calc.CalculateEndingGlobalCoordinates(start, angle, line_length);

            return end;
        }

        /// <summary>
        /// Обратная геодезическая задача
        /// </summary>
        /// <param name="end_point"></param>
        /// <returns>Азимут точки</returns>
        double get_direction(GlobalCoordinates end_point)
        {
            GlobalCoordinates start = UserPosition;
            GlobalCoordinates end = new GlobalCoordinates(end_point.Latitude.Degrees, end_point.Longitude.Degrees);
            GeodeticCurve curve = geo_calc.CalculateGeodeticCurve(start, end);
            return curve.Azimuth.Degrees;
        }

        //*******************************************************************

        void LoadSettins()
        {
            double SavedCalibLat;
            double SavedCalibLon;
            bool CalibSavedOk = SettingsSaver.GetCalib(out SavedCalibLat, out SavedCalibLon);

            if (CalibSavedOk)
            {
                CalibPosition = new GlobalCoordinates(SavedCalibLat, SavedCalibLon);
            }

            double SavedUserLat;
            double SavedUserLon;
            bool UserSavedOk = SettingsSaver.GetUserPos(out SavedUserLat, out SavedUserLon);
            if (UserSavedOk)
            {
                UserPosition = new GlobalCoordinates(SavedUserLat, SavedUserLon);
            }
        }

        void SaveSettings()
        {
            SettingsSaver.SaveCalib(CalibPosition.Latitude.Degrees, CalibPosition.Longitude.Degrees);
        }

        LatLng ConvertPos(GlobalCoordinates pos)
        {
            return new LatLng(pos.Latitude.Degrees, pos.Longitude.Degrees);
        }

        
    }
}