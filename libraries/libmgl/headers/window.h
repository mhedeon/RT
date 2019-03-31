/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:30:01 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:31:20 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "libmgl.h"

typedef struct		s_window
{
	int				w;
	int				h;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*tex;
	Uint32			*buff;
	SDL_Color		color;
}					t_window;

/*
**	---------------------------- window_create.c | start
*/

/*
**	\brief Creates a new ready-to-drawing window.
**	\param title The title of the window? in UTF-8 encoding.
**	\param w Width of the window.
**	\param h Height of the window.
**	\return Structure with window, renderer, texture,
**	and buffer, or NULL if creation failed.
**	\note Default position of the window if SDL_WINDOWPOS_CENTERED.
*/
t_window			*create_win(char *title, int w, int h);

/*
**	\brief Destroy the specified structure and sets the pointer to NULL.
**	\param win Double pointer to t_window structure.
**	\note Sets the poiner to NULL
*/
void				close_win(t_window **win);

/*
**	---------------------------- window_create.c | end
*/

/*
**	---------------------------- window_update.c | start
*/

/*
**	\brief Draws the context on the window.
**	\param win Pointer to t_window structure.
**	\note buffer -> texture -> render.
*/
void				upd_win(t_window *win);

/*
**	\brief Draws a part the context on the window.
**	\param win Pointer to t_window structure.
**	\param r A pointer to the rectangular of pixels to update.
**	\note Updates a part of the texture from the buffer.
**	Copies the entire texture into a renderer with a previous renderer cleanup.
*/
void				upd_area_tex(t_window *win, SDL_Rect *r);

/*
**	\brief Draws a part the context on the window.
**	\param win Pointer to t_window structure.
**	\param r A pointer to the rectangular of pixels to update.
**	\note Updates entire texture from the buffer.
**	Copies a part of the texture to the same part of the renderer
**	without a previous renderer cleanup.
*/
void				upd_area_ren(t_window *win, SDL_Rect *r);

/*
**	---------------------------- window_update.c | end
*/

/*
**	---------------------------- window_draw.c | start
*/
void				clear_area(t_window *win, SDL_Rect *area);
void				color_area(t_window *win, SDL_Rect *area, SDL_Color *color);
void				clear_buffer(t_window *win);
void				color_buffer(t_window *win, SDL_Color *color);
/*
**	---------------------------- window_draw.c | end
*/

/*
**	---------------------------- error.c | start
*/

int					error_log(const char *message);

/*
**	---------------------------- error.c | end
*/

/*
**	---------------------------- pixel.c | start
*/

void				set_pixel(t_window *win, SDL_Color *color, int x, int y);
int					window_within(t_window *win, int x, int y);

/*
**	---------------------------- pixel.c | end
*/

#endif
