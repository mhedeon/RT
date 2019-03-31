/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 04:52:25 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 04:54:24 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

t_checkbox		*checkbox_create(Uint8 status, Uint8 available, int x, int y)
{
	t_checkbox	*new;

	if ((new = (t_checkbox*)malloc(sizeof(t_checkbox))) == NULL)
	{
		error_log("Could not allocate memory for checkbox");
		return (NULL);
	}
	if ((status != CHECK_ON && status != CHECK_OFF) ||
		(available != CHECK_AVAILABLE && available != CHECK_UNAVAILABLE))
	{
		free(new);
		error_log("Incorrect checkbox data");
		return (NULL);
	}
	new->status = status;
	new->available = available;
	new->pos = (SDL_Rect) { x, y, CHECKBOX_SIZE, CHECKBOX_SIZE };
	return (new);
}

void			checkbox_delete(t_checkbox **check)
{
	if (*check == NULL)
		return ;
	free(*check);
	*check = NULL;
}
