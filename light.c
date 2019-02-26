/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 18:59:28 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 19:15:52 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light *add_ambient(t_light *l)
{
	t_light *start;
	t_light *new;

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

t_light *add_point(t_light *l)
{
	t_light *start;
	t_light *new;

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

int check_light(t_light *tmp, char *line)
{
	if (!ft_strncmp(line + 1, "position:", 9))
		tmp->pos = read_vec(line);
	else if (!ft_strncmp(line + 1, "intensivity:", 12))
		tmp->intens = read_number(line);
	else
		return (0);
	return (1);
}

void start_light(t_rtv *rtv, int *fd)
{
	char *line;
	t_light *tmp;

	tmp = rtv->light;
	if (tmp == NULL)
		printf("fdgh\n");
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	while (get_next_line(*fd, &line))
	{
		printf("|%s|\n", line);
		if (!check_light(tmp, line))
			if (!ft_strcmp(line, "#"))
			{
				free(line);
				return ;
			}
		free(line);
	}
}
