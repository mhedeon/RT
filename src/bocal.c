/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bocal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:16:25 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/31 18:19:10 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object		*add_bocal(t_object *obj, t_vec center, double size)
{
	t_object	*bocal;

	obj = add_plane(obj);
	bocal = obj;
	while (bocal->next)
		bocal = bocal->next;
	bocal->type = BOCAL_PLANE;
	bocal->center = (t_vec) {center.x, center.y - size, center.z};
	((t_plane*)(bocal->data))->radius = size / 2;
	bocal->cmp_start = bocal;
	obj = add_cone(obj);
	(bocal->next)->type = BOCAL_CONE;
	(bocal->next)->center = center;
	((t_cone*)((bocal->next)->data))->height2 = 0.0;
	((t_cone*)((bocal->next)->data))->height1 = size / 2;
	((t_cone*)((bocal->next)->data))->angle = tan(RAD(60));
	bocal->next->cmp_start = bocal;
	obj = add_cylinder(obj);
	(bocal->next->next)->type = BOCAL_CYLINDER;
	(bocal->next->next)->center = center;
	(bocal->next->next)->normal = (t_vec) {0.0, -1.0, 0.0};
	((t_cylinder*)((bocal->next->next)->data))->height = size;
	((t_cylinder*)((bocal->next->next)->data))->radius = size / 50;
	bocal->next->next->cmp_start = bocal;
	return (obj);
}

void			add_specular_bocal(t_object *bocal, double specular)
{
	t_object	*tmp;
	int			amount;

	if (bocal == NULL)
		return ;
	tmp = bocal->cmp_start;
	amount = 0;
	while (amount < 3)
	{
		tmp->specular = specular;
		amount++;
		tmp = tmp->next;
	}
}

void			add_reflective_bocal(t_object *bocal, double reflective)
{
	t_object	*tmp;
	int			amount;

	if (bocal == NULL)
		return ;
	tmp = bocal->cmp_start;
	amount = 0;
	while (amount < 3)
	{
		tmp->reflective = reflective;
		amount++;
		tmp = tmp->next;
	}
}

void			add_color_bocal(t_object *bocal, SDL_Color color)
{
	t_object	*tmp;
	int			amount;

	if (bocal == NULL)
		return ;
	tmp = bocal->cmp_start;
	amount = 0;
	while (amount < 3)
	{
		tmp->color = color;
		amount++;
		tmp = tmp->next;
	}
}

void set_bocal_origin(t_object *bocal, t_vec center)
{
	t_object *tmp;

	tmp = bocal->cmp_start;
	tmp->center = (t_vec) {center.x, center.y - 10.0, center.z};
	((t_plane*)(tmp->data))->radius = 10.0 / 2;
	tmp = tmp->next;
	tmp->center = center;
	((t_cone*)((tmp)->data))->height1 = 0.0;
	((t_cone*)((tmp)->data))->height2 = 10.0 / 2;
	((t_cone*)((tmp)->data))->angle = tan(RAD(60));
	tmp = tmp->next;
	tmp->center = center;
	tmp->normal = (t_vec) {0.0, -1.0, 0.0};
	((t_cylinder*)((tmp)->data))->height = 10.0;
	((t_cylinder*)((tmp)->data))->radius = 10.0 / 50;
}
