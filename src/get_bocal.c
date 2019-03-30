/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bocal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 20:33:17 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/30 21:57:10 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

t_vec	get_bocal_center(t_object *bocal)
{
	t_object	*first;

	if (!bocal)
		return ((t_vec) {0.0, 0.0, 0.0});
	first = bocal->cmp_start;
	return (first->next->center);
}

t_vec	get_bocal_axis(t_object *bocal)
{
	t_object	*first;

	if (!bocal)
		return ((t_vec) {0.0, 0.0, 0.0});
	first = bocal->cmp_start;
	return (first->next->normal);
}

SDL_Color	get_color(t_object *object)
{
	return (object->color);
}
