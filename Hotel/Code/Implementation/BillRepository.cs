using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;

namespace WindowsFormsHotel.Code
{
    public class BillRepository : IBillRepository
    {
        public Bill Get(Guid id)
        {
            Bill entity = null;
            using (HotelContext context = new HotelContext())
            {
                entity = context.Bill
                    .Include(p => p.Guest)
                    .Include(p => p.Room)
                    .FirstOrDefault(p => p.Id == id);
            }

            return entity;
        }

        public List<Bill> Get(BillFilter filter)
        {
            List<Bill> toReturn = null;

            using (HotelContext context = new HotelContext())
            {
                var query = context.Bill.AsQueryable();

                //TODO da bi pojednostavili implementaciju uključujemo Guest i Room objekte iz baze.
                query = query.Include(p => p.Guest);
                query = query.Include(path => path.Room);

                if (filter != null)
                {
                    if (filter.Id.HasValue)
                    {
                        query = query.Where(p => p.Id == filter.Id.Value);
                    }

                    if (!String.IsNullOrEmpty(filter.Text))
                    {
                        query = query.Where(p => p.Guest.FirstName.Contains(filter.Text) ||
                            p.Guest.LastName.Contains(filter.Text) ||
                            p.Guest.Phone.Contains(filter.Text) ||
                            p.Guest.PIN.Contains(filter.Text) ||
                            p.Service.Contains(filter.Text) ||
                            p.Room.Number.ToString().Contains(filter.Text));
                    }

                    if (filter.RoomId.HasValue)
                    {
                        query = query.Where(p => p.RoomId == filter.RoomId.Value);
                    }

                    if (filter.GuestId.HasValue)
                    {
                        query = query.Where(p => p.GuestId == filter.GuestId.Value);
                    }
                }

                toReturn = query.ToList();
            }

            return toReturn;
        }

        public Bill Create(Bill model)
        {
            if (model == null)
            {
                throw new ArgumentNullException();
            }

            bool result = false;
            Bill toReturn = null;

            model.Id = Guid.NewGuid();
            model.DateCreated =
            model.DateUpdated = DateTime.Now;

            using (HotelContext context = new HotelContext())
            {
                context.Bill.Add(model);
                result = context.SaveChanges() > 0;

                if (result)
                {
                    toReturn = Get(model.Id);
                }
            }

            return toReturn;
        }

        public bool Update(Bill model)
        {
            if (model == null)
            {
                throw new ArgumentNullException();
            }

            Bill entity = null;
            bool result = false;

            using (HotelContext context = new HotelContext())
            {
                entity = context.Bill.Find(model.Id);

                if (entity != null)
                {
                    entity.GuestId = model.GuestId;
                    entity.HotelId = model.HotelId;
                    entity.RoomId = model.RoomId;
                    entity.Service = model.Service;
                    entity.Amount = model.Amount;
                    entity.DateUpdated = DateTime.Now;

                    result = context.SaveChanges() > 0;
                }
            }

            return result;
        }

        public bool Delete(Guid id)
        {
            bool result = false;

            using (HotelContext context = new HotelContext())
            {
                Bill toDelete = context.Bill.Find(id);

                if (toDelete != null)
                {
                    context.Bill.Remove(toDelete);
                }

                result = context.SaveChanges() > 0;
            }

            return result;
        }
    }
}