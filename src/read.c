/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:57:02 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 17:34:01 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Color		read_color(char *line)
{
	char		**m;
	SDL_Color	res;

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

t_vec			read_vec(char *line)
{
	char		**m;
	t_vec		res;
	char		*s;

	m = ft_strsplit(line, ' ');
	if (matrix_height(m) < 4)
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

double			read_number(char *line)
{
	char		**m;
	double		res;
	char		*s;

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

t_vec			read_rot(t_object *obj, char *line)
{
	t_vec		normal;

	obj->rot = read_vec(line);
	normal = rot_x((t_vec){ 0.0, 1.0, 0.0 }, obj->rot.x);
	normal = rot_y(normal, obj->rot.y);
	normal = rot_z(normal, obj->rot.z);
	return (normal);
}

t_slice *read_slice(t_object *obj, char *line)
{
	char 		**m;
	int type;
	t_vec origin;
	t_vec axis;

	if (obj->slice != NULL)
		return (obj->slice);
	m = ft_strsplit(line, ' ');
	if (matrix_height(m) != 10)
	{
		matrix_del(m);
		return (NULL);
	}
	if (!ft_strcmp(m[1], "own"))
		type = OWN;
	else if (!ft_strcmp(m[1], "real"))
		type = REAL;
	else
	{
		matrix_del(m);
		return (NULL);
	}
	if (!ft_strcmp(m[2], "origin:"))
		origin = read_vec(line + ft_strlen(m[0]) + ft_strlen(m[1]) + 2);
	else
	{
		matrix_del(m);
		return (NULL);
	}
	if (!ft_strcmp(m[6], "axis:"))
		axis = read_vec(line + ft_strlen(m[0]) + ft_strlen(m[1]) +
				ft_strlen(m[2]) + ft_strlen(m[3]) + ft_strlen(m[4]) +
												ft_strlen(m[5]) + 6);
	else
	{
		matrix_del(m);
		return (NULL);
	}
	matrix_del(m);
	return (add_slice(obj->slice, origin, axis,type));
}
