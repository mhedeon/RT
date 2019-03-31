/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_composed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 20:38:49 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/31 05:50:39 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			rotation_bocal(t_object *bocal, int angle_x, int angle_y,
															int angle_z)
{
	t_object	*current;
	double		size;

	if (!(current = bocal->cmp_start))
		return ;
	size = length(substruct(current->next->center, current->center));
	current->normal = rot_x(current->normal, angle_x);
	current->normal = rot_y(current->normal, angle_y);
	current->normal = rot_z(current->normal, angle_z);
	current->center = substruct(current->next->center,
		multiply(size, current->normal));
	current = current->next;
	current->normal = rot_x(current->normal, angle_x);
	current->normal = rot_y(current->normal, angle_y);
	current->normal = rot_z(current->normal, angle_z);
	current = current->next;
	current->normal = rot_x(current->normal, angle_x);
	current->normal = rot_y(current->normal, angle_y);
	current->normal = rot_z(current->normal, angle_z);
}

void			translate_bocal(t_object *bocal, double x, double y, double z)
{
	t_object	*current;

	if (!(current = bocal->cmp_start))
		return ;
	current->center = (t_vec) {current->center.x + x, current->center.y + y,
							current->center.z + z};
	current = current->next;
	current->center = (t_vec) {current->center.x + x, current->center.y + y,
										current->center.z + z};
	current = current->next;
	current->center = (t_vec) {current->center.x + x, current->center.y + y,
									current->center.z + z};
}
