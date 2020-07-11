using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace mavlink_test1
{
    class AstronomyClass
    {
        double UserLatRad = 0.0;
        double UserLonRad = 0.0;

        public void SetUserPosition(double Lat, double Lon)
        {
            UserLatRad = ConvertToRad(Lat);
            UserLonRad = ConvertToRad(Lon);
        }

        public void CalculateEquatorialFromHorizontal(double altitude_deg, double azimuth_deg, out double RA_hours, out double DEC_deg)
        {
            //sin DEC = sin LAT sin ALT + cos LAT cos ALT cos AZ
            double altitude_Rad = ConvertToRad(altitude_deg);
            double azimuth_Rad = ConvertToRad(azimuth_deg);

            double sin_dec = Math.Sin(UserLatRad) * Math.Sin(altitude_Rad) + Math.Cos(UserLatRad) * Math.Cos(altitude_Rad) * Math.Cos(azimuth_Rad);
            sin_dec = CorrectValue(sin_dec);
            double DEC_Rad = Math.Asin(sin_dec);//radians

            //cos H = (sin ALT - sin DEC sin LAT)/(cos DEC cos LAT)
            double cos_H = (Math.Sin(altitude_Rad) - Math.Sin(DEC_Rad) * Math.Sin(UserLatRad)) / (Math.Cos(DEC_Rad) * Math.Cos(UserLatRad));
            cos_H = CorrectValue(cos_H);
            double H_Rad = Math.Acos(cos_H);// hour angle - radians
            double H_Deg = ConvertToDeg(H_Rad);

            //RA = LST - H //LST - local sidereal time
            double LST_Deg = GetLST_Deg();

            double RA_Deg;
            if (azimuth_deg > 180.0)
                RA_Deg = LST_Deg - H_Deg;
            else
                RA_Deg = LST_Deg + H_Deg;



            if (RA_Deg > 360.0)
                RA_Deg = RA_Deg - 360.0;
            else if (RA_Deg < 0.0)
                RA_Deg = 360.0 + RA_Deg;


            DEC_deg = ConvertToDeg(DEC_Rad);//degrees
            RA_hours = ConvertDegToHours(RA_Deg);
        }

        double GetLST_Deg()
        {
            DateTime LST = CalculateLocalSiderealTime(ConvertToDeg(UserLonRad));
            double LST_Deg = ConvertDateTimeToDeg(LST);
            return LST_Deg;
        }

        public double GetLST_Hours()
        {
            return ConvertDegToHours(GetLST_Deg());
        }

        //Убрать погрешность вычислений
        double CorrectValue(double value)
        {
            if (Math.Abs(value) < 1.0)
                return value;//все в порядке

            if (value > 0.0)
                return 1.0;
            else
                return -1.0;
        }

        // http://answers.yahoo.com/question/index?qid=20100509150032AAjyxX6
        public static DateTime CalculateLocalSiderealTime(double longitude)
        {
            var epoch = new DateTime(2000, 1, 1, 12, 0, 0, DateTimeKind.Utc);
            var sinceEpoch = DateTime.UtcNow - epoch;
            var hours = (18.697374558 + 24.06570982441908 * sinceEpoch.TotalDays) % 24 + longitude / 15.0;
            while (hours < 0) hours += 24;
            while (hours >= 24) hours -= 24;
            var localSiderealTimeSpan = TimeSpan.FromHours(hours);
            return DateTime.UtcNow.Date + localSiderealTimeSpan;
        }


        double ConvertToDeg(double radians)
        {
            return (radians * 180.0 / Math.PI );
        }

        double ConvertToRad(double degrees)
        {
            return (degrees * Math.PI / 180.0);
        }

        double ConvertDegToHours(double degrees)
        {
            return (degrees / 360.0 * 24.0);
        }

        public static double ConvertDateTimeToDeg(DateTime dateTime)
        {
            return dateTime.TimeOfDay.TotalHours * 360.0 / 24;
        }
    }
}
