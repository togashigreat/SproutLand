#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

Color bkgColor = {147, 211, 196, 255};

Texture2D grassSprite;
Texture2D playerSprite;
Rectangle playerSrc;
Rectangle playerDest;

Vector2 targetPos;
float playerSpeed = 2;
bool hasTarget = false;


void drawScene() {
    DrawTexture(grassSprite, 100, 50, WHITE);
    DrawTexturePro(playerSprite, playerSrc, playerDest, (Vector2){0, 0}, 0.0f, WHITE);
}

void input() {
    if (GetTouchPointCount() > 0) {
        Vector2 touch = GetTouchPosition(0);

        // Center player on touch
        targetPos.x = touch.x - playerDest.width / 2;
        targetPos.y = touch.y - playerDest.height / 2;
        hasTarget = true;
    }
}

void moveToTarget() {
    if (hasTarget) {
        Vector2 current = {playerDest.x, playerDest.y};
        Vector2 direction = Vector2Subtract(targetPos, current);
        float distance = Vector2Length(direction);

        if (distance > 1.0f) {
            Vector2 normalized = Vector2Normalize(direction);
            playerDest.x += normalized.x * playerSpeed;
            playerDest.y += normalized.y * playerSpeed;
        } else {
            hasTarget = false;  // Stop moving
        }
    }
}

void update() {
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
    SetTargetFPS(60);
    SetExitKey(0);

    // Load images from assets/ folder (no "./")
    grassSprite = LoadTexture("Grass.png");
    playerSprite = LoadTexture("BasicCharakterSpritesheet.png");

    playerSrc = (Rectangle){0, 0, 48, 48};      // First frame
    playerDest = (Rectangle){200, 200, 100, 100}; // Size on screen

    targetPos = (Vector2){playerDest.x, playerDest.y};
}

void quit() {
    UnloadTexture(grassSprite);
    UnloadTexture(playerSprite);
    CloseWindow();
}

int main() {
    init();

    while (!WindowShouldClose()) {
        input();
        update();
        render();
    }

    quit();
    return 0;
}

