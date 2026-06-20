#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>
#include <stdbool.h>

#define TIME_DIFF(START, END) ((double) (END - START))
#define TARGET_FPS 60
#define FRAME_TIME (1000 / TARGET_FPS)

const float g  = 500.0f;
const float dt = 0.016f;

// keep all this here so I memorize the API
int           SDL_Init(Uint32 flags);
SDL_Window   *SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags);
SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags);
int           SDL_RenderFillRect(SDL_Renderer *renderer, const SDL_Rect *rect);
int           SDL_PollEvent(SDL_Event *event);
int           SDL_SetRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void          SDL_RenderPresent(SDL_Renderer *renderer);
void          SDL_DestroyRenderer(SDL_Renderer *renderer);

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

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_Event event;
        static bool running = true;
	float x = 300, y = 200;
        float size = 50;
	float v = 0;

        while (running) {
		Uint32 start_time = SDL_GetTicks();
                while (SDL_PollEvent(&event))
                        if (event.type == SDL_QUIT)
                                running = false;

	        v += g * dt;
                y += v * dt;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
        
                SDL_Rect square = { (int)x, (int)y, (int)size, (int)size };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &square);

                SDL_RenderPresent(renderer);
		
		Uint32 frame_time = SDL_GetTicks() - start_time;
		if (frame_time < FRAME_TIME)
			SDL_Delay(FRAME_TIME - frame_time);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
}
