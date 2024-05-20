#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>

//Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

SDL_Window  *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Rect fillRect = {SCREEN_WIDTH  / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH  / 2, SCREEN_HEIGHT / 2};

int main(int argc, char *argv[])
{
  if(SDL_Init( SDL_INIT_VIDEO ) < 0)
      return -1;

  if ((window = SDL_CreateWindow( "RedRectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    return -1;

  if ((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL)
      return -1;

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, &fillRect);
  SDL_RenderPresent(renderer);
  SDL_Delay(4000);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  window = NULL;
  renderer = NULL;
  SDL_Quit();
  return 0;
}
