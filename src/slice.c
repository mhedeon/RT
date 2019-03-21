/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikoloshy <ikoloshy@unit.student.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 20:36:33 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/21 21:50:36 by ikoloshy         ###   ########.fr       */
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
	new->axis = axis;
	new->next = NULL;
	while(tmp && tmp->next)
		tmp = tmp->next;
	if (tmp == NULL)
		start = new;
	else
		tmp->next = new;
	return (start);
}

int	check_slice(double t, t_slice *slc, t_vec start, t_vec direction)
{
	t_vec	vector;
	double	angle_cos;

	if (!slc)
		return (1);
	vector = substruct(slc->point, add(start, multiply(t, direction)));
	angle_cos = dot(vector, slc->axis) / (length(slc->axis) * length(vector));
	if (angle_cos >= 0)
		return (0);
	return (1);
}