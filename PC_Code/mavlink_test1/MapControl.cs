using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using GMap.NET;
using GMap.NET.WindowsForms;
using Geodesy;
using GMap.NET.WindowsForms.Markers;
using GMap.NET.MapProviders;
using System.Net;

namespace mavlink_test1
{
    public partial class MapControl : UserControl
    {
        enum MouseMode_t
        {
            IDLE = 0,
            SET_CALIB_MARKER,
            SET_USER_MARKER,
        }

        double line_length = 5000;//meters

        const double DEG_IN_RAD = 57.295779;

        public PointLatLng UserPosition;
        PointLatLng CalibPosition;

        public double CalibYaw;//Угол в градусах для калибрационой точки

        bool is_initialized = false;

        GeodeticCalculator geo_calc = new GeodeticCalculator(Ellipsoid.WGS84);
        MouseMode_t mouse_mode = MouseMode_t.IDLE;

        public MapControl()
        {
            InitializeComponent();

            gMapControl1.Bearing = 0;
            gMapControl1.CanDragMap = true;
            gMapControl1.MaxZoom = 18;
            gMapControl1.Zoom = 16;
            gMapControl1.MouseWheelZoomType = GMap.NET.MouseWheelZoomType.MousePositionAndCenter;
            gMapControl1.NegativeMode = false;
            gMapControl1.DragButton = MouseButtons.Left;

            GMapProvider.WebProxy = WebRequest.GetSystemWebProxy();
            GMapProvider.WebProxy.Credentials = CredentialCache.DefaultNetworkCredentials;

            //gMapControl1.MapProvider = GMap.NET.MapProviders.GMapProviders.GoogleMap;
            gMapControl1.MapProvider = GMap.NET.MapProviders.GMapProviders.OpenStreetMap;

            GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerAndCache;

            
            GMapOverlay polyOverlay = new GMapOverlay("polygons");
            gMapControl1.Overlays.Add(polyOverlay);//[0]

            GMapOverlay markerOverlay = new GMapOverlay("markers");
            gMapControl1.Overlays.Add(markerOverlay);//[1]


            if (Properties.Settings1.Default.CabibrationLat != 0.0)
            {
                PointLatLng marker = new PointLatLng(Properties.Settings1.Default.CabibrationLat, Properties.Settings1.Default.CabibrationLon);
                SetCalibrationMarker(marker);
            }

            PointLatLng marker_user;
            if (Properties.Settings1.Default.UserLat != 0.0)
            {
                marker_user = new PointLatLng(Properties.Settings1.Default.UserLat, Properties.Settings1.Default.UserLon);
            }
            else
            {
                marker_user = new PointLatLng(45.356219, 36.467378);
            }
            SetUserMarker(marker_user);

            UserPosition = new PointLatLng(UserPosition.Lat, UserPosition.Lng);
            gMapControl1.Position = UserPosition;

            UpdateMarkers();


            is_initialized = true;
        }

        public void draw_direction(double angle)
        {
            if (is_initialized == false)
                return;

            List<PointLatLng> points = new List<PointLatLng>();
            points.Add(UserPosition);
            points.Add(get_line_position2(angle));
            GMapPolygon polygon = new GMapPolygon(points, "direction_line")
            {
                Fill = new SolidBrush(Color.FromArgb(50, Color.Blue)),
                Stroke = new Pen(Color.Blue, 1)
            };
            if (gMapControl1.Overlays[0].Polygons.Count == 0)
            {
                gMapControl1.Overlays[0].Polygons.Add(polygon);
            }  
            else
                gMapControl1.Overlays[0].Polygons[0] = polygon;

            gMapControl1.Overlays[0].IsVisibile = false;
            gMapControl1.Overlays[0].IsVisibile = true;
            gMapControl1.Refresh();
        }

        /// <summary>
        /// Прямая геодезическая задача
        /// </summary>
        /// <param name="angle">Азимут визира</param>
        /// <returns></returns>
        PointLatLng get_line_position2(double angle)
        {
            PointLatLng result = new PointLatLng();

            GlobalCoordinates start = new GlobalCoordinates(UserPosition.Lat, UserPosition.Lng);
            GlobalCoordinates end = geo_calc.CalculateEndingGlobalCoordinates(start, angle, line_length);

            result.Lat = end.Latitude.Degrees;
            result.Lng = end.Longitude.Degrees;

            return result;
        }

        /// <summary>
        /// Обратная геодезическая задача
        /// </summary>
        /// <param name="end_point"></param>
        /// <returns>Азимут точки</returns>
        double get_direction(PointLatLng end_point)
        {
            GlobalCoordinates start = new GlobalCoordinates(UserPosition.Lat, UserPosition.Lng);
            GlobalCoordinates end = new GlobalCoordinates(end_point.Lat, end_point.Lng);
            GeodeticCurve curve = geo_calc.CalculateGeodeticCurve(start, end);
            return curve.Azimuth.Degrees;
        }

        /// <summary>
        /// Нажатие на карту
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void gMapControl1_MouseClick(object sender, MouseEventArgs e)
        {
            PointLatLng mouse_pos = gMapControl1.FromLocalToLatLng(e.X, e.Y);

            if (mouse_mode == MouseMode_t.SET_CALIB_MARKER)
            {
                SetCalibrationMarker(mouse_pos);
                mouse_mode = MouseMode_t.IDLE;
            }
            else if (mouse_mode == MouseMode_t.SET_USER_MARKER)
            {
                SetUserMarker(mouse_pos);
                mouse_mode = MouseMode_t.IDLE;
            }
        }

        void UpdateMarkers()
        {
            gMapControl1.Overlays[1].Markers.Clear();

            GMarkerGoogle marker = new GMarkerGoogle(CalibPosition, GMarkerGoogleType.arrow);
            gMapControl1.Overlays[1].Markers.Add(marker);

            GMarkerGoogle marker2 = new GMarkerGoogle(UserPosition, GMarkerGoogleType.blue);
            gMapControl1.Overlays[1].Markers.Add(marker2);
        }

        /// <summary>
        /// Установить маркер калибровки
        /// </summary>
        /// <param name="marker_pos"></param>
        void SetCalibrationMarker(PointLatLng marker_pos)
        {
            CalibPosition = marker_pos;

            CalibYaw = get_direction(marker_pos);

            Properties.Settings1.Default.CabibrationLat = marker_pos.Lat;
            Properties.Settings1.Default.CabibrationLon = marker_pos.Lng;
            Properties.Settings1.Default.Save();

            UpdateMarkers();
        }

        /// <summary>
        /// Установить маркер калибровки
        /// </summary>
        /// <param name="marker_pos"></param>
        void SetUserMarker(PointLatLng marker_pos)
        {
            UserPosition = marker_pos;

            Properties.Settings1.Default.UserLat = marker_pos.Lat;
            Properties.Settings1.Default.UserLon = marker_pos.Lng;
            Properties.Settings1.Default.Save();

            UpdateMarkers();
        }

        /// <summary>
        /// Перейти в режим ожидания калибровочной точки
        /// </summary>
        public void start_set_calibration_pos()
        {
            mouse_mode = MouseMode_t.SET_CALIB_MARKER;
        }

        /// <summary>
        /// Перейти в режим ожидания калибровочной точки
        /// </summary>
        public void start_set_user_pos()
        {
            mouse_mode = MouseMode_t.SET_USER_MARKER;
        }
    }//class
}
