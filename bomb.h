// Cấu trúc lưu trữ thông tin bom
struct Bomb {
    int x, y;
    Uint32 plantTime; // Thời gian đặt bom
    bool exploded;    // Trạng thái bom đã nổ hay chưa
    Uint32 explosionTime; // Thời gian vùng nổ bắt đầu
};
