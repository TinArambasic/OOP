using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsHotel.Forms.Hotel
{
    public partial class HotelEdit : Form
    {

        public string Name { get; private set; }
        public string Address { get; private set; }
        public string Tel { get; private set; }

        public HotelEdit()
        {
            InitializeComponent();

           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void button2_Click(object sender, EventArgs e)
        {

            Name = txtName.Text;
            Address = txtAddress.Text;
            Tel = txtPhone.Text;
            this.Close();

        }
    }
}
