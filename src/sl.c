/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 18:45:55 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 19:06:11 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_slice	*err(char **m)
{
	matrix_del(m);
	return (NULL);
}

static t_slice	*arrrrr_norm(t_object *obj, char *line, int type)
{
	t_vec		origin;
	t_vec		axis;
	char		**m;

	m = ft_strsplit(line, ' ');
	if (!ft_strcmp(m[2], "origin:"))
		origin = read_vec(line + ft_strlen(m[0]) + ft_strlen(m[1]) + 2);
	else
		return (err(m));
	if (!ft_strcmp(m[6], "axis:"))
		axis = read_vec(line + ft_strlen(m[0]) + ft_strlen(m[1]) +
				ft_strlen(m[2]) + ft_strlen(m[3]) + ft_strlen(m[4]) +
												ft_strlen(m[5]) + 6);
	else
		return (err(m));
	matrix_del(m);
	return (add_slice(obj->slice, origin, axis, type));
}

t_slice			*read_slice(t_object *obj, char *line)
{
	char		**m;
	int			type;

	if (obj->slice != NULL)
		return (obj->slice);
	m = ft_strsplit(line, ' ');
	if (matrix_height(m) != 10)
		return (err(m));
	if (!ft_strcmp(m[1], "own"))
		type = OWN;
	else if (!ft_strcmp(m[1], "real"))
		type = REAL;
	else
		return (err(m));
	matrix_del(m);
	return (arrrrr_norm(obj, line, type));
}
