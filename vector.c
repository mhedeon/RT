/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:43 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/11 17:20:33 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double length(t_vector v1)
{
	return (sqrt(dot(v1, v1)));
}

t_vector add(t_vector v1, t_vector v2)
{
	return ((t_vector) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z });
}

t_vector substruct(t_vector v1, t_vector v2)
{
	return ((t_vector) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z });
}

t_vector multiply(double k, t_vector v1)
{
	return ((t_vector) { v1.x * k, v1.y * k, v1.z * k });
}

t_vector reflect(t_vector v1, t_vector v2)
{
	return (substruct(multiply(2.0 * dot(v1, v2), v2), v1));
}
