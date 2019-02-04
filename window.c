#include "test.h"

void init(t_test *test)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	test->win = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	test->ren = SDL_CreateRenderer(test->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	test->tex = SDL_CreateTexture(test->ren, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	test->buff = (Uint32 *)malloc(sizeof(Uint32) * (SCREEN_HEIGHT * SCREEN_WIDTH));
	clear_buffer(test);
}

void garbage(t_test *test)
{
	SDL_DestroyTexture(test->tex);
	SDL_DestroyRenderer(test->ren);
	SDL_DestroyWindow(test->win);
	free(test->buff);
	free(test);
}

void	set_pixel(t_test *test, SDL_Color *color, int x, int y)
{
	test->buff[y * SCREEN_WIDTH + x] = 
		color->r << 16 |
		color->g << 8 |
		color->b;
}

void	clear_buffer(t_test *test)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			test->buff[y * SCREEN_WIDTH + x] = 0 << 16 |
			0 << 8 |
			0;
	}
}

void	screen_upd(t_test *test)
{
	SDL_UpdateTexture(test->tex, NULL, test->buff,
		SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(test->ren);
	SDL_RenderCopy(test->ren, test->tex, NULL, NULL);
	SDL_RenderPresent(test->ren);
}