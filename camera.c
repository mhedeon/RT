/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:49:04 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 20:50:45 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			check_camera(t_rtv *rtv, char *line)
{
	if (!ft_strncmp(line + 1, "center:", 7))
		rtv->camera = read_vec(line);
	else if (!ft_strncmp(line + 1, "angle_x:", 8))
		rtv->angle_x = read_number(line);
	else if (!ft_strncmp(line + 1, "angle_y:", 8))
		rtv->angle_y = read_number(line);
	else
		return (0);
	return (1);
}

void		start_camera(t_rtv *rtv, int *fd)
{
	char	*line;

	while (get_next_line(*fd, &line))
	{
		if (!check_camera(rtv, line))
			if (!ft_strcmp(line, "#"))
			{
				free(line);
				return ;
			}
		free(line);
	}
}

t_vec		rot_y(t_vec v, int angle)
{
	double	x;
	double	z;

	x = v.x;
	z = v.z;
	v.x = x * cos(RAD(angle)) + z * sin(RAD(angle));
	v.z = -x * sin(RAD(angle)) + z * cos(RAD(angle));
	return (v);
}

t_vec		rot_x(t_vec v, int angle)
{
	double	y;
	double	z;

	y = v.y;
	z = v.z;
	v.y = y * cos(RAD(angle)) + z * sin(RAD(angle));
	v.z = -y * sin(RAD(angle)) + z * cos(RAD(angle));
	return (v);
}

t_vec		rot_z(t_vec v, int angle)
{
	double	y;
	double	x;

	y = v.y;
	x = v.x;
	v.x = x * cos(RAD(angle)) + y * sin(RAD(angle));
	v.y = -x * sin(RAD(angle)) + y * cos(RAD(angle));
	return (v);
}
