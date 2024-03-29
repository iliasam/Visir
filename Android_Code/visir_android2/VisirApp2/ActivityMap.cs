﻿
using Android.App;
using Android.Content;
using Android.Graphics;
using Android.OS;

using Android.Widget;
using BruTile;
using BruTile.Predefined;
using BruTile.Web;
using Geodesy;
using Mapsui;
using Mapsui.Geometries;
using Mapsui.Layers;
using Mapsui.Projection;
using Mapsui.Providers;
using Mapsui.Styles;
using Mapsui.UI.Android;
using Mapsui.Utilities;
using Mapsui.Widgets.ScaleBar;
using Mapsui.Widgets.Zoom;
using MavLink;
using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Reflection;

namespace VisirApp2
{
    [Activity(Label = "ActivityMap")]
    public class ActivityMap : Activity
    {
        double line_length = 10000;//meters

        double currVisirDirGeg = 0.0;//current visir direction

        const double DEG_IN_RAD = 57.295779;

        public GlobalCoordinates UserPosition;
        public GlobalCoordinates CalibPosition;

        GeodeticCalculator geo_calc = new GeodeticCalculator(Ellipsoid.WGS84);

        bool is_initialized = false;

        private MapControl _mapControl;
        MemoryLayer lineLayer;
        MemoryLayer UserPosPointsLayer;
        MemoryLayer CalibPointsLayer;
        SettingsClass SettingsSaver = new SettingsClass();

        public static Action<double> CalibrationAngleEvent;//callback - new calibration event



        //*********************************************************8

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2140:TransparentMethodsMustNotReferenceCriticalCodeFxCopRule")]
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            SetContentView(Resource.Layout.MapLayout);
            //ActionBar.Hide();

            UserPosition = new GlobalCoordinates(55.83231, 37.29907);
            CalibPosition = new GlobalCoordinates(55.832, 37.29907);
            LoadSettins();

            InitMap();

             is_initialized = true;
            //***********************************

            DrawDirection(45);
            UpdateUserPosPoints();
            UpdateCalibPoints();

            BluetoothClass.MavlinkDataReceived += MavlinkDataReceivedHandlerMap;

            PositionClass.NewGPSPosition += NewGPSPositionEvent;

            Button btnUseGPS = FindViewById<Button>(Resource.Id.btnUseGPS);
            btnUseGPS.Click += BtnUseGPS_Click;

            BluetoothClass.map1_correction_yaw = get_direction(CalibPosition);
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
                DrawDirection(currVisirDirGeg);
            }
        }

        void InitMap()
        {
            //MAP
            _mapControl = FindViewById<MapControl>(Resource.Id.mapControl1);

            var httpClient = new HttpClient();
            httpClient.DefaultRequestHeaders.Add("User-Agent", "VisirApp");
            var osmAttribution = new Attribution("© OpenStreetMap contributors", "https://www.openstreetmap.org/copyright");
            var osmSource = new HttpClientTileSource(httpClient, new GlobalSphericalMercator(), 
                "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", new[] { "a", "b", "c" }, 
                name: "OpenStreetMap", attribution: osmAttribution);
            var osmLayer = new TileLayer(osmSource) { Name = "OpenStreetMap" };

            Map map = new Map();
            //map.Layers.Add(OpenStreetMap.CreateTileLayer());
            map.Layers.Add(osmLayer);

            var sphericalMercatorCoordinate = SphericalMercator.FromLonLat(UserPosition.Longitude.Degrees, UserPosition.Latitude.Degrees);
            map.NavigateTo(sphericalMercatorCoordinate);
            map.NavigateTo(map.Resolutions[15]);

            _mapControl.Map = map;

            map.Widgets.Add(new ZoomInOutWidget(map) { MarginX = 20, MarginY = 20, HorizontalAlignment = Mapsui.Widgets.HorizontalAlignment.Left, VerticalAlignment = Mapsui.Widgets.VerticalAlignment.Top });
            map.Widgets.Add(new Mapsui.Widgets.ScaleBar.ScaleBarWidget(map) { TextAlignment = Mapsui.Widgets.Alignment.Center, HorizontalAlignment = Mapsui.Widgets.HorizontalAlignment.Center, VerticalAlignment = Mapsui.Widgets.VerticalAlignment.Top });

            lineLayer = new MemoryLayer
            {
                //DataSource = new MemoryProvider(feature),
                Name = "LineStringLayer",
                Style = CreateLineStringStyle(),
            };

            UserPosPointsLayer = new MemoryLayer
            {
                Name = "UserPoint",
                Style = CreateUserPinStyle(),
            };

            CalibPointsLayer = new MemoryLayer
            {
                Name = "CalibPoints",
                Style = CreateCalibPinStyle(),
            };

            map.Layers.Add(lineLayer);
            map.Layers.Add(UserPosPointsLayer);
            map.Layers.Add(CalibPointsLayer);

            map.Info += Map_Info;
        }




        /// <summary>
        /// Event generated by map
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Map_Info(object sender, Mapsui.UI.MapInfoEventArgs e)
        {
            CheckBox chkCalibOn = FindViewById<CheckBox>(Resource.Id.chkCalibOn);
            CheckBox chkUserOn = FindViewById<CheckBox>(Resource.Id.chkUserOn);

            if (chkCalibOn.Checked)
            {
                //recalculate calib point position
                Mapsui.Geometries.Point p = SphericalMercator.ToLonLat(e.MapInfo.WorldPosition.X, e.MapInfo.WorldPosition.Y);
                CalibPosition = new GlobalCoordinates(p.Y, p.X);
                UpdateCalibPoints();
                SaveSettings();
                _mapControl.Refresh();
            }
            else if (chkUserOn.Checked)
            {
                //set user position
                Mapsui.Geometries.Point p = SphericalMercator.ToLonLat(e.MapInfo.WorldPosition.X, e.MapInfo.WorldPosition.Y);
                UserPosition = new GlobalCoordinates(p.Y, p.X);
                UpdateUserPosPoints();
                SettingsSaver.SaveUserPos(UserPosition.Latitude.Degrees, UserPosition.Longitude.Degrees);
                _mapControl.Refresh();
            }
        }

        /// <summary>
        /// Event from bluetooth device
        /// </summary>
        /// <param name="packet"></param>
        private void MavlinkDataReceivedHandlerMap(MavlinkPacket packet)
        {
            CheckBox chkMagnOn = FindViewById<CheckBox>(Resource.Id.chkMagnetic);

            if (packet.Message.GetType() == typeof(MavLink.Msg_mav_game_rotation_vector_euler))
            {
                Msg_mav_game_rotation_vector_euler game_angle = (MavLink.Msg_mav_game_rotation_vector_euler)packet.Message;
                if (chkMagnOn.Checked == false)
                {
                    currVisirDirGeg = game_angle.yaw;
                    DrawDirection(currVisirDirGeg);
                }
                
            }
            if (packet.Message.GetType() == typeof(MavLink.Msg_mav_rotation_vector_euler))
            {
                Msg_mav_rotation_vector_euler rotation_angle = (MavLink.Msg_mav_rotation_vector_euler)packet.Message;
                if (chkMagnOn.Checked == true)
                {
                    currVisirDirGeg = rotation_angle.yaw;
                    DrawDirection(currVisirDirGeg);
                }
            }
            else if (packet.Message.GetType() == typeof(MavLink.Msg_mav_button_event))
            {
                parse_keys_event((MavLink.Msg_mav_button_event)packet.Message);
            }
        }

        void parse_keys_event(MavLink.Msg_mav_button_event msg)
        {
            if (true) //Здесь может быть проверка режима работы устройства
            {
                /*
                 if ((msg.button_code == 2) && (msg.event_code == 2))//event_code == 2
                {
                 //menu button pressed
                 CalibYaw = get_direction(CalibPosition);
                 CalibrationAngleEvent?.Invoke(CalibYaw);
                }
                 * */
            }
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

            LineString line = new LineString();
            var point_start = SphericalMercator.FromLonLat(UserPosition.Longitude.Degrees, UserPosition.Latitude.Degrees);
            var point_stop = SphericalMercator.FromLonLat(stop_geo.Longitude.Degrees, stop_geo.Latitude.Degrees);
            line.Vertices.Add(point_start);
            line.Vertices.Add(point_stop);

            var feature = new Feature();
            feature.Geometry = line;

            lineLayer.DataSource = new MemoryProvider(feature);
            _mapControl.Refresh();
        }

        public static IStyle CreateLineStringStyle()
        {
            return new VectorStyle
            {
                Fill = null,
                Outline = null,
                Line = { Color = Mapsui.Styles.Color.Red, Width = 2, PenStyle = PenStyle.Solid}
            };
        }

        void UpdateUserPosPoints()
        {
            var feature = new Feature();
            var point = SphericalMercator.FromLonLat(UserPosition.Longitude.Degrees, UserPosition.Latitude.Degrees);

            feature.Geometry = point;
            feature["name"] = "User";

            UserPosPointsLayer.DataSource = new MemoryProvider(feature);
        }

        void UpdateCalibPoints()
        {
            //update map
            var feature = new Feature();
            var point = SphericalMercator.FromLonLat(CalibPosition.Longitude.Degrees, CalibPosition.Latitude.Degrees);

            feature.Geometry = point;
            feature["name"] = "Calib";

            CalibPointsLayer.DataSource = new MemoryProvider(feature);

            //update direction
            BluetoothClass.map1_correction_yaw = get_direction(CalibPosition);
        }

        private static SymbolStyle CreateUserPinStyle()
        {
            var path = "VisirApp2.Resources.drawable.pin2.png";// ‘embedded resource‘ in settings
            var bitmapId = GetBitmapIdForEmbeddedResource(path);
            var bitmapHeight = 32; // To set the offset correct we need to know the bitmap height
            return new SymbolStyle { BitmapId = bitmapId, SymbolScale = 1.0, SymbolOffset = new Offset(0, bitmapHeight * 0.5) };
        }

        private static SymbolStyle CreateCalibPinStyle()
        {
            var path = "VisirApp2.Resources.drawable.pin3.png";// ‘embedded resource‘ in settings
            var bitmapId = GetBitmapIdForEmbeddedResource(path);
            var bitmapHeight = 32; // To set the offset correct we need to know the bitmap height
            return new SymbolStyle { BitmapId = bitmapId, SymbolScale = 1.0, SymbolOffset = new Offset(0, bitmapHeight * 0.5) };
        }

        private static int GetBitmapIdForEmbeddedResource(string imagePath)
        {
            var assemblyName = new AssemblyName("VisirApp2");
            var resources = string.Join(System.Environment.NewLine, Assembly.Load(assemblyName).GetManifestResourceNames());
            Console.WriteLine("List of Manifest Resource Names");
            Console.WriteLine("======================");
            Console.WriteLine(resources);

            var assembly = typeof(ActivityMap).GetTypeInfo().Assembly;
            var image = assembly.GetManifestResourceStream(imagePath);
            return BitmapRegistry.Instance.Register(image);
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
    }//end of class

    internal class HttpClientTileSource : ITileSource
    {
        private readonly HttpClient _HttpClient;
        private readonly HttpTileSource _WrappedSource;

        public HttpClientTileSource(HttpClient httpClient, ITileSchema tileSchema, string urlFormatter, IEnumerable<string> serverNodes = null, string apiKey = null, string name = null, BruTile.Cache.IPersistentCache<byte[]> persistentCache = null, Attribution attribution = null)
        {
            _HttpClient = httpClient ?? throw new ArgumentNullException(nameof(httpClient));
            _WrappedSource = new HttpTileSource(tileSchema, urlFormatter, serverNodes, apiKey, name, persistentCache, ClientFetch, attribution);
        }

        public ITileSchema Schema => _WrappedSource.Schema;

        public string Name => _WrappedSource.Name;

        public Attribution Attribution => _WrappedSource.Attribution;

        public byte[] GetTile(TileInfo tileInfo) => _WrappedSource.GetTile(tileInfo);

        private byte[] ClientFetch(Uri uri) => _HttpClient.GetByteArrayAsync(uri).ConfigureAwait(false).GetAwaiter().GetResult();
    }
}