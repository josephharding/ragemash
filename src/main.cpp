#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct BMP_DICT
{
  SDL_Surface* player;
  SDL_Surface* enemy;
};

bool loadAssets(BMP_DICT* dict)
{
  SDL_Surface* red = SDL_LoadBMP("assets/red.bmp");
  SDL_Surface* blue = SDL_LoadBMP("assets/blue.bmp");
  dict -> player = blue;
  dict -> enemy = red;
  return true;
}

int main(int argc, char* args[])
{
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;
  SDL_Surface* redBlock = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  window = SDL_CreateWindow("ragemash",
          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
          SCREEN_WIDTH, SCREEN_HEIGHT,
          SDL_WINDOW_SHOWN
          );
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  screenSurface = SDL_GetWindowSurface(window);
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);

  BMP_DICT image_dict;
  loadAssets (&image_dict);

  int red_change = 1;
  SDL_Rect red_loc = {0,0,600,400};
  SDL_Rect blue_loc = {0,0,600,400};
  
  //Main loop flag
  bool quit = false;
  bool red_dead = false;

  //Event handler
  SDL_Event e;

  //While application is running
  while( !quit )
  {
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
      //User requests quit
      switch( e.type )
      {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          if(e.key.keysym.sym == SDLK_ESCAPE)
          {
            quit = true;
          }
          else if (e.key.keysym.sym == SDLK_LEFT)
          {
            blue_loc.x--;
          }
          else if (e.key.keysym.sym == SDLK_RIGHT)
          {
            blue_loc.x++;
          }
          else if (e.key.keysym.sym == SDLK_SPACE)
          {
            std::cout << "SMASH!" << std::endl;
            if (abs(red_loc.x - blue_loc.x) < 10)
            {
              std::cout << "YOU KILLED A CITIZEN!" << std::endl;
              red_dead = true;
            }
          }
          break;
      }
    }

    if(!red_dead)
    {
      red_loc.x += red_change;
      if(red_loc.x <= 0 || red_loc.x >= SCREEN_WIDTH)
      {
        red_change *= -1;
      } 
    }

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_BlitSurface( image_dict.enemy, NULL, screenSurface, &red_loc );
    SDL_BlitSurface( image_dict.player, NULL, screenSurface, &blue_loc );

    //Update the surface
    SDL_UpdateWindowSurface( window );
  }
 
  //SDL_Delay(3000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
