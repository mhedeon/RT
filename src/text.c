# include "rt.h"

/*
ttf_render_text(rt->win->ren, face->font, &(SDL_Rect) { 50, 50, 50, 25 }, "hello");
*/

void draw_rgb(t_rt *rt, t_face *face)
{
	char rgb[7];
	SDL_Color c;

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

void draw_hsv(t_rt *rt, t_face *face)
{
	char rgb[8];
	t_hsv h;

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
// "x: 999.999"


static char *get_str_from_double(double xyz, char *start)
{
	double i;
	char *tmp;
	char *s;
	int l;

	tmp = ft_itoa((int)xyz);
	l = ft_strlen(tmp);
	s = ft_strjoin(tmp, ".");
	free(tmp);
	tmp = s;
	s = ft_strjoin(tmp, ft_itoa(modf(xyz, &i) * 100));
	free(tmp);
	if (l < 7)
		while (++l <= 10)
		{
			tmp = s;
			s = ft_strjoin(" ", tmp);
			free(tmp);
		}
	tmp = s;
	s = ft_strjoin(start, tmp);
	free(tmp);
	return (s);
}

void draw_angles(t_rt *rt, t_face *face)
{
	char *s;

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

void draw_xyz(t_rt *rt, t_face *face)
{
	char *s;
	
	if (face->o_focus == NULL)
		return ;
	s = get_str_from_double(face->o_focus->center.x, "x: ");
	ttf_render_text(rt->win->ren, face->font, &(T_X), s);
	free(s);
	s = get_str_from_double(face->o_focus->center.y, "y: ");
	ttf_render_text(rt->win->ren, face->font, &(T_Y), s);
	free(s);
	s = get_str_from_double(face->o_focus->center.z, "z: ");
	ttf_render_text(rt->win->ren, face->font, &(T_Z), s);
	free(s);
}

void draw_o_list(t_rt *rt, t_face *face)
{
	t_object *tmp;
	static int i;
	SDL_Rect r = { 25, 250, 250, 50 };

	i = face->start;
	tmp = face->o_focus;
	while (tmp != NULL && (face->end - ++i) >= 0)
	{
		if (tmp->type == PLANE)
			ttf_render_text(rt->win->ren, face->font, &r, "PLANE");
		else if (tmp->type == SPHERE)
			ttf_render_text(rt->win->ren, face->font, &r, "SPHERE");
		else if (tmp->type == CONE)
			ttf_render_text(rt->win->ren, face->font, &r, "CONE");
		else
			ttf_render_text(rt->win->ren, face->font, &r, "CYLINDER");
		r.y += 60;
		tmp = tmp->next;
	}
}

void text_draw(t_rt *rt, t_face *face)
{
	draw_rgb(rt, face);
	draw_hsv(rt, face);
	draw_xyz(rt, face);
	draw_angles(rt, face);
	draw_o_list(rt, face);
}