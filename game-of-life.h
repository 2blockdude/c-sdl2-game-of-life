#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

typedef struct gol gol;

struct gol
{
	char *output;
	char *buffer;

	int width;
	int height;
};

struct gol *gol_create	(int width, int height);
void gol_free				(struct gol *game);
void gol_update			(struct gol *game);
void gol_dump_map			(const struct gol *game);

void gol_build_shape		(struct gol *game, char *shape, int x, int y);
void gol_build_dot		(struct gol *game, int x, int y);
void gol_build_glider	(struct gol *game, int x, int y);
void gol_build_blinker	(struct gol *game, int x, int y);
void gol_build_toad		(struct gol *game, int x, int y);
void gol_build_beacon	(struct gol *game, int x, int y);
void gol_build_ant		(struct gol *game, int x, int y);
void gol_build_growth	(struct gol *game, int x, int y);
void gol_build_random	(struct gol *game, int seed);

#endif
