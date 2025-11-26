#include <iostream>
#include <cmath>
#include <SDL3/SDL.h>

///dimensiunile la fereastra
constexpr int WINDOW_WIDTH{ 800 };
constexpr int WINDOW_HEIGHT{ 800 };
constexpr float PI = 3.14159265f;

SDL_Window* window{ nullptr };
SDL_Renderer* renderer{ nullptr };
SDL_Event currentEvent;
SDL_Color backgroundColor{ 0, 0, 0, 255 };

bool quit{ false };
float displayScale{ 1.0f };

///starea jocului: 0=joc, 1=castigat, 2=pierdut
int gameState = 0;
///o variabila sa nu imi afiseze mesajul in consola de 1000 de ori
bool messagePrinted = false;

struct Brick {
    float x, y;
    float w, h;
    bool active;
    int lives;
};

struct Paddle {
    float x, y;
    float w, h;
    float speed;
};

struct Ball {
    float x, y;
    float radius;
    float dx, dy;
    bool launched;
    float speedVal;
};

///vectori globali
Brick bricks[51];
Paddle paddle;
Ball ball;

void initGame() {
    gameState = 0;
    messagePrinted = false;

    ///resetam titlul ferestrei la cel normal
    if (window) SDL_SetWindowTitle(window, "CodeRun Breakout HARD");

    ///setez paleta
    paddle.w = 100.0f;
    paddle.h = 25.0f;
    paddle.x = WINDOW_WIDTH / 2.0f;
    paddle.y = WINDOW_HEIGHT - (paddle.h / 2.0f);
    paddle.speed = 8.0f;

    ///setez mingea
    ball.radius = 10.0f;
    ball.launched = false;
    ball.speedVal = paddle.speed;
    ball.dx = 0.0f;
    ball.dy = 0.0f;
    ball.x = paddle.x;
    ball.y = paddle.y - (paddle.h / 2.0f) - ball.radius;

    ///setez caramizile
    float brickWidth = static_cast<float>(WINDOW_WIDTH) / 17.0f;
    float brickHeight = 20.0f;

    int index = 0;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 17; ++col) {
            bricks[index].w = brickWidth;
            bricks[index].h = brickHeight;
            bricks[index].active = true;
            bricks[index].x = (col * brickWidth) + (brickWidth / 2.0f);
            bricks[index].y = 100.0f + (row * brickHeight) + (brickHeight / 2.0f);

            ///vieti: rosu(1), galben(2), verde(3)
            if (row == 0) bricks[index].lives = 1;
            else if (row == 1) bricks[index].lives = 2;
            else bricks[index].lives = 3;

            index++;
        }
    }

    ///Curatam consola cand dam restart (optional)
    system("cls");
    std::cout << "Jocul a inceput! Sparge caramizile!" << std::endl;
}

bool initWindow() {
    bool success{ true };
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        success = false;
    }
    else {
        displayScale = SDL_GetDisplayContentScale(1);
        if (displayScale == 0) displayScale = 1.0f;

        if (!SDL_CreateWindowAndRenderer("CodeRun Breakout HARD", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
            success = false;
        }
        else {
            SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
            SDL_RenderClear(renderer);
        }
    }
    return success;
}

void processEvents() {
    while (SDL_PollEvent(&currentEvent)) {
        if (currentEvent.type == SDL_EVENT_QUIT) quit = true;
        if (currentEvent.type == SDL_EVENT_KEY_DOWN) {
            switch (currentEvent.key.key) {
            case SDLK_SPACE:
                if (!ball.launched && gameState == 0) {
                    ball.launched = true;
                    ball.dx = 0.0f;
                    ball.dy = -ball.speedVal;
                }
                break;
            case SDLK_R:
                ///reset doar la final
                if (gameState != 0) initGame();
                break;
            case SDLK_ESCAPE:
                quit = true;
                break;
            }
        }
    }
}

bool checkCollision(const Ball& b, float rx, float ry, float rw, float rh, float& overlapX, float& overlapY) {
    float closestX = std::max(rx - rw / 2.0f, std::min(b.x, rx + rw / 2.0f));
    float closestY = std::max(ry - rh / 2.0f, std::min(b.y, ry + rh / 2.0f));

    float distanceX = b.x - closestX;
    float distanceY = b.y - closestY;
    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    if (distanceSquared < (b.radius * b.radius)) {
        float ballLeft = b.x - b.radius;
        float ballRight = b.x + b.radius;
        float ballTop = b.y - b.radius;
        float ballBottom = b.y + b.radius;
        float rectLeft = rx - rw / 2.0f;
        float rectRight = rx + rw / 2.0f;
        float rectTop = ry - rh / 2.0f;
        float rectBottom = ry + rh / 2.0f;

        float ox = std::min(ballRight, rectRight) - std::max(ballLeft, rectLeft);
        float oy = std::min(ballBottom, rectBottom) - std::max(ballTop, rectTop);
        overlapX = ox; overlapY = oy;
        return true;
    }
    return false;
}

void update() {
    ///Daca jocul s-a terminat, verificam daca am afisat mesajul
    if (gameState != 0) {
        if (!messagePrinted) {
            messagePrinted = true;
            if (gameState == 1) {
                ///CASTIGAT - Setam titlul si scriem in consola cu VERDE
                SDL_SetWindowTitle(window, "4.bin WON!!! <3 <3 <3");
                /// \033[32m este codul pentru VERDE in consola
                std::cout << "\033[32m" << "4.bin WON!!! <3 <3 <3" << "\033[0m" << std::endl;
                std::cout << "Press R to play again!" << std::endl;
            }
            else {
                ///PIERDUT - Setam titlul si scriem in consola cu ROSU
                SDL_SetWindowTitle(window, "4.bin LOST!!! :( :( :(");
                /// \033[31m este codul pentru ROSU in consola
                std::cout << "\033[31m" << "4.bin LOST!!! :( :( :(" << "\033[0m" << std::endl;
                std::cout << "\033[31m" << "Press R to play again!" << "\033[0m" << std::endl;
            }
        }
        return; ///Oprim animatia
    }

    const bool* keyState = SDL_GetKeyboardState(nullptr);

    if (keyState[SDL_SCANCODE_LEFT]) paddle.x -= paddle.speed;
    if (keyState[SDL_SCANCODE_RIGHT]) paddle.x += paddle.speed;

    if (paddle.x - (paddle.w / 2.0f) < 0) paddle.x = paddle.w / 2.0f;
    if (paddle.x + (paddle.w / 2.0f) > WINDOW_WIDTH) paddle.x = WINDOW_WIDTH - (paddle.w / 2.0f);

    if (!ball.launched) {
        ball.x = paddle.x;
        ball.y = paddle.y - (paddle.h / 2.0f) - ball.radius;
    }
    else {
        ball.x += ball.dx;
        ball.y += ball.dy;

        if (ball.x - ball.radius < 0) { ball.x = ball.radius; ball.dx = -ball.dx; }
        if (ball.x + ball.radius > WINDOW_WIDTH) { ball.x = WINDOW_WIDTH - ball.radius; ball.dx = -ball.dx; }
        if (ball.y - ball.radius < 0) { ball.y = ball.radius; ball.dy = -ball.dy; }

        ///PIERDERE
        if (ball.y - ball.radius > WINDOW_HEIGHT) {
            gameState = 2;
        }

        float ox, oy;
        if (checkCollision(ball, paddle.x, paddle.y, paddle.w, paddle.h, ox, oy)) {
            float hitPoint = ball.x - paddle.x;
            float normalizedHit = hitPoint / (paddle.w / 2.0f);
            if (normalizedHit < -1.0f) normalizedHit = -1.0f;
            if (normalizedHit > 1.0f) normalizedHit = 1.0f;

            float angleDeg = normalizedHit * 80.0f;
            float angleRad = angleDeg * (PI / 180.0f);

            ball.dx = std::sin(angleRad) * ball.speedVal;
            ball.dy = -std::abs(std::cos(angleRad) * ball.speedVal);
            ball.y = paddle.y - (paddle.h / 2.0f) - ball.radius - 1.0f;
        }

        int activeCount = 0;
        for (int i = 0; i < 51; ++i) {
            if (bricks[i].active) {
                activeCount++;
                if (checkCollision(ball, bricks[i].x, bricks[i].y, bricks[i].w, bricks[i].h, ox, oy)) {
                    bricks[i].lives--;
                    if (bricks[i].lives <= 0) bricks[i].active = false;

                    if (ox < oy) {
                        ball.dx = -ball.dx;
                        if (ball.x < bricks[i].x) ball.x -= ox; else ball.x += ox;
                    }
                    else {
                        ball.dy = -ball.dy;
                        if (ball.y < bricks[i].y) ball.y -= oy; else ball.y += oy;
                    }
                }
            }
        }
        ///CASTIG
        if (activeCount == 0) gameState = 1;
    }
}

void drawFilledCircle(SDL_Renderer* renderer, float cx, float cy, float radius) {
    for (float dy = -radius; dy <= radius; dy++) {
        float dx = std::sqrt(radius * radius - dy * dy);
        SDL_RenderLine(renderer, cx - dx, cy + dy, cx + dx, cy + dy);
    }
}

void drawFrame() {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(renderer);

    ///Caramizi
    for (int i = 0; i < 51; ++i) {
        if (bricks[i].active) {
            if (bricks[i].lives == 1) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            else if (bricks[i].lives == 2) SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            else SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

            SDL_FRect brickRect;
            brickRect.x = bricks[i].x - (bricks[i].w / 2.0f);
            brickRect.y = bricks[i].y - (bricks[i].h / 2.0f);
            brickRect.w = bricks[i].w - 1.0f;
            brickRect.h = bricks[i].h - 1.0f;
            SDL_RenderFillRect(renderer, &brickRect);
        }
    }

    ///Paleta isi schimba culoarea la final
    if (gameState == 0) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    else if (gameState == 1) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); ///Verde
    else SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); ///Rosu

    SDL_FRect paddleRect;
    paddleRect.x = paddle.x - (paddle.w / 2.0f);
    paddleRect.y = paddle.y - (paddle.h / 2.0f);
    paddleRect.w = paddle.w;
    paddleRect.h = paddle.h;
    SDL_RenderFillRect(renderer, &paddleRect);

    ///Mingea
    if (gameState != 1) {
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
        drawFilledCircle(renderer, ball.x, ball.y, ball.radius);
    }

    SDL_RenderPresent(renderer);
}

void cleanup() {
    if (renderer) { SDL_DestroyRenderer(renderer); renderer = nullptr; }
    if (window) { SDL_DestroyWindow(window); window = nullptr; }
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!initWindow()) return -1;

    initGame();
    SDL_zero(currentEvent);

    while (!quit) {
        Uint64 start = SDL_GetTicks();

        processEvents();
        update();
        drawFrame();

        Uint64 end = SDL_GetTicks();
        float elapsedMS = (float)(end - start);
        if (elapsedMS < 16.666f) {
            SDL_Delay((Uint32)(16.666f - elapsedMS));
        }
    }

    cleanup();
    return 0;
}

