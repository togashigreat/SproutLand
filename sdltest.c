#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

bool running = true;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *grassTexture = NULL;
SDL_Texture *playerTexture = NULL;

SDL_Rect playerSrc;
SDL_Rect playerDest;

float playerSpeed = 3.0f;

SDL_Color bkgColor = {147, 211, 196, 255};

void drawScene() {
    // Draw grass
    SDL_Rect grassDest = {100, 50, 0, 0};
    SDL_QueryTexture(grassTexture, NULL, NULL, &grassDest.w, &grassDest.h);
    SDL_RenderCopy(renderer, grassTexture, NULL, &grassDest);

    // Draw player sprite
    SDL_RenderCopy(renderer, playerTexture, &playerSrc, &playerDest);
}

void input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_w:
                case SDLK_UP:
                    SDL_Log("Moving Up");
                    playerDest.y -= playerSpeed;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    SDL_Log("Moving Down");
                    playerDest.y += playerSpeed;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    SDL_Log("Moving Left");
                    playerDest.x -= playerSpeed;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    SDL_Log("Moving Right");
                    playerDest.x += playerSpeed;
                    break;
            }
        }
    }
}

void update() {
    // Nothing dynamic here except input
}

void render() {
    SDL_SetRenderDrawColor(renderer, bkgColor.r, bkgColor.g, bkgColor.b, bkgColor.a);
    SDL_RenderClear(renderer);

    drawScene();

    SDL_RenderPresent(renderer);
}

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Sprout SDL Game",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load grass texture
    grassTexture = IMG_LoadTexture(renderer, "./res/Tilesets/Grass.png");
    if (!grassTexture) SDL_Log("Failed to load grass: %s", SDL_GetError());

    // Load player sprite
    playerTexture = IMG_LoadTexture(renderer, "./res/Characters/BasicCharakterSpritesheet.png");
    if (!playerTexture) SDL_Log("Failed to load player: %s", SDL_GetError());

    // Set source and destination rectangles
    playerSrc = (SDL_Rect){0, 0, 48, 48};
    playerDest = (SDL_Rect){200, 200, 100, 100};
}

void quit() {
    SDL_DestroyTexture(grassTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main() {
    init();

    while (running) {
        input();
        update();
        render();
        SDL_Delay(16);  // ~60 FPS
    }

    quit();
    return 0;
}

