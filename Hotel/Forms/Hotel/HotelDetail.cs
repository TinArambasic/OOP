using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WindowsFormsHotel.Forms.Hotel;

namespace WindowsFormsHotel
{
    public partial class HotelDetail : Form
    {
        public HotelDetail()
        {
            InitializeComponent();

            HotelEdit hotelEditForm = new HotelEdit();
            hotelEditForm.ShowDialog();

            string name = hotelEditForm.Name;
            string address = hotelEditForm.Address;
            string tel = hotelEditForm.Tel;

            lblNameData.Text = name;
            lblAddressData.Text = address;
            lblPhoneData.Text = tel;
        }

        private void btnEdit_Click(object sender, EventArgs e)
        {
            HotelEdit edit = new HotelEdit();
            edit.Show();
        }
    }
}
