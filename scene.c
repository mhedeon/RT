/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:59:02 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 21:49:51 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int check_struct(t_rtv *rtv, char *line)
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
		rtv->light = add_ambient(rtv->light);
	else if (!ft_strcmp(line, "POINT:"))
		rtv->light = add_point(rtv->light);
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

	tmp = rtv->obj;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (get_next_line(*fd, &line))
	{
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
		write(1, "Could not open <", 17);
		write(1, name, ft_strlen(name) + 1);
		write(1, "> file\n", 8);
		return ;
	}
	while (get_next_line(fd, &line))
	{
		if (!check_struct(rtv, line))
			break ;
		if (!ft_strcmp(line, "CAMERA:"))
			start_camera(rtv, &fd);
		else if (!ft_strcmp(line, "AMBIENT:") || !ft_strcmp(line, "POINT:"))
			start_light(rtv, &fd);
		else
			start_object(rtv, &fd);
		free(line);
	}
	close(fd);
}
