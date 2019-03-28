#include "libmgl.h"

int checkbox_within(t_checkbox *check, int x, int y)
{
	if ((x >= checkbox_get_pos_x(check) &&
		x < (checkbox_get_pos_x(check) + CHECKBOX_SIZE)) &&
		(y >= checkbox_get_pos_y(check) &&
		y < (checkbox_get_pos_y(check) + CHECKBOX_SIZE)))
		return (1);
	return (0);
}

int checkbox_is_on(t_checkbox *check)
{
	if (checkbox_get_status(check) == CHECK_ON)
		return (1);
	return (0);
}

int checkbox_is_off(t_checkbox *check)
{
	if (checkbox_get_status(check) == CHECK_OFF)
		return (1);
	return (0);
}

int checkbox_is_available(t_checkbox *check)
{
	if (checkbox_get_availalbe(check) == CHECK_AVAILABLE)
		return (1);
	return (0);
}

int checkbox_is_unavailable(t_checkbox *check)
{
	if (checkbox_get_availalbe(check) == CHECK_UNAVAILABLE)
		return (1);
	return (0);
}
