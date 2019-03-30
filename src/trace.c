/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 22:05:29 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/28 22:16:47 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Color		trace(t_rt *rt, t_fov tmp)
{
	double		close;
	t_object	*close_o;
	SDL_Color	local_color;

	close_inters(rt, rt->fov, EPSILON, INFINITY);
	close = rt->close;
	close_o = rt->close_o;
	if (close_o == NULL)
		return ((SDL_Color) { 0, 0, 0, 0 });
	rt->fov.cam = add(rt->fov.cam, multiply(close, rt->fov.dir));
	tmp.dir = close_o->get_normal(rt, tmp.cam, rt->fov.dir, rt->fov.cam);
	rt->fov.dir = multiply(-1.0, rt->fov.dir);
	close = lighting(rt, rt->fov, tmp.dir, close_o->specular);
	local_color = do_color((SDL_Color){0, 0, 0, 0}, close_o->color, close);
	if (close_o->reflective <= 0.0 || rt->depth <= 0)
		return (local_color);
	rt->fov.dir = reflect(rt->fov.dir, tmp.dir);
	rt->depth -= 1;
	return (do_color(local_color, trace(rt, rt->fov), close_o->reflective));
}

void			go(t_rt *rt)
{
	int			x;
	int			y;

	y = rt->start - 1;
	while (++y < rt->end)
	{
		x = -(SCENE_W / 2) - 1;
		while (++x < SCENE_W / 2)
		{
			rt->depth = DEPTH;
			rt->fov.dir = direction(x, y, rt->angle_x, rt->angle_y);
			rt->fov.cam = rt->camera;
			// rt->win->color = trace(rt, rt->fov);
			put_pixel(rt, trace(rt, rt->fov), x, y);
		}
	}
}

void			threads(t_rt *rt)
{
	int			i;
	SDL_Thread	*thread[THREADS];
	t_rt		ttt[THREADS];
	SDL_Color	col[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		ttt[i] = *rt;
		ttt[i].win->color = col[i];
		ttt[i].start = i * SCENE_H / THREADS - SCENE_H / 2;
		ttt[i].end = (i + 1) * SCENE_H / THREADS - SCENE_H / 2;
		thread[i] = SDL_CreateThread((int(*)())go, "go", &ttt[i]);
	}
	while (--i >= 0)
		SDL_WaitThread(thread[i], NULL);
	// upd_win(rt->win);
	// upd_area_ren(rt->win, &rt->scene_r);
}
