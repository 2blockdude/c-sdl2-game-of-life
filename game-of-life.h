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
void gol_free				(struct gol *map);
void gol_update			(struct gol *map);
void gol_dump_map			(const struct gol *map);

void gol_build_shape		(struct gol *map, char *shape, int x, int y);
void gol_build_glider	(struct gol *map, int x, int y);
void gol_build_blinker	(struct gol *map, int x, int y);
void gol_build_toad		(struct gol *map, int x, int y);
void gol_build_beacon	(struct gol *map, int x, int y);
void gol_build_ant		(struct gol *map, int x, int y);
void gol_build_growth	(struct gol *map, int x, int y);
void gol_build_random	(struct gol *map, int seed);

#endif
