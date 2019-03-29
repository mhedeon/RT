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

void text_draw(t_rt *rt, t_face *face)
{
	draw_rgb(rt, face);
	draw_hsv(rt, face);
}