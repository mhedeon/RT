/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:59:02 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 19:07:55 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			check_struct(t_rt *rt, char *line)
{
	if (!ft_strcmp(line, "SPHERE:"))
		rt->obj = add_sphere(rt->obj);
	else if (!ft_strcmp(line, "PLANE:"))
		rt->obj = add_plane(rt->obj);
	else if (!ft_strcmp(line, "CYLINDER:"))
		rt->obj = add_cylinder(rt->obj);
	else if (!ft_strcmp(line, "CONE:"))
		rt->obj = add_cone(rt->obj);
	else if (!ft_strcmp(line, "BOCAL:"))
		rt->obj = add_bocal(rt->obj, (t_vec) { 0, 0, 0 }, 10.0);
	else if (!ft_strcmp(line, "AMBIENT:"))
		rt->light = add_ambient(rt->light);
	else if (!ft_strcmp(line, "POINT:"))
		rt->light = add_point(rt->light);
	else if (!ft_strcmp(line, "DIRECT:"))
		rt->light = add_direct(rt->light);
	else if (!ft_strcmp(line, "PARALLEL:"))
		rt->light = add_parallel(rt->light);
	else if (ft_strcmp(line, "CAMERA:"))
	{
		free(line);
		return (0);
	}
	return (1);
}

int			check_option_bocal(t_object *bocal, char *line)
{
	if (!ft_strncmp(line + 1, "center:", 7))
		translate_bocal(bocal, read_vec(line));
	else if (!ft_strncmp(line + 1, "rotation:", 9))
		rotation_bocal(bocal, read_vec(line));
	else if (!ft_strncmp(line + 1, "color:", 6))
		add_color_bocal(bocal, read_color(line));
	else if (!ft_strncmp(line + 1, "specular:", 9))
		add_specular_bocal(bocal, read_number(line) < 2 ? 2 :
															read_number(line));
	else if (!ft_strncmp(line + 1, "reflective:", 11))
		add_reflective_bocal(bocal, read_number(line) < 2 ? 2 :
															read_number(line));
	else
		return (0);
	return (1);
}

int			check_option_o2(t_object *tmp, char *line)
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
	else if (!ft_strncmp(line + 1, "slice:", 6))
		tmp->slice = read_slice(tmp, line);
	else
		return (0);
	return (1);
}

int			check_option_o(t_object *tmp, char *line)
{
	if (tmp->type >= BOCAL_PLANE && tmp->type <= BOCAL_CYLINDER)
		return (check_option_bocal(tmp, line));
	else if (ft_strlen(line) < 2)
		return (0);
	if (!ft_strncmp(line + 1, "center:", 7))
		tmp->center = read_vec(line);
	else if (!ft_strncmp(line + 1, "rotation:", 9))
		tmp->normal = read_rot(tmp, line);
	else if (!ft_strncmp(line + 1, "color:", 6))
		tmp->color = read_color(line);
	else if (!ft_strncmp(line + 1, "specular:", 9))
		tmp->specular = read_number(line) < 2 ? 2 : read_number(line);
	else if (!ft_strncmp(line + 1, "reflective:", 11))
		tmp->reflective = read_number(line) > 1.0 ? 1.0 : read_number(line);
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

void		get_data(t_rt *rt, char *name)
{
	int		fd;
	char	*line;

	rt->close = rt->close;
	if ((fd = open(name, O_RDONLY)) < 0)
	{
		write(1, "Could not open <", 17);
		write(1, name, ft_strlen(name) + 1);
		write(1, "> file\n", 8);
		return ;
	}
	while (get_next_line(fd, &line))
	{
		if (!check_struct(rt, line))
			break ;
		if (!ft_strcmp(line, "CAMERA:"))
			start_camera(rt, &fd);
		else if (!ft_strcmp(line, "AMBIENT:") || !ft_strcmp(line, "POINT:") ||
				!ft_strcmp(line, "DIRECT:") || !ft_strcmp(line, "PARALLEL:"))
			start_light(rt, &fd);
		else
			start_object(rt, &fd);
		free(line);
	}
	close(fd);
}
