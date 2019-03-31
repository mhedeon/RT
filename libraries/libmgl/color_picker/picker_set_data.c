/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picker_set_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:03:49 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:08:16 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

void			picker_set_pos(t_picker *picker, int x, int y)
{
	int			h;

	if (picker == NULL)
		return ;
	h = picker->pos.h;
	picker->pos = (SDL_Rect) { x, y, h, h };
	picker->hue = (SDL_Rect) { x + h + h / 18, y, h / 18, h };
	slider_set_border(picker->sl_pal, &(SDL_Rect) { x, y,
		x + picker->pos.w - 1, y + picker->pos.h - 1 });
	slider_set_border(picker->sl_hue, &(SDL_Rect) {picker->hue.x, picker->hue.y,
		picker->hue.x + picker->hue.w - 1, picker->hue.y + picker->hue.h - 1 });
	picker_set_slider_hue(picker);
	picker_set_slider_pal(picker);
}

void			picker_set_size(t_picker *picker, int height)
{
	int			x;
	int			y;

	if (picker == NULL)
		return ;
	x = picker->pos.x;
	y = picker->pos.y;
	picker->pos = (SDL_Rect) { x, y, height, height };
	picker->hue = (SDL_Rect) {x + height + height / 18, y, height / 18, height};
	slider_set_size(picker->sl_hue, picker->hue.w, picker->hue.w / 2);
	slider_set_size(picker->sl_pal, picker->hue.w / 2, picker->hue.w / 2);
	slider_set_border(picker->sl_pal, &(SDL_Rect) { x, y,
		x + picker->pos.w - 1, y + picker->pos.h - 1 });
	slider_set_border(picker->sl_hue, &(SDL_Rect) {picker->hue.x, picker->hue.y,
		picker->hue.x + picker->hue.w - 1, picker->hue.y + picker->hue.h - 1 });
	picker_set_slider_hue(picker);
	picker_set_slider_pal(picker);
}

void			picker_set_h_s_v(t_picker *picker, double h, double s, double v)
{
	if (picker == NULL ||
		(h < 0.0 || h > 360.0) ||
		(s < 0.0 || s > 1.0) ||
		(v < 0.0 || v > 1.0))
		return ;
	picker->hsv = (t_hsv) { h, s, v };
	picker_set_slider_hue(picker);
	picker_set_slider_pal(picker);
}

void			picker_set_slider_pal(t_picker *p)
{
	SDL_Color	color;

	color = hsv2rgb(p->hsv.h, p->hsv.s, p->hsv.v);
	slider_set_pos(p->sl_pal, p->pos.x + (int)(p->pos.w *
		p->hsv.s), p->pos.y + p->pos.h - (int)(p->pos.h * p->hsv.v));
	slider_set_color(p->sl_pal, &color);
}

void			picker_set_slider_hue(t_picker *p)
{
	SDL_Color	color;

	color = hsv2rgb(p->hsv.h, 1.0, 1.0);
	slider_set_pos(p->sl_hue, 0, p->pos.y + p->hsv.h * p->hue.h / 360.0);
	slider_set_color(p->sl_hue, &color);
}
