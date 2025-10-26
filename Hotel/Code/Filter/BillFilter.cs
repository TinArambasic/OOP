using System;

namespace WindowsFormsHotel.Code
{
    public class BillFilter : BaseFilter
    {
        public Guid? RoomId { get; set; }

        public Guid? GuestId { get; set; }
    }
}