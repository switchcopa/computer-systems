#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TIME_DIFF(START, END) ((double) (END - START))

SDL_Window *SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags);

int main(void) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                fprintf(stderr, "failed to init SDL: %s\n", SDL_GetError());
                return EXIT_FAILURE;
        }

        SDL_Window *window = SDL_CreateWindow(
                "Simple Window",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                800, 600,
                SDL_WINDOW_SHOWN
        );
        
        time_t start = time(NULL);
        SDL_Event event;
        static bool running = true;

        while (running) {
                while (SDL_PollEvent(&event))
                        if (event.type == SDL_QUIT || TIME_DIFF(start, time(NULL)) >= 3.0)
                                running = false;
        }
        
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
}
