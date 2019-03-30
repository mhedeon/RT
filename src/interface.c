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
				while (--i > 0)
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
	face->left_r = (SDL_Rect) { 0, WIN_H - SCENE_H, (WIN_W - SCENE_W) / 2, SCENE_H };
	face->right_r = (SDL_Rect) { SCENE_W + face->left_r.w, WIN_H - SCENE_H, (WIN_W - SCENE_W) / 2, SCENE_H };
	face->rt = rt;
	face->start = 0;
	face->end = 12;
	if ((face->picker = picker_create(200)) == NULL)
		return (error_log("Interface initiation failed"));
	// picker_set_pos(face->picker, face->right_r.x + 50, face->right_r.y + 50);

	return (1);
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
	i = face->start;
	r = T_LIST;
	while ((face->end - i++) > 0)
	{
		color_area(rt->win, &r, &(SDL_Color) {128, 128, 128, 0});
		r.y += 60;
	}
}