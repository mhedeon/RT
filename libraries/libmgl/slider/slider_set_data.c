/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_set_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:17:16 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:17:26 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

void	slider_set_pos(t_slider *sl, int x, int y)
{
	if (sl == NULL)
		return ;
	if (x < sl->border.x)
		sl->pos.x = sl->border.x - SLIDER_BORDER;
	else if (x > (sl->border.w - sl->pos.w))
		sl->pos.x = sl->border.w - sl->pos.w - SLIDER_BORDER;
	else
		sl->pos.x = x - SLIDER_BORDER;
	if (y < sl->border.y)
		sl->pos.y = sl->border.y - SLIDER_BORDER;
	else if (y > (sl->border.h - sl->pos.h))
		sl->pos.y = sl->border.h - sl->pos.h - SLIDER_BORDER;
	else
		sl->pos.y = y - SLIDER_BORDER;
}

void	slider_set_size(t_slider *sl, int width, int height)
{
	if (sl == NULL)
		return ;
	sl->pos.w = width;
	sl->pos.h = height;
}

void	slider_set_color(t_slider *sl, SDL_Color *color)
{
	if (sl == NULL ||
		color == NULL)
		return ;
	sl->color = *color;
}

void	slider_set_border(t_slider *sl, SDL_Rect *b)
{
	if (sl == NULL ||
		b == NULL)
		return ;
	sl->border = *b;
}
