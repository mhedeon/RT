/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox_get_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 04:53:11 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:01:05 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

Uint8			checkbox_get_status(t_checkbox *check)
{
	if (check == NULL)
		return (INVALID_POINTER);
	return (check->status);
}

Uint8			checkbox_get_availalbe(t_checkbox *check)
{
	if (check == NULL)
		return (INVALID_POINTER);
	return (check->available);
}

int				checkbox_get_pos_x(t_checkbox *check)
{
	if (check == NULL)
		return (-1);
	return (check->pos.x);
}

int				checkbox_get_pos_y(t_checkbox *check)
{
	if (check == NULL)
		return (-1);
	return (check->pos.y);
}

SDL_Rect		checkbox_get_pos(t_checkbox *check)
{
	SDL_Rect	pos;

	pos = (SDL_Rect) { 0, 0, 0, 0 };
	if (check == NULL)
		return (pos);
	pos.x = check->pos.x;
	pos.y = check->pos.y;
	pos.w = CHECKBOX_SIZE;
	pos.h = CHECKBOX_SIZE;
	return (pos);
}
