/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picker_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:02:28 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:02:34 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

void	picker_draw(t_window *win, t_picker *picker)
{
	int	x;
	int	y;

	y = picker->pos.y - 1;
	while (++y < (picker->pos.y + picker->pos.h))
	{
		x = picker->pos.x - 1;
		while (++x < (picker->pos.x + picker->pos.w))
		{
			win->color = hsv2rgb(picker->hsv.h,
							(x - picker->pos.x) / (double)picker->pos.w,
							1.0 - (y - picker->pos.y) / (double)picker->pos.h);
			set_pixel(win, &win->color, x, y);
		}
		win->color = hsv2rgb(((y - (double)picker->pos.y) *
							360.0 / picker->pos.h), 1.0, 1.0);
		color_area(win, &(SDL_Rect) { picker->hue.x, y, picker->hue.w, 1 },
										&win->color);
	}
	slider_draw(win, picker->sl_hue);
	slider_draw(win, picker->sl_pal);
}
