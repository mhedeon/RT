/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 20:36:33 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/31 17:04:25 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_slice		*add_slice(t_slice *slice, t_vec point, t_vec axis, int type)
{
	t_slice	*new;

	if (slice != NULL)
		return (slice);
	if ((new = (t_slice*)malloc(sizeof(t_slice))) == NULL)
		return (NULL);
	new->type = type;
	new->point = point;
	new->axis = normalize(axis);
	new->next = NULL;
	return (new);
}

int			check_slice(double t, t_slice *slc, t_vec start, t_vec direction)
{
	t_vec	vector;
	t_slice	*tmp;

	tmp = slc;
	if (!slc)
		return (0);
	while (tmp)
	{
		vector = substruct(add(start, multiply(t, direction)), tmp->point);
		if (dot(vector, tmp->axis) / (length(tmp->axis) * length(vector)) <= 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		slice_axis_change(t_slice *slc, int angle_x, int angle_y,
																int angle_z)
{
	t_slice	*tmp;

	tmp = slc;
	while (tmp)
	{
		if (tmp->type == OWN)
		{
			slc->axis = rot_x(slc->axis, angle_x);
			slc->axis = rot_y(slc->axis, angle_y);
			slc->axis = rot_z(slc->axis, angle_z);
		}
		tmp = tmp->next;
	}
}

void		slice_point_change(t_slice *slc, double x, double y, double z)
{
	t_slice	*tmp;

	tmp = slc;
	while (tmp)
	{
		if (tmp->type == OWN)
		{
			slc->axis.x += x;
			slc->axis.y += y;
			slc->axis.z += z;
		}
		tmp = tmp->next;
	}
}
