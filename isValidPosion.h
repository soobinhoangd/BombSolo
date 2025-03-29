// Hàm kiểm tra vị trí có hợp lệ không (không trùng với chướng ngại vật)
bool isValidPosition(int x, int y, const std::vector<SDL_Rect>& obstacles) {
    for (const auto& obstacle : obstacles) {
        if (checkCollision(x, y, PLAYER_SIZE, obstacle.x, obstacle.y, OBSTACLE_SIZE)) {
            return false;
        }
    }
    return true;
}
