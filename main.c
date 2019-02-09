#include "test.h"



double* intersect_sphere(t_vector *camera, t_vector *dir, t_sphere *sphere, double *ts)
{
	t_vector oc = substruct(camera, &sphere->center);
	double k1 = dot(dir, dir);
	double k2 = 2.0 * dot(&oc, dir);
	double k3 = dot(&oc, &oc) - sphere->radius * sphere->radius;

	double dis = k2 * k2 - 4.0 * k1 * k3;
	if (dis < 0.0)
	{
		ts[0] = INFINITY;
		ts[1] = INFINITY;
		return (ts);
	}
	ts[0] = (-k2 + sqrt(dis)) / (2.0 * k1);
	ts[1] = (-k2 - sqrt(dis)) / (2.0 * k1);
	return (ts);

}


double *intersect_plane(t_vector *camera, t_vector *dir, t_sphere *sphere, double *ts)
{
	t_vector C = { 0.0, -0.5, 0.0 };
	t_vector N = { 0.0, 1.0, 0.0 };
	t_vector tmp = substruct(camera, &C);
	ts[0] = -dot(&tmp, &N);
	ts[1] = dot(dir, &N);
	if (ts[1] != 0.0)
	{
		ts[0] = ts[0] / ts[1];
		ts[1] = INFINITY;
		return (ts);
	}
	ts[0] = INFINITY;
	ts[1] = INFINITY;
	return (ts);
}
void close_inters(t_test *test, t_vector *origin, t_vector *dir, double min, double max)
{
	test->close = INFINITY;
	test->close_sph = NULL;
	double *ts = malloc(sizeof(double) * 2);

	for (int i = 0; i < 5; i++)
	{
		if (i == 3)
			intersect_plane(origin, dir, &test->sphere[i], ts);
		else
			intersect_sphere(origin, dir, &test->sphere[i], ts);
		if (ts[0] < test->close && min < ts[0] && ts[0] < max)
		{
			test->close = ts[0];
			test->close_sph = &test->sphere[i];
		}
		if (ts[1] < test->close && min < ts[1] && ts[1] < max)
		{
			test->close = ts[1];
			test->close_sph = &test->sphere[i];
		}
	}
	free(ts);
}

double lighting(t_test *test, t_vector *point, t_vector *normal, t_vector *view, int specular)
{
	double in = 0.0;
	double len = length(normal);
	double len_v = length(view);

	for (int i = 0; i < 3; i++)
	{
		if (test->light[i].type == AMBIENT)
			in += (test->light[i]).intens;
		else
		{
			t_vector vec_l;
			if (test->light[i].type == POINT)
				vec_l = substruct(&test->light[i].pos, point);
			else
				vec_l = test->light[i].pos;

			close_inters(test, point, &vec_l, 0.00001, INFINITY);
			if (test->close_sph != NULL)
				continue ;

			 // difuse
			double n_dot = dot(normal, &vec_l);
			if (n_dot > 0.0)
				in += test->light[i].intens * n_dot /
						(len * length(&vec_l));

			// specular
			if (specular != -1)
			{
				t_vector vec_r = multiply(2.0 * dot(normal, &vec_l), normal);
				vec_r = substruct(&vec_r, &vec_l);
				double r_dot = dot(&vec_r, view);
				if (r_dot > 0.0)
					in += test->light[i].intens * pow(r_dot / (length(&vec_r) * len_v), specular);
			}
		}
	}
	if (in > 1.0)
		in = 1.0;
	return (in);
}

SDL_Color trace(t_test *test, t_vector *origin, t_vector *dir, double min, double max, int depth)
{
	double close;
	t_sphere *close_sph;
	close_inters(test, origin, dir,  min, max);

	close = test->close;
	close_sph = test->close_sph;

	if (close_sph == NULL)
		return ((SDL_Color) { 0, 0, 0 });

	t_vector tmp = multiply(close, dir);
	t_vector point = add(origin, &tmp);
	t_vector normal;
	if (close_sph->radius == 5000.0)
	{
		normal.x = 0.0;
		normal.y = 1.0;
		normal.z = 0.0;
	}
	else
	{
		normal = substruct(&point, &close_sph->center);
		normal = multiply(1.0 / length(&normal), &normal);
	}

	t_vector view = multiply(-1.0, dir);
	close = lighting(test, &point, &normal, &view, close_sph->specular);
	SDL_Color local_color = { (Uint8)(close * close_sph->color.r),
								(Uint8)(close * close_sph->color.g),
								(Uint8)(close * close_sph->color.b) };

	if (close_sph->reflective <= 0.0 || depth <= 0)
		return (local_color);

	t_vector ray = reflect(&view, &normal);
	
	SDL_Color ref_c = trace(test, &point, &ray, 0.0001, max, depth - 1);
	return ((SDL_Color) { (Uint8)((1.0 - close_sph->reflective) * local_color.r + close_sph->reflective * ref_c.r),
							(Uint8)((1.0 - close_sph->reflective) * local_color.g + close_sph->reflective * ref_c.g),
							(Uint8)((1.0 - close_sph->reflective) * local_color.b + close_sph->reflective * ref_c.b) });
}

void put_pixel(t_test *test, int x, int y)
{
	x = SCREEN_WIDTH / 2 + x;
	y = SCREEN_HEIGHT / 2 - y - 1;
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		set_pixel(test, &test->color, x, y);
}

void go(t_test *test)
{
	for (int y = test->start; y < test->end; y++)
	{
		for (int x = -(SCREEN_WIDTH / 2); x < SCREEN_WIDTH / 2; x++)
		{

			t_vector direction = { (double)x * 1.0 / (double)SCREEN_WIDTH, (double)y * 1.0 / (double)SCREEN_HEIGHT, 1.0 };
			test->dir = direction;
			test->color = trace(test, &test->camera, &test->dir, 1.0, INFINITY, 3);
			put_pixel(test, x, y);
		}
	}
}

int main(int ac, char **av)
{
	t_test *test = (t_test *)malloc(sizeof(t_test));
	init(test);
	t_vector camera = { 0.0, 0.5, -1.5 };
	t_sphere sphere[5] = { { { 0.0, -0.5, 3.0 }, 1.0, { 255, 0, 0 }, 1000, 0.2 },
							{ { 2.0, 0.5, 4.0 }, 1.0, { 0, 0, 255 }, 500, 0.3 },
							{ { -2.0, 0.5, 4.0 }, 1.0, { 0, 255, 0}, 10, 0.4 },
							{ { 0.0, 0.0, 0.0}, 5000.0, {255, 255, 0}, 100, 0.2 },
							{ { 0.0, 1.5, 3.5}, 0.8, { 123, 123, 123}, 150, 0.3} };
	t_light light[3] = { { AMBIENT, 0.1, { 0.0, 0.0, 0.0 } },
						{ POINT, 0.8, {2.0, 2.0, 0.0 } },
						{ DIRECTIONAL, 0.0, { 1.0, 4.0, 4.0 } } };

	test->sphere[0] = sphere[0];
	test->sphere[1] = sphere[1];
	test->sphere[2] = sphere[2];
	test->sphere[3] = sphere[3];
	test->sphere[4] = sphere[4];
	test->light[0] = light[0];
	test->light[1] = light[1];
	test->light[2] = light[2];
	test->camera = camera;

	for (int y = -(SCREEN_HEIGHT / 2); y < SCREEN_HEIGHT / 2; y++)
	{
		for (int x = -(SCREEN_WIDTH / 2); x < SCREEN_WIDTH / 2; x++)
		{
			
			t_vector direction = { (double)x * 1.0 / (double)SCREEN_WIDTH, (double)y * 1.0 / (double)SCREEN_HEIGHT, 1.0 };
			test->dir = direction;
			test->color = trace(test, &test->camera, &test->dir, 1.0, INFINITY, 3);
			put_pixel(test, x, y);
		}
	}
	screen_upd(test);
	SDL_Event e;
	while (1)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT ||
				(KEY == SDLK_ESCAPE))
				break;
			if (KEY == SDLK_LEFT)
			{
				test->camera.x -= 0.25;
				printf("go left\n");
			}
			if (KEY == SDLK_RIGHT)
			{
				test->camera.x += 0.25;
				printf("go right\n");
			}
			if (KEY == SDLK_UP)
			{
				test->camera.y += 0.25;
				printf("go up\n");
			}
			if (KEY == SDLK_DOWN)
			{
				test->camera.y -= 0.25;
				printf("go down\n");
			}
			if (e.type == SDL_KEYDOWN)
			{
				SDL_Thread *thread[THREADS];
				t_test ttt[THREADS];

				for (int i = 0; i < THREADS; i++)
				{
					ttt[i] = *test;
					ttt[i].start = i * SCREEN_HEIGHT / THREADS - SCREEN_HEIGHT / 2;
					ttt[i].end = (i + 1) * SCREEN_HEIGHT / THREADS - SCREEN_HEIGHT / 2;
					thread[i] = SDL_CreateThread(go, "go", (void(__cdecl *)(t_test *))&ttt[i]);
					printf("[%d] start: %d | end: %d\n", i, ttt[i].start, ttt[i].end);
				}
				for (int i = 0; i < THREADS; i++)
					SDL_WaitThread(thread[i], NULL);
				screen_upd(test);
				printf("DONE\n");
			}
		}
	}

	garbage(test);
	return (0);
}
