/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:03 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/16 22:27:37 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

t_object *new_obj(t_object *obj, int type, t_vec center, t_vec normal, SDL_Color color, double radius, double specular, double reflect)
{
	t_object	*start;
	t_object	*new;

	start = obj;
	while (obj != NULL && obj->next != NULL)
		obj = obj->next;
	new = (t_object *)malloc(sizeof(t_object));
	new->type = type;
	new->center = center;
	new->normal = normal;
	new->color = color;
	new->radius = radius;
	new->specular = specular;
	new->reflective = reflect;
	new->next = NULL;
	if (obj == NULL)
		obj = new;
	else
		obj->next = new;
	return (start == NULL ? obj : start);
}

t_light *new_light(t_light *l, int type, double intens, t_vec pos)
{
	t_light *start;
	t_light *new;

	start = l;
	while (l != NULL && l->next != NULL)
		l = l->next;
	new = (t_light *)malloc(sizeof(t_light));
	new->type = type;
	new->intens = intens;
	new->pos = pos;
	new->next = NULL;
	if (l == NULL)
		l = new;
	else
		l->next = new;
	return (start == NULL ? l : start);
}
