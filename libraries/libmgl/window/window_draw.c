/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:21:54 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:23:40 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

void	clear_area(t_window *win, SDL_Rect *area)
{
	int	x;
	int	y;
	int	h;
	int	w;

	h = area->y + area->h;
	w = area->x + area->w;
	y = area->y - 1;
	while (++y < h)
	{
		x = area->x - 1;
		while (++x < w)
			set_pixel(win, &(SDL_Color) { 0, 0, 0, 0 }, x, y);
	}
}

void	color_area(t_window *win, SDL_Rect *area, SDL_Color *color)
{
	int	x;
	int	y;
	int	h;
	int	w;

	h = area->y + area->h;
	w = area->x + area->w;
	y = area->y - 1;
	while (++y < h)
	{
		x = area->x - 1;
		while (++x < w)
			set_pixel(win, color, x, y);
	}
}

void	clear_buffer(t_window *win)
{
	int	x;
	int	y;

	y = -1;
	while (++y < win->h)
	{
		x = -1;
		while (++x < win->w)
			win->buff[y * win->w + x] =
			0 << 24 |
			0 << 16 |
			0 << 8 |
			0;
	}
}

void	color_buffer(t_window *win, SDL_Color *color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < win->h)
	{
		x = -1;
		while (++x < win->w)
			win->buff[y * win->w + x] =
			color->r << 24 |
			color->g << 16 |
			color->b << 8 |
			color->a;
	}
}
