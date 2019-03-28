/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 22:39:45 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/28 18:17:38 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec		normalize(t_vec v)
{
	return (multiply(1.0 / length(v), v));
}

t_vec		normal_plane(t_rt *rt, t_vec camera, t_vec dir, t_vec point)
{
	t_vec	normal;

	camera.x = camera.x;
	point.x = point.x;
	normal = dot(dir, rt->close_o->normal) < 0.0 ?
					rt->close_o->normal : multiply(-1.0, rt->close_o->normal);
	return (normal);
}

t_vec		normal_sphere(t_rt *rt, t_vec camera, t_vec dir, t_vec point)
{
	t_vec	normal;

	camera.x = camera.x;
	dir.x = dir.x;
	normal = substruct(point, rt->close_o->center);
	return (normalize(normal));
}

t_vec		normal_cylinder(t_rt *rt, t_vec camera, t_vec dir, t_vec point)
{
	t_vec	normal;
	double	m;

	m = dot(dir, rt->close_o->normal) * rt->close +
			dot(substruct(camera, rt->close_o->center), rt->close_o->normal);
	normal = substruct(substruct(point, rt->close_o->center),
									multiply(m, rt->close_o->normal));
	return (normalize(normal));
}

t_vec		normal_cone(t_rt *rt, t_vec camera, t_vec dir, t_vec point)
{
	t_vec	normal;
	double	m;

	m = dot(dir, rt->close_o->normal) * rt->close +
			dot(substruct(camera, rt->close_o->center), rt->close_o->normal);
	normal = substruct(substruct(point, rt->close_o->center),
			multiply(1.0 + pow(((t_cone*)(rt->close_o->data))->angle, 2.0),
			multiply(m, rt->close_o->normal)));
	return (normalize(normal));
}
