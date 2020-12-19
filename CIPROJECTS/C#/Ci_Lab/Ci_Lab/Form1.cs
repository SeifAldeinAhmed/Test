using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO.Ports;

using System.Windows.Forms.DataVisualization.Charting;

namespace Ci_Lab
{
    public partial class Form1 : Form
    {
        SerialPort Port= null;
        //Intiating Global Variable to recieve
        string Data_Rx = "";
        //flag 34an mmla4 el Rx ella lma da yb2a true
        bool Flag_st = false;
        int counter = 0;
        //Int32[] arr0 = new Int32[100];
        //Int32[] arr1 = new Int32[100];
        //Int32[] arr2 = new Int32[100];
        byte e0;
        Int32 e1=0;
        int i;
        int[] a = new int[10];
        string[] Ch_arr = { "ch0", "ch1", "ch2", "ch3", "ch4", "ch5", "ch6", "ch7"};
        float[] Previous_arr = { 0, 0, 0, 0, 0, 0, 0, 0 };
        Int64 waving = 0;
        public Form1()
        {
            InitializeComponent();
            refresh_com();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            refresh_com();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            connect_com();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            diconnect_com();
        }

        private void refresh_com()
        {
            //List of Activated COM Ports in Windows
            comboBox1.DataSource = SerialPort.GetPortNames();
        }

        private void connect_com()
        {
            //First we must Configure The port, Then Open it
            Port = new SerialPort(comboBox1.SelectedItem.ToString());
            //Take Func to execute when he recieved a byte.
            Port.DataReceived += new SerialDataReceivedEventHandler(Data_Rx_Handler);

            Port.BaudRate = 9600;
            Port.DataBits = 8;
            Port.StopBits= StopBits.One;

            var chart = chart1.ChartAreas[0];
            chart.AxisX.IntervalType = DateTimeIntervalType.Number;
            chart.AxisX.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.IsEndLabelVisible = true;

            chart.AxisX.Minimum = -99;
            chart.AxisX.Maximum = 0;
            chart.AxisX.Interval = 5;


            chart.AxisY.Minimum = 0;
            chart.AxisY.Maximum = 7.5;
            chart.AxisY.Interval = 1;

            try
            {
                if (!Port.IsOpen)
                {
                    Port.Open();
                    label1.Text = "Connected!";
                    label1.ForeColor = Color.Green;
                }
            }
            catch (Exception ex)
            {

            }
        }

        private void diconnect_com()
        {
            try
            {
                if (Port.IsOpen)
                {
                    Port.Close();
                    label1.Text = "Disonnected!";
                    label1.ForeColor = Color.Red;
                }
            }
            catch (Exception ex)
            {

            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            diconnect_com();
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            send();
        }

        private void send()
        {
            try
            {
                Port.Write(textBox1.Text);
            }
            catch (Exception ex)
            { 
            
            }
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            //If I pressed Enter, then send
            if (e.KeyCode == Keys.Enter)
            {
                send();
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            textBox2.Text = Data_Rx;
            /*string[] parts = Data_Rx.Split(new string[] { "," }, StringSplitOptions.None);
            arr0[counter] = Int16.Parse(parts[0]);
            arr1[counter] = Int16.Parse(parts[1]);
            arr2[counter] = Int16.Parse(parts[2]);*/
        }

        private void Data_Rx_Handler(object sender, SerialDataReceivedEventArgs e)
        {
            //Another Object of SerialPort Class
            SerialPort sp = (SerialPort)sender;
            //Recieving Data
            string indata = sp.ReadExisting();
            
            int idx_end = indata.IndexOf(";");
            if ((idx_end >= 0) && (Flag_st))
            {
                Flag_st = false;
                Data_Rx += indata.Substring(0, idx_end);
            }

            if (Flag_st)
            {
                Data_Rx += indata;
            }

            int idx_st = indata.IndexOf("@");
            if (idx_st>=0)
            {
                Flag_st = true;
                //make el RX empty
                Data_Rx = "";
                if (indata.Length > (idx_st + 1))
                {
                    Data_Rx += indata.Substring((idx_st + 1), (indata.Length-1));
                    int idx = indata.IndexOf(";");
                    if (idx >= 0)
                    {
                        Data_Rx = Data_Rx.Substring(0, idx);
                    }
                }
            }

            /*if (Flag_st)
            {
                //Then we store it in Data_Rx
                Data_Rx += indata;
            }*/
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                var chart = chart1.ChartAreas[0];
                textBox2.Text = Data_Rx;
                string[] parts = new string[2];
                parts = Data_Rx.Split(new string[] { "," }, StringSplitOptions.None);
                string p0 = parts[0];
                string p1 = parts[1];
                
                textBox3.Text = p0;
                textBox4.Text = p1;
                e0 = byte.Parse(p0);
                counter++;
                for (i = 0; e0 > 0||i<8; i++)
                {
                    a[i] = e0 % 2;
                    e0 = (byte)((int) e0 /2);
                }
                for (i = 0; i <8 ; i++)
                {
                    if (a[i] == 0)
                    {
                        chart1.Series[Ch_arr[i]].Points.AddXY(e1, Previous_arr[i]);
                        Previous_arr[i] = i;
                        chart1.Series[Ch_arr[i]].Points.AddXY(e1, i);

                    }
                    else {
                        chart1.Series[Ch_arr[i]].Points.AddXY(e1, Previous_arr[i]);
                        Previous_arr[i] = i+(float)0.5;
                        chart1.Series[Ch_arr[i]].Points.AddXY(e1, (i + 0.5));
                    }
                    if (e1 >= (chart.AxisX.Maximum-4))
                    {
                        waving += 1;
                        chart.AxisX.Minimum = waving-99;
                        chart.AxisX.Maximum = 0+waving;
                    }
                    
                }
                e1++;
            }
            catch (Exception ex)
            { 
            
            
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            var chart = chart1.ChartAreas[0];
            chart.AxisX.IntervalType=DateTimeIntervalType.Number;
            chart.AxisX.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.IsEndLabelVisible = true;
            
            chart.AxisX.Minimum=0;
            chart.AxisX.Maximum=1;
            chart.AxisX.Interval=0.5;
            
            
            chart.AxisY.Minimum=0;
            chart.AxisY.Maximum=10;
            chart.AxisY.Interval=1;
           
            chart1.Series["signal"].Points.AddXY(0,0);
            chart1.Series["signal"].Points.AddXY(0.2,5);
            chart1.Series["signal"].Points.AddXY(0.3, 0);
            chart1.Series["signal"].Points.AddXY(0.4,5);
            chart1.Series["signal"].Points.AddXY(0.5, 0);
            chart1.Series["signal"].Points.AddXY(0.6, 5);
            chart1.Series["signal"].Points.AddXY(0.7, 0);
            chart1.Series["signal"].Points.AddXY(0.8, 5);
            chart1.Series["signal"].Points.AddXY(0.9, 0);
            chart1.Series["signal"].Points.AddXY(1, 5);
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

    }
}
