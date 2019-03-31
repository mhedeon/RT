/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 04:52:49 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 04:55:27 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

#define BLACK &(SDL_Color){0, 0, 0, 0}

static void	draw_check_off(t_window *win, int x, int y)
{
	color_area(win, &(SDL_Rect){x, y, CHECKBOX_SIZE, CHECKBOX_SIZE},
		&(SDL_Color) { 255, 255, 255, 0 });
	color_area(win, &(SDL_Rect){x, y, CHECKBOX_SIZE, 1}, BLACK);
	color_area(win, &(SDL_Rect){x, y + 1, CHECKBOX_SIZE, 1}, BLACK);
	color_area(win, &(SDL_Rect){x, y + CHECKBOX_SIZE - 1, CHECKBOX_SIZE, 1},
		BLACK);
	color_area(win, &(SDL_Rect){x, y + CHECKBOX_SIZE - 2, CHECKBOX_SIZE, 1},
		BLACK);
	color_area(win, &(SDL_Rect){x, y, 1, CHECKBOX_SIZE}, BLACK);
	color_area(win, &(SDL_Rect){x + 1, y, 1, CHECKBOX_SIZE}, BLACK);
	color_area(win, &(SDL_Rect){x + CHECKBOX_SIZE - 1, y, 1, CHECKBOX_SIZE},
		BLACK);
	color_area(win, &(SDL_Rect){x + CHECKBOX_SIZE - 2, y, 1, CHECKBOX_SIZE},
		BLACK);
}

static void	draw_check_on(t_window *win, int x, int y)
{
	draw_check_off(win, x, y);
	color_area(win, &(SDL_Rect){x + 10, y + 3, 2, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 10, y + 4, 2, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 9, y + 5, 2, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 9, y + 6, 2, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 8, y + 7, 2, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 8, y + 8, 2, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 7, y + 9, 2, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 3, y + 8, 2, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 3, y + 9, 3, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 4, y + 10, 5, 1}, BLACK);
	color_area(win, &(SDL_Rect){x + 5, y + 11, 3, 1}, BLACK);
}

static void	draw_check_unavailable(t_window *win, int x, int y)
{
	int		xx;
	int		yy;

	yy = y - 1;
	while (++yy < (y + CHECKBOX_SIZE))
	{
		xx = x - 1;
		while (++xx - (x + CHECKBOX_SIZE))
		{
			if (window_within(win, xx, yy))
				win->buff[yy * win->w + xx] = 2 *
							((win->buff[yy * win->w + xx] & 0xfcfcfcfc) >> 2);
		}
	}
}

void		draw_checkbox(t_window *win, t_checkbox *check)
{
	if (check == NULL)
	{
		error_log("Invalid pointer to checkbox");
		return ;
	}
	if (check->status == CHECK_ON)
		draw_check_on(win, check->pos.x, check->pos.y);
	else if (check->status == CHECK_OFF)
		draw_check_off(win, check->pos.x, check->pos.y);
	else
		error_log("Incorrect checkbox state");
	if (check->available == CHECK_UNAVAILABLE)
		draw_check_unavailable(win, check->pos.x, check->pos.y);
}
