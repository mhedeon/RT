/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 22:05:29 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 23:00:44 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

SDL_Color trace(t_rtv *rtv, t_fov tmp)
{
	double close;
	t_object *close_o;
	SDL_Color local_color;

	close_inters(rtv, rtv->fov, EPSILON, INFINITY);
	close = rtv->close;
	close_o = rtv->close_o;
	if (close_o == NULL)
		return ((SDL_Color) { 0, 0, 0, 0 });
	rtv->fov.cam = add(rtv->fov.cam, multiply(close, rtv->fov.dir));
	tmp.dir = close_o->get_normal(rtv, tmp.cam, rtv->fov.dir, rtv->fov.cam);
	rtv->fov.dir = multiply(-1.0, rtv->fov.dir);
	close = lighting(rtv, rtv->fov, tmp.dir, close_o->specular);
	local_color = do_color((SDL_Color){0, 0, 0, 0}, close_o->color, close);
	if (close_o->reflective <= 0.0 || rtv->depth <= 0)
		return (local_color);
	rtv->fov.dir = reflect(rtv->fov.dir, tmp.dir);
	rtv->depth -= 1;
	return (do_color(local_color, trace(rtv, rtv->fov), close_o->reflective));
}

void go(t_rtv *rtv)
{
	for (int y = rtv->start; y < rtv->end; y++)
	{
		for (int x = -(SCREEN_WIDTH / 2); x < SCREEN_WIDTH / 2; x++)
		{
			rtv->depth = DEPTH;
			rtv->fov.dir = direction(x, y, rtv->angle_x, rtv->angle_y);
			rtv->fov.cam = rtv->camera;
			rtv->color = trace(rtv, rtv->fov);
			put_pixel(rtv, x, y);
		}
	}
}

void threads(t_rtv *rtv)
{
	int i;
	SDL_Thread *thread[THREADS];
	t_rtv ttt[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		ttt[i] = *rtv;
		ttt[i].start = i * SCREEN_HEIGHT / THREADS - SCREEN_HEIGHT / 2;
		ttt[i].end = (i + 1) * SCREEN_HEIGHT / THREADS - SCREEN_HEIGHT / 2;
		thread[i] = SDL_CreateThread((int(*)())go, "go", &ttt[i]);
	}
	while (--i >= 0)
		SDL_WaitThread(thread[i], NULL);
	screen_upd(rtv);
}