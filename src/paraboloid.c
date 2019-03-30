/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikoloshy <ikoloshy@unit.student.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:08:11 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/30 23:28:50 by ikoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_vec	normal_paraboloid(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point)
{
	t_vec	normal;
	double	m;

	dir.x = dir.x;
	camera.x = camera.x;
	m = dot(substruct(point, rtv->close_o->center), rtv->close_o->normal);
	//m = dot(dir, rtv->close_o->normal) * rtv->close +
	//	dot(substruct(camera, rtv->close_o->center), rtv->close_o->normal);

	normal = substruct(substruct(point, rtv->close_o->center), multiply((m +
	((t_paraboloid*)(rtv->close_o->data))->distance), rtv->close_o->normal));
	return (normalize(normal));
}

void	intersect_paraboloid(t_vec camera, t_vec dir,
							 t_object *prbld, double *ts)
{
	t_vec	oc;
	double	value[4];
	double	tmp[2];

	oc = substruct(camera, prbld->center);
	tmp[0] = dot(dir, prbld->normal);
	tmp[1] = dot(oc, prbld->normal);
	value[0] = dot(dir, dir) - pow(tmp[0], 2);
	value[1] = 2.0 * (dot(dir, oc) - tmp[0] * (tmp[1] + 2 *
		((t_paraboloid*)(prbld->data))->distance));
	value[2] = dot(oc, oc) - tmp[1] * (tmp[1] + 4 *
		((t_paraboloid*)(prbld->data))->distance);
	value[3] = sqrt(pow(value[1], 2) - 4.0 * value[0] * value[2]);
	if (value[3] < 0)
	{
		ts[0] = INFINITY;
		ts[0] = INFINITY;
		return ;
	}
	ts[0] = (-value[1] + value[3] / (2.0 * value[0]));
	ts[0] = (-value[1] - value[3] / (2.0 * value[0]));
}

t_object		*add_paraboloid(t_object *obj)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = PARABOLOID;
	new->center = (t_vec) { 0.0, 0.0, 0.0 };
	new->normal = (t_vec) { 0.0, 0.0, -1.0 };
	new->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	new->specular = 5.0;
	new->reflective = 0.0;
	new->data = (t_paraboloid *)malloc(sizeof(t_paraboloid));
	((t_paraboloid*)(new->data))->distance = 1.0;
	new->intersect = intersect_paraboloid;
	new->get_normal = normal_paraboloid;
	new->next = NULL;
	new->slice = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

// add enum PARBOLOID

// typedef struct		s_paraboloid
//{
//	double			distance;
//}					t_paraboloid;