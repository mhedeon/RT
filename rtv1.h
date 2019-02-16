/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:08:48 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/16 22:27:26 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <float.h>
# include "limits.h"

# define SCREEN_WIDTH 600
# define SCREEN_HEIGHT 600

# define THREADS 8

/*
**	from radians to degrees
*/
# define RAD(a) ((double)a * M_PI / 180.0)

/*
**	types of light
*/
# define AMBIENT 1
# define POINT 2
# define DIRECTIONAL 3

/*
**	types of objects
*/
# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4

# define KEY e.type == SDL_KEYDOWN && e.key.keysym.sym

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct	s_light
{
	int			type;
	double		intens;
	t_vec	pos;
	struct s_light		*next;
}				t_light;

typedef struct	s_object
{
	int			type;
	t_vec	center;
	t_vec	normal;
	SDL_Color	color;
	double		radius;
	double		specular;
	double		reflective;
	struct s_object *next;
}				t_object;


typedef struct	s_rtv
{
	SDL_Window	*win;
	SDL_Renderer	*ren;
	SDL_Texture	*tex;
	Uint32	*buff;
	SDL_Color color;
	t_vec camera;
	t_vec  dir;
	double close;
	t_object *close_sph;

	t_object *obj;
	t_light *light;

	int angle_y;
	int angle_x;

	int start;
	int end;
}				t_rtv;

/*
**	main.c
*/
double lighting(t_rtv *rtv, t_vec *point, t_vec *normal, t_vec *view, int specular);
SDL_Color trace(t_rtv *rtv, t_vec *origin, t_vec *dir, double min, double max, int depth);
t_vec rot_y(t_vec v, int angle);
t_vec rot_x(t_vec v, int angle);
t_vec direction(int x, int y, int angle_x, int angle_y);

/*
**	intersect.c
*/
void close_inters(t_rtv *rtv, t_vec *origin, t_vec *dir, double min, double max);
double *intersect_sphere(t_vec *camera, t_vec *dir, t_object *sphere, double *ts);
double *intersect_plane(t_vec *camera, t_vec *dir, t_object *plane, double *ts);
double *intersect_cylinder(t_vec *camera, t_vec *dir, t_object *cylinder, double *ts);
double *intersect_cone(t_vec *camera, t_vec *dir, t_object *cone, double *ts);

/*
**	window,c
*/
void init(t_rtv *test);
void garbage(t_rtv *test);
void put_pixel(t_rtv *rtv, int x, int y);
void	set_pixel(t_rtv *test, SDL_Color *color, int x, int y);
void	clear_buffer(t_rtv *test);
void	screen_upd(t_rtv *test);

/*
**	vector.c
*/
double dot(t_vec v1, t_vec v2);
t_vec substruct(t_vec v1, t_vec v2);
double length(t_vec v1);
t_vec multiply(double k, t_vec v1);
t_vec add(t_vec v1, t_vec v2);
t_vec reflect(t_vec v1, t_vec v2);
t_vec normalize(t_vec v);

/*
**	objects.c
*/
t_object *new_obj(t_object *obj, int type, t_vec center, t_vec normal, SDL_Color color, double radius, double specular, double reflect);
t_light *new_light(t_light *l, int type, double intens, t_vec pos);

#endif