using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Xamarin.Essentials;

namespace VisirApp2
{
    class SettingsClass
    {
        public void SaveCalib(double Lat, double Lon)
        {
            Preferences.Set("Lat", Lat);
            Preferences.Set("Lon", Lon);
        }

        public void SaveVertCorrection(double VertCorrection)
        {
            Preferences.Set("VertCorr", VertCorrection);
        }

        //telescope calibration azimuth
        public void SaveTeleCalibAzimuth(double Azimuth)
        {
            Preferences.Set("TeleCalibAzim", Azimuth);
        }

        public void SaveUserPos(double Lat, double Lon)
        {
            Preferences.Set("UserLat", Lat);
            Preferences.Set("UserLon", Lon);
        }

        public bool GetCalib(out double Lat, out double Lon)
        {
            Lat = Preferences.Get("Lat", 55.832);
            Lon = Preferences.Get("Lon", 37.29907);
            return Preferences.ContainsKey("Lat");
        }

        public bool GetUserPos(out double Lat, out double Lon)
        {
            Lat = Preferences.Get("UserLat", 55.83231);
            Lon = Preferences.Get("UserLon", 37.29907);
            return Preferences.ContainsKey("UserLat");
        }

        public bool GetVertCorr(out double VertCorr)
        {
            VertCorr = Preferences.Get("VertCorr", 0.0);
            return Preferences.ContainsKey("VertCorr");
        }

        public bool GetTeleCalibAzimuth(out double Azimuth)
        {
            Azimuth = Preferences.Get("TeleCalibAzim", 0.0);
            return Preferences.ContainsKey("TeleCalibAzim");
        }

    }//end of class
}