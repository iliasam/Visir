using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace VisirApp2
{
    class MeadeClass
    {
        public Boolean Connected = false;
        private Double _selectedRightAscensionHours;
        private Double _selectedDeclinationDegrees;
        private Double _telescopeRightAscensionHours;
        private Double _telescopeDeclinationDegrees;
        private static readonly DateTime StellariumEpoch = new DateTime(1970, 01, 01);

        private TcpClient _client;
        NetworkStream _stream;

        IPAddress localAddr = IPAddress.Parse("192.168.1.6");

        TcpListener listener;

        public string State = "IDLE";


        //readonly Timer _dispatcherTimer = new Timer();

        public MeadeClass()
        {
            Thread thread1 = new Thread(ThreadStart);
            thread1.Start();
        }

        void ThreadStart()
        {
            bool connnExeption = false;
            try
            {
                listener = new TcpListener(IPAddress.Loopback, 10002);
                //listener = new TcpListener(localAddr, 10002);
                listener.Start();
            }
            catch (Exception ex)
            {
                Close();
                connnExeption = true;
            }

            if (connnExeption)
            {
                //second try
                try
                {
                    listener = new TcpListener(IPAddress.Loopback, 10002);
                    listener.Start();
                }
                catch (Exception ex)
                {
                    if (listener != null)
                        listener.Stop();

                    return;
                }
            }

            State = "WAIT";
            System.Diagnostics.Debug.WriteLine("Listener was started");

            while (true)
            {
                try
                {
                    _client = listener.AcceptTcpClient();
                }
                catch (Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine(ex);
                    State = "ERROR 1";
                    return;
                }
                
                System.Diagnostics.Debug.WriteLine("Connected!");
                _stream = _client.GetStream();

                while ((_client != null) && (_client.Available == 0))
                {
                }

                Byte[] bytes = new Byte[256];
                _stream.Read(bytes, 0, _client.Available);
                string str_data = System.Text.Encoding.ASCII.GetString(bytes);

                if (str_data.Contains(":GR#"))
                {
                    SendGR();
                }
                else if (str_data.Contains(":GD#"))
                {
                    SendGD();
                }
                _client.Close();
            }
        }

        public void UpdateCurrentPos(double RightAscensionHours, double DeclinationDegrees)
        {
            _telescopeRightAscensionHours = RightAscensionHours;
            _telescopeDeclinationDegrees = DeclinationDegrees;
        }


        public void Close()
        {
            try
            {
                if (listener != null)
                {
                    listener.Stop();
                }

                if (_client != null)
                {
                    _client.Close();
                } 
            }
            catch (Exception)
            {
            }

            Connected = false;
            State = "CLOSED";
        }

        private void MyAsyncCallback(IAsyncResult ar)
        {
            var listener = (TcpListener)ar.AsyncState;
            _client = listener.EndAcceptTcpClient(ar);
            Connected = true;
            _stream = _client.GetStream();
        }

        void SendGR() //ra
        {
            string str = "";

            TimeSpan interval = TimeSpan.FromHours(_telescopeRightAscensionHours);

            int hours = interval.Hours;
            int minutes = interval.Minutes;
            int seconds = interval.Seconds;            

            str = $"{hours:00}:{minutes:00}:{seconds:00}#";
            byte[] data = System.Text.Encoding.ASCII.GetBytes(str);
            _stream.Write(data, 0, data.Length);

           // System.Diagnostics.Debug.WriteLine("Send GR");
        }

        void SendGD() //dec
        {
            string str = "";

            double coord = _telescopeDeclinationDegrees;
            int sec = (int)Math.Round(coord * 3600);
            int deg = sec / 3600;
            sec = Math.Abs(sec % 3600);
            int min = sec / 60;
            sec %= 60;

            str = $"{deg:00}:{min:00}:{sec:00}#";
            byte[] data = System.Text.Encoding.ASCII.GetBytes(str);
            _stream.Write(data, 0, data.Length);

           // System.Diagnostics.Debug.WriteLine("Send GD");
        }

    }
}
