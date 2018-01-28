#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

  redBlock = SDL_LoadBMP("assets/red.bmp");
  if(redBlock == NULL)
  {
    fprintf(stderr, "ERROR: couldn't load red.bmp");
  }

	SDL_Rect location = {0,0,600,400};
	
	//Main loop flag
	bool quit = false;

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
					printf("got the quit event\n");
					break;
				case SDL_KEYDOWN:
					if(e.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
						printf("got the quit event\n");
					}
					break;
			}
		}

		location.x++;
		if(location.x > SCREEN_WIDTH)
		{ location.x = 0;
		}
  	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		SDL_BlitSurface( redBlock, NULL, screenSurface, &location );
		SDL_UpdateWindowSurface(window);

		//Update the surface
		SDL_UpdateWindowSurface( window );
	}
 
  //SDL_Delay(3000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
