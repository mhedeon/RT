/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:42:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/30 22:01:28 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_pixel(t_rt *rt, SDL_Color color, int x, int y)
{
	x = SCENE_W / 2 + x;
	y = SCENE_H / 2 - y - 1;
	
	SDL_Color c;

	c.r = fmin(color.r * 0.393 + color.g * 0.769 + color.b * 0.189, 255);
	c.g = fmin(color.r * 0.349 + color.g * 0.686 + color.b * 0.168, 255);
	c.b = fmin(color.r * 0.272 + color.g * 0.534 + color.b * 0.131, 256);

	if (x >= 0 && x < SCENE_W && y >= 0 && y < SCENE_W)
		set_pixel(rt->win, &c, x + rt->scene_r.x, y + rt->scene_r.y );
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
	t_face		*face;
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

	// get_data(rt, av[ac - 1]);
	get_data(rt, "./scene/scene1");

	if ((face = (t_face*)malloc(sizeof(t_face))) == NULL)
		return (error_log("Could not allocate memory for interface"));
	if (!init_face(face, rt))
		face_close(face, rt);

add_bocal(rt->obj, (t_vec) {-25.0, -1.0, 0.0}, 10.0);

	threads(rt);

	int click_pal = 0, click_hue = 0;
	while (SDL_PollEvent(&e) || 1)
	{
		
		if (e.type == SDL_QUIT || (KEY == SDLK_ESCAPE))
			break ;
		else if (rotate(rt, e) || translate(rt, e))
			threads(rt);


		int x, y;
		if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			printf("x: %d | y: %d\n", x, y);
			if (picker_within_hue(face->picker, x, y) && !click_pal)
			{
				picker_set_h_by_pos(face->picker, y);
				if (face->o_focus != NULL)
				face->o_focus->color = hsv2rgb(face->picker->hsv.h,
									face->picker->hsv.s, face->picker->hsv.v);
				click_hue = 1;
			}
			else if (picker_within_pal(face->picker, x, y) && !click_hue)
			{
				picker_set_sv_by_pos(face->picker, x, y);
				if (face->o_focus != NULL)
				face->o_focus->color = hsv2rgb(face->picker->hsv.h,
									face->picker->hsv.s, face->picker->hsv.v);
				click_pal = 1;
			}
			if (click_hue == 1)
			{
				picker_set_h_by_pos(face->picker, y);
				if (face->o_focus != NULL)
				face->o_focus->color = hsv2rgb(face->picker->hsv.h,
									face->picker->hsv.s, face->picker->hsv.v);
			}
			else if (click_pal == 1)
			{
				picker_set_sv_by_pos(face->picker, x, y);
				if (face->o_focus != NULL)
				face->o_focus->color = hsv2rgb(face->picker->hsv.h,
									face->picker->hsv.s, face->picker->hsv.v);
			}
			
			
			threads(rt);

			face->o_focus = in_list(rt, face, x, y);
		}
		else
		{
			click_hue = 0;
			click_pal = 0;
		}
		
		
		interface_draw(face, rt);
		SDL_UpdateTexture(rt->win->tex, NULL, rt->win->buff,
							rt->win->w * sizeof(Uint32));
							
		// SDL_RenderClear(rt->win->ren);
		SDL_RenderCopy(rt->win->ren, rt->win->tex, NULL, NULL);
	text_draw(rt, face);
		SDL_RenderPresent(rt->win->ren);
		// upd_win(rt->win);
	}
	ttf_close_font(face->font);
	garbage(rt);
	return (0);
}
