using System;
using System.Globalization;
using System.Windows.Forms;
using WindowsFormsHotel.Code;

namespace WindowsFormsHotel.Forms.Bill
{
    public partial class BillEdit : Form
    {
        #region Events

        public event EventHandler OnSaved;

        #endregion Events

        #region Properties

        private bool EditMode { get; set; }

        private Guid? Id { get; set; }

        private IBillRepository BillRepository { get; set; }

        private IGuestRepository GuestRepository { get; set; }

        private IRoomRepository RoomRepository { get; set; }

        private IHotelRepository HotelRepository { get; set; }

        #endregion Properties

        #region Ctor

        public BillEdit(bool editMode = false, Guid? id = null)
        {
            InitializeComponent();

            BillRepository = new BillRepository();
            GuestRepository = new GuestRepository();
            RoomRepository = new RoomRepository();
            HotelRepository = new HotelRepository();

            EditMode = editMode;
            Id = id;

            lblMessage.Visible = false;

            BindData();
        }

        #endregion Ctor

        #region Methods

        private void BindData()
        {
            var guests = GuestRepository.Get();
            cmbGuest.DisplayMember = nameof(WindowsFormsHotel.Guest.LastName);
            cmbGuest.ValueMember = nameof(WindowsFormsHotel.Guest.Id);
            cmbGuest.DataSource = guests;

            var rooms = RoomRepository.Get();
            cmbRoom.DisplayMember = nameof(WindowsFormsHotel.Room.Number);
            cmbRoom.ValueMember = nameof(WindowsFormsHotel.Room.Id);
            cmbRoom.DataSource = rooms;

            if (EditMode)
            {
                var entity = BillRepository.Get(Id.Value);
                cmbGuest.SelectedIndex = cmbGuest.FindString(entity.Guest.LastName.ToString());
                cmbRoom.SelectedIndex = cmbRoom.FindString(entity.Room.Number.ToString());
                txtAmount.Text = entity.Amount.ToString();
                txtService.Text = entity.Service;
            }
        }

        #endregion Methods

        #region UI Events

        private void btnSave_Click(object sender, EventArgs e)
        {
            //TODO provjerava se jesu li svi elementi unešeni
            if (cmbGuest.SelectedValue != null &&
                cmbRoom.SelectedValue != null &&
                !String.IsNullOrEmpty(txtAmount.Text) && Decimal.TryParse(txtAmount.Text, out decimal value) &&
                !String.IsNullOrEmpty(txtService.Text)

                )
            {
                WindowsFormsHotel.Bill entity = null;
                if (EditMode)
                {
                    //TODO edit mode - moramo dohvatiti postojeći entitet
                    entity = BillRepository.Get(Id.Value);
                }
                else
                {
                    //TODO create mode - moramo kreirati entitet
                    entity = new WindowsFormsHotel.Bill();

                    var hotel = HotelRepository.Get();
                    if (hotel != null)
                    {
                        entity.HotelId = hotel.Id;
                    }
                }

                entity.GuestId = (Guid)cmbGuest.SelectedValue;
                entity.RoomId = (Guid)cmbRoom.SelectedValue;
                entity.Service = txtService.Text;

                entity.Amount = Convert.ToDecimal(txtAmount.Text, new CultureInfo("hr-HR"));

                try
                {
                    if (EditMode)
                    {
                        BillRepository.Update(entity);
                    }
                    else
                    {
                        BillRepository.Create(entity);
                    }
                }
                catch (Exception ex)
                {
                    lblMessage.Text = "Dogodila se greška prilikom snimanja. Pokušajte ponovno kasnije.";
                }

                //TODO pozivamo event/događaj koji javi BillList formi da se odradilo snimanje i da se mogu ponovno učitati podatci u grid zbog izmjena na računu na ovoj formi.
                if (OnSaved != null)
                {
                    OnSaved(this, e);
                }

                lblMessage.Visible = false;

                this.Close();
            }
            else
            {
                lblMessage.Visible = true;
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        #endregion UI Events
    }
}