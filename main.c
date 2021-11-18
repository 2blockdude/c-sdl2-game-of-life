#include <math.h>
#include <SDL2/SDL.h>
#include "game-of-life.h"

#define SCREEN_WIDTH 650
#define SCREEN_HEIGHT 650

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

typedef struct game_window game_window;

struct game_window
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Event event;

	char running;

	int width;
	int height;
};

int init_window(game_window *win, char *title, int width, int height)
{
	int wflags = 0; // window flags
	int rflags = 0; // render flags

	win->width = width;
	win->height = height;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return -1;

	win->window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height,
			wflags);

	if (!win->window)
	{
		win->running = 0;
		return -2;
	}

	win->renderer = SDL_CreateRenderer(win->window, -1, rflags);

	if (!win->renderer)
	{
		win->running = 0;
		return -3;
	}

	SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, 255);

	win->running = 1;

	return 0;
}

void destroy_window(game_window *win)
{
	// clean up
	SDL_DestroyWindow(win->window);
	SDL_DestroyRenderer(win->renderer);
	SDL_Quit();
}

void handle_events(game_window *win)
{
	while (SDL_PollEvent(&(win->event)))
	{
		switch (win->event.type)
		{
			case SDL_QUIT:
				win->running = 0;
		};
	}
}

void render(SDL_Renderer *renderer, gol *game)
{
	SDL_RenderClear(renderer);

	for (int i = 0; i < game->width * game->height; i++)
	{
		if (game->output[i] > 0)
		{
			int x = i % game->width;			// column
			int y = (i - x) / game->width;	// row

			float pixel_w = (float)SCREEN_WIDTH / (float)game->width;		// pixel width
			float pixel_h = (float)SCREEN_HEIGHT / (float)game->height;	// pixel height

			// stupid round up thing... sorry
			pixel_w = (pixel_w - (int)pixel_w) >= 0.5f ? (int)pixel_w + 1 : (int)pixel_w;
			pixel_h = (pixel_h - (int)pixel_h) >= 0.5f ? (int)pixel_h + 1 : (int)pixel_h;

			SDL_Rect tile = { x * pixel_w, y * pixel_h, pixel_w, pixel_h };
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &tile);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
}

int main()
{
	game_window win;
	gol *game = gol_create(MAP_WIDTH, MAP_HEIGHT);
	gol_build_random(game, 1000);

	init_window(&win, "gameoflife", SCREEN_WIDTH, SCREEN_HEIGHT);

	while (win.running)
	{
		handle_events(&win);
		gol_update(game);
		render(win.renderer, game);
		SDL_Delay(100);
	}

	destroy_window(&win);
	gol_free(game);

	return 0;
}
