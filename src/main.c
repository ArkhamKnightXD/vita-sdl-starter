#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>

// Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_GameController* controller = NULL;

SDL_Rect rectangle = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64};

const int SPEED = 5; // Lower speed for testing

// Exit the game and clean up
void quitGame() {
    SDL_GameControllerClose(controller);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Function to handle events
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            quitGame();
            exit(0);
        }
    }
}

// Function to update rectangle movement
void update() {
    SDL_GameControllerUpdate();

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP) && rectangle.y > 0) {
        rectangle.y -= SPEED;
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) && rectangle.y < SCREEN_HEIGHT - rectangle.h) {
        rectangle.y += SPEED;
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) && rectangle.x > 0) {
        rectangle.x -= SPEED;
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) && rectangle.x < SCREEN_WIDTH - rectangle.w) {
        rectangle.x += SPEED;
    }
}

// Function to render graphics
void render() {
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Render the rectangle
    SDL_RenderFillRect(renderer, &rectangle);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        return -1;
    }

    if ((window = SDL_CreateWindow("RedRectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
        return -1;
    }

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        return -1;
    }

    if (SDL_NumJoysticks() < 1) {
        printf("No game controllers connected!\n");
        return -1;
    } else {
        controller = SDL_GameControllerOpen(0);
        if (controller == NULL) {
            printf("Unable to open game controller! SDL Error: %s\n", SDL_GetError());
            return -1;
        }
    }

    // Main loop
    while (1) {
        handleEvents();
        update();
        render();
    }

    quitGame();
    return 0;
}
