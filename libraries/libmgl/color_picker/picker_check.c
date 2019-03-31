/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picker_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:01:51 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:02:14 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

int			picker_within_pal(t_picker *picker, int x, int y)
{
	if (picker == NULL)
		return (0);
	if ((x >= picker->pos.x && x < (picker->pos.x + picker->pos.w)) &&
		(y >= picker->pos.y && y < (picker->pos.y + picker->pos.h)))
		return (1);
	return (0);
}

int			picker_within_hue(t_picker *picker, int x, int y)
{
	if (picker == NULL)
		return (0);
	if ((x >= picker->hue.x && x < (picker->hue.x + picker->hue.w)) &&
		(y >= picker->hue.y && y < (picker->hue.y + picker->hue.h)))
		return (1);
	return (0);
}

void		picker_set_h_by_pos(t_picker *picker, int y)
{
	double	h;
	double	s;
	double	v;

	if (picker == NULL)
		return ;
	h = (y - picker->hue.y) * 360.0 / picker->hue.h;
	h = h > 360.0 ? 360.0 : h;
	h = h < 0.0 ? 0.0 : h;
	s = picker_get_hsv_s(picker);
	v = picker_get_hsv_v(picker);
	picker_set_h_s_v(picker, h, s, v);
}

void		picker_set_sv_by_pos(t_picker *picker, int x, int y)
{
	double	h;
	double	s;
	double	v;

	if (picker == NULL)
		return ;
	h = picker_get_hsv_h(picker);
	s = (x - picker->pos.x) / (double)picker->pos.w;
	s = s > 1.0 ? 1.0 : s;
	s = s < 0.0 ? 0.0 : s;
	v = 1.0 - (y - picker->pos.y) / (double)picker->pos.h;
	v = v > 1.0 ? 1.0 : v;
	v = v < 0.0 ? 0.0 : v;
	picker_set_h_s_v(picker, h, s, v);
}
