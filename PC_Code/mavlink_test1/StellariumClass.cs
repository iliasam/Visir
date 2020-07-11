//taken from here

using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;

namespace mavlink_test1
{
    public class StellariumClass
    {
        public Boolean Connected = false;
        private Double _selectedRightAscensionHours;
        private Double _selectedDeclinationDegrees;
        private Double _telescopeRightAscensionHours;
        private Double _telescopeDeclinationDegrees;
        private static readonly DateTime StellariumEpoch = new DateTime(1970, 01, 01);


        private TcpClient _client;
        private BinaryWriter _writer;
        private BinaryReader _reader;

        // http://sourceforge.net/p/stellarium/code/HEAD/tree/trunk/telescope_server/stellarium_telescope_protocol.txt

        readonly Timer _dispatcherTimer = new Timer();

        public StellariumClass()
        {
            //var listener = new TcpListener(IPAddress.Loopback, 10001);//ДОЛЖНО БЫТЬ  10001 !!!!!!!!!!!!!!!!!!!
            IPAddress localAddr = IPAddress.Parse("192.168.1.6");
            var listener = new TcpListener(localAddr, 10001);//ДОЛЖНО БЫТЬ  10001 !!!!!!!!!!!!!!!!!!!
            listener.Start();
            listener.BeginAcceptTcpClient(MyAsyncCallback, listener);

            _dispatcherTimer.Interval = 500;
            _dispatcherTimer.Tick += OnTick;
            _dispatcherTimer.Start();
        }

        public void UpdateCurrentPos(double RightAscensionHours, double DeclinationDegrees)
        {
            _telescopeRightAscensionHours = RightAscensionHours;
            _telescopeDeclinationDegrees = DeclinationDegrees;
        }

        private void OnTick(object sender, EventArgs e)
        {
            try
            {
                if (Connected)
                {
                    while (_client.Available != 0)
                    {
                        var packetLength = _reader.ReadUInt16();
                        var packetType = _reader.ReadUInt16();
                        if (packetType == 0) // SLEW (aka GOTO)
                        {
                            _reader.ReadUInt64(); // time
                            _selectedRightAscensionHours = _reader.ReadUInt32() / (double)uint.MaxValue * 24;
                            _selectedDeclinationDegrees = _reader.ReadInt32() / (double)int.MaxValue * 180;
                        }
                        else
                            _reader.ReadBytes(packetLength - 4);
                    }

                    SendCurrentPosition();
                }
            }
            catch (Exception)
            {
                Connected = false;
            }
        }

        void MyAsyncCallback(IAsyncResult ar)
        {
            var listener = (TcpListener)ar.AsyncState;
            _client = listener.EndAcceptTcpClient(ar);
            Connected = true;
            _writer = new BinaryWriter(_client.GetStream());
            _reader = new BinaryReader(_client.GetStream());
        }

        public void SendCurrentPosition(int status = 0)
        {
            if (_writer == null)
            {
                return;
            }

            UInt32 realRa = (UInt32)(_telescopeRightAscensionHours / 24.0 * UInt32.MaxValue);
            Int32 realDec = (Int32)(_telescopeDeclinationDegrees / 180.0 * Int32.MaxValue);
            Int64 time = (DateTime.UtcNow - StellariumEpoch).Ticks * 100; // microseconds
            try
            {
                _writer.Write((ushort)24); // length
                _writer.Write((ushort)0); // message type
                _writer.Write(time);
                _writer.Write(realRa);
                _writer.Write(realDec);
                _writer.Write(status);
            }
            catch
            {
            }
        }


    }
}
