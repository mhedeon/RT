/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:29:49 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:29:49 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLIDER_H
# define SLIDER_H

# include "libmgl.h"

# define SLIDER_BORDER 3

typedef struct	s_slider
{
	SDL_Rect	pos;
	SDL_Rect	border;
	SDL_Color	color;
}				t_slider;

t_slider		*slider_create(int width, int height);
void			slider_delete(t_slider **sl);

void			slider_draw(t_window *win, t_slider *sl);

void			slider_set_pos(t_slider *sl, int x, int y);
void			slider_set_size(t_slider *sl, int width, int height);
void			slider_set_color(t_slider *sl, SDL_Color *color);
void			slider_set_border(t_slider *sl, SDL_Rect *b);

#endif
