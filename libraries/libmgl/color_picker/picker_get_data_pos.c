/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picker_get_data_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:03:03 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:03:40 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

SDL_Rect		picker_get_pos(t_picker *picker)
{
	SDL_Rect	pos;

	pos = (SDL_Rect) { 0, 0, 0, 0 };
	if (picker == NULL)
		return (pos);
	pos = (SDL_Rect) { picker->pos.x,
						picker->pos.y,
						picker->hue.x + picker->hue.w - picker->pos.x,
						picker->pos.h };
	return (pos);
}

int				picker_get_x(t_picker *picker)
{
	if (picker == NULL)
		return (-1);
	return (picker->pos.x);
}

int				picker_get_y(t_picker *picker)
{
	if (picker == NULL)
		return (-1);
	return (picker->pos.y);
}

int				picker_get_h(t_picker *picker)
{
	if (picker == NULL)
		return (-1);
	return (picker->pos.h);
}

int				picker_get_w(t_picker *picker)
{
	if (picker == NULL)
		return (-1);
	return (picker->hue.x + picker->hue.w - picker->pos.x);
}
