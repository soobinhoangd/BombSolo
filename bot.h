// Cấu trúc lưu trữ thông tin bot
struct Bot {
    int x, y;
    bool alive; // Trạng thái sống/chết
    Uint32 lastMoveTime; // Thời gian di chuyển cuối cùng
    Uint32 lastBombTime; // Thời gian đặt bom cuối cùng
};


// Hàm di chuyển bot
void moveBot(Bot& bot, const std::vector<SDL_Rect>& obstacles) {
    int Directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int dir = rand() % 4;
    int newX = bot.x + Directions[dir][0] * 20;
    int newY = bot.y + Directions[dir][1] * 20;

    if (isValidPosition(newX, newY, obstacles)) {
        bot.x = newX;
        bot.y = newY;
    }
    if(bot.x<0) bot.x=0;
    if(bot.x+PLAYER_SIZE>SCREEN_WIDTH) bot.x=SCREEN_WIDTH-PLAYER_SIZE;
    if(bot.y<0)  bot.y=0;
    if(bot.y+PLAYER_SIZE>SCREEN_HEIGHT) bot.y=SCREEN_HEIGHT-PLAYER_SIZE;
}
