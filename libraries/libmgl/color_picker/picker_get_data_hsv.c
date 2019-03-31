/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picker_get_data_hsv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:02:40 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:02:56 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

t_hsv		picker_get_hsv(t_picker *picker)
{
	t_hsv	res;

	res = (t_hsv) { 0, 0, 0 };
	if (picker == NULL)
		return (res);
	res = picker->hsv;
	return (res);
}

double		picker_get_hsv_h(t_picker *picker)
{
	if (picker == NULL)
		return (0.0);
	return (picker->hsv.h);
}

double		picker_get_hsv_s(t_picker *picker)
{
	if (picker == NULL)
		return (0.0);
	return (picker->hsv.s);
}

double		picker_get_hsv_v(t_picker *picker)
{
	if (picker == NULL)
		return (0);
	return (picker->hsv.v);
}
