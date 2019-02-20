/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/19 23:31:58 by mhedeon          ###   ########.fr       */
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
				close_inters(rtv, (t_fov){*point, vec_l}, 0.000000001, 1.0);
			}
			else
			{
				vec_l = tmp->pos;
				close_inters(rtv, (t_fov){*point, vec_l}, 0.000000001, INFINITY);
			}

			if (rtv->close_o != NULL)
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
			if (specular != -1)
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

void pr_v(char *s, t_vec v)
{
	printf("%s: x: %f | y: %f | z: %f\n", s, v.x, v.y, v.z);
}

SDL_Color trace(t_rtv *rtv, t_fov *fov, double min, double max, int depth)
{
	double close;
	t_object *close_o;
	t_fov	pr;

	close_inters(rtv, *fov,  min, max);

	close = rtv->close;
	close_o = rtv->close_o;

	if (close_o == NULL)
		return ((SDL_Color) { 0, 0, 0, 0});

	// pr = *fov;
	pr.c = add(fov->c, multiply(close, fov->d)); //point

	t_vec normal = close_o->get_normal(rtv, fov->c, fov->d, pr.c);

	t_vec view = multiply(-1.0, fov->d);
	pr.d = multiply(-1.0, fov->d);
	close = lighting(rtv, &pr.c, &normal, &view, close_o->specular);
	SDL_Color local_color = { (Uint8)(close * close_o->color.r),
								(Uint8)(close * close_o->color.g),
								(Uint8)(close * close_o->color.b), 0 };

	if (close_o->reflective <= 0.0 || depth <= 0)
		return (local_color);

	pr.d = reflect(view, normal);
	SDL_Color ref_c = trace(rtv, &pr, 0.000000001, max, depth - 1);
	return ((SDL_Color) { (Uint8)((1.0 - close_o->reflective) * local_color.r + close_o->reflective * ref_c.r),
							(Uint8)((1.0 - close_o->reflective) * local_color.g + close_o->reflective * ref_c.g),
							(Uint8)((1.0 - close_o->reflective) * local_color.b + close_o->reflective * ref_c.b), 0 });
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

void optimisation(t_vec *camera, t_object *obj)
{
	while (obj != NULL)
	{
		if(obj->type == PLANE)
			((t_plane*)obj->data)->dot1 = -dot(substruct(*camera,
												obj->center), obj->normal);
		else if (obj->type == SPHERE)
		{
			((t_sphere*)obj->data)->oc = substruct(*camera, obj->center);
			((t_sphere*)obj->data)->k3 = dot(((t_sphere*)obj->data)->oc,
			((t_sphere*)obj->data)->oc) - ((t_sphere*)obj->data)->radius_square;
		}
		// else if ()

		obj = obj->next;
	}
}

void go(t_rtv *rtv)
{
	for (int y = rtv->start; y < rtv->end; y++)
	{
		for (int x = -(SCREEN_WIDTH / 2); x < SCREEN_WIDTH / 2; x++)
		{
			rtv->dir = direction(x, y, rtv->angle_x, rtv->angle_y);
			rtv->fov.c = rtv->camera;
			rtv->fov.d = rtv->dir;
			rtv->color = trace(rtv, &rtv->fov, 1.0, INFINITY, 3);
			put_pixel(rtv, x, y);
		}
	}
}

void threads(t_rtv *rtv)
{
	SDL_Thread *thread[THREADS];
	t_rtv ttt[THREADS];

	// optimisation(&rtv->camera, rtv->obj);
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
	if (rtv == NULL)
		return (1);
	init(rtv);
	rtv->angle_x = 0;
	rtv->angle_y = 0;
	rtv->depth = 3;

	rtv->obj = new_obj(rtv->obj, CONE, (t_vec) { -1.0, 3.5, -2.0 }, (t_vec) { 0.0, -1.0, 0.0 },
											(SDL_Color) {204, 102, 255, 0}, 500, 0.6, 5.0, 2.0, 15.0);
	rtv->obj = new_obj(rtv->obj, CYLINDER, (t_vec) { 3.0, 1.0, 4.0 }, (t_vec) { 0.0, 1.0, 0.0 },
											(SDL_Color) {0, 255, 255, 0}, 500, 0.5, 1.5, 4.0, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 0.0, -0.25, 3.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {255, 0, 0, 0}, 1000, 0.2, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, PLANE, (t_vec) { 0.0, 0.0, 0.0}, (t_vec) { 0.0, 1.0, 0.0 },
											(SDL_Color) {255, 255, 0, 0}, 5000, 0.1, -1, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 2.0, 0.5, 4.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {0, 0, 255, 0}, 500, 0.3, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { -2.0, 0.5, 4.0 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {0, 255, 0, 0}, 3000, 0.4, 1.0, -1, -1);
	rtv->obj = new_obj(rtv->obj, SPHERE, (t_vec) { 0.0, 1.5, 3.5 }, (t_vec) { 0.0, 0.0, 0.0 },
											(SDL_Color) {123, 123, 123, 0}, 150, 0.3, 1.0, -1, -1);

	((t_cone*)(rtv->obj->data))->angle = tan(RAD(((t_cone*)(rtv->obj->data))->angle));
	double xx = rtv->obj->next->normal.x;
	double yy = rtv->obj->next->normal.y;
	rtv->obj->next->normal.x = xx * cos(RAD(-45)) - yy * sin(RAD(-45));
	rtv->obj->next->normal.y = -xx * sin(RAD(-45)) + yy * cos(RAD(-45));

	rtv->light = new_light(rtv->light, AMBIENT, 0.2, (t_vec) { 0.0, 0.0, 0.0 });
	rtv->light = new_light(rtv->light, POINT, 0.8, (t_vec) { 0.0, 4.0, -4.0 });
	rtv->light = new_light(rtv->light, DIRECTIONAL, 0.0, (t_vec) { 1.0, 4.0, 4.0 });

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
