#include "libmgl.h"

SDL_Rect picker_get_pos(t_picker *picker)
{
	SDL_Rect pos;

	pos = (SDL_Rect) { 0, 0, 0, 0 };
	if (picker == NULL)
		return (pos);
	pos = (SDL_Rect) { picker->pos.x,
						picker->pos.y,
						picker->hue.x + picker->hue.w - picker->pos.x,
						picker->pos.h };
	return (pos);
}

int picker_get_x(t_picker *picker)
{
	if (picker == NULL)
		return (-1);
	return (picker->pos.x);
}

int picker_get_y(t_picker *picker)
{
	if (picker == NULL)
		return (-1);
	return (picker->pos.y);
}

int picker_get_h(t_picker *picker)
{
	if (picker == NULL)
		return (-1);
	return (picker->pos.h);
}

int picker_get_w(t_picker *picker)
{
	if (picker == NULL)
		return (-1);
	return (picker->hue.x + picker->hue.w - picker->pos.x);
}
