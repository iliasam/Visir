using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace mavlink_test1
{
    public class NMEAPublisherClass
    {

        TcpClient client;

        Thread ServerThread;

        public double CurrentAngle = 45.0;

        double locLat = 55;
        double locLon = 37;

        public NMEAPublisherClass()
        {
            
        }

        public void Start()
        {
            ServerThread = new Thread(ServerThreadFunc);
            ServerThread.Start();
        }

        private void ServerThreadFunc()
        {

            IPAddress localAddr = IPAddress.Parse("127.0.0.1");
            TcpListener server = new TcpListener(localAddr, 3000);

            server.Start();  // this will start the server

            while (true)   //we wait for a connection
            {
                client = server.AcceptTcpClient();
                NetworkStream stream = client.GetStream();

                while (client.Connected)
                {
                    System.Threading.Thread.Sleep(200);

                    byte[] bytes = new byte[100];

                    CultureInfo.CurrentCulture = CultureInfo.GetCultureInfo("en-US");

                    //string baseStr = $"$GPHDT,{CurrentAngle:0.000},T*";

                    LoadSettings();
                    string baseStr = $"$GPRMC,123519,A,{NMEAConvertPos(locLat)},N,{NMEAConvertPos(locLon)},E,020.0,{CurrentAngle:0.000},230394,0.0,W*";

                    string checkSummStr = getChecksum(baseStr);
                    string resultStr = baseStr + checkSummStr + "\r\n";

                    bytes = Encoding.Default.GetBytes(resultStr);
                    try
                    {
                        stream.Write(bytes, 0, bytes.Length);
                    }
                    catch (Exception)
                    {
                    }
                }//while

                Thread.Sleep(10);
            }
        }

        double NMEAConvertPos(double value)
        {
            double intPart = Math.Truncate(value);
            double frac = value - intPart;//0-1
            
            double degFrac = frac * 60.0;//градусы

            return (intPart * 100 + degFrac);
        }

        private static string getChecksum(string sentence)
        {
            //Start with first Item
            int checksum = Convert.ToByte(sentence[sentence.IndexOf('$') + 1]);
            // Loop through all chars to get a checksum
            for (int i = sentence.IndexOf('$') + 2; i < sentence.IndexOf('*'); i++)
            {
                // No. XOR the checksum with this character's value
                checksum ^= Convert.ToByte(sentence[i]);
            }
            // Return the checksum formatted as a two-character hexadecimal
            return checksum.ToString("X2");
        }

        void LoadSettings()
        {
            locLat = Properties.Settings1.Default.UserLat;
            locLon = Properties.Settings1.Default.UserLon;
        }

        public void Stop()
        {
            client.Close();
            ServerThread.Abort();
        }


    }//class
}
