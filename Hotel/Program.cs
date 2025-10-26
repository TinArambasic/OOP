using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using WindowsFormsHotel.Forms.Main;

namespace WindowsFormsHotel
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //TODO prvi upit na bazu podataka preko EF-a traje duže
            //pa ga odrađujemo ovdje da se ubrza učitavanje podataka na 
            //inicijalnom ekranu.
            using (HotelContext context = new HotelContext())
            {
                context.Hotel.FirstOrDefault();
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());

            
        }
    }
}
