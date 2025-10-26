using System.Windows.Forms;
using WindowsFormsHotel.Forms.Bill;
using WindowsFormsHotel.Forms.Guest;
using WindowsFormsHotel.Forms.Reservation;
using WindowsFormsHotel.Forms.Room;

namespace WindowsFormsHotel.Forms.Main
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            //NOTE: postavljamo Hotel detail kao početnu formu
            Form initialForm = new HotelDetail();

            DisplayForm(initialForm);
        }

        private void DisplayForm(Form form)
        {
            form.TopLevel = false;
            form.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            form.Dock = DockStyle.Fill;
            form.Show();

            //NOTE: panel na ovoj formi služi za prikaz child formi.
            this.pnlContainer.Controls.Clear();
            this.pnlContainer.Controls.Add(form);
        }

        private void menu_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            Form formToShow = null;

            //NOTE: u ovisnosti o kliknutom menu item-u prikazujemo formu.
            switch (e.ClickedItem.Text)
            {
                case "Hotel":
                    formToShow = new HotelDetail();
                    DisplayForm(formToShow);
                    break;

                case "Gosti":
                    formToShow = new GuestList();
                    DisplayForm(formToShow);
                    break;

                case "Sobe":
                    formToShow = new RoomList();
                    DisplayForm(formToShow);
                    break;

                case "Rezervacije":
                    formToShow = new ReservationList();
                    DisplayForm(formToShow);
                    break;

                case "Računi":
                    formToShow = new BillList();
                    DisplayForm(formToShow);
                    break;

                default:
                    break;
            }
        }
    }
}