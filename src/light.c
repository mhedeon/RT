/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:59:28 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/28 16:42:39 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

void		start_light(t_rtv *rtv, int *fd)
{
	char	*line;
	t_light	*tmp;

	tmp = rtv->light;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	while (get_next_line(*fd, &line))
	{
		if (!ft_strncmp(line + 1, "position:", 9))
			tmp->pos = read_vec(line);
		else if (!ft_strncmp(line + 1, "intensivity:", 12))
			tmp->intens = read_number(line) >= 1.0 ? 1.0 : read_number(line);
		else if (!ft_strcmp(line, "#"))
		{
			free(line);
			return ;
		}
		free(line);
	}
}

double		point(t_rtv *rtv, t_fov pv, t_vec normal, double specular)
{
	double	in;
	t_vec	vec_l;
	t_vec	vec_r;

	in = 0.0;
	vec_l = substruct(rtv->light->pos, pv.cam);
	close_inters(rtv, (t_fov){pv.cam, vec_l}, EPSILON, 1.0);
	if (rtv->close_o != NULL)
		return (0.0);
	rtv->close = dot(normal, vec_l);
	in += rtv->close > 0.0 ? rtv->light->intens * rtv->close /
			(length(normal) * length(vec_l)) : 0.0;
	vec_r = multiply(2.0 * dot(normal, vec_l), normal);
	vec_r = substruct(vec_r, vec_l);
	rtv->close = dot(vec_r, pv.dir);
	in += rtv->close > 0.0 ? rtv->light->intens * pow(rtv->close /
			(length(vec_r) * length(pv.dir)), specular) : 0.0;
	return (in);
}

double		lighting(t_rtv *rtv, t_fov pv, t_vec normal, double specular)
{
	double	in;
	t_light	*tmp;

	in = 0.0;
	tmp = rtv->light;
	while (rtv->light != NULL)
	{
		in += rtv->light->type == AMBIENT ? rtv->light->intens : 0.0;
		in += rtv->light->type == POINT ?
				point(rtv, pv, normal, specular) : 0.0;
		rtv->light = rtv->light->next;
	}
	rtv->light = tmp;
	in = in > 1.0 ? 1.0 : in;
	in = in < 0.0 ? 0.0 : in;
	return (in);
}
