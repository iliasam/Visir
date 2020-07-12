using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;

using Geodesy;
using Xamarin.Essentials;

namespace VisirApp2
{
    public class PositionClass
    {
        public byte state;
        private System.Timers.Timer aTimer;
        public static int CurrentGPSAccuracy = 1000;

        bool GetLocationEnabled = true;

        public static GlobalCoordinates UserPosition;
        public static GlobalCoordinates UserGPSPosition;

        SettingsClass SettingsSaver = new SettingsClass();

        public static Action<double> NewGPSPosition;//callback - new position - send accuracy

        public PositionClass()
        {
            //this call happens in main Thead so it will rise Permision request
            LocationRequest();

            //calls from timer did not rise permission request
            aTimer = new System.Timers.Timer(2000);
            aTimer.Elapsed += OnTimedEvent;
            aTimer.AutoReset = true;
            aTimer.Enabled = true;
            LoadSettings();
        }

        public void LoadSettings()
        {
            double SavedUserLat;
            double SavedUserLon;
            bool SavedOk = SettingsSaver.GetCalib(out SavedUserLat, out SavedUserLon);

            if (SavedOk)
            {
                UserPosition = new GlobalCoordinates(SavedUserLat, SavedUserLon);
            }
        }

        public void SaveSettngs()
        {
            SettingsSaver.SaveUserPos(UserPosition.Latitude.Degrees, UserPosition.Longitude.Degrees);
        }

        private void OnTimedEvent(object sender, ElapsedEventArgs e)
        {
            aTimer.Enabled = false;
            if (GetLocationEnabled)
                LocationRequest();
            aTimer.Enabled = true;
        }

        public async void LocationRequest()
        {
            try
            {
                GetLocationEnabled = false;
                var request = new GeolocationRequest(GeolocationAccuracy.High);
                request.Timeout = new TimeSpan(0, 0, 0, 5);
                var location = await Geolocation.GetLocationAsync(request);

                if (location != null)
                {
                    CurrentGPSAccuracy = (int)location.Accuracy;
                    UserGPSPosition.Latitude = location.Latitude;
                    UserGPSPosition.Longitude = location.Longitude;
                    Console.WriteLine($"Latitude: {location.Latitude}, Longitude: {location.Longitude}, Altitude: {location.Altitude}");
                    NewGPSPosition?.Invoke(CurrentGPSAccuracy);
                    
                }
                GetLocationEnabled = true;
            }
            catch (FeatureNotSupportedException)
            {
                // Handle not supported on device exception
                GetLocationEnabled = false;
            }
            catch (FeatureNotEnabledException)
            {
                // Handle not enabled on device exception
                GetLocationEnabled = true;
            }
            catch (PermissionException)
            {
                // Handle permission exception
                GetLocationEnabled = false;
                Console.WriteLine($"GPS PERMISSION EXEPTION");
                CurrentGPSAccuracy = 2000;
                NewGPSPosition?.Invoke(CurrentGPSAccuracy);
            }
            catch (Exception)
            {
                // Unable to get location
                GetLocationEnabled = true;
            }
        }
    }
}