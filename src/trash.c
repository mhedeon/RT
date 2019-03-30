/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:35:38 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/27 19:41:35 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		limit_cylinder(t_object *cylinder, t_vec cam,
								double tmp, double t)
{
	double	m;

	m = tmp * t + dot(substruct(cam, cylinder->center), cylinder->normal);
	return ((m < 0.0 || m > CYLINDER_D->height) ? INFINITY : t);
}

double		limit_cone(t_object *cone, t_vec cam,
							double tmp, double t)
{
	double	m;

	m = tmp * t + dot(substruct(cam, cone->center), cone->normal);
	return ((m < -CONE_D->height2 || m > CONE_D->height1) ? INFINITY : t);
}

t_vec		reflect(t_vec v1, t_vec v2)
{
	return (substruct(multiply(2.0 * dot(v1, v2), v2), v1));
}

t_vec		direction(int x, int y, int angle_x, int angle_y)
{
	t_vec	direction;

	direction = (t_vec){ (double)x / (double)SCREEN_WIDTH,
							(double)y / (double)SCREEN_HEIGHT, 1.0 };
	direction = rot_x(direction, angle_x);
	direction = rot_y(direction, angle_y);
	direction = normalize(direction);
	return (direction);
}
