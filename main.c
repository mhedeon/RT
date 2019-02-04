#include "test.h"

double dot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector substruct(t_vector *v1, t_vector *v2)
{
	t_vector oc;

	oc.x = v1->x - v2->x;
	oc.y = v1->y - v2->y;
	oc.z = v1->z - v2->z;
	return (oc);
}

double length(t_vector *v1)
{
	return (sqrt(dot(v1, v1)));
}

t_vector multiply(double k, t_vector *v1)
{
	t_vector tmp;

	tmp.x = v1->x * k;
	tmp.y = v1->y * k;
	tmp.z = v1->z * k;
	return (tmp);
}

t_vector add(t_vector *v1, t_vector *v2)
{
	t_vector tmp;

	tmp.x = v1->x + v2->x;
	tmp.y = v1->y + v2->y;
	tmp.z = v1->z + v2->z;
	return (tmp);
}

double* intersect(t_vector *camera, t_vector *dir, t_sphere *sphere, double *ts)
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

double lighting(t_vector *point, t_vector *normal, t_light *light)
{
	double in = 0.0;
	double len = length(normal);

	for (int i = 0; i < 3; i++)
	{
		if ((light[i]).type == AMBIENT)
			in += (light[i]).intens;
		else
		{
			t_vector vec;
			if ((light[i]).type == POINT)
				vec = substruct(&(light[i]).pos, point);
			else
				vec = (light[i]).pos;
			double n_dot = dot(normal, &vec);
			if (n_dot > 0.0)
				in += (light[i]).intens * n_dot /
						(len * length(&vec));
		}
	}
	return (in);
}

SDL_Color trace(t_vector *camera, t_vector *dir, double min, double max, t_sphere *sphere, t_light *light)
{
	double close = INFINITY;
	t_sphere *closest_sph = NULL;
	double *ts = malloc(sizeof(double) * 2);

	for (int i = 3; i >= 0; i--)
	{
		intersect(camera, dir, &sphere[i], ts);
		if (ts[0] < close && min < ts[0] && ts[0] < max)
		{
			close = ts[0];
			closest_sph = &sphere[i];
		}
		if (ts[1] < close && min < ts[1] && ts[1] < max)
		{
			close = ts[1];
			closest_sph = &sphere[i];
		}
	}
	free(ts);
	if (closest_sph == NULL)
		return ((SDL_Color) { 255, 255, 255 });
	t_vector tmp = multiply(close, dir);
	t_vector point = add(camera, &tmp);
	t_vector normal = substruct(&point, &closest_sph->center);
	normal = multiply(1.0 / length(&normal), &normal);

	close = lighting(&point, &normal, light);
	return ((SDL_Color) {
		(int)(close * closest_sph->color.r), (int)(close * closest_sph->color.g),
			(int)(close * closest_sph->color.b) });
}

void put_pixel(t_test *test, int x, int y)
{
	x = SCREEN_WIDTH / 2 + x;
	y = SCREEN_HEIGHT / 2 - y - 1;
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		set_pixel(test, &test->color, x, y);
}

int main(int ac, char **av)
{
	t_test *test = (t_test *)malloc(sizeof(t_test));
	init(test);
	t_vector camera = { 0.0, 0.0, 0.0 };
	t_sphere sphere[4] = { { { 0.0, -1.0, 3.0 }, 1.0, { 255, 0, 0 } },
							{ { 2.0, 0.0, 4.0 }, 1.0, { 0, 0, 255 } },
							{ { -2.0, 0.0, 4.0 }, 1.0, { 0, 255, 0} },
							{ { 0.0, -5001, 0.0}, 5000.0, {255, 255, 0} } };
	t_light light[3] = { { AMBIENT, 0.2, { 0.0, 0.0, 0.0 } },
						{ POINT, 0.8, {2.0, 1.0, 0.0 } },
						{ DIRECTIONAL, 0.2, { 1.0, 4.0, 4.0 } } };

	for (int y = -(SCREEN_HEIGHT / 2); y < SCREEN_HEIGHT / 2; y++)
	{
		for (int x = -(SCREEN_WIDTH / 2); x < SCREEN_WIDTH / 2; x++)
		{
			// t_vector direction = { (double)x * 1.0 / (double)SCREEN_WIDTH, (double)y / 1.0 / (double)SCREEN_HEIGHT, 1.0 };
			t_vector direction = { (double)x * 1.0 / (double)SCREEN_WIDTH, (double)y * 1.0 / (double)SCREEN_HEIGHT, 1.0 };
			test->color = trace(&camera, &direction, 1, INFINITY, sphere, light);
			put_pixel(test, x, y);
		}
		//screen_upd(test);
	}
	screen_upd(test);
	SDL_Event e;
	while (1)
	{
		if (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT ||
				(KEY == SDLK_ESCAPE))
				break ;
	}

	garbage(test);
	return (0);
}
