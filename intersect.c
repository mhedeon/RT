/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:27:52 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/17 22:31:24 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void close_inters(t_rtv *rtv, t_vec *origin, t_vec *dir, double min, double max)
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
		else if (tmp->type == CYLINDER)
			intersect_cylinder(origin, dir, tmp, ts);
		else if (tmp->type == CONE)
			intersect_cone(origin, dir, tmp, ts);
		if (ts[0] < rtv->close && min < ts[0] && ts[0] < max)
		{
			rtv->close = ts[0];
			rtv->close_sph = tmp;
		}
		if (ts[1] < rtv->close && min < ts[1] && ts[1] < max)
		{
			rtv->close = ts[1];
			rtv->close_sph = tmp;
		}
		tmp = tmp->next;
	}
	free(ts);
}

double *intersect_sphere(t_vec *camera, t_vec *dir, t_object *sphere, double *ts)
{
	t_vec oc = substruct(*camera, sphere->center);
	double k1 = dot(*dir, *dir);
	double k2 = 2.0 * dot(oc, *dir);
	double k3 = dot(oc, oc) - SPHERE_D->radius_square;

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

double *intersect_plane(t_vec *camera, t_vec *dir, t_object *plane, double *ts)
{
	t_vec	p;

	ts[0] = -dot(substruct(*camera, plane->center), plane->normal);
	ts[1] = dot(*dir, plane->normal);
	if (ts[1] != 0.0)
	{
		ts[0] = ts[0] / ts[1];
		ts[1] = INFINITY;
		p = add(multiply(ts[0], *dir), *camera);
		if (PLANE_D->radius > 0.0 && 
				length(p) > PLANE_D->radius)
			ts[0] = INFINITY;
		return (ts);
	}
	ts[0] = INFINITY;
	ts[1] = INFINITY;
	return (ts);
}

double *intersect_cylinder(t_vec *camera, t_vec *dir, t_object *cylinder, double *ts)
{
	t_vec oc = substruct(*camera, cylinder->center);
	double k1 = dot(*dir, *dir) - dot(*dir, cylinder->normal) * dot(*dir, cylinder->normal);
	double k2 = 2.0 * ( dot(*dir, oc) - dot(*dir, cylinder->normal) * dot(oc, cylinder->normal) );
	double k3 = dot(oc, oc) - pow(dot(oc, cylinder->normal), 2.0) - pow(CYLINDER_D->radius, 2.0);

	double dis = k2 * k2 - 4.0 * k1 * k3;
	if (dis < 0.0)
	{
		ts[0] = INFINITY;
		ts[1] = INFINITY;
		return (ts);
	}
	ts[0] = (-k2 + sqrt(dis)) / (2.0 * k1);
	ts[1] = (-k2 - sqrt(dis)) / (2.0 * k1);
	double m = dot(*dir, cylinder->normal) * ts[0] + dot(substruct(*camera, cylinder->center), cylinder->normal);
	if (m < 0 || m > CYLINDER_D->height)
		ts[0] = INFINITY;
	m = dot(*dir, cylinder->normal) * ts[1] + dot(substruct(*camera, cylinder->center), cylinder->normal);
	if (m < 0 || CYLINDER_D->height > 4.0)
		ts[1] = INFINITY;
	return (ts);
}

double *intersect_cone(t_vec *camera, t_vec *dir, t_object *cone, double *ts)
{
	t_vec oc = substruct(*camera, cone->center);
	double k1 = dot(*dir, *dir) - (1.0 + pow(CONE_D->angle, 2.0)) * pow(dot(*dir, cone->normal), 2.0);
	double k2 = 2.0 * ( dot(*dir, oc) - (1.0 + pow(CONE_D->angle, 2.0)) * dot(*dir, cone->normal) * dot(oc, cone->normal) );
	double k3 = dot(oc, oc) - (1.0 + pow(CONE_D->angle, 2.0)) * pow(dot(oc, cone->normal), 2.0);

	double dis = k2 * k2 - 4.0 * k1 * k3;
	if (dis < 0.0)
	{
		ts[0] = INFINITY;
		ts[1] = INFINITY;
		return (ts);
	}
	ts[0] = (-k2 + sqrt(dis)) / (2.0 * k1);
	ts[1] = (-k2 - sqrt(dis)) / (2.0 * k1);
	double m = dot(*dir, cone->normal) * ts[0] + dot(substruct(*camera, cone->center), cone->normal);
	if (m < 0 || m > 2.0)
		ts[0] = INFINITY;
	m = dot(*dir, cone->normal) * ts[1] + dot(substruct(*camera, cone->center), cone->normal);
	if (m < 0 || m > 2.0)
		ts[1] = INFINITY;
	return (ts);
}
