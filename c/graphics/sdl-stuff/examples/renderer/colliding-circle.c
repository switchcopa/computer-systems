#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_WIDTH 900 
#define WINDOW_HEIGHT 600
#define MAX_CIRCLES 100
#define TIME_DIFF(START, END) ((double) (END - START))
#define TARGET_FPS 60
#define FRAME_TIME (1000 / TARGET_FPS)

typedef struct {
        float radius;
	float vx, vy;
        int cx, cy;
} circle;

typedef struct {
	
} Grid;

void init_circle(circle *c, float r, int x, int y);
void circle_update_position(circle *c);
void circle_apply_gravity(circle *c);
void circle_detect_collisions(circle *c);
void draw_circle(SDL_Renderer *renderer, circle *c);
bool cursor_in_circle(circle *c);
void render_balls(SDL_Renderer* renderer, circle* arr, int max);
void add_ball(circle *arr, circle *c);

const float eps = 1.5f;
const float e_bounce = -.5f;
const float g  = 1200.0f;
const float dt = 0.016f;
const float throw_scale = 30.0f;

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
                WINDOW_WIDTH, WINDOW_HEIGHT,
                SDL_WINDOW_SHOWN
        );

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_Event event;
        static bool running = true;
        bool is_holding_mouse = false;
        
        circle c;
        circle *circle_arr = malloc(sizeof(circle) * MAX_CIRCLES);
	int arr_idx = -1;
	add_ball(circle_arr, &c, &arr_idx);

        init_circle(&c, 50, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        while (running) {
		Uint32 start_time = SDL_GetTicks();
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                                case SDL_QUIT:
                                        running = false;
                                        break;
                                case SDL_MOUSEBUTTONDOWN:
                                        if (event.button.button == SDL_BUTTON_LEFT && cursor_in_circle(&c)) {
                                                is_holding_mouse = true;
                                        }
                                case SDL_KEYDOWN:
                                        if (event.key.keysym.sym == SDLK_e) {
                                                circle new_circle;
                                        }
                                        break;
                                case SDL_MOUSEBUTTONUP:
                                        if (event.button.button == SDL_BUTTON_LEFT && is_holding_mouse) {
                                                is_holding_mouse = false;
                                                int dx, dy;
                                                SDL_GetRelativeMouseState(&dx, &dy);

                                                c.vx = dx * throw_scale;
                                                c.vy = dy * throw_scale;
                                        }
                                        break;       
                        }
                }
	
		// remove all this too or change it to be for all balls
                int mx, my;
                SDL_GetMouseState(&mx, &my);
                if (!is_holding_mouse) {
                        circle_update_position(&c);
                        circle_apply_gravity(&c);
                } else {
                        c.cx = mx;
                        c.cy = my;
                        c.vx = c.vy = 0;
                }
		// 

		circle_detect_collisions(&c); //update this for all balls

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                draw_circle(renderer, &c); // change this
                SDL_RenderPresent(renderer);
                
		Uint32 frame_time = SDL_GetTicks() - start_time;
		if (frame_time < FRAME_TIME)
			SDL_Delay(FRAME_TIME - frame_time);
        }

        free(circle_arr);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
}

void init_circle(circle *c, float r, int x, int y) {
        c->radius = r;
        c->cx = x;
        c->cy = y;
        c->vx = c->vy = 0;
}

void circle_update_position(circle *c) {
        c->cx += c->vx * dt;
	c->cy += c->vy * dt;
}

void circle_apply_gravity(circle *c) {
	c->vy += g * dt;
}

void circle_detect_collisions(circle *c) {
	if (c->cy + c->radius > WINDOW_HEIGHT) {
		c->cy = WINDOW_HEIGHT - c->radius;
		c->vy *= e_bounce;
	}

	if (c->cy - c->radius < 0) {
		c->cy = c->radius;
		c->vy *= e_bounce;
                if (fabs(c->vy) < eps)
                        c->vy = 0;
	}

	if (c->cx - c->radius < 0) {
		c->cx = c->radius;
		c->vx *= e_bounce;
                if (fabs(c->vx) < eps)
                        c->vx = 0;
	}

	if (c->cx + c->radius > WINDOW_WIDTH) {
		c->cx = WINDOW_WIDTH - c->radius;
		c->vx *= e_bounce;

	        if (fabs(c->vx) < eps) 
                        c->vx = 0;
	}

        if (fabs(c->vy) < eps)
                c->vy = 0;
}

void draw_circle(SDL_Renderer *renderer, circle *c) {
        int x = c->radius;
        int y = 0;
        int decision = 1 - c->radius;
        int cx = c->cx;
        int cy = c->cy;
	
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        while (x >= y) {
                SDL_RenderDrawLine(renderer, cx - x, cy + y, cx + x, cy + y);
                SDL_RenderDrawLine(renderer, cx - x, cy - y, cx + x, cy - y);
                SDL_RenderDrawLine(renderer, cx - y, cy + x, cx + y, cy + x);
                SDL_RenderDrawLine(renderer, cx - y, cy - x, cx + y, cy - x);

                y++;
                if (decision <= 0)
                        decision += 2 * y + 1;
                else {
                        x--;
                        decision += 2 * (y - x) + 1;
                }
        }
}

bool cursor_in_circle(circle *c) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        return (pow(mx - c->cx, 2) + pow(my - c->cy, 2) < pow(c->radius, 2));
}

void render_balls(SDL_Renderer* renderer, circle* arr, int max) {
	for (int i = max; i >= 0 ; i--)
		draw_circle(renderer, arr[i]);	
}

void add_ball(circle *arr, circle *c, int *arr_idx) {
	arr[++*arr_idx] = *c;
}
