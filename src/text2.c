/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 06:07:21 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 06:19:26 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			draw_rgb(t_rt *rt, t_face *face)
{
	char		rgb[7];
	SDL_Color	c;

	c = hsv2rgb(face->picker->hsv.h, face->picker->hsv.s, face->picker->hsv.v);
	ft_strcpy(rgb, "R: 000");
	rgb[5] = c.r % 10 + '0';
	rgb[4] = c.r / 10 % 10 + '0';
	rgb[3] = c.r / 100 + '0';
	ttf_render_text(rt->win->ren, face->font, &(T_R), rgb);
	ft_strcpy(rgb, "G: 000");
	rgb[5] = c.g % 10 + '0';
	rgb[4] = c.g / 10 % 10 + '0';
	rgb[3] = c.g / 100 + '0';
	ttf_render_text(rt->win->ren, face->font, &(T_G), rgb);
	ft_strcpy(rgb, "B: 000");
	rgb[5] = c.b % 10 + '0';
	rgb[4] = c.b / 10 % 10 + '0';
	rgb[3] = c.b / 100 + '0';
	ttf_render_text(rt->win->ren, face->font, &(T_B), rgb);
}

void			draw_hsv(t_rt *rt, t_face *face)
{
	char		rgb[8];
	t_hsv		h;

	h = face->picker->hsv;
	ft_strcpy(rgb, "H: 000");
	rgb[5] = (int)h.h % 10 + '0';
	rgb[4] = (int)h.h / 10 % 10 + '0';
	rgb[3] = (int)h.h / 100 + '0';
	ttf_render_text(rt->win->ren, face->font, &(T_H), rgb);
	ft_strcpy(rgb, "S: 0.00");
	rgb[6] = (int)(h.s * 100) % 10 + '0';
	rgb[5] = (int)(h.s * 100) / 10 % 10 + '0';
	rgb[3] = (int)h.s + '0';
	ttf_render_text(rt->win->ren, face->font, &(T_S), rgb);
	ft_strcpy(rgb, "V: 0.00");
	rgb[6] = (int)(h.v * 100) % 10 + '0';
	rgb[5] = (int)(h.v * 100) / 10 % 10 + '0';
	rgb[3] = (int)h.v + '0';
	ttf_render_text(rt->win->ren, face->font, &(T_V), rgb);
}

void			draw_xyz_angles(t_rt *rt, t_face *face)
{
	char		*s;

	if (face->o_focus == NULL)
		return ;
	s = get_str_from_double(face->o_focus->rot.x, "0x\xB0: ");
	ttf_render_text(rt->win->ren, face->font, &(T_XA), s);
	free(s);
	s = get_str_from_double(face->o_focus->rot.y, "0y\xB0: ");
	ttf_render_text(rt->win->ren, face->font, &(T_YA), s);
	free(s);
	s = get_str_from_double(face->o_focus->rot.z, "0z\xB0: ");
	ttf_render_text(rt->win->ren, face->font, &(T_ZA), s);
	free(s);
}

void			draw_xyz(t_rt *rt, t_face *face)
{
	char		*s;
	t_vec		data;

	if (face->o_focus == NULL)
		return ;
	if (face->o_focus->type >= 5 && face->o_focus->type <= 7)
		data = get_bocal_center(face->o_focus);
	else
		data = face->o_focus->center;
	s = get_str_from_double(data.x, "x: ");
	ttf_render_text(rt->win->ren, face->font, &(T_X), s);
	free(s);
	s = get_str_from_double(data.y, "y: ");
	ttf_render_text(rt->win->ren, face->font, &(T_Y), s);
	free(s);
	s = get_str_from_double(data.z, "z: ");
	ttf_render_text(rt->win->ren, face->font, &(T_Z), s);
	free(s);
}
