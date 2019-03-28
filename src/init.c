/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:16:25 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/28 22:31:12 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				init(t_rt *rt)
{
	rt->obj = NULL;
	rt->light = NULL;
	rt->close_o = NULL;
	if ((rt->win = create_win("RT", WIN_W, WIN_H)) == NULL)
		return (error_log("Initiation failed"));

	rt->scene_r = (SDL_Rect) { (WIN_W - SCENE_W) / 2, WIN_H - SCENE_H, SCENE_W, SCENE_H };
	clear_buffer(rt->win);
	return (1);
}

int			init_face(t_face *face)
{
	
	
	face->top_r = (SDL_Rect) { 0, 0, WIN_W, WIN_H - SCENE_H };
	face->left_r = (SDL_Rect) { 0, WIN_H - SCENE_H, (WIN_W - SCENE_W) / 2, SCENE_H };
	face->right_r = (SDL_Rect) { SCENE_W + face->left_r.w, WIN_H - SCENE_H, (WIN_W - SCENE_W) / 2, SCENE_H };

	face->picker = picker_create(200);
	picker_set_pos(face->picker, face->right_r.x + 50, face->right_r.y + 50);

	return (1);
}

int				garbage(t_rt *rt)
{
	t_object	*o_tmp;
	t_light		*l_tmp;

	while (rt->obj != NULL)
	{
		o_tmp = rt->obj;
		rt->obj = rt->obj->next;
		free(o_tmp->data);
		free(o_tmp);
	}
	while (rt->light != NULL)
	{
		l_tmp = rt->light;
		rt->light = rt->light->next;
		free(l_tmp);
	}
	close_win(&rt->win);
	free(rt);
	SDL_Quit();
	return (0);
}

int				matrix_height(char **m)
{
	int	i;

	i = 0;
	while (m[i])
		i++;
	return (i);
}

void			matrix_del(char **m)
{
	int	i;

	i = -1;
	while (m[++i])
		free(m[i]);
	free(m[i]);
	free(m);
}
