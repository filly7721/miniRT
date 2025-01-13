#include "miniRT.h"

t_tuple	set_tuple(double x, double y, double z, double w)
{
	t_tuple t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = w;
	return (t);
}

t_tuple add_tuples(t_tuple t1, t_tuple t2)
{
	return (set_tuple(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w));
}

t_tuple sub_tuples(t_tuple t1, t_tuple t2)
{
	return (set_tuple(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w));
}

t_tuple mul_tuple(t_tuple t, double scalar)
{
	return (set_tuple(t.x * scalar, t.y * scalar, t.z * scalar, t.w * scalar));
}

t_tuple negate_tuple(t_tuple t)
{
	return (set_tuple(-t.x, -t.y, -t.z, -t.w));
}

double	dot_tuple(t_tuple t1, t_tuple t2)
{
	return (t1.x * t2.x + t1.y * t2.y + t1.z * t2.z + t1.w * t2.w);
}

t_tuple	cross_tuple(t_tuple t1, t_tuple t2)
{
	return set_tuple(
		t1.y * t2.z - t1.z * t2.y,
		t1.z * t2.x - t1.x * t2.z,
		t1.x * t2.y - t1.y * t2.x,
		0);
}

double	mag_tuple(t_tuple t)
{
	return (sqrt(dot_tuple(t, t)));
}

t_tuple normalize_tuple(t_tuple t)
{
	return mul_tuple(t, 1 / mag_tuple(t));
}