using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsHotel.Forms.Guest
{
    public partial class GuestList : Form
    {
        public GuestList()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            GuestEdit form = new GuestEdit();
            form.Show();

        }
    }
}
