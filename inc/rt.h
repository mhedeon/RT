/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:08:48 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/29 18:44:06 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libmgl.h"
# include "libft.h"
# include "text.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# define WIN_W 1400
# define WIN_H 1000
# define SCENE_W 800
# define SCENE_H 800

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
# define PLANE 1
# define SPHERE 2
# define CYLINDER 3
# define CONE 4

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
	void			(*intersect)();
	t_vec			(*get_normal)();
	struct s_object	*next;
}					t_object;

typedef struct		s_fov
{
	t_vec			cam;
	t_vec			dir;
}					t_fov;

typedef struct		s_rt
{
	t_window		*win;
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
	SDL_Rect		scene_r;
}					t_rt;

typedef struct		s_face
{
	t_picker		*picker;
	SDL_Rect		left_r;
	SDL_Rect		right_r;
	SDL_Rect		top_r;
	t_rt			*rt;
	t_object		*o_focus;
	TTF_Font		*font;
}					t_face;

/*
**	camera.c
*/
int					check_camera(t_rt *rt, char *line);
void				start_camera(t_rt *rt, int *fd);
t_vec				rot_x(t_vec v, int angle);
t_vec				rot_y(t_vec v, int angle);
t_vec				rot_z(t_vec v, int angle);

/*
**	init.c
*/
int					init(t_rt *test);
int					garbage(t_rt *test);
int					matrix_height(char **m);
void				matrix_del(char **m);

/*
**	intersect.c
*/
void				close_inters(t_rt *rt, t_fov fov, double min, double max);
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
void				start_light(t_rt *rt, int *fd);
double				point(t_rt *rt, t_fov pv, t_vec normal, double specular);
double				lighting(t_rt *rt, t_fov pv, t_vec normal,
								double specular);

/*
**	main.c
*/
void				put_pixel(t_rt *rt, SDL_Color color, int x, int y);
int					rnd();
SDL_Color			do_color(SDL_Color local, SDL_Color reflected,
								double reflective);

/*
**	normal.c
*/
t_vec				normalize(t_vec v);
t_vec				normal_plane(t_rt *rt, t_vec camera, t_vec dir,
									t_vec point);
t_vec				normal_sphere(t_rt *rt, t_vec camera, t_vec dir,
									t_vec point);
t_vec				normal_cylinder(t_rt *rt, t_vec camera, t_vec dir,
									t_vec point);
t_vec				normal_cone(t_rt *rt, t_vec camera, t_vec dir,
									t_vec point);

/*
**	object.c
*/
t_object			*add_plane(t_object *obj);
t_object			*add_sphere(t_object *obj);
t_object			*add_cylinder(t_object *obj);
t_object			*add_cone(t_object *obj);
void				start_object(t_rt *rt, int *fd);

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
int					check_struct(t_rt *rt, char *line);
int					check_option_o2(t_object *tmp, char *line);
int					check_option_o(t_object *tmp, char *line);
void				get_data(t_rt *rt, char *name);

/*
**	trace.c
*/
SDL_Color			trace(t_rt *rt, t_fov fov);
void				go(t_rt *rt);
void				threads(t_rt *rt);

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



////////////////////////
int	init_face(t_face *face, t_rt *rt);
void interface_set_obj(t_face *face, t_rt *rt);
void interface_draw(t_face *face, t_rt *rt);


void text_draw(t_rt *rt, t_face *face);

#endif
