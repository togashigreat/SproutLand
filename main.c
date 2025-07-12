#include <raylib.h>
#include <stdbool.h>
#include <raymath.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

bool running = true;

Color bkgColor = {147, 211, 196, 255};
Texture2D grassSprite;
Texture2D playerSprite;
Rectangle playerSrc;
Rectangle playerDest;

float playerSpeed = 2.0f;
Vector2 targetPos;
bool hasTarget = false;


void drawScene() {
    DrawTexture(grassSprite, 100, 50, WHITE);
    DrawTexturePro(playerSprite, playerSrc, playerDest, (Vector2){0, 0}, 0, WHITE);
}

void input() {
#if defined(PLATFORM_ANDROID)
    if (GetTouchPointCount() > 0) {
        Vector2 touch = GetTouchPosition(0);
        targetPos.x = touch.x - playerDest.width / 2;
        targetPos.y = touch.y - playerDest.height / 2;
        hasTarget = true;
    }
#else
    // For debugging on desktop with mouse
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 click = GetMousePosition();
        targetPos.x = click.x - playerDest.width / 2;
        targetPos.y = click.y - playerDest.height / 2;
        hasTarget = true;
    }
#endif
}

void moveToTarget() {
    if (hasTarget) {
        Vector2 current = (Vector2){playerDest.x, playerDest.y};
        Vector2 direction = Vector2Subtract(targetPos, current);
        float distance = Vector2Length(direction);

        if (distance > 1.0f) {
            Vector2 normalized = Vector2Normalize(direction);
            playerDest.x += normalized.x * playerSpeed;
            playerDest.y += normalized.y * playerSpeed;
        } else {
            hasTarget = false; // Reached destination
        }
    }
}

void update() {
    running = !WindowShouldClose();
    moveToTarget();
}

void render() {
    BeginDrawing();
    ClearBackground(bkgColor);

    drawScene();

    EndDrawing();
}

void init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sprout Game");
    SetExitKey(0);
    SetTargetFPS(60);

    grassSprite = LoadTexture("./res/Tilesets/Grass.png");
    playerSprite = LoadTexture("./res/Characters/BasicCharakterSpritesheet.png");

    playerSrc = (Rectangle){0, 0, 48, 48};
    playerDest = (Rectangle){200, 200, 100, 100};

    targetPos = (Vector2){playerDest.x, playerDest.y};
}

void quit() {
    UnloadTexture(grassSprite);
    UnloadTexture(playerSprite);
    CloseWindow();
}

int main() {
    init();

    while (running) {
        input();
        update();
        render();
    }

    quit();
    return 0;
}

