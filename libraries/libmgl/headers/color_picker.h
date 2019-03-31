/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_picker.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:27:15 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:27:16 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_PICKER_H
# define COLOR_PICKER_H

# include "libmgl.h"

typedef struct	s_picker
{
	SDL_Rect	pos;
	SDL_Rect	hue;
	t_hsv		hsv;
	t_slider	*sl_hue;
	t_slider	*sl_pal;
}				t_picker;

t_picker		*picker_create(int height);
void			picker_delete(t_picker **picker);

void			picker_draw(t_window *win, t_picker *picker);

void			picker_set_pos(t_picker *picker, int x, int y);
void			picker_set_size(t_picker *picker, int height);
void			picker_set_h_s_v(t_picker *picker, double h, double s,
																	double v);
void			picker_set_slider_pal(t_picker *p);
void			picker_set_slider_hue(t_picker *p);

t_hsv			picker_get_hsv(t_picker *picker);
double			picker_get_hsv_h(t_picker *picker);
double			picker_get_hsv_s(t_picker *picker);
double			picker_get_hsv_v(t_picker *picker);

SDL_Rect		picker_get_pos(t_picker *picker);
int				picker_get_x(t_picker *picker);
int				picker_get_y(t_picker *picker);
int				picker_get_h(t_picker *picker);
int				picker_get_w(t_picker *picker);

int				picker_within_pal(t_picker *picker, int x, int y);
int				picker_within_hue(t_picker *picker, int x, int y);
void			picker_set_h_by_pos(t_picker *picker, int y);
void			picker_set_sv_by_pos(t_picker *picker, int x, int y);

#endif
