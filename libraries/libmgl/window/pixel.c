/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:21:06 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:22:26 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

void	set_pixel(t_window *win, SDL_Color *color, int x, int y)
{
	if (!window_within(win, x, y))
		return ;
	win->buff[y * win->w + x] =
								color->r << 24 |
								color->g << 16 |
								color->b << 8 |
								color->a;
}

int		window_within(t_window *win, int x, int y)
{
	if ((x >= 0 && x < win->w) &&
		(y >= 0 && y < win->h))
		return (1);
	return (0);
}
