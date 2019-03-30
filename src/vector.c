/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:43 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/27 19:41:56 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	length(t_vec v1)
{
	return (sqrt(dot(v1, v1)));
}

t_vec	add(t_vec v1, t_vec v2)
{
	return ((t_vec) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z });
}

t_vec	substruct(t_vec v1, t_vec v2)
{
	return ((t_vec) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z });
}

t_vec	multiply(double k, t_vec v1)
{
	return ((t_vec) { v1.x * k, v1.y * k, v1.z * k });
}

double      ft_vangle(t_vec a, t_vec b)
{
	return (dot(a, b) / (length(a) * length(b)));
}