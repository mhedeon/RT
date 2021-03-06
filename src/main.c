/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 19:19:25 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			put_pixel(t_rt *rt, SDL_Color color, int x, int y)
{
	SDL_Color	c;

	x = SCENE_W / 2 + x;
	y = SCENE_H / 2 - y - 1;
	c = color;
	if (rt->sepia)
	{
		c.r = fmin(color.r * 0.393 + color.g * 0.769 + color.b * 0.189, 255);
		c.g = fmin(color.r * 0.349 + color.g * 0.686 + color.b * 0.168, 255);
		c.b = fmin(color.r * 0.272 + color.g * 0.534 + color.b * 0.131, 256);
	}
	if (x >= 0 && x < SCENE_W && y >= 0 && y < SCENE_W)
		set_pixel(rt->win, &c, x + rt->scene_r.x, y + rt->scene_r.y);
}

SDL_Color		do_color(SDL_Color local, SDL_Color reflected, double reflect)
{
	SDL_Color	result;

	result.r = (Uint8)((1.0 - reflect) * local.r + reflect * reflected.r);
	result.g = (Uint8)((1.0 - reflect) * local.g + reflect * reflected.g);
	result.b = (Uint8)((1.0 - reflect) * local.b + reflect * reflected.b);
	result.a = 0;
	return (result);
}

int				translate(t_rt *rt, SDL_Event e)
{
	if (KEY == SDLK_LEFT)
		rt->camera = add(rt->camera, multiply(0.25,
						direction(0, 0, 0, rt->angle_y - 90)));
	else if (KEY == SDLK_RIGHT)
		rt->camera = add(rt->camera, multiply(0.25,
						direction(0, 0, 0, rt->angle_y + 90)));
	else if (KEY == SDLK_UP)
		rt->camera = add(rt->camera, multiply(0.25,
						direction(0, 0, rt->angle_x, rt->angle_y)));
	else if (KEY == SDLK_DOWN)
		rt->camera = add(rt->camera, multiply(-0.25,
						direction(0, 0, rt->angle_x, rt->angle_y)));
	else
		return (0);
	return (1);
}

int				rotate(t_rt *rt, SDL_Event e)
{
	if (KEY == SDLK_w)
		rt->angle_x -= 5;
	else if (KEY == SDLK_s)
		rt->angle_x += 5;
	else if (KEY == SDLK_a)
		rt->angle_y -= 5;
	else if (KEY == SDLK_d)
		rt->angle_y += 5;
	else
		return (0);
	return (1);
}

int				main(int ac, char **av)
{
	t_rt		*rt;
	t_face		*face;

	if (ac != 2)
	{
		write(1, "Usage: ./rt ./scene/<scene file>\n", 36);
		return (0);
	}
	if ((rt = (t_rt *)malloc(sizeof(t_rt))) == NULL)
		return (error_log("Could not allocate memory for rt"));
	if (!init(rt))
		return (garbage(rt));
	get_data(rt, av[ac - 1]);
	if ((face = (t_face*)malloc(sizeof(t_face))) == NULL)
		return (error_log("Could not allocate memory for interface"));
	if (!init_face(face, rt))
		face_close(face, rt);
	threads(rt);
	while (event(rt, face))
		;
	face_close(face, rt);
	return (0);
}
