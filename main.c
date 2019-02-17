/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/17 22:31:21 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double lighting(t_rtv *rtv, t_vec *point, t_vec *normal, t_vec *view, int specular)
{
	double in = 0.0;
	double len = length(*normal);
	double len_v = length(*view);
	t_light *tmp = rtv->light;

	while (tmp != NULL)
	{
		if (tmp->type == AMBIENT)
			in += tmp->intens;
		else
		{
			t_vec vec_l;
			if (tmp->type == POINT)
			{
				vec_l = substruct(tmp->pos, *point);
				close_inters(rtv, point, &vec_l, 0.001, 1.0);
			}
			else
			{
				vec_l = tmp->pos;
				close_inters(rtv, point, &vec_l, 0.001, INFINITY);
			}

			if (rtv->close_sph != NULL)
			{
				tmp = tmp->next;
				continue ;
			}

			 // difuse
			double n_dot = dot(*normal, vec_l);
			if (n_dot > 0.0)
				in += tmp->intens * n_dot /
						(len * length(vec_l));

			// specular
			if (specular != -1.0)
			{
				t_vec vec_r = multiply(2.0 * dot(*normal, vec_l), *normal);
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

SDL_Color trace(t_rtv *rtv, t_vec *origin, t_vec *dir, double min, double max, int depth)
{
	double close;
	t_object *close_sph;
	close_inters(rtv, origin, dir,  min, max);

	close = rtv->close;
	close_sph = rtv->close_sph;

	if (close_sph == NULL)
		return ((SDL_Color) { 0, 0, 0, 0});

	t_vec tmp = multiply(close, *dir);
	t_vec point = add(*origin, tmp);
	t_vec normal;
	if (close_sph->type == PLANE)
	{
		if (dot(*dir, close_sph->normal) < 0.0)
			normal = close_sph->normal;
		else
			normal = multiply(-1.0, close_sph->normal);
	}
	else if (close_sph->type == SPHERE)
	{
		normal = normalize(substruct(point, close_sph->center));
	}
	else if (close_sph->type == CYLINDER)
	{
		double m = dot(*dir, close_sph->normal) * close + dot(substruct(*origin, close_sph->center), close_sph->normal);
		normal = substruct(substruct(point, close_sph->center), multiply(m, close_sph->normal));
		normal = normalize(normal);
	}
	else if (close_sph->type == CONE)
	{
		double m = dot(*dir, close_sph->normal) * close + dot(substruct(*origin, close_sph->center), close_sph->normal);
		normal = substruct(substruct(point, close_sph->center), multiply(1.0 + pow(((t_cone*)(close_sph->data))->angle, 2.0), multiply(m, close_sph->normal)));
		normal = normalize(normal);
	}

	t_vec view = multiply(-1.0, *dir);
	close = lighting(rtv, &point, &normal, &view, close_sph->specular);
	SDL_Color local_color = { (Uint8)(close * close_sph->color.r),
								(Uint8)(close * close_sph->color.g),
								(Uint8)(close * close_sph->color.b), 0 };

	if (close_sph->reflective <= 0.0 || depth <= 0)
		return (local_color);

	t_vec ray = reflect(view, normal);
	SDL_Color ref_c = trace(rtv, &point, &ray, 0.0001, max, depth - 1);
	return ((SDL_Color) { (Uint8)((1.0 - close_sph->reflective) * local_color.r + close_sph->reflective * ref_c.r),
							(Uint8)((1.0 - close_sph->reflective) * local_color.g + close_sph->reflective * ref_c.g),
							(Uint8)((1.0 - close_sph->reflective) * local_color.b + close_sph->reflective * ref_c.b), 0 });
}

t_vec rot_y(t_vec v, int angle)
{
	double x = v.x;
	double z = v.z;
	v.x = x * cos(RAD(angle)) + z * sin(RAD(angle));
	v.z = -x * sin(RAD(angle)) + z * cos(RAD(angle));
	return (v);
}

t_vec rot_x(t_vec v, int angle)
{
	double y = v.y;
	double z = v.z;
	v.y = y * cos(RAD(angle)) + z * sin(RAD(angle));
	v.z = -y * sin(RAD(angle)) + z * cos(RAD(angle));
	return (v);
}

t_vec direction(int x, int y, int angle_x, int angle_y)
{
	t_vec direction = { (double)x / (double)SCREEN_WIDTH,
							(double)y / (double)SCREEN_HEIGHT, 1.0 };
	direction = rot_x(direction, angle_x);
	direction = rot_y(direction, angle_y);
	direction = normalize(direction);
	return (direction);
}

void go(t_rtv *rtv)
{
	for (int y = rtv->start; y < rtv->end; y++)
	{
		for (int x = -(SCREEN_WIDTH / 2); x < SCREEN_WIDTH / 2; x++)
		{
			rtv->dir = direction(x, y, rtv->angle_x, rtv->angle_y);
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

int main()
{
	t_rtv *rtv = (t_rtv *)malloc(sizeof(t_rtv));
	init(rtv);
	rtv->angle_x = 0;
	rtv->angle_y = 0;
	
	rtv->obj = new_obj(rtv->obj, CONE, (t_vec) { -1.0, 2.0, -2.0 }, (t_vec) { 0.0, -1.0, 0.0 },
											(SDL_Color) {204, 102, 255, 0}, 500.0, 0.6, 5.0, 5.6, 15.0);
	rtv->obj = new_obj(rtv->obj, CYLINDER, (t_vec) { 3.0, 1.0, 4.0 }, (t_vec) { 0.0, 1.0, 0.0 },
											(SDL_Color) {0, 255, 255, 0}, 500.0, 0.5, 1.5, 4.0, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 0.0, -0.25, 3.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {255, 0, 0, 0}, 1000.0, 0.2, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, PLANE, (t_vec) { 0.0, 0.0, 0.0}, (t_vec) { 0.0, 1.0, 0.0 },
											(SDL_Color) {255, 255, 0, 0}, 5000, 0.1, -1, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 2.0, 0.5, 4.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {0, 0, 255, 0}, 500.0, 0.3, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { -2.0, 0.5, 4.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {0, 255, 0, 0}, 10000.0, 0.2, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 0.0, 1.5, 3.5 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {123, 123, 123, 0}, 150.0, 0.3, 1.0, -1, -1);

	// ((t_cone*)(rtv->obj->data))->angle = tan(RAD(((t_cone*)(rtv->obj->data))->angle));
	// double xx = rtv->obj->next->normal.x;
	// double yy = rtv->obj->next->normal.y;
	// rtv->obj->next->normal.x = xx * cos(RAD(-45)) - yy * sin(RAD(-45));
	// rtv->obj->next->normal.y = -xx * sin(RAD(-45)) + yy * cos(RAD(-45));

	rtv->light = new_light(rtv->light, AMBIENT, 0.2, (t_vec) { 0.0, 0.0, 0.0 });
	rtv->light = new_light(rtv->light, POINT, 0.4, (t_vec) { 0.0, 1.0, -4.0 });
	// rtv->light = new_light(rtv->light, DIRECTIONAL, 0.2, (t_vec) { 1.0, 4.0, 4.0 });

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
		if (KEY == SDLK_LEFT)
		{
			rtv->dir = direction(0, 0, 0, rtv->angle_y - 90);
			rtv->camera = add(rtv->camera, multiply(0.25, rtv->dir));
			printf("go left\n");
		}
		if (KEY == SDLK_RIGHT)
		{
			rtv->dir = direction(0, 0, 0, rtv->angle_y + 90);
			rtv->camera = add(rtv->camera, multiply(0.25, rtv->dir));
			printf("go right\n");
		}
		if (KEY == SDLK_UP)
		{
			rtv->dir = direction(0, 0, rtv->angle_x, rtv->angle_y);
			rtv->camera = add(rtv->camera, multiply(0.25, rtv->dir));
			printf("go up\n");
		}
		if (KEY == SDLK_DOWN)
		{
			rtv->dir = direction(0, 0, rtv->angle_x, rtv->angle_y);
			rtv->camera = add(rtv->camera, multiply(-0.25, rtv->dir));
			printf("go down\n");
		}
		if (KEY == SDLK_w)
			rtv->angle_x -= 5;
		if (KEY == SDLK_s)
			rtv->angle_x += 5;
		if (KEY == SDLK_a)
			rtv->angle_y -= 5;
		if (KEY == SDLK_d)
			rtv->angle_y += 5;
		if (e.type == SDL_KEYDOWN)
		{
			threads(rtv);
		}
	}

	garbage(rtv);
	// system("leaks rtv");
	return (0);
}
