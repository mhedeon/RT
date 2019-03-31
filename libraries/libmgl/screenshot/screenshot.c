/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:09:22 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:11:33 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screenshot.h"

static void		screenshot_error(SDL_Surface *scr, const char *msg)
{
	SDL_FreeSurface(scr);
	error_log(msg);
}

static void		screen_all(SDL_Renderer *ren, SDL_Texture *tex, char *filename)
{
	int			width;
	int			height;
	SDL_Surface	*scr;

	if (SDL_QueryTexture(tex, NULL, NULL, &width, &height) < 0)
		return (screenshot_error(NULL, NULL));
	if ((scr = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0)) == NULL)
		return (screenshot_error(NULL, NULL));
	if (SDL_RenderReadPixels(ren, NULL, scr->format->format,
						scr->pixels, scr->pitch) < 0)
		return (screenshot_error(scr, NULL));
	if (IMG_SavePNG(scr, filename) < 0)
		return (screenshot_error(scr, NULL));
	SDL_FreeSurface(scr);
}

static void		screen_rect(SDL_Renderer *ren, SDL_Rect *rect, char *filename)
{
	SDL_Surface	*scr;

	if ((scr = SDL_CreateRGBSurface(0, rect->w, rect->h,
													32, 0, 0, 0, 0)) == NULL)
		return (screenshot_error(NULL, NULL));
	if (SDL_RenderReadPixels(ren, rect, scr->format->format,
						scr->pixels, scr->pitch) < 0)
		return (screenshot_error(scr, NULL));
	if (IMG_SavePNG(scr, filename) < 0)
		return (screenshot_error(scr, NULL));
	SDL_FreeSurface(scr);
}

void			screenshot(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *rect)
{
	SDL_Texture	*render_target;
	char		*filename;

	if ((filename = file_name()) == NULL)
		return (screenshot_error(NULL, NULL));
	render_target = SDL_GetRenderTarget(ren);
	SDL_SetRenderTarget(ren, render_target);
	if (rect == NULL)
		screen_all(ren, tex, filename);
	else
		screen_rect(ren, rect, filename);
	SDL_SetRenderTarget(ren, render_target);
	SDL_Log("Screenshot saved to \"%s\"\n", filename);
	free(filename);
}
