/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 17:27:52 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 19:54:50 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			close_inters(t_rtv *rtv, t_fov fov, double min, double max)
{
	double		ts[2];
	t_object	*tmp;

	tmp = rtv->obj;
	rtv->close = INFINITY;
	rtv->close_o = NULL;
	while (tmp != NULL)
	{
		tmp->intersect(fov.cam, fov.dir, tmp, ts);
		if (ts[0] < rtv->close && min < ts[0] && ts[0] < max)
		{
			rtv->close = ts[0];
			rtv->close_o = tmp;
		}
		if (ts[1] < rtv->close && min < ts[1] && ts[1] < max)
		{
			rtv->close = ts[1];
			rtv->close_o = tmp;
		}
		tmp = tmp->next;
	}
}

void			intersect_plane(t_vec camera, t_vec dir,
								t_object *plane, double *ts)
{
	ts[0] = -dot(substruct(camera, plane->center), plane->normal);
	ts[1] = dot(dir, plane->normal);
	if (ts[1] != 0.0)
	{
		ts[0] = ts[0] / ts[1];
		ts[1] = INFINITY;
		if (length(add(multiply(ts[0], dir), camera)) > PLANE_D->radius)
			ts[0] = INFINITY;
		return ;
	}
	ts[0] = INFINITY;
	ts[1] = INFINITY;
}

void			intersect_sphere(t_vec camera, t_vec dir,
								t_object *sphere, double *ts)
{
	t_vec		oc;
	double		k[3];
	double		d;

	oc = substruct(camera, sphere->center);
	k[0] = dot(dir, dir);
	k[1] = 2.0 * dot(oc, dir);
	k[2] = dot(oc, oc) - SPHERE_D->radius_square;
	d = sqrt(k[1] * k[1] - 4.0 * k[0] * k[2]);
	if (d < 0.0)
	{
		ts[0] = INFINITY;
		ts[1] = INFINITY;
		return ;
	}
	ts[0] = (-k[1] + d) / (2.0 * k[0]);
	ts[1] = (-k[1] - d) / (2.0 * k[0]);
}

double			limit_cylinder(t_object *cylinder, t_vec cam,
								double tmp, double t)
{
	double		m;

	m = tmp * t + dot(substruct(cam, cylinder->center), cylinder->normal);
	return ((m < 0.0 || m > CYLINDER_D->height) ? INFINITY : t);
}

void			intersect_cylinder(t_vec camera, t_vec dir,
									t_object *cylinder, double *ts)
{
	t_vec		oc;
	double		k[3];
	double		d;
	double		tmp;

	tmp = dot(dir, cylinder->normal);
	oc = substruct(camera, cylinder->center);
	k[0] = dot(dir, dir) - tmp * tmp;
	k[1] = 2.0 * (dot(dir, oc) - tmp * dot(oc, cylinder->normal));
	k[2] = dot(oc, oc) - pow(dot(oc, cylinder->normal), 2.0) -
						pow(CYLINDER_D->radius, 2.0);
	d = sqrt(k[1] * k[1] - 4.0 * k[0] * k[2]);
	if (d < 0.0)
	{
		ts[0] = INFINITY;
		ts[1] = INFINITY;
		return ;
	}
	ts[0] = (-k[1] + d) / (2.0 * k[0]);
	ts[1] = (-k[1] - d) / (2.0 * k[0]);
	if (CYLINDER_D->height != INFINITY)
	{
		ts[0] = limit_cylinder(cylinder, camera, tmp, ts[0]);
		ts[1] = limit_cylinder(cylinder, camera, tmp, ts[1]);
	}
}

double			limit_cone(t_object *cone, t_vec cam,
							double tmp, double t)
{
	double		m;

	m = tmp * t + dot(substruct(cam, cone->center), cone->normal);
	return ((m < -CONE_D->height2 || m > CONE_D->height1) ? INFINITY : t);
}

void			intersect_cone(t_vec camera, t_vec dir,
								t_object *cone, double *ts)
{
	t_vec		oc;
	double		k[3];
	double		d;
	double		tmp[2];

	tmp[0] = dot(dir, cone->normal);
	tmp[1] = 1.0 + CONE_D->angle * CONE_D->angle;
	oc = substruct(camera, cone->center);
	k[0] = dot(dir, dir) - tmp[1] * tmp[0] * tmp[0];
	k[1] = 2.0 * (dot(dir, oc) - tmp[1] * tmp[0] * dot(oc, cone->normal));
	k[2] = dot(oc, oc) - tmp[1] * pow(dot(oc, cone->normal), 2.0);
	d = sqrt(k[1] * k[1] - 4.0 * k[0] * k[2]);
	if (d < 0.0)
	{
		ts[0] = INFINITY;
		ts[1] = INFINITY;
		return ;
	}
	ts[0] = (-k[1] + d) / (2.0 * k[0]);
	ts[1] = (-k[1] - d) / (2.0 * k[0]);
	ts[0] = limit_cone(cone, camera, tmp[0], ts[0]);
	ts[1] = limit_cone(cone, camera, tmp[0], ts[1]);
}
