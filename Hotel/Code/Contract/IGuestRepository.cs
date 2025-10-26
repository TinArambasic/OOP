using System.Collections.Generic;

namespace WindowsFormsHotel.Code
{
    public interface IGuestRepository
    {
        List<Guest> Get(GuestFilter filter = null);
    }
}