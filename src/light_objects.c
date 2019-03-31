/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:40:06 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:40:24 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light		*add_ambient(t_light *l)
{
	t_light	*start;
	t_light	*new;

	start = l;
	while (l != NULL && l->next != NULL)
		l = l->next;
	new = (t_light *)malloc(sizeof(t_light));
	new->type = AMBIENT;
	new->intens = 0.2;
	new->pos = (t_vec){ 0.0, 0.0, 0.0 };
	new->next = NULL;
	if (l == NULL)
		l = new;
	else
		l->next = new;
	return (start == NULL ? l : start);
}

t_light		*add_point(t_light *l)
{
	t_light	*start;
	t_light	*new;

	start = l;
	while (l != NULL && l->next != NULL)
		l = l->next;
	new = (t_light *)malloc(sizeof(t_light));
	new->type = POINT;
	new->intens = 0.2;
	new->pos = (t_vec){ 0.0, 0.0, 0.0 };
	new->next = NULL;
	if (l == NULL)
		l = new;
	else
		l->next = new;
	return (start == NULL ? l : start);
}

t_light		*add_parallel(t_light *l)
{
	t_light	*start;
	t_light	*new;

	start = l;
	while (l != NULL && l->next != NULL)
		l = l->next;
	new = (t_light *)malloc(sizeof(t_light));
	new->type = PARALLEL;
	new->intens = 0.2;
	new->pos = (t_vec){ 0.0, 0.0, 0.0 };
	new->normal = (t_vec){ 0.0, 0.0, 1.0 };
	new->next = NULL;
	if (l == NULL)
		l = new;
	else
		l->next = new;
	return (start == NULL ? l : start);
}

t_light		*add_direct(t_light *l)
{
	t_light	*start;
	t_light	*new;

	start = l;
	while (l != NULL && l->next != NULL)
		l = l->next;
	new = (t_light *)malloc(sizeof(t_light));
	new->type = DIRECT;
	new->intens = 0.2;
	new->pos = (t_vec){ 0.0, 0.0, 0.0 };
	new->normal = (t_vec){ 0.0, 0.0, 1.0 };
	new->cos_angle = 1;
	new->next = NULL;
	if (l == NULL)
		l = new;
	else
		l->next = new;
	return (start == NULL ? l : start);
}
