/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:59:02 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/22 21:28:50 by mhedeon          ###   ########.fr       */
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
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = -1;
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
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = -1;
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
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = -1;
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
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = -1;
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
		return (1);
	}
	return (0);
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

t_vec read_vec(char *line)
{
	char **m;
	t_vec res;
	char *s;

	m = ft_strsplit(line, ' ');
	if (matrix_height(m != 4))
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

int check_option(t_rtv *rtv, char *line)
{
	if (ft_strlen(line) < 2)
		return (0);
	
}

int start_struct(t_rtv *rtv, int *fd)
{
	char *line;
	t_object *tmp;

	tmp = rtv->obj;
	while (tmp != NULL)
		tmp = tmp->next;
	while (get_next_line(*fd, &line))
	{
		if (!ft_strcmp(line, "#"))
		{
			free(line);
			return (1);
		}


	}
	rtv->camera = rtv->camera;
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
		if (!check_struct(rtv, line))
			break ;
		
	}
}
