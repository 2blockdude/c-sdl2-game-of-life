#include <stdio.h>
#include <stdlib.h>

#include "game-of-life.h"

struct gol *gol_create(int width, int height)
{
	struct gol *game = malloc(sizeof(struct gol));
	game->output = calloc(width * height, sizeof(char));
	game->buffer = calloc(width * height, sizeof(char));

	game->width = width;
	game->height = height;

	return game;
}

void gol_free(struct gol *game)
{
	free(game->output);
	free(game->buffer);
	free(game);
}

void gol_update(struct gol *game)
{
	// update alive state
	for (int i = 0; i < game->height * game->width; i++)
	{
		game->output[i] = game->buffer[i];

		// gets columns and rows
		int x = i % game->width;			// column
		int y = (i - x) / game->width;	// row

		// wrap around left right
		int left = (x - 1) < 0 ? game->width - 1 : x - 1;
		int right = (x + 1) % game->width;

		// wrap around above below
		int above = (y - 1) < 0 ? game->height - 1 : y - 1;
		int below = (y + 1) % game->height;

		int neighbors =
			// get above
			game->buffer[above * game->width + left] +
			game->buffer[above * game->width + x] +
			game->buffer[above * game->width + right] +
			// get middle
			game->buffer[y * game->width + left] +
			game->buffer[y * game->width + right] +
			// get below
			game->buffer[below * game->width + left] +
			game->buffer[below * game->width + x] +
			game->buffer[below * game->width + right];

		// cell rules
		if (neighbors >= 4 || neighbors <= 1)
			game->output[i] = 0;
		else if (neighbors == 3)
			game->output[i] = 1;

	}

	// swap output and buffer
	char *temp = game->output;
	game->output = game->buffer;
	game->buffer = temp;
}

void gol_dump_map(const struct gol *game)
{
	for (int i = 0; i < game->height * game->width; i++)
	{
		switch (game->output[i])
		{
			case 0:
				printf(" ");
				break;

			case 1:
				printf("#");
				break;
		};

		if ((i % game->width) == (game->width - 1))
			printf("\n");
	}
}

void gol_build_shape(struct gol *game, char *shape, int x, int y)
{
	for (int i = 0; i < game->height && *shape; i++, shape++)
	{
		for (int j = 0; j < game->width && *shape != '\n'; j++, shape++)
		{
			if (*shape == '#')
				game->buffer[(i + y) * game->width + (j + x)] = game->output[(i + y) * game->width + (j + x)] = 1;
			else
				game->buffer[(i + y) * game->width + (j + x)] = game->output[(i + y) * game->width + (j + x)] = 0;
		}
	}
}

void gol_build_dot(struct gol *game, int x, int y)
{
	char shape[] = 
		"#\n";

	gol_build_shape(game, shape, x, y);
}

void gol_build_glider(struct gol *game, int x, int y)
{
	char shape[] = 
		" # \n" \
		"  #\n" \
		"###\n";

	gol_build_shape(game, shape, x, y);
}

void gol_build_blinker(struct gol *game, int x, int y)
{
	char shape[] =
		" # \n" \
		" # \n" \
		" # ";

	gol_build_shape(game, shape, x, y);
}

void gol_build_toad(struct gol *game, int x, int y)
{
	char shape[] =
		" ###\n" \
		"### ";

	gol_build_shape(game, shape, x, y);
}

void gol_build_beacon(struct gol *game, int x, int y)
{
	char shape[] =
		"  ##\n" \
		"  ##\n" \
		"##  \n" \
		"##  ";

	gol_build_shape(game, shape, x, y);
}

void gol_build_ant(struct gol *game, int x, int y)
{
	char shape[] =
		"##  \n" \
		"  ##\n" \
		"  ##\n" \
		"##  ";

	gol_build_shape(game, shape, x, y);
}

void gol_build_growth(struct gol *game, int x, int y)
{
	char shape[] =
		"######## #####   ###      ####### #####";

	gol_build_shape(game, shape, x, y);
}

void gol_build_random(struct gol *game, int seed)
{
	srand(seed);
	for (int i = 0; i < game->height * game->width; i++)
		game->output[i] = game->buffer[i] = rand() % 2;
}
