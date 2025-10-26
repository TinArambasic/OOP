using System;
using System.Collections.Generic;

namespace WindowsFormsHotel.Code
{
    public interface IBillRepository
    {
        Bill Create(Bill model);
        bool Delete(Guid id);
        List<Bill> Get(BillFilter filter);
        Bill Get(Guid id);
        bool Update(Bill model);
    }
}