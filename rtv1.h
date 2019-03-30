/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikoloshy <ikoloshy@unit.student.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:08:48 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/30 21:56:04 by ikoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "frameworks/SDL2.framework/Headers//SDL.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>



#include <stdio.h>

# define SCREEN_WIDTH 600
# define SCREEN_HEIGHT 600

# define THREADS 8
# define DEPTH 3
# define EPSILON ((double)0.000000001)

/*
**	from radians to degrees
*/
# define RAD(a) ((double)a * M_PI / 180.0)

/*
**	types of light
*/
# define AMBIENT 1
# define POINT 2

/*
**	types of objects
*/
typedef enum		e_type
{
	NINE,
	PLANE,
	SPHERE,
	CYLINDER,
	PARABOLOID,
	CONE,
	BOCAL_PLANE,
	BOCAL_CONE,
	BOCAL_CYLINDER
}					t_type;

/*
**	cast
*/
# define PLANE_D ((t_plane*)(plane->data))
# define SPHERE_D ((t_sphere*)(sphere->data))
# define CYLINDER_D ((t_cylinder*)(cylinder->data))
# define CONE_D ((t_cone*)(cone->data))

# define KEY e.type == SDL_KEYDOWN && e.key.keysym.sym



typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;


//add slice struct
typedef struct		s_slice
{
	int				type;
	t_vec			point;
	t_vec			axis;
	struct s_slice	*next;
}					t_slice;

typedef struct		s_light
{
	int				type;
	double			intens;
	t_vec			pos;
	struct s_light	*next;
}					t_light;

typedef struct		s_plane
{
	double			radius;
}					t_plane;

typedef struct		s_sphere
{
	double			radius_square;
}					t_sphere;

typedef struct		s_paraboloid
{
	double			distance;
}					t_paraboloid;

typedef struct		s_cylinder
{
	double			radius;
	double			height;
}					t_cylinder;

typedef struct		s_cone
{
	double			angle;
	double			height1;
	double			height2;
}					t_cone;

typedef struct		s_object
{
	int				type;
	t_vec			center;
	t_vec			normal;
	SDL_Color		color;
	double			specular;
	double			reflective;
	void			*data;
	void			*cmp_start;
	void			(*intersect)();
	t_vec			(*get_normal)();
	t_slice			*slice;
	struct s_object	*next;
}					t_object;

typedef struct		s_fov
{
	t_vec			cam;
	t_vec			dir;
}					t_fov;

typedef struct		s_rtv
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*tex;
	Uint32			*buff;
	SDL_Color		color;
	t_vec			camera;
	t_fov			fov;
	t_object		*obj;
	t_light			*light;
	t_object		*close_o;
	double			close;
	int				angle_y;
	int				angle_x;
	int				start;
	int				end;
	int				depth;
}					t_rtv;

/*
** Slice the object
*/

typedef enum		e_slice_type
{
	REAL,
	OWN
}					t_slice_type;

t_slice	*			add_slice(t_slice *start, t_vec point,
									t_vec axis, int type);
int					check_slice(double t, t_slice *slc, t_vec start,
									t_vec direction);
void				slice_axis_change(t_slice *slc, int angle_x,
									int angle_y, int angle_z);
void				slice_point_change(t_slice *slc, double x,
									double y, double z);

/*
**	bocal.c
*/
t_object			*add_bocal(t_object *obj, t_vec center, double size);
void				add_specular_bocal(t_object *bocal, double specular);
void				add_reflective_bocal(t_object *bocal, double reflective);
void				add_color_bocal(t_object *bocal, SDL_Color color);


/*
**	get_bocal.c
*/
t_vec				get_bocal_center(t_object *bocal);
t_vec				get_bocal_axis(t_object *bocal);
SDL_Color			get_bocal_color(t_object *bocal);

/*
**	rot_composed.c
*/
void				rotation_bocal(t_object *bocal, int angle_x, int angle_y,
									int angle_z);
void				translate_bocal(t_object *bocal, double x, double y,
									double z);

/*
**	paraboloid.c
*/
t_object			*add_paraboloid(t_object *obj);
void				intersect_paraboloid(t_vec camera, t_vec dir,
							 t_object *prbld, double *ts);
t_vec				normal_paraboloid(t_rtv *rtv, t_vec camera, t_vec dir,
								t_vec point);

/*
**	camera.c
*/
int					check_camera(t_rtv *rtv, char *line);
void				start_camera(t_rtv *rtv, int *fd);
t_vec				rot_x(t_vec v, int angle);
t_vec				rot_y(t_vec v, int angle);
t_vec				rot_z(t_vec v, int angle);

/*
**	init.c
*/
int					init(t_rtv *test);
int					garbage(t_rtv *test);
int					error_log(char *message);
int					matrix_height(char **m);
void				matrix_del(char **m);

/*
**	intersect.c
*/
void				close_inters(t_rtv *rtv, t_fov fov, double min, double max);
void				intersect_sphere(t_vec camera, t_vec dir, t_object *sphere,
										double *ts);
void				intersect_plane(t_vec camera, t_vec dir, t_object *plane,
										double *ts);
void				intersect_cylinder(t_vec camera, t_vec dir,
										t_object *cylinder, double *ts);
void				intersect_cone(t_vec camera, t_vec dir, t_object *cone,
										double *ts);

/*
**	light.c
*/
t_light				*add_ambient(t_light *l);
t_light				*add_point(t_light *l);
void				start_light(t_rtv *rtv, int *fd);
double				point(t_rtv *rtv, t_fov pv, t_vec normal, double specular);
double				lighting(t_rtv *rtv, t_fov pv, t_vec normal,
								double specular);

/*
**	main.c
*/
int					rnd();
SDL_Color			do_color(SDL_Color local, SDL_Color reflected,
								double reflective);

/*
**	normal.c
*/
t_vec				normalize(t_vec v);
t_vec				normal_plane(t_rtv *rtv, t_vec camera, t_vec dir,
									t_vec point);
t_vec				normal_sphere(t_rtv *rtv, t_vec camera, t_vec dir,
									t_vec point);
t_vec				normal_cylinder(t_rtv *rtv, t_vec camera, t_vec dir,
									t_vec point);
t_vec				normal_cone(t_rtv *rtv, t_vec camera, t_vec dir,
									t_vec point);

/*
**	object.c
*/
t_object			*add_plane(t_object *obj);
t_object			*add_sphere(t_object *obj);
t_object			*add_cylinder(t_object *obj);
t_object			*add_cone(t_object *obj);
void				start_object(t_rtv *rtv, int *fd);

/*
**	read.c
*/
SDL_Color			read_color(char *line);
t_vec				read_vec(char *line);
double				read_number(char *line);
t_vec				read_rot(char *line);

/*
**	scene.c
*/
int					check_struct(t_rtv *rtv, char *line);
int					check_option_o2(t_object *tmp, char *line);
int					check_option_o(t_object *tmp, char *line);
void				get_data(t_rtv *rtv, char *name);

/*
**	trace.c
*/
SDL_Color			trace(t_rtv *rtv, t_fov fov);
void				go(t_rtv *rtv);
void				threads(t_rtv *rtv);

/*
**	trash.c
*/
double				limit_cylinder(t_object *cylinder, t_vec cam, double tmp,
										double t);
double				limit_cone(t_object *cone, t_vec cam, double tmp, double t);
t_vec				reflect(t_vec v1, t_vec v2);
t_vec				direction(int x, int y, int angle_x, int angle_y);

/*
**	vector.c
*/
double				dot(t_vec v1, t_vec v2);
t_vec				substruct(t_vec v1, t_vec v2);
double				length(t_vec v1);
t_vec				multiply(double k, t_vec v1);
t_vec				add(t_vec v1, t_vec v2);

/*
**	window,c
*/
void				put_pixel(t_rtv *rtv, int x, int y);
void				set_pixel(t_rtv *test, SDL_Color *color, int x, int y);
void				clear_buffer(t_rtv *test);
void				screen_upd(t_rtv *test);

#endif
