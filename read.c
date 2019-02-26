/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:57:02 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 20:52:26 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

t_vec			read_rot(char *line)
{
	t_vec		angles;
	t_vec		normal;

	angles = read_vec(line);
	normal = rot_x((t_vec){ 0.0, 1.0, 0.0 }, angles.x);
	normal = rot_y(normal, angles.y);
	normal = rot_z(normal, angles.z);
	return (normal);
}
