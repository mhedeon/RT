/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:59:02 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/22 23:15:03 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object *add_plane(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = PLANE;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, 1.0, 0.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 1.0;
	new->reflective = 0.0;
	new->data = (t_plane *)malloc(sizeof(t_plane));
	((t_plane*)(new->data))->radius = INFINITY;
	new->intersect = intersect_plane;
	new->get_normal = normal_plane;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

t_object *add_sphere(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = SPHERE;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, 1.0, 0.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 1.0;
	new->reflective = 0.0;
	new->data = (t_sphere *)malloc(sizeof(t_sphere));
	((t_sphere*)(new->data))->radius_square = 1.0;
	new->intersect = intersect_sphere;
	new->get_normal = normal_sphere;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

t_object *add_cylinder(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = CYLINDER;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, 1.0, 0.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 1.0;
	new->reflective = 0.0;
	new->data = (t_cylinder *)malloc(sizeof(t_cylinder));
	((t_cylinder*)(new->data))->height = INFINITY;
	((t_cylinder*)(new->data))->radius = 1.0;
	new->intersect = intersect_cylinder;
	new->get_normal = normal_cylinder;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

t_object *add_cone(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = CONE;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, -1.0, 0.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 1.0;
	new->reflective = 0.0;
	new->data = (t_cone *)malloc(sizeof(t_cone));
	((t_cone*)(new->data))->angle = tan(RAD(15));
	((t_cone*)(new->data))->height1 = INFINITY;
	((t_cone*)(new->data))->height2 = INFINITY;
	new->intersect = intersect_cone;
	new->get_normal = normal_cone;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

static int check_struct(t_rtv *rtv, char *line)
{
	if (!ft_strcmp(line, "SPHERE:"))
		rtv->obj = add_sphere(rtv->obj);
	else if (!ft_strcmp(line, "PLANE:"))
		rtv->obj = add_plane(rtv->obj);
	else if (!ft_strcmp(line, "CYLINDER:"))
		rtv->obj = add_cylinder(rtv->obj);
	else if (!ft_strcmp(line, "CONE:"))
		rtv->obj = add_cone(rtv->obj);
	else if (!ft_strcmp(line, "AMBIENT:"))
		;
	else if (!ft_strcmp(line, "POINT:"))
		;
	else if (!ft_strcmp(line, "CAMERA:"))
		;
	else
	{
		free(line);
		return (0);
	}
	return (1);
}

int				matrix_height(char **m)
{
	int	i;

	i = 0;
	while (m[i])
		i++;
	return (i);
}

void			matrix_del(char **m)
{
	int	i;

	i = -1;
	while (m[++i])
		free(m[i]);
	free(m[i]);
	free(m);
}

SDL_Color read_color(char *line)
{
	char **m;
	SDL_Color res;

	m = ft_strsplit(line, ' ');
	if (matrix_height(m) != 4)
	{
		matrix_del(m);
		return ((SDL_Color){ 0.0, 0.0, 0.0, 0.0 });
	}
	res.r = ft_atoi(m[1]);
	res.g = ft_atoi(m[2]);
	res.b = ft_atoi(m[3]);
	matrix_del(m);
	return (res);
}

t_vec read_vec(char *line)
{
	char **m;
	t_vec res;
	char *s;

	m = ft_strsplit(line, ' ');
	if (matrix_height(m) != 4)
	{
		matrix_del(m);
		return ((t_vec){ 0.0, 0.0, 0.0 });
	}
	res.x = ft_atoi(m[1]);
	if ((s = ft_strchr(m[1], '.')) != NULL)
		res.x += ft_atoi(s + 1) / pow(10, ft_strlen(s) - 1);
	res.y = ft_atoi(m[2]);
	if ((s = ft_strchr(m[2], '.')) != NULL)
		res.y += ft_atoi(s + 1) / pow(10, ft_strlen(s) - 1);
	res.z = ft_atoi(m[3]);
	if ((s = ft_strchr(m[3], '.')) != NULL)
		res.z += ft_atoi(s + 1) / pow(10, ft_strlen(s) - 1);
	matrix_del(m);
	return (res);
}

double read_number(char *line)
{
	char **m;
	double res;
	char *s;

	m = ft_strsplit(line, ' ');
	if (matrix_height(m) != 2)
	{
		matrix_del(m);
		return (0.0);
	}
	res = ft_atoi(m[1]);
	if ((s = ft_strchr(m[1], '.')) != NULL)
		res += ft_atoi(s + 1) / pow(10, ft_strlen(s) - 1);
	matrix_del(m);
	return (res);
}

t_vec read_rot(char *line)
{
	t_vec angles;
	t_vec normal;

	angles = read_vec(line);
	normal = rot_x((t_vec){ 0.0, 1.0, 0.0 }, angles.x);
	normal = rot_y(normal, angles.y);
	normal = rot_z(normal, angles.z);
	return (normal);
}


int check_option_o2(t_object *tmp, char *line)
{
	if (!ft_strncmp(line + 1, "angle:", 6) && tmp->type == CONE)
		((t_cone*)tmp->data)->angle = tan(RAD(read_number(line)));
	else if (!ft_strncmp(line + 1, "height:", 7) && tmp->type == CYLINDER)
		((t_cylinder*)tmp->data)->height = read_number(line);
	else if (!ft_strncmp(line + 1, "height:", 7) && tmp->type == CONE)
	{
		if (((t_cone*)tmp->data)->height1 == INFINITY)
			((t_cone*)tmp->data)->height1 = read_number(line);
		else
			((t_cone*)tmp->data)->height2 = read_number(line);
	}
	else
		return (0);
	return (1);
}

int check_option_o(t_object *tmp, char *line)
{
	if (ft_strlen(line) < 2)
		return (0);
	
	if (!ft_strncmp(line + 1, "center:", 7))
		tmp->center = read_vec(line);
	else if (!ft_strncmp(line + 1, "rotation:", 9))
		tmp->normal = read_rot(line);
	else if (!ft_strncmp(line + 1, "color:", 6))
		tmp->color = read_color(line);
	else if (!ft_strncmp(line + 1, "specular:", 9))
		tmp->specular = read_number(line);
	else if (!ft_strncmp(line + 1, "reflective:", 11))
		tmp->reflective = read_number(line);
	else if (!ft_strncmp(line + 1, "radius:", 7) && tmp->type == SPHERE)
		((t_sphere*)tmp->data)->radius_square = pow(read_number(line), 2.0);
	else if (!ft_strncmp(line + 1, "radius:", 7) && tmp->type == PLANE)
		((t_plane*)tmp->data)->radius = read_number(line);
	else if (!ft_strncmp(line + 1, "radius:", 7) && tmp->type == CYLINDER)
		((t_cylinder*)tmp->data)->radius = read_number(line);
	else
		return (check_option_o2(tmp, line));
	return (1);
}

void start_object(t_rtv *rtv, int *fd)
{
	char *line;
	t_object *tmp;

	if (rtv->obj == NULL)
		printf("sfgdgh\n");
	tmp = rtv->obj;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (get_next_line(*fd, &line))
	{
		printf("|%s|\n", line);
		if (!check_option_o(tmp, line))
			if (!ft_strcmp(line, "#"))
			{
				free(line);
				return ;
			}
		free(line);
	}

}

void	get_data(t_rtv *rtv, char *name)
{
	int fd;
	char *line;

	rtv->close = rtv->close;
	if ((fd = open(name, O_RDONLY)) < 0)
	{
		write(1, "Wrong file\n", 12);
		return ;
	}

	while (get_next_line(fd, &line))
	{
		// printf("|%s|\n", line);
		if (!check_struct(rtv, line))
			break ;
		start_object(rtv, &fd);
	}
}
