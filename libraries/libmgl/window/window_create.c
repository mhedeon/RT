/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:22:34 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:22:34 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

static int		init_win(t_window *win, char *title, int w, int h)
{
	win->win = NULL;
	win->ren = NULL;
	win->tex = NULL;
	win->buff = NULL;
	win->w = w > 0 ? w : 100;
	win->h = h > 0 ? h : 100;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (error_log("Unable to initialize SDL:"));
	if ((win->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, win->w, win->h, SDL_WINDOW_SHOWN)) == NULL)
		return (error_log("Could not create window:"));
	if ((win->ren = SDL_CreateRenderer(win->win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC)) == NULL)
		return (error_log("Could not create renderer:"));
	if ((win->tex = SDL_CreateTexture(win->ren, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, win->w, win->h)) == NULL)
		return (error_log("Could not create texture:"));
	if ((win->buff = (Uint32*)malloc(sizeof(Uint32) *
		(win->h * win->w))) == NULL)
		return (error_log("Could not allocate memory for buff"));
	clear_buffer(win);
	win->color = (SDL_Color) { 0, 0, 0, 0 };
	return (1);
}

t_window		*create_win(char *title, int w, int h)
{
	t_window	*win;

	if ((win = (t_window*)malloc(sizeof(t_window))) == NULL)
	{
		error_log("Could not allocate memory for window");
		return (NULL);
	}
	if (!init_win(win, title, w, h))
	{
		close_win(&win);
		return (NULL);
	}
	return (win);
}

void			close_win(t_window **win)
{
	if (*win == NULL)
		return ;
	if ((*win)->tex != NULL)
		SDL_DestroyTexture((*win)->tex);
	if ((*win)->ren != NULL)
		SDL_DestroyRenderer((*win)->ren);
	if ((*win)->win != NULL)
		SDL_DestroyWindow((*win)->win);
	if ((*win)->buff != NULL)
		free((*win)->buff);
	(*win)->w = 0;
	(*win)->h = 0;
	(*win)->color = (SDL_Color) { 0, 0, 0, 0 };
	free(*win);
	*win = NULL;
}
