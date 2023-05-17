namespace BAIGIUXE
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.label_chotrong = new System.Windows.Forms.Label();
            this.label_thoigian = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label_tien = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.panel9 = new System.Windows.Forms.Panel();
            this.label_bai1 = new System.Windows.Forms.Label();
            this.panel6 = new System.Windows.Forms.Panel();
            this.label_bai2 = new System.Windows.Forms.Label();
            this.panel7 = new System.Windows.Forms.Panel();
            this.label_bai3 = new System.Windows.Forms.Label();
            this.panel8 = new System.Windows.Forms.Panel();
            this.label_bai4 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.label_STATUS = new System.Windows.Forms.Label();
            this.comboBoxBAUD = new System.Windows.Forms.ComboBox();
            this.comboBoxCOM = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button_CONNECT = new System.Windows.Forms.Button();
            this.button_DISCON = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label4 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel5.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.panel9.SuspendLayout();
            this.panel6.SuspendLayout();
            this.panel7.SuspendLayout();
            this.panel8.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Location = new System.Drawing.Point(12, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(465, 297);
            this.panel1.TabIndex = 0;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.panel5);
            this.panel3.Location = new System.Drawing.Point(3, 3);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(454, 195);
            this.panel3.TabIndex = 1;
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.label6);
            this.panel5.Controls.Add(this.label4);
            this.panel5.Controls.Add(this.label_chotrong);
            this.panel5.Controls.Add(this.label_thoigian);
            this.panel5.Controls.Add(this.label3);
            this.panel5.Controls.Add(this.label_tien);
            this.panel5.Controls.Add(this.label5);
            this.panel5.Controls.Add(this.flowLayoutPanel1);
            this.panel5.Controls.Add(this.label8);
            this.panel5.Location = new System.Drawing.Point(3, 3);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(448, 193);
            this.panel5.TabIndex = 1;
            this.panel5.Paint += new System.Windows.Forms.PaintEventHandler(this.panel5_Paint);
            // 
            // label_chotrong
            // 
            this.label_chotrong.AutoSize = true;
            this.label_chotrong.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label_chotrong.Location = new System.Drawing.Point(172, 19);
            this.label_chotrong.Name = "label_chotrong";
            this.label_chotrong.Size = new System.Drawing.Size(46, 17);
            this.label_chotrong.TabIndex = 8;
            this.label_chotrong.Text = "label6";
            // 
            // label_thoigian
            // 
            this.label_thoigian.AutoSize = true;
            this.label_thoigian.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label_thoigian.Location = new System.Drawing.Point(333, 19);
            this.label_thoigian.Name = "label_thoigian";
            this.label_thoigian.Size = new System.Drawing.Size(46, 17);
            this.label_thoigian.TabIndex = 7;
            this.label_thoigian.Text = "label4";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.label3.Location = new System.Drawing.Point(227, 19);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(86, 17);
            this.label3.TabIndex = 6;
            this.label3.Text = "THỜI GIAN :";
            // 
            // label_tien
            // 
            this.label_tien.AutoSize = true;
            this.label_tien.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label_tien.Location = new System.Drawing.Point(109, 49);
            this.label_tien.Name = "label_tien";
            this.label_tien.Size = new System.Drawing.Size(46, 17);
            this.label_tien.TabIndex = 5;
            this.label_tien.Text = "label7";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label5.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.label5.Location = new System.Drawing.Point(7, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(96, 17);
            this.label5.TabIndex = 4;
            this.label5.Text = "GIÁ TIỀN XE :";
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.panel9);
            this.flowLayoutPanel1.Controls.Add(this.panel6);
            this.flowLayoutPanel1.Controls.Add(this.panel7);
            this.flowLayoutPanel1.Controls.Add(this.panel8);
            this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 69);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(427, 119);
            this.flowLayoutPanel1.TabIndex = 1;
            // 
            // panel9
            // 
            this.panel9.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.panel9.Controls.Add(this.label_bai1);
            this.panel9.Location = new System.Drawing.Point(3, 3);
            this.panel9.Name = "panel9";
            this.panel9.Size = new System.Drawing.Size(100, 100);
            this.panel9.TabIndex = 3;
            // 
            // label_bai1
            // 
            this.label_bai1.AutoSize = true;
            this.label_bai1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label_bai1.Location = new System.Drawing.Point(17, 42);
            this.label_bai1.Name = "label_bai1";
            this.label_bai1.Size = new System.Drawing.Size(59, 17);
            this.label_bai1.TabIndex = 6;
            this.label_bai1.Text = "TRỐNG";
            // 
            // panel6
            // 
            this.panel6.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.panel6.Controls.Add(this.label_bai2);
            this.panel6.Location = new System.Drawing.Point(109, 3);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(100, 100);
            this.panel6.TabIndex = 0;
            // 
            // label_bai2
            // 
            this.label_bai2.AutoSize = true;
            this.label_bai2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label_bai2.Location = new System.Drawing.Point(21, 42);
            this.label_bai2.Name = "label_bai2";
            this.label_bai2.Size = new System.Drawing.Size(59, 17);
            this.label_bai2.TabIndex = 7;
            this.label_bai2.Text = "TRỐNG";
            // 
            // panel7
            // 
            this.panel7.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.panel7.Controls.Add(this.label_bai3);
            this.panel7.Location = new System.Drawing.Point(215, 3);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(100, 100);
            this.panel7.TabIndex = 1;
            // 
            // label_bai3
            // 
            this.label_bai3.AutoSize = true;
            this.label_bai3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label_bai3.Location = new System.Drawing.Point(21, 42);
            this.label_bai3.Name = "label_bai3";
            this.label_bai3.Size = new System.Drawing.Size(59, 17);
            this.label_bai3.TabIndex = 7;
            this.label_bai3.Text = "TRỐNG";
            // 
            // panel8
            // 
            this.panel8.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel8.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.panel8.Controls.Add(this.label_bai4);
            this.panel8.Location = new System.Drawing.Point(321, 3);
            this.panel8.Name = "panel8";
            this.panel8.Size = new System.Drawing.Size(100, 100);
            this.panel8.TabIndex = 2;
            // 
            // label_bai4
            // 
            this.label_bai4.AutoSize = true;
            this.label_bai4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label_bai4.Location = new System.Drawing.Point(21, 42);
            this.label_bai4.Name = "label_bai4";
            this.label_bai4.Size = new System.Drawing.Size(59, 17);
            this.label_bai4.TabIndex = 7;
            this.label_bai4.Text = "TRỐNG";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label8.ForeColor = System.Drawing.Color.Red;
            this.label8.Location = new System.Drawing.Point(7, 19);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(159, 17);
            this.label8.TabIndex = 0;
            this.label8.Text = "SỐ CHỖ CÒN TRỐNG :";
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.label_STATUS);
            this.panel2.Controls.Add(this.comboBoxBAUD);
            this.panel2.Controls.Add(this.comboBoxCOM);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Controls.Add(this.label1);
            this.panel2.Controls.Add(this.button_CONNECT);
            this.panel2.Controls.Add(this.button_DISCON);
            this.panel2.Location = new System.Drawing.Point(3, 200);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(454, 87);
            this.panel2.TabIndex = 0;
            // 
            // label_STATUS
            // 
            this.label_STATUS.AutoSize = true;
            this.label_STATUS.ForeColor = System.Drawing.Color.Red;
            this.label_STATUS.Location = new System.Drawing.Point(195, 63);
            this.label_STATUS.Name = "label_STATUS";
            this.label_STATUS.Size = new System.Drawing.Size(89, 13);
            this.label_STATUS.TabIndex = 6;
            this.label_STATUS.Text = "CHƯA KẾT NỐI !";
            // 
            // comboBoxBAUD
            // 
            this.comboBoxBAUD.FormattingEnabled = true;
            this.comboBoxBAUD.Location = new System.Drawing.Point(83, 55);
            this.comboBoxBAUD.Name = "comboBoxBAUD";
            this.comboBoxBAUD.Size = new System.Drawing.Size(86, 21);
            this.comboBoxBAUD.TabIndex = 5;
            this.comboBoxBAUD.Text = "9600";
            // 
            // comboBoxCOM
            // 
            this.comboBoxCOM.FormattingEnabled = true;
            this.comboBoxCOM.Location = new System.Drawing.Point(83, 20);
            this.comboBoxCOM.Name = "comboBoxCOM";
            this.comboBoxCOM.Size = new System.Drawing.Size(86, 21);
            this.comboBoxCOM.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label2.Location = new System.Drawing.Point(9, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "BAUD :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label1.Location = new System.Drawing.Point(9, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 20);
            this.label1.TabIndex = 2;
            this.label1.Text = "COM :";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // button_CONNECT
            // 
            this.button_CONNECT.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.button_CONNECT.Location = new System.Drawing.Point(198, 20);
            this.button_CONNECT.Name = "button_CONNECT";
            this.button_CONNECT.Size = new System.Drawing.Size(110, 40);
            this.button_CONNECT.TabIndex = 1;
            this.button_CONNECT.Text = "KẾT NỐI";
            this.button_CONNECT.UseVisualStyleBackColor = true;
            this.button_CONNECT.Click += new System.EventHandler(this.button_CONNECT_Click);
            // 
            // button_DISCON
            // 
            this.button_DISCON.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.button_DISCON.Location = new System.Drawing.Point(327, 20);
            this.button_DISCON.Name = "button_DISCON";
            this.button_DISCON.Size = new System.Drawing.Size(110, 40);
            this.button_DISCON.TabIndex = 0;
            this.button_DISCON.Text = "NGẮT KẾT NỐI";
            this.button_DISCON.UseVisualStyleBackColor = true;
            this.button_DISCON.Click += new System.EventHandler(this.button_DISCON_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.label4.Location = new System.Drawing.Point(227, 49);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(109, 17);
            this.label4.TabIndex = 9;
            this.label4.Text = "THỜI GIAN RA :";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label6.Location = new System.Drawing.Point(333, 49);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(46, 17);
            this.label6.TabIndex = 10;
            this.label6.Text = "label4";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
            this.ClientSize = new System.Drawing.Size(481, 314);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.panel1.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel5.ResumeLayout(false);
            this.panel5.PerformLayout();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.panel9.ResumeLayout(false);
            this.panel9.PerformLayout();
            this.panel6.ResumeLayout(false);
            this.panel6.PerformLayout();
            this.panel7.ResumeLayout(false);
            this.panel7.PerformLayout();
            this.panel8.ResumeLayout(false);
            this.panel8.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button_CONNECT;
        private System.Windows.Forms.Button button_DISCON;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Panel panel9;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label_STATUS;
        private System.Windows.Forms.ComboBox comboBoxBAUD;
        private System.Windows.Forms.ComboBox comboBoxCOM;
        private System.Windows.Forms.Label label_tien;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label_bai1;
        private System.Windows.Forms.Label label_bai2;
        private System.Windows.Forms.Label label_bai3;
        private System.Windows.Forms.Label label_bai4;
        private System.Windows.Forms.Label label_thoigian;
        private System.Windows.Forms.Label label_chotrong;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label4;
    }
}

