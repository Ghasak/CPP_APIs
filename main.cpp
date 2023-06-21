#include <iostream>
#include "./dependencies/include/SDL2/SDL.h"
// #include "./dependencies/SDL2.framework/Headers/SDL.h"
/* using namespace std; */
/* int main() { */
/*         cout << "Hello World!, SDL2. is installed correctly!" << endl; */
/*         SDL_Init(SDL_INIT_VIDEO); */
/*         return 0; */
/*     } */

/* int main(){ */
/*         SDL_Init(SDL_INIT_VIDEO); */
/*         SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN); */
/*         SDL_Renderer *renderer = SDL_CreateRenderer(window,-1 , 0); */
/*         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); */
/*         SDL_RenderPresent(renderer); */
/*         SDL_Delay(8000); */

/* } */

/****************************************************
//  How to  Draw a line in SDL2 :
//  https://wiki.libsdl.org/SDL_RenderDrawLine     */
//  SDL2 Library is up and running with MacOSX    */
/****************************************************/
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0)
        {
            SDL_bool done = SDL_FALSE;
            while (!done)
            {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 100, 200, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
                SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
                SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer)
        {
            SDL_DestroyRenderer(renderer);
        }
        if (window)
        {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}
