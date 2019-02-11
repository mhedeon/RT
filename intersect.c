/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:27:52 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/11 19:12:10 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void close_inters(t_rtv *rtv, t_vector *origin, t_vector *dir, double min, double max)
{
	t_object *tmp = rtv->obj;
	rtv->close = INFINITY;
	rtv->close_sph = NULL;
	double *ts = malloc(sizeof(double) * 2);

	while (tmp != NULL)
	{
		if (tmp->type == PLANE)
			intersect_plane(origin, dir, tmp, ts);
		else if (tmp->type == SPHERE)
			intersect_sphere(origin, dir, tmp, ts);
		if (ts[0] < rtv->close && min < ts[0] && ts[0] < max)
		{
			rtv->close = ts[0];
			rtv->close_sph = rtv->obj;
		}
		if (ts[1] < rtv->close && min < ts[1] && ts[1] < max)
		{
			rtv->close = ts[1];
			rtv->close_sph = tmp;
		}
		tmp = tmp->next;
	}

	// if (rtv->close_sph == NULL)
	// 	printf("NULL\n");
	// else
	// 	printf("----------------------------------------\n");
	// for (int i = 0; i < 5; i++)
	// {
	// 	if (i == 3)
	// 		intersect_plane(origin, dir, &rtv->sphere[i], ts);
	// 	else
	// 		intersect_sphere(origin, dir, &rtv->sphere[i], ts);
	// 	if (ts[0] < rtv->close && min < ts[0] && ts[0] < max)
	// 	{
	// 		rtv->close = ts[0];
	// 		rtv->close_sph = &rtv->sphere[i];
	// 	}
	// 	if (ts[1] < rtv->close && min < ts[1] && ts[1] < max)
	// 	{
	// 		rtv->close = ts[1];
	// 		rtv->close_sph = &rtv->sphere[i];
	// 	}
	// }
	free(ts);
}

double *intersect_sphere(t_vector *camera, t_vector *dir, t_object *sphere, double *ts)
{
	t_vector oc = substruct(*camera, sphere->center);
	double k1 = dot(*dir, *dir);
	double k2 = 2.0 * dot(oc, *dir);
	double k3 = dot(oc, oc) - sphere->radius * sphere->radius;

	double dis = k2 * k2 - 4.0 * k1 * k3;
	if (dis < 0.0)
	{
		ts[0] = INFINITY;
		ts[1] = INFINITY;
		return (ts);
	}
	ts[0] = (-k2 + sqrt(dis)) / (2.0 * k1);
	ts[1] = (-k2 - sqrt(dis)) / (2.0 * k1);
	return (ts);

}

double *intersect_plane(t_vector *camera, t_vector *dir, t_object *plane, double *ts)
{
	ts[0] = -dot(substruct(*camera, plane->center), plane->normal);
	ts[1] = dot(*dir, plane->normal);
	if (ts[1] != 0.0)
	{
		ts[0] = ts[0] / ts[1];
		ts[1] = INFINITY;
		return (ts);
	}
	ts[0] = INFINITY;
	ts[1] = INFINITY;
	return (ts);
}
