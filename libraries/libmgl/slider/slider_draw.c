/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:16:41 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:19:47 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

#define BLACK &(SDL_Color){0, 0, 0, 0}
#define WHITE &(SDL_Color){255, 255, 255, 0}
#define R SDL_Rect

static void	draw_corner(t_window *win, SDL_Rect *p, SDL_Color *color, int dir)
{
	if (dir > 0)
	{
		set_pixel(win, color, p->x, p->y + 2);
		set_pixel(win, color, p->x + 1, p->y + 1);
		set_pixel(win, color, p->x + 2, p->y);
		set_pixel(win, color, p->x + 1, p->y + 2);
		set_pixel(win, color, p->x + 2, p->y + 1);
	}
	else if (dir < 0)
	{
		set_pixel(win, color, p->x, p->y);
		set_pixel(win, color, p->x + 1, p->y + 1);
		set_pixel(win, color, p->x + 2, p->y + 2);
		set_pixel(win, color, p->x, p->y + 1);
		set_pixel(win, color, p->x + 1, p->y + 2);
	}
}

static void	slider_ty_norm(t_window *win, t_slider *sl)
{
	draw_corner(win, &(R){sl->pos.x + 1, sl->pos.y + 1, 0, 0}, BLACK, 1);
	draw_corner(win, &(R){sl->pos.x + 2 + sl->pos.w, sl->pos.y + 1, 0, 0},
													BLACK, -1);
	draw_corner(win, &(R){sl->pos.x, sl->pos.y + 2 + sl->pos.h, 0, 0}, WHITE,
																-1);
	draw_corner(win, &(R){sl->pos.x + 3 + sl->pos.w, sl->pos.y + 2 +
													sl->pos.h, 0, 0}, WHITE, 1);
	draw_corner(win, &(R){sl->pos.x + 1, sl->pos.y + 1 + sl->pos.h, 0, 0},
													BLACK, -1);
	draw_corner(win, &(R){sl->pos.x + 2 + sl->pos.w, sl->pos.y + 1 +
													sl->pos.h, 0, 0}, BLACK, 1);
}

void		slider_draw(t_window *win, t_slider *sl)
{
	color_area(win, &(R){sl->pos.x + 2, sl->pos.y + 2, sl->pos.w + 2,
													sl->pos.h + 2}, &sl->color);
	color_area(win, &(R){sl->pos.x + 2, sl->pos.y, sl->pos.w + 2, 1}, WHITE);
	color_area(win, &(R){sl->pos.x + 2, sl->pos.y + 6 + sl->pos.h - 1,
													sl->pos.w + 2, 1}, WHITE);
	color_area(win, &(R){sl->pos.x, sl->pos.y + 2, 1, sl->pos.h + 2}, WHITE);
	color_area(win, &(R){sl->pos.x + 6 + sl->pos.w - 1, sl->pos.y + 2, 1,
													sl->pos.h + 2}, WHITE);
	color_area(win, &(R){sl->pos.x + 3, sl->pos.y + 1, sl->pos.w, 1}, BLACK);
	color_area(win, &(R){sl->pos.x + 3, sl->pos.y + 6 + sl->pos.h - 2,
													sl->pos.w, 1}, BLACK);
	color_area(win, &(R){sl->pos.x + 1, sl->pos.y + 3, 1, sl->pos.h}, BLACK);
	color_area(win, &(R){sl->pos.x + 6 + sl->pos.w - 2, sl->pos.y + 3, 1,
													sl->pos.h}, BLACK);
	draw_corner(win, &(R){sl->pos.x, sl->pos.y, 0, 0}, WHITE, 1);
	draw_corner(win, &(R){sl->pos.x + 3 + sl->pos.w, sl->pos.y, 0, 0}, WHITE,
																		-1);
	slider_ty_norm(win, sl);
}
