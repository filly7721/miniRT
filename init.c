#include "miniRT.h"

t_minirt	*init()
{
	t_minirt	*minirt;

	minirt = ft_calloc(sizeof(t_minirt), 1);
	if (!minirt)
		return (NULL);
	minirt->mlx = mlx_init();
	if (!minirt->mlx)
		return (deinit(minirt), NULL);
	minirt->window = mlx_new_window(minirt->mlx, 1920, 1080, "example");
	if (!minirt->window)
		return (deinit(minirt), NULL);
	minirt->data.img = mlx_new_image(minirt->mlx, 1920, 1080);
	if (!minirt->data.img)
		return (deinit(minirt), NULL);
	minirt->data.addr = mlx_get_data_addr(minirt->data.img, &minirt->data.bits_per_pixel, &minirt->data.line_length, &minirt->data.endian);
	if (!minirt->data.addr)
		return (deinit(minirt), NULL);
	return (minirt);
}

void	deinit(t_minirt *minirt)
{
	if (minirt->data.img)
		mlx_destroy_image(minirt->mlx, minirt->data.img);
	if (minirt->window)
		mlx_destroy_window(minirt->mlx, minirt->window);
	free(minirt->mlx);
	free(minirt);
}
