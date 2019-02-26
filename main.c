/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/02/26 22:35:59 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

SDL_Color do_color(SDL_Color local, SDL_Color reflected, double reflective)
{
	SDL_Color result;

	result.r = (Uint8)((1.0 - reflective) * local.r + reflective * reflected.r);
	result.g = (Uint8)((1.0 - reflective) * local.g + reflective * reflected.g);
	result.b = (Uint8)((1.0 - reflective) * local.b + reflective * reflected.b);
	result.a = 0;
	return (result);
}



int main(int ac, char **av)
{
	t_rtv *rtv;
	
	if (ac != 2)
	{
		write(1, "Usage: ./RTv1 ./scene/<scene file>\n", 36);
		return (0);
	}
	rtv = (t_rtv *)malloc(sizeof(t_rtv));
	if (rtv == NULL)
		return (error_log("Could not allocate memory for rtv"));
	if (!init(rtv))
		return (0);
error_log("Could not allocate memory for object->data");
	rtv->angle_x = 0;
	rtv->angle_y = 0;
	rtv->camera = (t_vec) { 0.0, 0.5, -5.0 };
	get_data(rtv, av[ac - 1]);

	threads(rtv);
	screen_upd(rtv);
	SDL_Event e;
	while (SDL_PollEvent(&e) || 1)
	{
		if (e.type == SDL_QUIT || (KEY == SDLK_ESCAPE))
			break;
		else if (KEY == SDLK_LEFT)
			rtv->camera = add(rtv->camera, multiply(0.25,
							direction(0, 0, 0, rtv->angle_y - 90)));
		else if (KEY == SDLK_RIGHT)
			rtv->camera = add(rtv->camera, multiply(0.25,
							direction(0, 0, 0, rtv->angle_y + 90)));
		else if (KEY == SDLK_UP)
			rtv->camera = add(rtv->camera, multiply(0.25,
							direction(0, 0, rtv->angle_x, rtv->angle_y)));
		else if (KEY == SDLK_DOWN)
			rtv->camera = add(rtv->camera, multiply(-0.25,
							direction(0, 0, rtv->angle_x, rtv->angle_y)));
		else if (KEY == SDLK_w)
			rtv->angle_x -= 5;
		else if (KEY == SDLK_s)
			rtv->angle_x += 5;
		else if (KEY == SDLK_a)
			rtv->angle_y -= 5;
		else if (KEY == SDLK_d)
			rtv->angle_y += 5;
		else
			continue ;
		threads(rtv);
	}

	garbage(rtv);
	system("leaks rtv");
	return (0);
}

int rnd()
{
	static int seed = 0;

	seed = seed == 0 ? SDL_GetTicks() : seed;
	seed = (Uint8)(1664525 * seed + 1013904223);
	return (seed);
}
