#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>

//Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

SDL_Window  *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Rect rectangle = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64};

const int SPEED = 600;

//Exit the game and clean up
void quitGame() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Function to handle events
void handleEvents() {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
            
            quitGame();
            exit(0);
        }
    }
}

// Function to update rectangle movement.
void update() {

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_W] && rectangle.y > 0) {
        rectangle.y -= SPEED;
    }

    else if (currentKeyStates[SDL_SCANCODE_S] && rectangle.y < SCREEN_HEIGHT - rectangle.h) {
        rectangle.y += SPEED;
    }

    else if (currentKeyStates[SDL_SCANCODE_A] && rectangle.x > 0) {
        rectangle.x -= SPEED;
    }

    else if (currentKeyStates[SDL_SCANCODE_D] && rectangle.x < SCREEN_WIDTH - rectangle.w) {
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
   if(SDL_Init( SDL_INIT_VIDEO ) < 0)
      return -1;

  if ((window = SDL_CreateWindow( "RedRectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    return -1;

  if ((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL)
      return -1;

    // Main loop
    while (1) {
        
        handleEvents();
        update();
        render();
    }

    quitGame();
    return 0;
}
