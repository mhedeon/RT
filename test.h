#ifndef TEST_H
# define TEST_H

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_mixer.h>
# include <SDL_ttf.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# define SCREEN_WIDTH 600
# define SCREEN_HEIGHT 600

# define AMBIENT 1
# define POINT 2
# define DIRECTIONAL 3

# define KEY e.type == SDL_KEYDOWN && e.key.keysym.sym

typedef struct	s_vector
{
	double x;
	double y;
	double z;
}				t_vector;

typedef struct	s_light
{
	int			type;
	double		intens;
	t_vector	pos;
}				t_light;

typedef struct	s_sphere
{
	t_vector	center;
	double		radius;
	SDL_Color	color;
}				t_sphere;


typedef struct	s_test
{
	SDL_Window	*win;
	SDL_Renderer	*ren;
	SDL_Texture	*tex;
	Uint32	*buff;
	SDL_Color color;

}				t_test;





void init(t_test *test);
void garbage(t_test *test);
void	set_pixel(t_test *test, SDL_Color *color, int x, int y);
void	clear_buffer(t_test *test);
void	screen_upd(t_test *test);



#endif
