using System;
using System.Collections.Generic;
using System.Linq;

namespace WindowsFormsHotel.Code
{
    public class GuestRepository : IGuestRepository
    {
        public List<Guest> Get(GuestFilter filter = null)
        {
            List<Guest> toReturn = null;

            using (HotelContext context = new HotelContext())
            {
                var query = context.Guest.AsQueryable();

                if (filter != null)
                {
                    if (filter.Id.HasValue)
                    {
                        query = query.Where(p => p.Id == filter.Id.Value);
                    }

                    if (!String.IsNullOrEmpty(filter.Text))
                    {
                        query = query.Where(p => p.FirstName.ToString().Contains(filter.Text) ||
                            p.LastName.ToString().Contains(filter.Text) ||
                            p.PIN.ToString().Contains(filter.Text));
                    }
                }

                toReturn = query.ToList();
            }

            return toReturn;
        }
    }
}