#ifndef COLOR_H
# define COLOR_H

# include "libmgl.h"

typedef struct	s_hsv
{
	double		h;
	double		s;
	double		v;
}				t_hsv;

/*
**	---------------------------- convertion_HSV-RGB.c | start
*/

SDL_Color hsv2rgb(double h, double s, double v);

/*
**	---------------------------- convertion_HSV-RGB.c | end
*/

#endif
