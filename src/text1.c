/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:52:02 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 06:33:40 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		draw_o_list(t_rt *rt, t_face *face)
{
	t_object	*tmp;
	SDL_Rect	r;

	r = LIST_O;
	tmp = face->o_start;
	while (tmp != NULL && face->end-- > 0)
	{
		if (tmp->type == PLANE)
			ttf_render_text(rt->win->ren, face->font, &r, "PLANE");
		else if (tmp->type == SPHERE)
			ttf_render_text(rt->win->ren, face->font, &r, "SPHERE");
		else if (tmp->type == CONE)
			ttf_render_text(rt->win->ren, face->font, &r, "CONE");
		else if (tmp->type == CYLINDER)
			ttf_render_text(rt->win->ren, face->font, &r, "CYLINDER");
		else if (tmp->type == BOCAL_PLANE)
			ttf_render_text(rt->win->ren, face->font, &r, "BOCAL PLANE");
		else if (tmp->type == BOCAL_CONE)
			ttf_render_text(rt->win->ren, face->font, &r, "BOCAL CONE");
		else if (tmp->type == BOCAL_CYLINDER)
			ttf_render_text(rt->win->ren, face->font, &r, "BOCAL CYLINDER");
		r.y += 60;
		tmp = tmp->next;
	}
}

static void		draw_cam_angles(t_rt *rt, t_face *face)
{
	char		*s;

	s = get_str_from_double(rt->angle_x, "0x\xB0: ");
	ttf_render_text(rt->win->ren, face->font, &(C_XA), s);
	free(s);
	s = get_str_from_double(rt->angle_y, "0y\xB0: ");
	ttf_render_text(rt->win->ren, face->font, &(C_YA), s);
	free(s);
	s = get_str_from_double(0.0, "0z\xB0: ");
	ttf_render_text(rt->win->ren, face->font, &(C_ZA), s);
	free(s);
}

static void		draw_cam_xyz(t_rt *rt, t_face *face)
{
	char		*s;
	t_vec		data;

	data = rt->camera;
	s = get_str_from_double(data.x, "x: ");
	ttf_render_text(rt->win->ren, face->font, &(C_X), s);
	free(s);
	s = get_str_from_double(data.y, "y: ");
	ttf_render_text(rt->win->ren, face->font, &(C_Y), s);
	free(s);
	s = get_str_from_double(data.z, "z: ");
	ttf_render_text(rt->win->ren, face->font, &(C_Z), s);
	free(s);
}

static void		draw_sr(t_rt *rt, t_face *face)
{
	char		*s;
	double		data;

	if (face->o_focus == NULL)
		return ;
	data = face->o_focus->specular;
	s = get_str_from_double(data, "Specular: ");
	ttf_render_text(rt->win->ren, face->font, &(T_SPEC), s);
	free(s);
	data = face->o_focus->reflective;
	s = get_str_from_double(data, "Reflective: ");
	ttf_render_text(rt->win->ren, face->font, &(T_REFL), s);
	free(s);
}

void			text_draw(t_rt *rt, t_face *face)
{
	draw_rgb(rt, face);
	draw_hsv(rt, face);
	ttf_render_text(rt->win->ren, face->font, &(T_OBJ), "Object:");
	ttf_render_text(rt->win->ren, face->font, &(T_CAM), "Camera:");
	ttf_render_text(rt->win->ren, face->font, &(T_SEPIA), "Sepia");
	ttf_render_text(rt->win->ren, face->font, &(T_RENDER), "Render");
	ttf_render_text(rt->win->ren, face->font, &(T_SHOT), "Screenshot");
	draw_xyz(rt, face);
	draw_xyz_angles(rt, face);
	draw_o_list(rt, face);
	draw_cam_xyz(rt, face);
	draw_cam_angles(rt, face);
	draw_sr(rt, face);
	face->end = 12;
}
