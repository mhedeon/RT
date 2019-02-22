/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/22 21:28:47 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

SDL_Color do_color(SDL_Color local, SDL_Color reflected, double reflective)
{
	SDL_Color result;

	result.r = (Uint8)((1.0 - reflective) * local.r + reflective * reflected.r);
	result.g = (Uint8)((1.0 - reflective) * local.g + reflective * reflected.g);
	result.b = (Uint8)((1.0 - reflective) * local.b + reflective * reflected.b);
	result.a = 0;
	return (result);
}

double		point(t_rtv *rtv, t_fov pv, t_vec normal, int specular)
{
	double	in;
	t_vec	vec_l;
	t_vec	vec_r;

	in = 0.0;
	vec_l = substruct(rtv->light->pos, pv.cam);
	close_inters(rtv, (t_fov){pv.cam, vec_l}, 0.000000001, 1.0);
	if (rtv->close_o != NULL)
		return (0.0);
	rtv->close = dot(normal, vec_l);
	in += rtv->close > 0.0 ? rtv->light->intens * rtv->close /
			(length(normal) * length(vec_l)) : 0.0;
	vec_r = multiply(2.0 * dot(normal, vec_l), normal);
	vec_r = substruct(vec_r, vec_l);
	rtv->close = dot(vec_r, pv.dir);
	in += rtv->close > 0.0 ? rtv->light->intens * pow(rtv->close /
			(length(vec_r) * length(pv.dir)), specular) : 0.0;
	return (in);
}

double lighting(t_rtv *rtv, t_fov pv, t_vec normal, int specular)
{
	double in = 0.0;
	t_light *tmp;

	tmp = rtv->light;
	while (rtv->light != NULL)
	{
		in += rtv->light->type == AMBIENT ? rtv->light->intens : 0.0;
		in += rtv->light->type == POINT ?
				point(rtv, pv, normal, specular) : 0.0;
		rtv->light = rtv->light->next;
	}
	rtv->light = tmp;
	in = in > 1.0 ? 1.0 : in;
	in = in < 0.0 ? 0.0 : in;
	return (in);
}

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

int main()
{
	t_rtv *rtv = (t_rtv *)malloc(sizeof(t_rtv));
	if (rtv == NULL)
		return (1);
	init(rtv);
	rtv->angle_x = 0;
	rtv->angle_y = 0;


	rtv->obj = new_obj(rtv->obj, CYLINDER, (t_vec) { 4.0, 1.5, 3.5 }, (t_vec) { 0.0, 1.0, 0.0 },
											(SDL_Color) {0, 255, 255, 0}, 500, 0.0, 0.5, 1000, -1);
	rtv->obj = new_obj(rtv->obj, CONE, (t_vec) { 0.0, 3.5, -2.0 }, (t_vec) { 0.0, -1.0, 0.0 },
											(SDL_Color) {204, 102, 255, 0}, 500, 0.6, 5.0, 2.0, 15.0);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 0.0, -0.25, 3.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {255, 0, 0, 0}, 40, 0.3, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, PLANE, (t_vec) { 0.0, 0.0, 0.0}, (t_vec) { 0.0, 1.0, 0.0 },
											(SDL_Color) {255, 255, 0, 0}, 1000, 0.0, INFINITY, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 2.0, 0.5, 4.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {0, 0, 255, 0}, 500, 0.3, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { -2.0, 0.5, 4.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {0, 255, 0, 0}, 3000, 0.4, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 0.0, 2.5, 3.5 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {123, 123, 123, 0}, 5000, 0.5, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, CYLINDER, (t_vec) { 0.0, 2.5, 3.5 }, (t_vec) { 0.0, 1.0, 0.0 },
											(SDL_Color) {213, 156, 40, 0}, 500, 0.5, 1.5, 0.2, -1);
	rtv->obj = new_obj(rtv->obj, CONE, (t_vec) { 4.0, 3.5, -2.0 }, (t_vec) { 0.0, -1.0, 0.0 },
											(SDL_Color) {204, 102, 255, 0}, 500, 0.6, 5.0, 4.0, 15.0);

	rtv->light = new_light(rtv->light, AMBIENT, 0.2, (t_vec) { 0.0, 0.0, 0.0 });
	rtv->light = new_light(rtv->light, POINT, 0.5, (t_vec) { -1.0, 5.0, -3.5 });

	t_vec camera = { 0.0, 0.5, -5.0 };
	rtv->camera = camera;

	threads(rtv);
	screen_upd(rtv);
	SDL_Event e;
	while (SDL_PollEvent(&e) || 1)
	{
		if (e.type == SDL_QUIT ||
			(KEY == SDLK_ESCAPE))
			break;
		else if (KEY == SDLK_LEFT)
		{
			rtv->dir = direction(0, 0, 0, rtv->angle_y - 90);
			rtv->camera = add(rtv->camera, multiply(0.25, rtv->dir));
			printf("go left\n");
		}
		else if (KEY == SDLK_RIGHT)
		{
			rtv->dir = direction(0, 0, 0, rtv->angle_y + 90);
			rtv->camera = add(rtv->camera, multiply(0.25, rtv->dir));
			printf("go right\n");
		}
		else if (KEY == SDLK_UP)
		{
			rtv->dir = direction(0, 0, rtv->angle_x, rtv->angle_y);
			rtv->camera = add(rtv->camera, multiply(0.25, rtv->dir));
			printf("go up\n");
		}
		else if (KEY == SDLK_DOWN)
		{
			rtv->dir = direction(0, 0, rtv->angle_x, rtv->angle_y);
			rtv->camera = add(rtv->camera, multiply(-0.25, rtv->dir));
			printf("go down\n");
		}
		else if (KEY == SDLK_w)
			rtv->angle_x -= 5;
		else if (KEY == SDLK_s)
			rtv->angle_x += 5;
		else if (KEY == SDLK_a)
			rtv->angle_y -= 5;
		else if (KEY == SDLK_d)
			rtv->angle_y += 5;
		else
			continue ;
		threads(rtv);
	}

	//garbage(rtv);
	// system("leaks rtv");
	return (0);
}

void go(t_rtv *rtv)
{
	for (int y = rtv->start; y < rtv->end; y++)
	{
		for (int x = -(SCREEN_WIDTH / 2); x < SCREEN_WIDTH / 2; x++)
		{
			rtv->depth = DEPTH;
			rtv->dir = direction(x, y, rtv->angle_x, rtv->angle_y);
			rtv->fov.cam = rtv->camera;
			rtv->fov.dir = rtv->dir;
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
		printf("[%d] start: %d | end: %d\n", i, ttt[i].start, ttt[i].end);
	}
	while (--i >= 0)
		SDL_WaitThread(thread[i], NULL);
	screen_upd(rtv);
	printf("DONE\n");
}

int rnd()
{
	static int seed = 0;

	seed = seed == 0 ? SDL_GetTicks() : seed;
	seed = (Uint8)(1664525 * seed + 1013904223);
	return (seed);
}
