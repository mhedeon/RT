/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:25:13 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:25:48 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKBOX_H
# define CHECKBOX_H

# include "libmgl.h"

# define CHECKBOX_SIZE 15

# define CHECK_ON 11
# define CHECK_OFF 10

# define CHECK_AVAILABLE 0x7E
# define CHECK_UNAVAILABLE 0x81

typedef struct	s_checkbox
{
	Uint8		status;
	Uint8		available;
	SDL_Rect	pos;
}				t_checkbox;

/*
**	---------------------------- checkbox_draw.c | start
*/

void			draw_checkbox(t_window *win, t_checkbox *check);

/*
**	---------------------------- checkbox_draw.c | end
*/

/*
**	---------------------------- checkbox_create.c | start
*/

t_checkbox		*checkbox_create(Uint8 status, Uint8 available, int x, int y);
void			checkbox_delete(t_checkbox **check);

/*
**	---------------------------- checkbox_create.c | end
*/

/*
**	---------------------------- checkbox_set_data.c | start
*/

void			checkbox_set_status(t_checkbox *check, Uint8 status);
void			checkbox_set_invert_status(t_checkbox *check);
void			checkbox_set_available(t_checkbox *check, Uint8 available);
void			checkbox_set_invert_available(t_checkbox *check);
void			checkbox_set_pos(t_checkbox *check, int x, int y);

/*
**	---------------------------- checkbox_set_data.c | end
*/

/*
**	---------------------------- checkbox_get_data.c | start
*/

Uint8			checkbox_get_status(t_checkbox *check);
Uint8			checkbox_get_availalbe(t_checkbox *check);
int				checkbox_get_pos_x(t_checkbox *check);
int				checkbox_get_pos_y(t_checkbox *check);
SDL_Rect		checkbox_get_pos(t_checkbox*check);

/*
**	---------------------------- checkbox_get_data.c | end
*/

/*
**	---------------------------- checkbox_check.c | start
*/

int				checkbox_within(t_checkbox *check, int x, int y);
int				checkbox_is_on(t_checkbox *check);
int				checkbox_is_off(t_checkbox *check);
int				checkbox_is_available(t_checkbox *check);
int				checkbox_is_unavailable(t_checkbox *check);

/*
**	---------------------------- checkbox_check.c | end
*/

#endif
