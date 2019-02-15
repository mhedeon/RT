/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:08:48 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/15 22:08:41 by mhedeon          ###   ########.fr       */
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

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_light
{
	int			type;
	double		intens;
	t_vector	pos;
	struct s_light		*next;
}				t_light;

typedef struct	s_object
{
	int			type;
	t_vector	center;
	t_vector	normal;
	SDL_Color	color;
	double		radius;
	double		specular;
	double		reflective;
	int p;
	struct s_object *next;
}				t_object;


typedef struct	s_rtv
{
	SDL_Window	*win;
	SDL_Renderer	*ren;
	SDL_Texture	*tex;
	Uint32	*buff;
	SDL_Color color;
	t_vector camera;
	t_vector  dir;
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
**	intersect.c
*/
void close_inters(t_rtv *rtv, t_vector *origin, t_vector *dir, double min, double max);
double *intersect_sphere(t_vector *camera, t_vector *dir, t_object *sphere, double *ts);
double *intersect_plane(t_vector *camera, t_vector *dir, t_object *plane, double *ts);
double *intersect_cylinder(t_vector *camera, t_vector *dir, t_object *cylinder, double *ts);

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
double dot(t_vector v1, t_vector v2);
t_vector substruct(t_vector v1, t_vector v2);
double length(t_vector v1);
t_vector multiply(double k, t_vector v1);
t_vector add(t_vector v1, t_vector v2);
t_vector reflect(t_vector v1, t_vector v2);
t_vector normalize(t_vector v);

/*
**	objects.c
*/
t_object *new_obj(t_object *obj, int type, t_vector center, t_vector normal, SDL_Color color, double radius, double specular, double reflect, int tmp);
t_light *new_light(t_light *l, int type, double intens, t_vector pos);

#endif