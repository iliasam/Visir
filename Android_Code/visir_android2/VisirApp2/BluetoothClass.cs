using System;
using Android.Bluetooth;
using Java.Util;
using System.Threading.Tasks;
using Java.IO;
//using TestBth.Droid;
using System.Threading;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using Android.Runtime;
using Android.App;
using Android.Content;
using Android.OS;
using MavLink;

//taken from here: https://acaliaro.wordpress.com/2017/02/07/connect-a-barcode-reader-to-a-xamarin-forms-app-via-bluetooth/

namespace VisirApp2
{
    [Service]
    public class BluetoothClass : Service
    {

        private CancellationTokenSource _ct { get; set; }
        const int RequestResolveError = 1000;

        BluetoothSocket BthSocket = null;

        public static Action<MavlinkPacket> MavlinkDataReceived;//callback with the recived data

        bool running = false;

        Mavlink mavlink_obj;

        /// <summary>
        /// Едное значение коррекции - оно передается на визир при нажатии кнопки
        /// </summary>
        private double internal_correction_yaw = 0.0;

        /// <summary>
        /// Источник данных для коррекции 0-map1, 1 - map2, 2-telescope
        /// </summary>
        public static int correction_source = 0;

        // источники значений коррекции
        public static double map1_correction_yaw = 0;
        public static double map2_correction_yaw = 0;
        public static double telescope_correction_yaw = 0;

        public override IBinder OnBind(Intent intent)
        {
            throw new NotImplementedException();
        }

        public override void OnCreate()
        {
            base.OnCreate();
            if (running == false)
            {
                Start("SPP-CA");
                running = true;

                mavlink_obj = new Mavlink();
                mavlink_obj.PacketReceived += new PacketReceivedEventHandler(ProcessRxMavlinkPacket);
            }

            ActivityMap.CalibrationAngleEvent += CalibAngleEvent;
            ActivityMap2.SetTargetAngleEvent += SetTargetEvent;
        }

        private void SetTargetEvent(double angle)
        {
            if (BthSocket.IsConnected)
            {
                if (angle >= 0)
                {
                    sent_mavlink_target((float)angle);
                    sent_mavlink_switch_mode(1);
                }
                else
                {
                    sent_mavlink_switch_mode(0);
                }
            }
        }

        private void CalibAngleEvent(double angle)
        {
            if (BthSocket.IsConnected)
            {
                sent_mavlink_yaw_correction(255, (float)angle);
            }
        }

        public override StartCommandResult OnStartCommand(Intent intent, StartCommandFlags flags, int startId)
        {
            return StartCommandResult.NotSticky;
        }

        #region BluetoothClass implementation

        /// <summary>
        /// Start the "reading" loop 
        /// </summary>
        /// <param name="name">Name of the paired bluetooth device (also a part of the name)</param>
        public void Start(string name, int sleepTime = 50, bool readAsCharArray = false)
        {

            Task.Run(async () => loop(name, sleepTime, readAsCharArray));
        }

        private async Task loop(string name, int sleepTime, bool readAsCharArray)
        {
            BluetoothDevice device = null;
            BluetoothAdapter adapter = BluetoothAdapter.DefaultAdapter;
            

            //Thread.Sleep(1000);
            _ct = new CancellationTokenSource();
            while (_ct.IsCancellationRequested == false)
            {

                try
                {
                    Thread.Sleep(sleepTime);

                    adapter = BluetoothAdapter.DefaultAdapter;

                    if (adapter == null)
                    {
                        System.Diagnostics.Debug.WriteLine("No Bluetooth adapter found.");
                        continue;
                    } 
                    else
                        System.Diagnostics.Debug.WriteLine("Adapter found!!");

                    if (!adapter.IsEnabled)
                        System.Diagnostics.Debug.WriteLine("Bluetooth adapter is not enabled.");
                    else
                        System.Diagnostics.Debug.WriteLine("Adapter enabled!");

                    System.Diagnostics.Debug.WriteLine("Try to connect to " + name);

                    foreach (var bd in adapter.BondedDevices)
                    {
                        System.Diagnostics.Debug.WriteLine("Paired devices found: " + bd.Name.ToUpper());
                        if (bd.Name.ToUpper().IndexOf(name.ToUpper()) >= 0)
                        {

                            System.Diagnostics.Debug.WriteLine("Found " + bd.Name + ". Try to connect with it!");
                            device = bd;
                            break;
                        }
                    }

                    if (device == null)
                        System.Diagnostics.Debug.WriteLine("Named device not found.");
                    else
                    {
                        UUID uuid = UUID.FromString("00001101-0000-1000-8000-00805f9b34fb");//SerialPortServiceClass
                        if ((int)Android.OS.Build.VERSION.SdkInt >= 10) // Gingerbread 2.3.3 2.3.4
                            BthSocket = device.CreateInsecureRfcommSocketToServiceRecord(uuid);
                        else
                            BthSocket = device.CreateRfcommSocketToServiceRecord(uuid);

                        if (BthSocket != null)
                        {
                            await BthSocket.ConnectAsync();

                            if (BthSocket.IsConnected)
                            {
                                System.Diagnostics.Debug.WriteLine("Connected!");

                                while (_ct.IsCancellationRequested == false)
                                {
                                    using (var ist = BthSocket.InputStream)
                                    {
                                        var base_inp_steream = (ist as InputStreamInvoker).BaseInputStream;
                                        var data_size = 0;
                                        if ((data_size = base_inp_steream.Available()) > 0)
                                        {
                                            byte[] data = new byte[data_size];
                                            var nn = base_inp_steream.Read(data, 0, data_size);
                                            mavlink_obj.ParseBytes(data);
                                        }
                                    }

                                    // A little stop to the uneverending thread...
                                    System.Threading.Thread.Sleep(sleepTime);
                                    if (!BthSocket.IsConnected)
                                    {
                                        System.Diagnostics.Debug.WriteLine("BthSocket.IsConnected = false, Throw exception");
                                        throw new Exception();
                                    }
                                }

                                System.Diagnostics.Debug.WriteLine("Exit the inner loop");

                            }
                        }
                        else
                            System.Diagnostics.Debug.WriteLine("BthSocket = null");
                    }


                }
                catch (Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine("EXCEPTION: " + ex.Message);
                }

                finally
                {
                    if (BthSocket != null)
                        BthSocket.Close();
                    device = null;
                    adapter = null;
                }
            }

            System.Diagnostics.Debug.WriteLine("Exit the external loop");
        }

        /// <summary>
        /// Cancel the Reading loop
        /// </summary>
        /// <returns><c>true</c> if this instance cancel ; otherwise, <c>false</c>.</returns>
        public void Cancel()
        {
            if (_ct != null)
            {
                System.Diagnostics.Debug.WriteLine("Send a cancel to task!");
                _ct.Cancel();
            }
        }

        public ObservableCollection<string> PairedDevices()
        {
            BluetoothAdapter adapter = BluetoothAdapter.DefaultAdapter;
            ObservableCollection<string> devices = new ObservableCollection<string>();

            foreach (var bd in adapter.BondedDevices)
                devices.Add(bd.Name);

            return devices;
        }

        #endregion

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2140:TransparentMethodsMustNotReferenceCriticalCodeFxCopRule")]
        public void ProcessRxMavlinkPacket(object sender, MavlinkPacket e)
        {
            //partical parsing
            if (e.Message.GetType() == typeof(MavLink.Msg_mav_button_event))
            {
                parse_keys_event((MavLink.Msg_mav_button_event)e.Message);
            }                

            MavlinkDataReceived?.Invoke(e);
        }

        void parse_keys_event(MavLink.Msg_mav_button_event msg)
        {
            if ((msg.button_code == 2) && (msg.event_code == 2))//event_code == 2
            {
                //get corretion value from the sources
                switch (correction_source)
                {
                    case 0:
                        internal_correction_yaw = map1_correction_yaw;
                        break;

                    case 1:
                        internal_correction_yaw = map2_correction_yaw;
                        break;

                    case 2:
                        internal_correction_yaw = telescope_correction_yaw;
                        break;
                }
                CalibAngleEvent(internal_correction_yaw);
            }
        }

        void sent_mavlink_yaw_correction(byte vect_type, float correction)
        {
            MavLink.Msg_mav_set_yaw_correction mav_msg = new MavLink.Msg_mav_set_yaw_correction();

            mav_msg.vector_type = vect_type;
            mav_msg.value = correction;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            send_mavlink_paket(mvp);
        }

        //set direction
        void sent_mavlink_target(float direction_deg)
        {
            MavLink.Msg_mav_set_target_pos mav_msg = new MavLink.Msg_mav_set_target_pos();
            mav_msg.yaw = direction_deg;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            send_mavlink_paket(mvp);
        }

        /// <summary>
        /// Set mode
        /// </summary>
        /// <param name="mode">0 - base mode, 1 - target1</param>
        void sent_mavlink_switch_mode(byte mode)
        {
            MavLink.Msg_mav_set_visir_mode mav_msg = new MavLink.Msg_mav_set_visir_mode();
            mav_msg.mode_code = mode;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            send_mavlink_paket(mvp);
        }

        void send_mavlink_paket(MavlinkPacket packet)
        {
            byte[] data_to_send = mavlink_obj.Send(packet);

            if (BthSocket.IsConnected)
            {
                var outs = BthSocket.OutputStream;
                var base_out_steream = (outs as OutputStreamInvoker).BaseOutputStream;
                base_out_steream.Write(data_to_send);
            }
        }

    }//end o class
}
