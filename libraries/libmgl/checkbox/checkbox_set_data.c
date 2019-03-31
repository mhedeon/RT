/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox_set_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 04:53:31 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 04:54:56 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

void	checkbox_set_status(t_checkbox *check, Uint8 status)
{
	if (check == NULL ||
		(status != CHECK_ON && status != CHECK_OFF) ||
		checkbox_get_availalbe(check) == CHECK_UNAVAILABLE)
		return ;
	check->status = status;
}

void	checkbox_set_invert_status(t_checkbox *check)
{
	if (check == NULL)
		return ;
	if (checkbox_get_status(check) == CHECK_ON)
		checkbox_set_status(check, CHECK_OFF);
	else if (checkbox_get_status(check) == CHECK_OFF)
		checkbox_set_status(check, CHECK_ON);
}

void	checkbox_set_available(t_checkbox *check, Uint8 available)
{
	if (check == NULL ||
		(available != CHECK_AVAILABLE && available != CHECK_UNAVAILABLE))
		return ;
	check->available = available;
}

void	checkbox_set_invert_available(t_checkbox *check)
{
	if (check == NULL)
		return ;
	if (checkbox_get_availalbe(check) == CHECK_AVAILABLE)
		checkbox_set_available(check, CHECK_UNAVAILABLE);
	else if (checkbox_get_availalbe(check) == CHECK_UNAVAILABLE)
		checkbox_set_available(check, CHECK_AVAILABLE);
}

void	checkbox_set_pos(t_checkbox *check, int x, int y)
{
	if (check == NULL)
		return ;
	check->pos.x = x;
	check->pos.y = y;
}
