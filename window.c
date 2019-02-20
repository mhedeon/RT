/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:47 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/20 18:33:03 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void init(t_rtv *rtv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	rtv->win = SDL_CreateWindow("rtv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	rtv->ren = SDL_CreateRenderer(rtv->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	rtv->tex = SDL_CreateTexture(rtv->ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	rtv->buff = (Uint32 *)malloc(sizeof(Uint32) * (SCREEN_HEIGHT * SCREEN_WIDTH));
	rtv->obj = NULL;
	rtv->light = NULL;
	clear_buffer(rtv);
}

void garbage(t_rtv *rtv)
{
	SDL_DestroyTexture(rtv->tex);
	SDL_DestroyRenderer(rtv->ren);
	SDL_DestroyWindow(rtv->win);
	while (rtv->obj != NULL)
	{
		free(rtv->obj->data);
		free(rtv->obj);
		rtv->obj = rtv->obj->next;
	}
	while (rtv->light != NULL)
	{
		free(rtv->light);
		rtv->light = rtv->light->next;
	}
	free(rtv->buff);
	free(rtv);
}

void put_pixel(t_rtv *rtv, int x, int y)
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