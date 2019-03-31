/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion_hsv_rgb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 04:56:44 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:00:13 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

SDL_Color	hsv2rgb(double h, double s, double v)
{
	double	pqt[3];
	double	f;
	int		i;

	if (s == 0.0)
		return ((SDL_Color) { BOOST(v), BOOST(v), BOOST(v), 0 });
	h /= 60;
	f = h - floor(h);
	i = ((int)floor(h)) % 6;
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

SDL_Color	hsv_to_rgb(t_hsv *hsv)
{
	double	pqt[3];
	double	f;
	int		i;

	if (hsv->s == 0.0)
		return ((SDL_Color) { BOOST(hsv->v), BOOST(hsv->v), BOOST(hsv->v), 0 });
	hsv->h /= 60;
	f = hsv->h - floor(hsv->h);
	i = ((int)floor(hsv->h)) % 6;
	P = hsv->v * (1.0 - hsv->s);
	Q = hsv->v * (1.0 - hsv->s * f);
	T = hsv->v * (1.0 - hsv->s * (1.0 - f));
	if (i == 0)
		return ((SDL_Color) { BOOST(hsv->v), BOOST(T), BOOST(P), 0 });
	else if (i == 1)
		return ((SDL_Color) { BOOST(Q), BOOST(hsv->v), BOOST(P), 0 });
	else if (i == 2)
		return ((SDL_Color) { BOOST(P), BOOST(hsv->v), BOOST(T), 0 });
	else if (i == 3)
		return ((SDL_Color) { BOOST(P), BOOST(Q), BOOST(hsv->v), 0 });
	else if (i == 4)
		return ((SDL_Color) { BOOST(T), BOOST(P), BOOST(hsv->v), 0 });
	else if (i == 5)
		return ((SDL_Color) { BOOST(hsv->v), BOOST(P), BOOST(Q), 0 });
	return ((SDL_Color) { 0, 0, 0, 0 });
}
