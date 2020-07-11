using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace mavlink_test1
{
    public partial class TelescopeControl : UserControl
    {
        AstronomyClass astronomy_obj = new AstronomyClass();
        //StellariumClass sky_viwer_obj = new StellariumClass();
        //MeadeClass sky_viwer_obj = new MeadeClass();

        double CurrentRAHours = 0.0;
        double CurrentDecDeg = 0.0;

        public TelescopeControl()
        {
            InitializeComponent();
        }

        public void SetUserPosition(double Lat, double Lon)
        {
            astronomy_obj.SetUserPosition(Lat, Lon);
        }

        public void UpdateCurrentPosition(double altitude_deg, double azimuth_deg)
        {
            astronomy_obj.CalculateEquatorialFromHorizontal(altitude_deg, azimuth_deg, out double ra_hours, out double dec_deg);
            CurrentRAHours = ra_hours;
            CurrentDecDeg = dec_deg;
            UpdateGUI();
            //sky_viwer_obj.UpdateCurrentPos(CurrentRAHours, CurrentDecDeg);
        }

        void UpdateGUI()
        {
            lblDEC.Text = $"DEC: {CurrentDecDeg:0.00} Deg";
            lblRA.Text = $"RA: {CurrentRAHours:0.00} Hours";

            //if (sky_viwer_obj.Connected)
            //    lblStellarium.Text = "Stellarium: Connected";
            //else
            //    lblStellarium.Text = "Stellarium: Not Connected";

            double LST_Hours = astronomy_obj.GetLST_Hours();
            lblLSTTime.Text = $"LST: {LST_Hours:0.00} Hours";
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            //sky_viwer_obj.Close();
        }

        public void Close()
        {
            //sky_viwer_obj.Close();
        }
    }
}
