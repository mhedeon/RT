/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:11:04 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/21 19:11:35 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec normalize(t_vec v)
{
	return (multiply(1.0 / length(v), v));
}

t_vec normal_plane(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point)
{
	t_vec normal;

	camera.x = camera.x;
	point.x = point.x;
	normal = dot(dir, rtv->close_o->normal) < 0.0 ?
					rtv->close_o->normal : multiply(-1.0, rtv->close_o->normal);
	return (normal);
}

t_vec normal_sphere(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point)
{
	t_vec normal;

	camera.x = camera.x;
	dir.x = dir.x;
	normal = substruct(point, rtv->close_o->center);
	return (normalize(normal));
}

t_vec normal_cylinder(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point)
{
	t_vec normal;
	double m;

	m = dot(dir, rtv->close_o->normal) * rtv->close +
			dot(substruct(camera, rtv->close_o->center), rtv->close_o->normal);
	normal = substruct(substruct(point, rtv->close_o->center),
									multiply(m, rtv->close_o->normal));
	return (normalize(normal));
}

t_vec normal_cone(t_rtv *rtv, t_vec camera, t_vec dir, t_vec point)
{
	t_vec normal;
	double m;

	m = dot(dir, rtv->close_o->normal) * rtv->close +
			dot(substruct(camera, rtv->close_o->center), rtv->close_o->normal);
	normal = substruct(substruct(point, rtv->close_o->center),
			multiply(1.0 + pow(((t_cone*)(rtv->close_o->data))->angle, 2.0),
			multiply(m, rtv->close_o->normal)));
	return (normalize(normal));
}
