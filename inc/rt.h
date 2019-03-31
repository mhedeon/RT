/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:08:48 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 19:09:26 by mhedeon          ###   ########.fr       */
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
# define DEG(a) ((double)a * 180.0 / M_PI)

/*
**	types of light
*/
typedef enum		e_ltype
{
	AMBIENT = 1,
	POINT,
	DIRECT,
	PARALLEL
}					t_ltype;

/*
**	types of objects
*/
typedef enum		e_type
{
	NINE,
	PLANE,
	SPHERE,
	CYLINDER,
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
	double			cos_angle;
	t_vec			pos;
	t_vec			normal;
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
	t_vec			rot;
	double			specular;
	double			reflective;
	void			*cmp_start;
	t_slice			*slice;
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
	int				sepia;
}					t_rt;

typedef struct		s_face
{
	t_picker		*picker;
	SDL_Rect		left_r;
	SDL_Rect		right_r;
	SDL_Rect		top_r;
	t_rt			*rt;
	t_object		*o_focus;
	t_object		*o_start;
	int				start;
	int				end;
	TTF_Font		*font;
	t_checkbox		*sepia;
}					t_face;

typedef struct		s_vecl
{
	t_vec			v;
	double			specular;
}					t_vecl;

/*
** Slice the object
*/
typedef enum		e_slice_type
{
	REAL,
	OWN
}					t_slice_type;

t_slice				*add_slice(t_slice *start, t_vec point,
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
** get_bocal.c
*/
t_vec				get_bocal_center(t_object *bocal);
t_vec				get_bocal_axis(t_object *bocal);
SDL_Color			get_bocal_color(t_object *bocal);

/*
**	rot_composed.c
*/
void				rotation_bocal(t_object *bocal, t_vec rot);
void				translate_bocal(t_object *bocal, t_vec origin);

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
**	light_objects.c
*/
t_light				*add_ambient(t_light *l);
t_light				*add_point(t_light *l);
t_light				*add_parallel(t_light *l);
t_light				*add_direct(t_light *l);

/*
**	light.c
*/
void				start_light(t_rt *rt, int *fd);
double				point(t_rt *rt, t_fov pv, t_vec normal, t_vecl v);
SDL_Color			lighting(t_rt *rt, t_fov pv, t_vec normal,
								t_object *obj);

/*
**	main.c
*/
int					translate(t_rt *rt, SDL_Event e);
int					rotate(t_rt *rt, SDL_Event e);
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
t_vec				read_rot(t_object *obj, char *line);
t_slice				*read_slice(t_object *obj, char *line);

/*
**	scene.c
*/
int					check_struct(t_rt *rt, char *line);
int					check_option_o2(t_object *tmp, char *line);
int					check_option_o(t_object *tmp, char *line);
void				get_data(t_rt *rt, char *name);
int					check_option_bocal(t_object *bocal, char *line);

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
double				ft_vangle(t_vec a, t_vec b);

double				dual_cone_spotlight(t_vec p, t_light *light,
												double cos_angle);
int					init_face(t_face *face, t_rt *rt);
int					face_close(t_face *face, t_rt *rt);
void				interface_set_obj(t_face *face, t_rt *rt);
void				interface_draw(t_face *face, t_rt *rt);
t_object			*in_list(t_rt *rt, t_face *face, int x, int y);
int					event(t_rt *rt, t_face *face);
void				obj_help(t_object *obj);

/*
**	text1-3.c
*/
void				text_draw(t_rt *rt, t_face *face);
char				*get_str_from_double(double xyz, char *start);
void				draw_xyz(t_rt *rt, t_face *face);
void				draw_xyz_angles(t_rt *rt, t_face *face);
void				draw_hsv(t_rt *rt, t_face *face);
void				draw_rgb(t_rt *rt, t_face *face);

#endif
