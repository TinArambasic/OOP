using System;
using System.Windows.Forms;
using WindowsFormsHotel.Code;

namespace WindowsFormsHotel.Forms.Bill
{
    public partial class BillList : Form
    {
        #region Fields

        private readonly string GuestColumnKey = "Gost";
        private readonly string RoomColumnKey = "Soba";

        private readonly string GridEditColumnKey = "btnEdit";
        private readonly string GridDeleteColumnKey = "btnDelete";
        private readonly string GridNumberColumnKey = "Broj računa";
        private readonly string GridIdColumnKey = "Id";

        #endregion Fields

        #region Properties

        private IBillRepository BillRepository { get; set; }

        #endregion Properties

        #region Ctor

        public BillList()
        {
            InitializeComponent();

            BillRepository = new BillRepository();

            SetGrid();

            BindData();
        }

        #endregion Ctor

        #region Methods

        private void SetGrid()
        {
            //TODO postavljanje kolona grida.
            gridData.ColumnCount = 6;
            gridData.AutoGenerateColumns = false;

            gridData.Columns[0].Name = GridIdColumnKey;
            gridData.Columns[0].DataPropertyName = GridIdColumnKey;
            gridData.Columns[0].Visible = false;

            gridData.Columns[1].Name = GridNumberColumnKey;
            gridData.Columns[1].DataPropertyName = "Number";
            gridData.Columns[2].Name = GuestColumnKey;
            gridData.Columns[2].DataPropertyName = "Guest.FirstName";
            gridData.Columns[3].Name = RoomColumnKey;
            gridData.Columns[3].DataPropertyName = "Room.Number";
            gridData.Columns[4].Name = "Iznos";
            gridData.Columns[4].DataPropertyName = "Amount";
            gridData.Columns[5].Name = "Usluga";
            gridData.Columns[5].DataPropertyName = "Service";

            //TODO dodavanje akcija u grid
            DataGridViewButtonColumn btnEdit = new DataGridViewButtonColumn();
            gridData.Columns.Add(btnEdit);
            btnEdit.HeaderText = String.Empty;
            btnEdit.Text = "Izmijeni";
            btnEdit.Name = GridEditColumnKey;
            btnEdit.UseColumnTextForButtonValue = true;

            DataGridViewButtonColumn btnDelete = new DataGridViewButtonColumn();
            gridData.Columns.Add(btnDelete);
            btnDelete.HeaderText = String.Empty;
            btnDelete.Text = "Obriši";
            btnDelete.Name = GridDeleteColumnKey;
            btnDelete.UseColumnTextForButtonValue = true;
        }

        private void BindData()
        {
            //TODO metoda koju pozivamo kad je potrebno prikazati podatke
            var filter = new BillFilter();
            filter.Text = txtSearch.Text;

            var data = BillRepository.Get(filter);
            gridData.DataSource = data;
        }

        #endregion Methods

        #region UI Events

        private void btnAdd_Click(object sender, EventArgs e)
        {
            BillEdit form = new BillEdit();
            form.OnSaved += Form_OnSaved;
            form.Show();
        }

        private void Form_OnSaved(object sender, EventArgs e)
        {
            BindData();
        }

        private void txtSearch_TextChanged(object sender, EventArgs e)
        {
            BindData();
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            txtSearch.Text = String.Empty;

            BindData();
        }

        private void gridData_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                int editColumnIndex = gridData.Columns[GridEditColumnKey].Index;
                int deleteColumnIndex = gridData.Columns[GridDeleteColumnKey].Index;
                int numberColumnIndex = gridData.Columns[GridDeleteColumnKey].Index;

                long billNumber = (long)gridData.Rows[e.RowIndex].Cells[GridNumberColumnKey].Value;
                Guid id = (Guid)gridData.Rows[e.RowIndex].Cells[GridIdColumnKey].Value;

                if (e.ColumnIndex == editColumnIndex)
                {
                    BillEdit editForm = new BillEdit(true, id);
                    editForm.OnSaved += Form_OnSaved;
                    editForm.Show();
                }
                else if (e.ColumnIndex == deleteColumnIndex)
                {
                    MessageBoxButtons amessageBoxButtons = MessageBoxButtons.YesNo;
                    DialogResult result = MessageBox.Show($"Jeste li sigurni da želite obrisati račun broj: {billNumber}", "Brisanje računa", amessageBoxButtons);

                    if (result == DialogResult.Yes)
                    {
                        BillRepository.Delete(id);

                        BindData();
                    }
                }
            }
        }

        private void gridData_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            WindowsFormsHotel.Bill data = gridData.Rows[e.RowIndex].DataBoundItem as WindowsFormsHotel.Bill;

            //TODO na ovaj način dolazimo do podataka broja sobe i gostovih imena i prezimena.
            gridData.Rows[e.RowIndex].Cells[GuestColumnKey].Value = $"{data.Guest.FirstName} {data.Guest.LastName}";
            gridData.Rows[e.RowIndex].Cells[RoomColumnKey].Value = data.Room.Number;
        }

        #endregion UI Events
    }
}