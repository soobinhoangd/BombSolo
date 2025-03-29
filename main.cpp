#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>

std::string direction[2];
const int speed = 20;
// Kích thước cửa sổ

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Kích thước người chơi, bom và chướng ngại vật
const int PLAYER_SIZE = 40;
const int BOMB_SIZE = 40;
const int EXPLOSION_RADIUS = 40;
const int OBSTACLE_SIZE = 40;

// Thời gian bom nổ (ms)
const int BOMB_TIMER = 1500;

// Thời gian vùng nổ tồn tại (ms)
const int EXPLOSION_DURATION = 1500;

// Số lượng chướng ngại vật
const int NUM_OBSTACLES = 2;

// Số lượng bot
const int NUM_BOTS = 2;

#include "BOMB.h"
#include "player.h"
#include "initSDL.h"
#include "checkCollision.h"
#include "LoadAndDrawTexture.h"
#include "isValidPosion.h"
#include "distance.h"
#include "bot.h"
#include "checkAlive.h"


int main(int argc, char* argv[]) {
    int dir=1;
    direction[1]="RobotBlue.png";
    direction[2]="Robotblue2.png";
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Khởi tạo SDL
    if (!initSDL(window, renderer)) {
        return 1;
    }

    // Tải các texture
    SDL_Texture* backgroundTexture = loadTexture("background.png", renderer);
    SDL_Texture* player1Texture = loadTexture(direction[1], renderer);
    SDL_Texture* player2Texture = loadTexture(direction[2], renderer);
    SDL_Texture* obstacleTexture = loadTexture("obstacle.png", renderer);
    SDL_Texture* bombTexture = loadTexture("Potion Icon.png", renderer);
    SDL_Texture* botTexture = loadTexture(direction[1], renderer);
    SDL_Texture* explosionTexture = loadTexture("explosion.png", renderer);
    SDL_Texture* deadPlayer = loadTexture("go.png",renderer);

    // Danh sách chướng ngại vật
    std::vector<SDL_Rect> obstacles;
   // CreObstacle(obstacles);
    // Tạo chướng ngại vật dọc theo cạnh trên
    for (int x = 0; x < SCREEN_WIDTH; x += OBSTACLE_SIZE) {
        obstacles.push_back({x, 0,OBSTACLE_SIZE,OBSTACLE_SIZE});
    }

    // Tạo chướng ngại vật dọc theo cạnh dưới
    for (int x = 0; x < SCREEN_WIDTH; x += OBSTACLE_SIZE) {
        obstacles.push_back({x, SCREEN_HEIGHT - OBSTACLE_SIZE,OBSTACLE_SIZE,OBSTACLE_SIZE});
    }

    // Tạo chướng ngại vật dọc theo cạnh trái
    for (int y = OBSTACLE_SIZE; y < SCREEN_HEIGHT - OBSTACLE_SIZE; y += OBSTACLE_SIZE) {
        obstacles.push_back({0, y,OBSTACLE_SIZE,OBSTACLE_SIZE});
    }

    // Tạo chướng ngại vật dọc theo cạnh phải
    for (int y = OBSTACLE_SIZE; y < SCREEN_HEIGHT - OBSTACLE_SIZE; y += OBSTACLE_SIZE) {
        obstacles.push_back({SCREEN_WIDTH - OBSTACLE_SIZE, y,OBSTACLE_SIZE,OBSTACLE_SIZE});
    }
   /* obstacles.push_back({320,40,40,40});
    obstacles.push_back({480,40,40,40});
    obstacles.push_back({520,40,40,40});
    obstacles.push_back({720,40,40,40});
    obstacles.push_back({120,80,40,40});
    obstacles.push_back({160,80,40,40});
    obstacles.push_back({240,80,40,40});
    obstacles.push_back({280,80,40,40});
    obstacles.push_back({320,80,40,40});
    obstacles.push_back({640,80,40,40});
    obstacles.push_back({400,120,40,40});
    obstacles.push_back({640,120,40,40});
    obstacles.push_back({40,160,40,40});
    obstacles.push_back({80,160,40,40});
    obstacles.push_back({240,160,40,40});
    obstacles.push_back({280,160,40,40});
    obstacles.push_back({400,160,40,40});
    obstacles.push_back({480,160,40,40});
    obstacles.push_back({560,160,40,40});
    obstacles.push_back({640,160,40,40});
    obstacles.push_back({720,160,40,40});
    obstacles.push_back({160,200,40,40});
    obstacles.push_back({640,200,40,40});
    obstacles.push_back({560,200,40,40});
    obstacles.push_back({120,240,40,40});
    obstacles.push_back({160,240,40,40});
    obstacles.push_back({320,240,40,40});
    obstacles.push_back({440,240,40,40});
    obstacles.push_back({640,240,40,40});
    obstacles.push_back({160,280,40,40});
    obstacles.push_back({440,280,40,40});
    obstacles.push_back({280,320,40,40});
    obstacles.push_back({440,320,40,40});
    obstacles.push_back({520,320,40,40});
    obstacles.push_back({560,320,40,40});
    obstacles.push_back({680,320,40,40});
    obstacles.push_back({120,360,40,40});
    obstacles.push_back({160,360,40,40});
    obstacles.push_back({120,400,40,40});
    obstacles.push_back({240,400,40,40});
    obstacles.push_back({280,400,40,40});
    obstacles.push_back({400,400,40,40});
    obstacles.push_back({480,400,40,40});
    obstacles.push_back({600,400,40,40});
    obstacles.push_back({680,400,40,40});
    obstacles.push_back({720,400,40,40});
    obstacles.push_back({240,440,40,40});
    obstacles.push_back({400,440,40,40});
    obstacles.push_back({240,480,40,40});
    obstacles.push_back({360,480,40,40});
    obstacles.push_back({400,480,40,40});
    obstacles.push_back({480,480,40,40});
    obstacles.push_back({560,480,40,40});
    obstacles.push_back({160,520,40,40});
    obstacles.push_back({680,520,40,40});*/
    // Khởi tạo người chơi
    Player player1, player2;
    do {
        player1 = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, true};
    } while (!isValidPosition(player1.x, player1.y, obstacles)); // Đảm bảo vị trí người chơi 1 không trùng chướng ngại vật

    do {
        player2 = {3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, true};
    } while (!isValidPosition(player2.x, player2.y, obstacles)); // Đảm bảo vị trí người chơi 2 không trùng chướng ngại vật

    // Khởi tạo bot
    std::vector<Bot> bots;
    for (int i = 0; i < NUM_BOTS; i++) {
        Bot bot;
        do {
            bot = {rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, true, 0, 0};
        } while (!isValidPosition(bot.x, bot.y, obstacles)); // Đảm bảo vị trí bot không trùng chướng ngại vật
        bots.push_back(bot);
    }

    // Danh sách bom
    std::vector<Bomb> bombs;

    // Biến kiểm tra vòng lặp chính
    bool isRunning = true;
    SDL_Event event;
   // GameState currentState = MAIN_MENU;

    // Vòng lặp chính của trò chơi
    while (isRunning) {
        // Xử lý sự kiện
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        // Xử lý phím di chuyển và đặt bom cho người chơi 1 (WASD, Space để đặt bom)
            if (event.type == SDL_KEYDOWN) {
                int newX = player1.x;
                int newY = player1.y;
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        newY -= speed;    player1Texture = loadTexture(direction[dir], renderer);
                        break;
                    case SDLK_s:
                        newY += speed;  player1Texture = loadTexture(direction[dir], renderer);
                        break;
                    case SDLK_a:
                        newX -= speed; dir=2;   player1Texture = loadTexture(direction[dir], renderer);
                        break;
                    case SDLK_d:
                        newX += speed; dir=1;   player1Texture = loadTexture(direction[dir], renderer);
                        break;
                    case SDLK_SPACE:
                        bombs.push_back({player1.x, player1.y, SDL_GetTicks(), false, 0});
                        break;
                }

                // Kiểm tra giới hạn bản đồ
                if (newX < 0) newX = 0;
                if (newX + PLAYER_SIZE > SCREEN_WIDTH) newX = SCREEN_WIDTH - PLAYER_SIZE;
                if (newY < 0) newY = 0;
                if (newY + PLAYER_SIZE > SCREEN_HEIGHT) newY = SCREEN_HEIGHT - PLAYER_SIZE;

                // Kiểm tra va chạm với chướng ngại vật trước khi di chuyển
                bool canMove = true;
                SDL_Rect playerRect = {newX, newY, PLAYER_SIZE, PLAYER_SIZE};
                for (const auto& obstacle : obstacles) {
                    if (checkCollision(playerRect.x, playerRect.y, playerRect.w, obstacle.x, obstacle.y, obstacle.w)) {
                        canMove = false;
                        break;
                    }
                }

                if (canMove) {
                    player1.x = newX;
                    player1.y = newY;
                }
            }

            // Xử lý phím di chuyển và đặt bom cho người chơi 2 (Mũi tên, Enter để đặt bom)
            if (event.type == SDL_KEYDOWN) {
                int newX = player2.x;
                int newY = player2.y;
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        newY -= speed;  player2Texture = loadTexture(direction[dir], renderer);
                        break;
                    case SDLK_DOWN:
                        newY += speed;  player2Texture = loadTexture(direction[dir], renderer);
                        break;
                    case SDLK_LEFT:
                        newX -= speed; dir=2; player2Texture = loadTexture(direction[dir], renderer);
                        break;
                    case SDLK_RIGHT:
                        newX += speed; dir=1; player2Texture = loadTexture(direction[dir], renderer);
                        break;
                    case SDLK_RETURN:
                        bombs.push_back({player2.x, player2.y, SDL_GetTicks(), false, 0});
                        break;
                }

                // Kiểm tra giới hạn bản đồ
                if (newX < 0) newX = 0;
                if (newX + PLAYER_SIZE > SCREEN_WIDTH) newX = SCREEN_WIDTH - PLAYER_SIZE;
                if (newY < 0) newY = 0;
                if (newY + PLAYER_SIZE > SCREEN_HEIGHT) newY = SCREEN_HEIGHT - PLAYER_SIZE;

                // Kiểm tra va chạm với chướng ngại vật trước khi di chuyển
                bool canMove = true;
                SDL_Rect playerRect = {newX, newY, PLAYER_SIZE, PLAYER_SIZE};
                for (const auto& obstacle : obstacles) {
                    if (checkCollision(playerRect.x, playerRect.y, playerRect.w, obstacle.x, obstacle.y, obstacle.w)) {
                        canMove = false;
                        break;
                    }
                }

                if (canMove) {
                    player2.x = newX;
                    player2.y = newY;
                }
            }


        // Di chuyển và đặt bom cho b
        for (auto& bot : bots) {
            if (SDL_GetTicks() - bot.lastMoveTime > 500) { // Di chuyển mỗi 0.5 giây
                moveBot(bot, obstacles);
                bot.lastMoveTime = SDL_GetTicks();
            }
        }

        // Kiểm tra bom nổ và vùng nổ
        Uint32 explosionTime = 0 ;
        for (auto& bomb : bombs) {
            if (!bomb.exploded && SDL_GetTicks() - bomb.plantTime >= BOMB_TIMER) {
                bomb.exploded = true;
                bomb.explosionTime = SDL_GetTicks(); // Lưu thời gian bắt đầu vùng nổ
            }

            // Kiểm tra va chạm giữa vùng nổ và người chơi
            explosionTime = bomb.explosionTime ;
            if (bomb.exploded && SDL_GetTicks() - bomb.explosionTime <= EXPLOSION_DURATION) {
                if (checkAlive(player1.x, player1.y, PLAYER_SIZE, bomb.x , bomb.y )) {
                    player1.alive = false;
                }

                if (checkAlive(player2.x, player2.y, PLAYER_SIZE, bomb.x , bomb.y )) {
                    player2.alive = false;
                }

                for (auto& bot : bots) {
                    if (checkAlive(bot.x, bot.y, PLAYER_SIZE, bomb.x , bomb.y )) {
                        bot.alive = false;
                    }
                }
            }
        }

         // Xóa bot đã chết khỏi danh sách (tùy chọn)
        bots.erase(std::remove_if(bots.begin(), bots.end(), [](const Bot& bot) {
            return !bot.alive;
        }), bots.end());

        // Xóa bom nếu vùng nổ bat dau
        bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](const Bomb& bomb) {
            return bomb.exploded && SDL_GetTicks() - bomb.explosionTime > BOMB_TIMER ;
        }), bombs.end());

        // Kiểm tra kết thúc trò chơi
        if (!player1.alive || !player2.alive) {
            if(SDL_GetTicks() - explosionTime >= EXPLOSION_DURATION)
            {
                isRunning=false;
            std::cout << "Game Over! Winner: " << (player1.alive ? "Player 1" : "Player 2") << std::endl;
            }
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu đen
        SDL_RenderClear(renderer);

         // Vẽ nền
        drawTexture(renderer, backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Vẽ chướng ngại vật
        for (const auto& obstacle : obstacles) {
            drawTexture(renderer, obstacleTexture, obstacle.x, obstacle.y, OBSTACLE_SIZE, OBSTACLE_SIZE);
        }

        // Vẽ bom và vùng nổ
        for (const auto& bomb : bombs) {
            if (!bomb.exploded) {
                drawTexture(renderer, bombTexture, bomb.x, bomb.y, BOMB_SIZE, BOMB_SIZE);
            } else if (SDL_GetTicks() - bomb.explosionTime <= EXPLOSION_DURATION) {
                drawTexture(renderer, explosionTexture, bomb.x - EXPLOSION_RADIUS, bomb.y , EXPLOSION_RADIUS *3 , EXPLOSION_RADIUS );
                drawTexture(renderer, explosionTexture, bomb.x , bomb.y - EXPLOSION_RADIUS, EXPLOSION_RADIUS , EXPLOSION_RADIUS *3 );
            }
        }

        // Vẽ người chơi
        if (player1.alive) {
            drawTexture(renderer, player1Texture, player1.x, player1.y, PLAYER_SIZE, PLAYER_SIZE);
        }
        else
        {
            drawTexture(renderer, deadPlayer, player1.x, player1.y , PLAYER_SIZE, PLAYER_SIZE);
        }
        if (player2.alive) {
            drawTexture(renderer, player2Texture, player2.x, player2.y, PLAYER_SIZE, PLAYER_SIZE);
        }
        else{
                drawTexture(renderer, deadPlayer, player2.x, player2.y , PLAYER_SIZE, PLAYER_SIZE);
        }

        // Vẽ bot
        for (const auto& bot : bots) {
            if (bot.alive) {
                drawTexture(renderer, botTexture, bot.x, bot.y, PLAYER_SIZE, PLAYER_SIZE);
            }
        }


        // Cập nhật màn hình
        SDL_RenderPresent(renderer);

        // Điều chỉnh tốc độ trò chơi
        SDL_Delay(16);
        }
    }
    // Giải phóng bộ nhớ và thoát SDL
    //Mix_FreeMusic(backgroundMusic);
   // Mix_FreeChunk(bombExplosionSound);
    SDL_DestroyTexture(player1Texture);
    SDL_DestroyTexture(player2Texture);
    SDL_DestroyTexture(obstacleTexture);
    SDL_DestroyTexture(bombTexture);
    SDL_DestroyTexture(botTexture);
    SDL_DestroyTexture(explosionTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
