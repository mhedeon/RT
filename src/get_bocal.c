/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bocal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikoloshy <ikoloshy@unit.student.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 20:33:17 by ikoloshy          #+#    #+#             */
/*   Updated: 2019/03/30 20:45:15 by ikoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../rtv1.h"

t_vec	get_bocal_center(t_object *bocal)
{
	if (!bocal->cmp_start)
		return ((t_vec) {0.0, 0.0, 0.0});
	return (bocal->next->center);
}

t_vec	get_bocal_axis(t_object *bocal)
{
	if (!bocal->cmp_start)
		return ((t_vec) {0.0, 0.0, 0.0});
	return (bocal->next->normal);
}

SDL_Color	get_bocal_color(t_object *bocal)
{
	if (!bocal->cmp_start)
		return ((SDL_Color) {0, 0, 0, 0});
	return (bocal->color);
}
