/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:16:25 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 22:36:51 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				init(t_rtv *rtv)
{
	rtv->win = NULL;
	rtv->tex = NULL;
	rtv->ren = NULL;
	rtv->buff = NULL;
	rtv->obj = NULL;
	rtv->light = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (error_log("Unable to initialize SDL:"));
	if ((rtv->win = SDL_CreateWindow("rtv", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN)) == NULL)
		return (error_log("Could not create window:"));
	if ((rtv->ren = SDL_CreateRenderer(rtv->win, -1, SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC)) == NULL)
		return (error_log("Could not create renderer:"));
	if ((rtv->tex = SDL_CreateTexture(rtv->ren, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT)) == NULL)
		return (error_log("Could not create texture:"));
	if ((rtv->buff = (Uint32 *)malloc(sizeof(Uint32) *
			(SCREEN_HEIGHT * SCREEN_WIDTH))) == NULL)
		return (error_log("Could not allocate memory for buff"));
	clear_buffer(rtv);
	return (1);
}

void			garbage(t_rtv *rtv)
{
	t_object	*o_tmp;
	t_light		*l_tmp;

	while (rtv->obj != NULL)
	{
		o_tmp = rtv->obj;
		rtv->obj = rtv->obj->next;
		free(o_tmp->data);
		free(o_tmp);
	}
	while (rtv->light != NULL)
	{
		l_tmp = rtv->light;
		rtv->light = rtv->light->next;
		free(l_tmp);
	}
	SDL_DestroyTexture(rtv->tex);
	SDL_DestroyRenderer(rtv->ren);
	SDL_DestroyWindow(rtv->win);
	if (rtv->buff != NULL)
		free(rtv->buff);
	free(rtv);
}

int				error_log(char *message)
{
	SDL_Log("%s %s\n", message, SDL_GetError());
	return (0);
}
