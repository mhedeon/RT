/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_composed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 20:38:49 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/31 18:02:07 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			rotation_bocal(t_object *bocal, t_vec rot)
{
	t_object	*current;
	double		size;

	if (!(current = bocal->cmp_start))
		return ;
	size = length(substruct(current->next->center, current->center));
	current->normal = rot_x(current->normal, rot.x);
	current->normal = rot_y(current->normal, rot.y);
	current->normal = rot_z(current->normal, rot.z);
	current->center = substruct(current->next->center,
		multiply(size, current->normal));
	current = current->next;
	current->normal = rot_x(current->normal, rot.x);
	current->normal = rot_y(current->normal, rot.y);
	current->normal = rot_z(current->normal, rot.z);
	current = current->next;
	current->normal = rot_x(current->normal, rot.x);
	current->normal = rot_y(current->normal, rot.y);
	current->normal = rot_z(current->normal, rot.z);
}

void			translate_bocal(t_object *bocal, t_vec origin)
{
	t_object	*current;

	if (!(current = bocal->cmp_start))
		return ;
	current->center = (t_vec) {current->center.x + origin.x, current->center.y + origin.y,
							current->center.z + origin.z};
	current = current->next;
	current->center = (t_vec) {current->center.x + origin.x, current->center.y + origin.y,
										current->center.z + origin.z};
	current = current->next;
	current->center = (t_vec) {current->center.x + origin.x, current->center.y + origin.y,
									current->center.z + origin.z};
}
