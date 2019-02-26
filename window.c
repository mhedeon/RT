/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:47 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 21:49:52 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel(t_rtv *rtv, int x, int y)
{
	x = SCREEN_WIDTH / 2 + x;
	y = SCREEN_HEIGHT / 2 - y - 1;
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		set_pixel(rtv, &rtv->color, x, y);
}

void	set_pixel(t_rtv *rtv, SDL_Color *color, int x, int y)
{
	rtv->buff[y * SCREEN_WIDTH + x] =
		color->r << 24 |
		color->g << 16 |
		color->b << 8 |
		color->a;
}

void	clear_buffer(t_rtv *rtv)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			rtv->buff[y * SCREEN_WIDTH + x] = 0 << 16 |
			0 << 8 |
			0;
	}
}

void	screen_upd(t_rtv *rtv)
{
	SDL_UpdateTexture(rtv->tex, NULL, rtv->buff,
		SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(rtv->ren);
	SDL_RenderCopy(rtv->ren, rtv->tex, NULL, NULL);
	SDL_RenderPresent(rtv->ren);
}
