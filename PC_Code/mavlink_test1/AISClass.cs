using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;
using AISParser;

namespace mavlink_test1
{
    class AISClass
    {
        public Boolean Connected = false;

        private TcpClient _client;
        NetworkStream _stream;

        IPAddress localAddr = IPAddress.Parse("127.0.0.1");

        TcpListener listener;

        Thread thread1;

        private AsyncCallback AsyncReceiveCallback = new AsyncCallback(ProcessReceiveResults);

        public AISClass()
        {
            thread1 = new Thread(ThreadStart);
            thread1.Start();
        }

        void ThreadStart()
        {
            listener = new TcpListener(localAddr, 3007);
            listener.Start();

            while (true)
            {
                Thread.Sleep(100);
                try
                {
                    TcpClient _client = listener.AcceptTcpClient();
                }
                catch (Exception)
                {
                    return;
                }
                
                Console.WriteLine("Connected!");

                _stream = _client.GetStream();
                
                while ((_client != null) && (_client.Available == 0))
                {
                }

                Byte[] bytes = new Byte[256];
                _stream.BeginRead(bytes, 0, bytes.Length,
                                                 new AsyncCallback(AsyncReceiveCallback),
                                                 _stream);


                
                _stream.Read(bytes, 0, _client.Available);
                string str_data = System.Text.Encoding.ASCII.GetString(bytes);
                Console.WriteLine("BeginRead() is OK...");


                //_client.Close();
                //System.Diagnostics.Debug.WriteLine(str_data);
            }
        }


        static void ProcessReceiveResults(IAsyncResult ar)
        {
        }



            public void Close()
        {
            Connected = false;

            try
            {
                listener.Stop();
                _client.Close();
                listener = null;
            }
            catch (Exception)
            {
            }
        }

        private void MyAsyncCallback(IAsyncResult ar)
        {
            var listener = (TcpListener)ar.AsyncState;
            _client = listener.EndAcceptTcpClient(ar);
            Connected = true;
            _stream = _client.GetStream();
        }

    }
}
