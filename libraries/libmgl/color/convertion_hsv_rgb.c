#include "libmgl.h"

#define P pqt[0]
#define Q pqt[1]
#define T pqt[2]
#define BOOST(X) (Uint8)(X * 255.0)

/*
**	hue = [0, 360]
**	saturation = [0, 1]
**	value = [0, 1]
*/

SDL_Color hsv2rgb(double h, double s, double v)
{
	double pqt[3];
	double f;
	int i;

	if (s == 0.0)
		return ((SDL_Color) { BOOST(v), BOOST(v), BOOST(v), 0 });
	h /= 60;
	i = (int)floor(h);
	f = h - (double)i;
	i %= 6;
	P = v * (1.0 - s);
	Q = v * (1.0 - s * f);
	T = v * (1.0 - s * (1.0 - f));
	if (i == 0)
		return ((SDL_Color) { BOOST(v), BOOST(T), BOOST(P), 0 });
	else if (i == 1)
		return ((SDL_Color) { BOOST(Q), BOOST(v), BOOST(P), 0 });
	else if (i == 2)
		return ((SDL_Color) { BOOST(P), BOOST(v), BOOST(T), 0 });
	else if (i == 3)
		return ((SDL_Color) { BOOST(P), BOOST(Q), BOOST(v), 0 });
	else if (i == 4)
		return ((SDL_Color) { BOOST(T), BOOST(P), BOOST(v), 0 });
	else if (i == 5)
		return ((SDL_Color) { BOOST(v), BOOST(P), BOOST(Q), 0 });
	return ((SDL_Color) { 0, 0, 0, 0 });
}