using System;
using System.Collections.Generic;
using System.Linq;

namespace WindowsFormsHotel.Code
{
    public class RoomRepository : IRoomRepository
    {
        public List<Room> Get(RoomFilter filter = null)
        {
            List<Room> toReturn = null;

            using (HotelContext context = new HotelContext())
            {
                var query = context.Room.AsQueryable();
                if (filter != null)
                {
                    if (filter.Id.HasValue)
                    {
                        query = query.Where(p => p.Id == filter.Id.Value);
                    }

                    if (!String.IsNullOrEmpty(filter.Text))
                    {
                        query = query.Where(p => p.Number.ToString().Contains(filter.Text));
                    }
                }

                toReturn = query.ToList();
            }

            return toReturn;
        }
    }
}