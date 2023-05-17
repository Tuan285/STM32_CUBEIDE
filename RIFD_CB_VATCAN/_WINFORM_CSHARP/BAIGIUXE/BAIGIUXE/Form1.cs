using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;

namespace BAIGIUXE
{
    public partial class Form1 : Form
    {
        static DateTime[] A = new DateTime[5];
        String[] ports;
        String data_rev;
        String dt1, dt2, dt3, dt4;
        String trong = "Chưa có xe";
        String day = "Đã có xe";
        int giatien = 2, the;
        String giatien_s, the_s;
        public Form1()
        {
            InitializeComponent();
            //InitializeComponent();
            ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                comboBoxCOM.Items.Add(port);
                if (ports[0] != null)
                {
                    comboBoxCOM.SelectedItem = ports[0];
                }
            }
            string[] BaudRate = { "9600", "19200", "38400", "37600", "115200" };
            comboBoxBAUD.Items.AddRange(BaudRate);
            comboBoxBAUD.Text = BaudRate[0];
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            int Index = comboBoxBAUD.SelectedIndex;
            String[] list_com = SerialPort.GetPortNames();
            int[] ComnumberList = new int[list_com.Length];
            for (int i = 0; i < list_com.Length; i++)
            {
                ComnumberList[i] = int.Parse(list_com[i].Substring(3));
            }
            panel5.Enabled = false;
            khoitaoM1C();
        }

        private void button_CONNECT_Click(object sender, EventArgs e)
        {
            try
            {
                if (!serialPort1.IsOpen)
                {
                    serialPort1.PortName = comboBoxCOM.Text;
                    serialPort1.BaudRate = (int)Convert.ToInt32(comboBoxBAUD.Text);
                    serialPort1.Open();
                    label_STATUS.Text = "Kết Nối Thành Công !";
                    label_STATUS.ForeColor = Color.Green;
                    button_CONNECT.Enabled = false;
                    button_DISCON.Enabled = true;
                    comboBoxBAUD.Enabled = false;
                    comboBoxCOM.Enabled = false;
                    panel5.Enabled = true;
                }
            }
            catch
            {
                label_STATUS.Text = "Ngat Kết Nối Thành Công !!";
                label_STATUS.ForeColor = Color.Red;
            }
        }

        private void button_DISCON_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                label_STATUS.Text = "Ngắt Kết Nối Thành Công !";
                label_STATUS.ForeColor = Color.Red;
                button_CONNECT.Enabled = true;
                button_DISCON.Enabled = false;
                comboBoxBAUD.Enabled = true;
                comboBoxCOM.Enabled = true;
                panel5.Enabled = false;
            }
        }

        delegate void SetTextCallback(string text);
        private void SetText(string text)
        {
            if (this.label_chotrong.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else { 
                text = text.Trim();     // string 
                string[] text_num = text.Split('/');   
                the_s = text_num[0].ToString();       // 1
                
                dt1 = text_num[1].ToString();       // 0
                dt2 = text_num[2].ToString();       
                dt3 = text_num[3].ToString();       // tien 1
                dt4 = text_num[4].ToString();
                giatien_s = text_num[5].ToString();         
                giatien = Int16.Parse(giatien_s.ToString());
                the = Int16.Parse(the_s.ToString());
                function_main(the);
                // gia tien 5       -> 5
                // 
                // 1/0/1/0/1/3/4        // the/cb1/cb2/cb3/cb4/giatien/chotrong     
                // 1/../../../../5/..
                // fucntion(1);
                check(dt1, dt2, dt3, dt4);
            }
        }
        void check(string d1, string d2, string d3, string d4)
        {
            if (d1 == "1")
            {
                label_bai1.Text = trong;
                label_bai1.ForeColor = Color.Green;
            }
            if (d1 == "0")
            {
                label_bai1.Text = day;
                label_bai1.ForeColor = Color.Red;
            }
            if (d2 == "1")
            {
                label_bai2.Text = trong;
                label_bai2.ForeColor = Color.Green;
            }
            if (d2 == "0")
            {
                label_bai2.Text = day;
                label_bai2.ForeColor = Color.Red;
            }
            if (d3 == "1")
            {
                label_bai3.Text = trong;
                label_bai3.ForeColor = Color.Green;
            }
            if (d3 == "0")
            {
                label_bai3.Text = day;
                label_bai3.ForeColor = Color.Red;
            }
            if (d4 == "1")
            {
                label_bai4.Text = trong;
                label_bai4.ForeColor = Color.Green;
            }
            if (d4 == "0")
            {
                label_bai4.Text = day;
                label_bai4.ForeColor = Color.Red;
            }

        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            label_thoigian.Text = DateTime.Now.ToLongTimeString();
            label_thoigian.ForeColor = Color.Blue;
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            data_rev = serialPort1.ReadLine().ToString();
            SetText(data_rev);
            data_rev = "";
        }
        public static void khoitaoM1C()
        {
            DateTime firstDateTime = new DateTime(0001, 1, 1);

            for (int i = 1; i < 5; i++)
            {

                A[i] = firstDateTime;
            }
        }
        public void function_main(int x)
        {
            DateTime firstDateTime = new DateTime(0001, 1, 1); //khởi tạo ngày 1/1/0001         
            DateTime now = DateTime.Now;
            //DateTime[] A = new DateTime[5];
            for (int i = 1; i < 5; i++)
            {
                if (A[i] == firstDateTime && i == x)
                {
                    A[i] = now;
                    Console.WriteLine("da gui xe ngay: " + A[i]);
                }
                else
                {
                    if (A[i] != firstDateTime && i == x)
                    {
                        //Console.WriteLine("gui xe tu ngay: " + A[i] + " den ngay: " + now + ", so tien phai tra la: " + function_momey(A[i], now));
                        //label_time.Text = A[i].ToString();
                        label6.Text = A[i].ToString();
                        label_tien.Text = function_momey(A[i], now).ToString();
                    }
                    else { Console.WriteLine(""); }
                }
            }

        }
        public int function_momey(DateTime a, DateTime b)
        {
            int tongtien = 0;
            TimeSpan Time = b - a;

            int TongSoGio = Time.Days * 24 + Time.Hours;
            int ngay = TongSoGio / 24;
            if (ngay == 0)
            {
                tongtien = giatien * 1000;//1000 là giá tiền gửi xe trong ngày đầu nếu ko qua ngày thứ hai,
            }
            else
            {
                tongtien = 1 * giatien * 1000 + ngay * 2000; //1000  là giá tiền xe trong  ngày 1 2000 là giá từ ngày 2 trở đi
            }

            return tongtien;
        }
        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void panel5_Paint(object sender, PaintEventArgs e)
        {

        }
        

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

    }
}
