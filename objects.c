/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:03 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/18 19:18:32 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"
/*
SPHERE | center 1.0 2.0 3.0 | color 255 255 255 | specular 100 | reflective 0.5 | radius 1.5
PLANE | center 0.0 0.0 0.0 | normal 1.0.0.0 0.0 | color 255 255 255 | specular 200 | reflective 0.5 | radius 25.0
*/

// t_object *new_obj(t_object *obj, char *line)
t_object *new_obj(t_object *obj, int type, t_vec center, t_vec normal, SDL_Color color, int specular, double reflect,  double radius,  double height,  double angle)
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
	new->specular = specular;
	new->reflective = reflect;
	if (type == SPHERE)
	{
		new->data = (t_sphere *)malloc(sizeof(t_sphere));
		((t_sphere*)(new->data))->radius_square = pow(radius, 2.0);
	}
	else if (type == PLANE)
	{
		new->data = (t_plane *)malloc(sizeof(t_plane));
		((t_plane*)(new->data))->radius = radius;
	}
	else if (type == CYLINDER)
	{
		new->data = (t_cylinder *)malloc(sizeof(t_cylinder));
		((t_cylinder*)(new->data))->radius = radius;
		((t_cylinder*)(new->data))->height = height;
	}
	else if (type == CONE)
	{
		new->data = (t_cone *)malloc(sizeof(t_cone));
		((t_cone*)(new->data))->height = height;
		((t_cone*)(new->data))->angle = angle;
	}
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
