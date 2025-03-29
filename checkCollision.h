// Hàm kiểm tra va chạm giữa hai hình chữ nhật
bool checkCollision(int x1, int y1, int size1, int x2, int y2, int size2) {
    return (x1  < x2 + size2 && x1 + size1 > x2 &&

            y1 < y2 + size2 && y1 + size1 > y2 );
}
