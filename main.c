/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/11 20:58:50 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double lighting(t_rtv *rtv, t_vector *point, t_vector *normal, t_vector *view, int specular)
{
	double in = 0.0;
	double len = length(*normal);
	double len_v = length(*view);
	t_light *tmp = rtv->light;

	for (int i = 0; i < 3; i++)
	{
		if (tmp->type == AMBIENT)
			in += tmp->intens;
		else
		{
			t_vector vec_l;
			if (tmp->type == POINT)
				vec_l = substruct(tmp->pos, *point);
			else
				vec_l = tmp->pos;

			close_inters(rtv, point, &vec_l, 0.00001, INFINITY);
			if (rtv->close_sph != NULL)
				continue ;

			 // difuse
			double n_dot = dot(*normal, vec_l);
			if (n_dot > 0.0)
				in += tmp->intens * n_dot /
						(len * length(vec_l));

			// specular
			if (specular != -1)
			{
				t_vector vec_r = multiply(2.0 * dot(*normal, vec_l), *normal);
				vec_r = substruct(vec_r, vec_l);
				double r_dot = dot(vec_r, *view);
				if (r_dot > 0.0)
					in += tmp->intens * pow(r_dot / (length(vec_r) * len_v), specular);
			}
		}
		tmp = tmp->next;
	}
	if (in > 1.0)
		in = 1.0;
	return (in);
}

SDL_Color trace(t_rtv *rtv, t_vector *origin, t_vector *dir, double min, double max, int depth)
{
	double close;
	t_object *close_sph;
	close_inters(rtv, origin, dir,  min, max);

	close = rtv->close;
	close_sph = rtv->close_sph;

	if (close_sph == NULL)
		return ((SDL_Color) { 0, 0, 0 });

	t_vector tmp = multiply(close, *dir);
	t_vector point = add(*origin, tmp);
	t_vector normal;
	if (close_sph->type == PLANE)
	{
		normal = close_sph->normal;
	}
	else
	{
		normal = substruct(point, close_sph->center);
		normal = multiply(1.0 / length(normal), normal);
	}

	t_vector view = multiply(-1.0, *dir);
	close = lighting(rtv, &point, &normal, &view, close_sph->specular);
	SDL_Color local_color = { (Uint8)(close * close_sph->color.r),
								(Uint8)(close * close_sph->color.g),
								(Uint8)(close * close_sph->color.b), 0 };

	if (close_sph->reflective <= 0.0 || depth <= 0)
		return (local_color);

	t_vector ray = reflect(view, normal);
	
	SDL_Color ref_c = trace(rtv, &point, &ray, 0.0001, max, depth - 1);
	return ((SDL_Color) { (Uint8)((1.0 - close_sph->reflective) * local_color.r + close_sph->reflective * ref_c.r),
							(Uint8)((1.0 - close_sph->reflective) * local_color.g + close_sph->reflective * ref_c.g),
							(Uint8)((1.0 - close_sph->reflective) * local_color.b + close_sph->reflective * ref_c.b), 0 });
}

void go(t_rtv *rtv)
{
	for (int y = rtv->start; y < rtv->end; y++)
	{
		for (int x = -(SCREEN_WIDTH / 2); x < SCREEN_WIDTH / 2; x++)
		{

			t_vector direction = { (double)x * 1.0 / (double)SCREEN_WIDTH, (double)y * 1.0 / (double)SCREEN_HEIGHT, 1.0 };
			rtv->dir = direction;
			rtv->color = trace(rtv, &rtv->camera, &rtv->dir, 1.0, INFINITY, 3);
			put_pixel(rtv, x, y);
		}
	}
}

void threads(t_rtv *rtv)
{
	SDL_Thread *thread[THREADS];
	t_rtv ttt[THREADS];

	for (int i = 0; i < THREADS; i++)
	{
		ttt[i] = *rtv;
		ttt[i].start = i * SCREEN_HEIGHT / THREADS - SCREEN_HEIGHT / 2;
		ttt[i].end = (i + 1) * SCREEN_HEIGHT / THREADS - SCREEN_HEIGHT / 2;
		thread[i] = SDL_CreateThread((int(*)())go, "go", &ttt[i]);
		printf("[%d] start: %d | end: %d\n", i, ttt[i].start, ttt[i].end);
	}
	for (int i = 0; i < THREADS; i++)
		SDL_WaitThread(thread[i], NULL);
	screen_upd(rtv);
	printf("DONE\n");
}

int main(int ac, char **av)
{
	t_rtv *rtv = (t_rtv *)malloc(sizeof(t_rtv));
	init(rtv);
	rtv->obj = new_obj(rtv->obj, PLANE, (t_vector) { 0.0, -0.5, 0.0}, (t_vector) { 0.0, 1.0, 0.0 },
											(SDL_Color) {255, 255, 0}, 0.0, -1.0, 0.0);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vector) { 0.0, -0.25, 3.0 }, (t_vector) { 0.0, 0.0, 0.0 },
											(SDL_Color) {255, 0, 0}, 1.0, 1000.0, 0.2);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vector) { 2.0, 0.5, 4.0 }, (t_vector) { 0.0, 0.0, 0.0 },
											(SDL_Color) {0, 0, 255}, 1.0, 500.0, 0.3);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vector) { -2.0, 0.5, 4.0 }, (t_vector) { 0.0, 0.0, 0.0 },
											(SDL_Color) {0, 255, 0}, 1.0, 10.0, 0.4);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vector) { 0.0, 1.5, 3.5 }, (t_vector) { 0.0, 0.0, 0.0 },
											(SDL_Color) {123, 123, 123}, 1.0, 150.0, 0.3);

	rtv->light = new_light(rtv->light, AMBIENT, 0.1, (t_vector) { 0.0, 0.0, 0.0 });
	rtv->light = new_light(rtv->light, POINT, 0.8, (t_vector) { 2.0, 2.0, 0.0 });
	rtv->light = new_light(rtv->light, DIRECTIONAL, 0.0, (t_vector) { 1.0, 4.0, 4.0 });

	t_vector camera = { 0.0, 0.5, -5.0 };
	rtv->camera = camera;

	threads(rtv);
	screen_upd(rtv);
	SDL_Event e;
	while (SDL_PollEvent(&e) || 1)
	{
		if (e.type == SDL_QUIT ||
			(KEY == SDLK_ESCAPE))
			break;
		if (KEY == SDLK_LEFT)
		{
			rtv->camera.x -= 0.25;
			printf("go left\n");
		}
		if (KEY == SDLK_RIGHT)
		{
			rtv->camera.x += 0.25;
			printf("go right\n");
		}
		if (KEY == SDLK_UP)
		{
			rtv->camera.y += 0.25;
			printf("go up\n");
		}
		if (KEY == SDLK_DOWN)
		{
			rtv->camera.y -= 0.25;
			printf("go down\n");
		}
		if (e.type == SDL_KEYDOWN)
		{
			threads(rtv);
		}
	}

	garbage(rtv);
	// system("leaks rtv");
	return (0);
}
