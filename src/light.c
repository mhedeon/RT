/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:59:28 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:45:48 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		start_light(t_rt *rt, int *fd)
{
	char	*line;
	t_light	*tmp;

	tmp = rt->light;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	while (get_next_line(*fd, &line))
	{
		if (!ft_strncmp(line + 1, "position:", 9))
			tmp->pos = read_vec(line);
		else if (!ft_strncmp(line + 1, "rotation:", 9))
			tmp->normal = read_vec(line);
		else if (!ft_strncmp(line + 1, "intensivity:", 12))
			tmp->intens = read_number(line) >= 1.0 ? 1.0 : read_number(line);
		else if (!ft_strncmp(line + 1, "angle:", 6))
			tmp->cos_angle = read_number(line) >= 1.0 ? 1.0 : read_number(line);
		else if (!ft_strcmp(line, "#"))
		{
			free(line);
			return ;
		}
		free(line);
	}
}

double		point(t_rt *rt, t_fov pv, t_vec normal, double specular, t_vec vec_l)
{
	double	in;
	t_vec	vec_r;
	double	reflect_v;

	in = 0.0;
	close_inters(rt, (t_fov){pv.cam, vec_l}, EPSILON, 1.0);
	if (rt->close_o == NULL)
	{
		rt->close = dot(normal, vec_l);
		if (rt->close > 0.0)
			in += rt->light->intens * rt->close / (length(normal) *
																length(vec_l));
		vec_r = reflect(vec_l, normal);
		reflect_v = dot(vec_r, pv.dir);
		if (reflect_v > 0.0)
			in += rt->light->intens * pow(reflect_v / (length(vec_r) *
													length(pv.dir)), specular);
	}
	return (in);
}

double		smoothstep(double min, double max, double x)
{
	if (x < min)
		return (0);
	if (x >= max)
		return (1);
	return (-2 * pow(((x - min) / (max - min)), 3)
						+ 3 * pow(((x - min) / (max - min)), 2));
}

double		dual_cone_spotlight(t_vec p, t_light *light, double cos_angle)
{
	t_vec	v;
	double	cos_outer_cone;
	double	cos_inner_cone;
	double	cos_direction;

	v = substruct(p, light->pos);
	v = normalize(v);
	cos_outer_cone = fabs(cos(cos_angle)) - 0.07;
	cos_inner_cone = fabs(cos(cos_angle));
	cos_direction = dot(v, light->normal);
	return (smoothstep(cos_outer_cone, cos_inner_cone, cos_direction));
}

SDL_Color		lighting(t_rt *rt, t_fov pv, t_vec normal, t_object *obj)
{
	double	in;
	t_light	*tmp;
	double	spot_effect;
	double	t;

	in = 0.0;
	tmp = rt->light;
	while (rt->light != NULL)
	{
		in += rt->light->type == AMBIENT ? rt->light->intens : 0.0;
		in += rt->light->type == POINT ? point(rt, pv, normal, obj->specular,
									substruct(rt->light->pos, pv.cam)) : 0.0;
		in += rt->light->type == PARALLEL ? point(rt, pv, normal, obj->specular,
							substruct(multiply(-(1000000), rt->light->normal),
												(t_vec){ 0, 0, 0 })) : 0.0;
		if (rt->light->type == DIRECT && (spot_effect =
		dual_cone_spotlight(pv.cam, rt->light, rt->light->cos_angle)) != 0.0)
		{
			t = rt->light->type == DIRECT ? point(rt, pv, normal, obj->specular,
									substruct(rt->light->pos, pv.cam)) : 0.0;
			in += (spot_effect * t);
		}
		rt->light = rt->light->next;
	}
	rt->light = tmp;
	in = in > 1.0 ? 1.0 : in;
	in = in < 0.0 ? 0.0 : in;
	return (do_color((SDL_Color){0, 0, 0, 0}, obj->color, in));
}
