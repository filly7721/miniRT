#include "miniRT.h"

int	rgbtoint(t_tuple color)
{
	int		col;
	char	*i;

	i = (char *)&col;
	i[0] = (int)color.a * 255;
	i[1] = (int)color.r * 255;
	i[2] = (int)color.g * 255;
	i[3] = (int)color.b * 255;
	return (col);
}
