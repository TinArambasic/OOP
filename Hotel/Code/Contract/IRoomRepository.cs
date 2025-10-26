using System.Collections.Generic;

namespace WindowsFormsHotel.Code
{
    public interface IRoomRepository
    {
        List<Room> Get(RoomFilter filter = null);
    }
}