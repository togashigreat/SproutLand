#include <raylib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

bool running = true;

Color bkgColor = {147, 211, 196, 255};
Texture2D grassSprite;
Texture2D playerSprite;
Rectangle playerSrc;
Rectangle playerDest;

float playerSpeed = 3;


void drawScene() {
  DrawTexture(grassSprite, 100, 50, WHITE);
  DrawTexturePro(playerSprite, playerSrc, playerDest, (Vector2){0,0}, 0, WHITE);
}

void input() {
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    TraceLog(LOG_INFO, "Moving up");
    playerDest.y -= playerSpeed;
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    TraceLog(LOG_INFO, "Moving Down");
    playerDest.y += playerSpeed;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    TraceLog(LOG_INFO, "Moving Left");
    playerDest.x -= playerSpeed;
  }
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    TraceLog(LOG_INFO, "Moving Right");
    playerDest.x += playerSpeed;
  }
}

void update() {
  running = !WindowShouldClose();
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

  
  playerSrc = (Rectangle){0,0,48,48};
  playerDest = (Rectangle){200,200,100,100};

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
