#include "rt.h"

static void event_picker_click(t_face *face, int *xy, int *cl, char hsv)
{
	SDL_Color c;

	c = hsv2rgb(face->picker->hsv.h, face->picker->hsv.s, face->picker->hsv.v);
	if (hsv == 'h')
		picker_set_h_by_pos(face->picker, xy[1]);
	else if (hsv == 'p')
		picker_set_sv_by_pos(face->picker, xy[0], xy[1]);
	if (face->o_focus->type >= 5 && face->o_focus->type <= 7)
		add_color_bocal(face->o_focus, c);
	else
		face->o_focus->color = c;
	*cl = 1;
}

static void event_picker(t_face *face, int *xy, int click)
{
	static int click_pal = 0;
	static int click_hue = 0;

	click_hue = click_hue & click;
	click_pal = click_pal & click;
	if (picker_within_hue(face->picker, xy[0], xy[1]) && !click_pal && click)
		event_picker_click(face, xy, &click_hue, 'h');
	else if (picker_within_pal(face->picker, xy[0], xy[1]) && !click_hue &&
																		click)
		event_picker_click(face, xy, &click_pal, 'p');
	if (click_hue)
		event_picker_click(face, xy, &click_hue, 'h');
	else if (click_pal)
		event_picker_click(face, xy, &click_pal, 'p');
}

static int within_area(int x, int y, SDL_Rect *r)
{
	if ((x >= r->x && x < (r->x + r->w)) &&
		(y >= r->y && y < (r->y + r->h)))
		return (1);
	return (0);
}

static void event_button(t_face *face, t_rt *rt, int *xy, int clicked)
{
	SDL_Rect r;

	r = T_RENDER;
	if (!clicked && within_area(xy[0], xy[1], &r))
		threads(rt);
	r = T_SHOT;
	if (!clicked && within_area(xy[0], xy[1], &r))
		screenshot(rt->win->ren, rt->win->tex, &face->rt->scene_r);

}


void event_mouse(t_rt *rt, t_face *face)
{
	int xy[2];
	int click;
	static int clicked = 0;

	if (SDL_GetMouseState(&xy[0], &xy[1]) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		click = 1;
		if (checkbox_within(face->sepia, xy[0], xy[1]) && !clicked)
		{
			checkbox_set_invert_status(face->sepia);
			face->rt->sepia = face->rt->sepia == 0 ? 1 : 0;
			clicked = 1;
		}
		event_button(face, rt, xy, clicked);
		printf("x: %d | y: %d\n", xy[0], xy[1]);
		clicked = 1;
	}
	else
	{
		click = 0;
		clicked = 0;
	}
	if (click)
	{
		face->o_focus = in_list(rt, face, xy[0], xy[1]);
		
	}
	event_picker(face, xy, click);
	
}