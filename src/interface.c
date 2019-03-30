#include "rt.h"

t_object *in_list(t_rt *rt, t_face *face, int x, int y)
{
	int i;
	SDL_Rect r;
	t_object *tmp;

	r = T_LIST;
	i = face->start;
	while (i++ < face->end)
	{
		if (x >= r.x && x < (r.x + r.w) &&
			y >= (r.y + 60 * (i - 1)) && y < (r.y + r.h + 60 * (i - 1)))
			{
				tmp = rt->obj;
				while (tmp != NULL && --i > 0)
					tmp = tmp->next;
				face->o_focus = tmp;
				return (tmp);
			}
	}
	return (face->o_focus);
}

int			init_face(t_face *face, t_rt *rt)
{
	face->top_r = (SDL_Rect) { 0, 0, WIN_W, WIN_H - SCENE_H };
	face->left_r = (SDL_Rect) { 0, WIN_H - SCENE_H, (WIN_W - SCENE_W) / 2,
																	SCENE_H };
	face->right_r = (SDL_Rect) { SCENE_W + face->left_r.w, WIN_H - SCENE_H,
											(WIN_W - SCENE_W) / 2, SCENE_H };
	face->rt = rt;
	face->start = 0;
	face->end = 12;
	face->o_start = rt->obj;
	face->o_focus = face->o_start;
	face->font = NULL;
	face->picker = NULL;
	face->sepia = NULL;
	if ((face->picker = picker_create(200)) == NULL)
		return (error_log("Interface initiation failed"));
	if ((face->font = ttf_open_font("./libraries/libmgl/ttf/OSR.ttf", 150)) ==
																		NULL)
		return (error_log("Interface initiation failed"));
	if ((face->sepia = checkbox_create(CHECK_OFF, CHECK_AVAILABLE, 1140,
			620)) == NULL)
		return (error_log("Interface initiation failed"));
	face->rt->sepia = 0;
	return (1);
}

int face_close(t_face *face, t_rt *rt)
{
	garbage(rt);
	if (face->picker != NULL)
		picker_delete(&face->picker);
	if (face->font != NULL)
		ttf_close_font(face->font);
	if (face->sepia != NULL)
		checkbox_delete(&face->sepia);
	free(face);
	return (0);
}

static void interface_draw_bg(t_face *face, t_rt *rt)
{
	rt->win->color = hsv_to_rgb(&(t_hsv) { 0, 0 ,0.15 });
	color_area(rt->win, &face->top_r, &rt->win->color);
	rt->win->color = hsv_to_rgb(&(t_hsv) { 0, 0 ,0.20 });
	color_area(rt->win, &face->left_r, &rt->win->color);	
	color_area(rt->win, &face->right_r, &rt->win->color);		
	rt->win->color = hsv_to_rgb(&(t_hsv) { 0, 0 ,0.35 });
	color_area(rt->win, &(SDL_Rect) { rt->scene_r.x - 1, rt->scene_r.y, 2,
													SCENE_H }, &rt->win->color);
	color_area(rt->win, &(SDL_Rect) { 0, rt->scene_r.y - 1,
												WIN_W, 2 }, &rt->win->color);
	color_area(rt->win, &(SDL_Rect) { face->right_r.x - 1, face->right_r.y, 2,
													SCENE_H }, &rt->win->color);
	color_area(rt->win, &(T_RENDER), &rt->win->color);
	color_area(rt->win, &(T_SHOT), &rt->win->color);
}

void interface_set_obj(t_face *face, t_rt *rt)
{
	rt->start = rt->start;
	picker_set_pos(face->picker, face->right_r.x + 40, face->right_r.y + 40);
}

void interface_draw(t_face *face, t_rt *rt)
{
	int i;
	SDL_Rect r;

	interface_draw_bg(face, rt);
	interface_set_obj(face, rt);
	picker_draw(rt->win, face->picker);
	draw_checkbox(rt->win, face->sepia);
	i = face->start;
	r = T_LIST;
	while ((face->end - i++) > 0)
	{
		color_area(rt->win, &r, &(SDL_Color) {128, 128, 128, 0});
		r.y += 60;
	}
}