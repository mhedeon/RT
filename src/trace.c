/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 22:05:29 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/27 19:19:36 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

SDL_Color blind(t_rtv *rtv)
{
	t_light	*light;
	double in;
	double t;
	double spot_effect;

	in = 0;
	light = rtv->light;
	while (rtv->light != NULL)
	{
		if (rtv->light->type == DIRECT)
		{
			if ((spot_effect = dual_cone_spotlight(rtv->fov.cam, rtv->light, rtv->cos_angle)) != 0)
			{
				t = rtv->light->type == DIRECT ? point(rtv, rtv->fov, rtv->fov.dir, 0, multiply(-1, rtv->light->normal)) : 0.0;
				if (ft_vangle(rtv->fov.dir, rtv->light->normal) < -0.1)
				{
					in += (spot_effect * t);
					rtv->light = light;
					return ((do_color((SDL_Color) {0, 0, 0, 0}, (SDL_Color) {255, 255, 255, 0}, in)));
				}
				break;
			}
		}
		rtv->light = rtv->light->next;
	}
	rtv->light = light;
	return ((SDL_Color) { 0, 0, 0, 0 });
}

SDL_Color		trace(t_rtv *rtv, t_fov tmp)
{
	double		close;
	t_object	*close_o;
	SDL_Color	local_color;

	close_inters(rtv, rtv->fov, EPSILON, INFINITY);
	close = rtv->close;
	close_o = rtv->close_o;
	local_color = blind(rtv);
	rtv->close_o = close_o;
	if (close_o == NULL)
		return (local_color);
	rtv->fov.cam = add(rtv->fov.cam, multiply(close, rtv->fov.dir));
	tmp.dir = close_o->get_normal(rtv, tmp.cam, rtv->fov.dir, rtv->fov.cam);
	rtv->fov.dir = multiply(-1.0, rtv->fov.dir);
//	close = lighting(rtv, rtv->fov, tmp.dir, close_o->specular);
//	local_color = do_color((SDL_Color){0, 0, 0, 0}, close_o->color, close);
	local_color = do_color(local_color, lighting(rtv, rtv->fov, tmp.dir, close_o), 1);

	if (close_o->reflective <= 0.0 || rtv->depth <= 0)
		return (local_color);
	rtv->fov.dir = reflect(rtv->fov.dir, tmp.dir);
	rtv->depth -= 1;
	return (do_color(local_color, trace(rtv, rtv->fov), close_o->reflective));
}

/*SDL_Color		trace(t_rtv *rtv, t_fov tmp)
{
	double		close;
	t_object	*close_o;
	SDL_Color	local_color;

	close_inters(rtv, rtv->fov, EPSILON, INFINITY);
	close = rtv->close;
	close_o = rtv->close_o;
//	local_color = blind(rtv, close_o);
//	if (local_color.a == 0 && local_color.b == 0 && local_color.g == 0 && local_color.r == 0)
//		return local_color;
	if (close_o == NULL)
		return ((SDL_Color) { 0, 0, 0, 0 });
	rtv->fov.cam = add(rtv->fov.cam, multiply(close, rtv->fov.dir));
	tmp.dir = close_o->get_normal(rtv, tmp.cam, rtv->fov.dir, rtv->fov.cam);
	rtv->fov.dir = multiply(-1.0, rtv->fov.dir);
//	close = lighting(rtv, rtv->fov, tmp.dir, close_o->specular);
//	local_color = do_color((SDL_Color){0, 0, 0, 0}, close_o->color, close);



	local_color = lighting(rtv, rtv->fov, tmp.dir, close_o);

	if (close_o->reflective <= 0.0 || rtv->depth <= 0)
		return (local_color);
	rtv->fov.dir = reflect(rtv->fov.dir, tmp.dir);
	rtv->depth -= 1;
	return (do_color(local_color, trace(rtv, rtv->fov), close_o->reflective));
}*/

void			go(t_rtv *rtv)
{
	int			x;
	int			y;

	y = rtv->start - 1;
	while (++y < rtv->end)
	{
		x = -(SCREEN_WIDTH / 2) - 1;
		while (++x < SCREEN_WIDTH / 2)
		{
			rtv->depth = DEPTH;
			rtv->fov.dir = direction(x, y, rtv->angle_x, rtv->angle_y);
			rtv->fov.cam = rtv->camera;
			rtv->color = trace(rtv, rtv->fov);
			put_pixel(rtv, x, y);
		}
	}
}

void			threads(t_rtv *rtv)
{
	int			i;
	SDL_Thread	*thread[THREADS];
	t_rtv		ttt[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		ttt[i] = *rtv;
		ttt[i].start = i * SCREEN_HEIGHT / THREADS - SCREEN_HEIGHT / 2;
		ttt[i].end = (i + 1) * SCREEN_HEIGHT / THREADS - SCREEN_HEIGHT / 2;
		ttt[i].cos_angle = rtv->cos_angle;
		thread[i] = SDL_CreateThread((int(*)())go, "go", &ttt[i]);
	}
	while (--i >= 0)
		SDL_WaitThread(thread[i], NULL);
	screen_upd(rtv);
}
