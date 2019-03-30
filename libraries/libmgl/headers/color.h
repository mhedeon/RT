#ifndef COLOR_H
# define COLOR_H

# include "libmgl.h"

typedef struct	s_hsv
{
	double		h;
	double		s;
	double		v;
}				t_hsv;

typedef struct	s_rgb
{
	Uint8		r;
	Uint8		g;
	Uint8		b;
}				t_rgb;

/*
**	---------------------------- convertion_HSV-RGB.c | start
*/

SDL_Color hsv2rgb(double h, double s, double v);
SDL_Color hsv_to_rgb(t_hsv *hsv);

/*
**	---------------------------- convertion_HSV-RGB.c | end
*/

#endif
