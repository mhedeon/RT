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

t_vector reflect(t_vector *v1, t_vector *v2)
{
	t_vector tmp;

	tmp = multiply(2.0 * dot(v1, v2), v2);
	tmp = substruct(&tmp, v1);
	return (tmp);
}