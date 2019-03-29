/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikoloshy <ikoloshy@unit.student.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 20:36:33 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/28 21:55:18 by ikoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_slice	*add_slice(t_slice *start, t_vec point, t_vec axis, int type)
{
	t_slice	*new;
	t_slice	*tmp;

	tmp = start;
	new = (t_slice*)malloc(sizeof(t_slice));
	new->type = type;
	new->point = point;
	new->axis = normalize(axis);
	new->next = NULL;
	while(tmp && tmp->next)
		tmp = tmp->next;
	if (tmp == NULL)
		start = new;
	else
		tmp->next = new;
	return (start);
}

int		check_slice(double t, t_slice *slc, t_vec start, t_vec direction)
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

void	slice_axis_change(t_slice *slc, int angle_x, int angle_y, int angle_z)
{
	t_slice	*tmp;

	tmp = slc;
	while(tmp)
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

void	slice_point_change(t_slice *slc, double x, double y, double z)
{
	t_slice	*tmp;

	tmp = slc;
	while(tmp)
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