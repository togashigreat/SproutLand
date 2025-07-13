#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

Color bkgColor = {147, 211, 196, 255};

Texture2D grassSprite;
Texture2D playerSprite;
Rectangle playerSrc;
Rectangle playerDest;

float playerSpeed = 2.5f;
bool running = true;


// Joystick state
Vector2 joyCenter = {100, SCREEN_HEIGHT - 100};  // Fixed position
float joyRadius = 60;
float joyInnerRadius = 25;
Vector2 joyTouch = {0};
bool joyActive = false;

void drawScene() {
    DrawTexture(grassSprite, 100, 50, WHITE);
    DrawTexturePro(playerSprite, playerSrc, playerDest, (Vector2){0, 0}, 0, WHITE);
}

void drawJoystick() {
    DrawCircleV(joyCenter, joyRadius, Fade(GRAY, 0.3f));
  
    if (joyActive) {
        DrawCircleV(joyTouch, joyInnerRadius, Fade(DARKGRAY, 0.8f));
    } else {
        DrawCircleV(joyCenter, joyInnerRadius, Fade(DARKGRAY, 0.4f));
    }
}

void inputJoystick() {
    if (GetTouchPointCount() > 0) {
        Vector2 touchPos = GetTouchPosition(0);
        float dist = Vector2Distance(touchPos, joyCenter);
        if (dist <= joyRadius) {
            joyTouch = touchPos;
            joyActive = true;

            Vector2 direction = Vector2Normalize(Vector2Subtract(touchPos, joyCenter));
            playerDest.x += direction.x * playerSpeed;
            playerDest.y += direction.y * playerSpeed;
        }
    } else {
        joyActive = false;
    }
}

void update() {
    running = !WindowShouldClose();
    inputJoystick();
}

void render() {
    BeginDrawing();
    ClearBackground(bkgColor);
    drawScene();
    drawJoystick();
    EndDrawing();
}

void init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sprout Game");
    SetExitKey(0);
    SetTargetFPS(60);

    grassSprite = LoadTexture("Grass.png");
    playerSprite = LoadTexture("BasicCharakterSpritesheet.png");

    playerSrc = (Rectangle){0, 0, 48, 48};
    playerDest = (Rectangle){200, 200, 100, 100};
}

void quit() {
    UnloadTexture(grassSprite);
    UnloadTexture(playerSprite);
    CloseWindow();
}

int main() {
    init();
    while (running) {
        update();
        render();
    }
    quit();
    return 0;
}

