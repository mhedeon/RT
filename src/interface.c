#include "rt.h"

int			init_face(t_face *face, t_rt *rt)
{
	face->top_r = (SDL_Rect) { 0, 0, WIN_W, WIN_H - SCENE_H };
	face->left_r = (SDL_Rect) { 0, WIN_H - SCENE_H, (WIN_W - SCENE_W) / 2, SCENE_H };
	face->right_r = (SDL_Rect) { SCENE_W + face->left_r.w, WIN_H - SCENE_H, (WIN_W - SCENE_W) / 2, SCENE_H };
	face->rt = rt;
	face->start = 0;
	face->end = 5;
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
	interface_draw_bg(face, rt);
	interface_set_obj(face, rt);
	picker_draw(rt->win, face->picker);
	color_area(rt->win, &(SDL_Rect){ 25, 250, 250, 50 }, &(SDL_Color) {128, 128, 128, 0});
	color_area(rt->win, &(SDL_Rect){ 25, 310, 250, 50 }, &(SDL_Color) {128, 128, 128, 0});
	color_area(rt->win, &(SDL_Rect){ 25, 370, 250, 50 }, &(SDL_Color) {128, 128, 128, 0});
	color_area(rt->win, &(SDL_Rect){ 25, 430, 250, 50 }, &(SDL_Color) {128, 128, 128, 0});
	color_area(rt->win, &(SDL_Rect){ 25, 490, 250, 50 }, &(SDL_Color) {128, 128, 128, 0});
}