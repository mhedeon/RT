/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:20:07 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:20:45 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

TTF_Font		*ttf_open_font(char *name, int size)
{
	TTF_Font	*new;

	if (!TTF_WasInit() && TTF_Init() == -1)
	{
		error_log(TTF_GetError());
		return (NULL);
	}
	if ((new = (TTF_OpenFont(name, size))) == NULL)
	{
		error_log(TTF_GetError());
		return (NULL);
	}
	return (new);
}

void			ttf_close_font(TTF_Font *font)
{
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}
	if (TTF_WasInit())
		TTF_Quit();
}

void			ttf_render_text(SDL_Renderer *ren, TTF_Font *font, SDL_Rect *r,
															char *text)
{
	SDL_Surface	*sur;
	SDL_Texture	*msg;

	sur = TTF_RenderText_Solid(font, text, (SDL_Color) { 255, 255, 255, 0 });
	if (sur == NULL)
	{
		error_log("Text error");
		return ;
	}
	msg = SDL_CreateTextureFromSurface(ren, sur);
	if (msg == NULL)
	{
		SDL_FreeSurface(sur);
		error_log("Text error");
		return ;
	}
	SDL_RenderCopy(ren, msg, NULL, r);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(msg);
}
