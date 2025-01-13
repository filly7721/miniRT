#include "miniRT.h"

bool eq(double f1, double f2)
{
	if (f1 - f2 < __DBL_EPSILON__ && f1 - f2 > 0)
		return (true);
	return (false);
}

t_tuple	set_point(double x, double y, double z)
{
	return (set_tuple(x, y, z, 1));
}

t_tuple	set_vector(double x, double y, double z)
{
	return (set_tuple(x, y, z, 0));
}