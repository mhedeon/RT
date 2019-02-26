/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:43 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 21:49:51 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double length(t_vec v1)
{
	return (sqrt(dot(v1, v1)));
}

t_vec add(t_vec v1, t_vec v2)
{
	return ((t_vec) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z });
}

t_vec substruct(t_vec v1, t_vec v2)
{
	return ((t_vec) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z });
}

t_vec multiply(double k, t_vec v1)
{
	return ((t_vec) { v1.x * k, v1.y * k, v1.z * k });
}

t_vec reflect(t_vec v1, t_vec v2)
{
	return (substruct(multiply(2.0 * dot(v1, v2), v2), v1));
}

////////////////////////////////////////////////////////////////

t_vec direction(int x, int y, int angle_x, int angle_y)
{
	t_vec direction = { (double)x / (double)SCREEN_WIDTH,
							(double)y / (double)SCREEN_HEIGHT, 1.0 };
	direction = rot_x(direction, angle_x);
	direction = rot_y(direction, angle_y);
	direction = normalize(direction);
	return (direction);
}
