/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 06:17:37 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 06:26:50 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		obj_help(t_object *obj)
{
	obj->center = (t_vec) { 0.0, 0.0, 0.0 };
	if (obj->type == CYLINDER)
		obj->normal = (t_vec) { 0.0, -1.0, 0.0 };
	else
		obj->normal = (t_vec) { 0.0, 1.0, 0.0 };
	obj->rot = (t_vec) { 0, 0, 0 };
	obj->color = (SDL_Color) { rnd(), rnd(), rnd(), 0 };
	obj->specular = 5.0;
	obj->reflective = 0.0;
}

double		ft_vangle(t_vec a, t_vec b)
{
	return (dot(a, b) / (length(a) * length(b)));
}

static char	*str_help(char *s, char *str)
{
	char	*tmp;

	tmp = s;
	s = ft_strjoin(tmp, str);
	free(tmp);
	return (s);
}

char		*get_str_from_double(double xyz, char *start)
{
	double	i;
	char	*str;
	char	*s;
	int		l;

	s = ft_itoa((int)xyz);
	s = str_help(s, ".");
	l = ft_strlen(s) - 1;
	str = ft_itoa(abs((int)(modf(xyz, &i) * 100)));
	s = str_help(s, str);
	free(str);
	if (l < 7)
		while (++l <= 10)
			s = str_help(s, " ");
	str = s;
	s = ft_strjoin(start, str);
	free(str);
	return (s);
}
