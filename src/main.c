/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/28 19:50:14 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_pixel(t_rt *rt, SDL_Color color, int x, int y)
{
	x = SCENE_W / 2 + x;
	y = SCENE_H / 2 - y - 1;
	if (x >= 0 && x < SCENE_W && y >= 0 && y < SCENE_W)
		set_pixel(rt->win, &color, x, y);
}

int				rnd(void)
{
	static int	seed = 0;

	seed = seed == 0 ? SDL_GetTicks() : seed;
	seed = (Uint8)(1664525 * seed + 1013904223);
	return (seed);
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

static int		translate(t_rt *rt, SDL_Event e)
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

static int		rotate(t_rt *rt, SDL_Event e)
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

// int				main(int ac, char **av)
int main()
{
	t_rt		*rt;
	SDL_Event	e;

	// if (ac != 2)
	// {
	// 	write(1, "Usage: ./rt ./scene/<scene file>\n", 36);
	// 	return (0);
	// }
	if ((rt = (t_rt *)malloc(sizeof(t_rt))) == NULL)
		return (error_log("Could not allocate memory for rt"));
	if (!init(rt))
		return (garbage(rt));
	rt->angle_x = 0;
	rt->angle_y = 0;
	rt->camera = (t_vec) { 0.0, 0.5, -5.0 };
	// get_data(rt, av[ac - 1]);
	get_data(rt, "./scene/scene1");
	threads(rt);
	while (SDL_PollEvent(&e) || 1)
		if (e.type == SDL_QUIT || (KEY == SDLK_ESCAPE))
			break ;
		else if (rotate(rt, e) || translate(rt, e))
			threads(rt);
	garbage(rt);
	return (0);
}
