/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:16:22 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:17:59 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

t_slider		*slider_create(int width, int height)
{
	t_slider	*new;

	if ((new = (t_slider*)malloc(sizeof(t_slider))) == NULL)
	{
		error_log("Could not allocate memory for color slider");
		return (NULL);
	}
	if (width < 2 || height < 2)
		new->pos = (SDL_Rect) { 0, 0, 2, 2 };
	else
		new->pos = (SDL_Rect) { 0, 0, width, height };
	new->border = (SDL_Rect) { 0, 0, 0, 0 };
	new->color = (SDL_Color) { 255, 255, 255, 0 };
	return (new);
}

void			slider_delete(t_slider **sl)
{
	if (*sl == NULL)
		return ;
	free(*sl);
	*sl = NULL;
}
