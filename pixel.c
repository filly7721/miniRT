
#include "miniRT.h"

void	pixel_put(t_mlxdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	per_pixel(t_minirt *minirt, int x, int y)
{
	if (x > minirt->width / 4.0 && x < 3 * minirt->width / 4.0 \
		&& y > minirt->height / 4.0 && y < 3 * minirt->height / 4.0)
		return (0x0ffff000);
	return (0x00000fff);
}
bool	eq_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple	res;

	res = sub_tuples(t2, t1);
	if (res.x > 0.001 || res.y > 0.001 || res.z > 0.001)
		return (false);
	return (true);
}
