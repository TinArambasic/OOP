using System;
using System.Linq;

namespace WindowsFormsHotel.Code
{
    public class HotelRepository : IHotelRepository
    {
        public Hotel Get()
        {
            Hotel entity = null;
            using (HotelContext context = new HotelContext())
            {
                //TODO primjetite da ovdje ne proslijeđujemo Id i ne radimo filter po Id-u. Razlog je što ćemo uvijek u bazi podataka imati samo jedan hotel koji koristimo za aplikaciju.
                entity = context.Hotel.FirstOrDefault();
            }

            return entity;
        }
    }
}