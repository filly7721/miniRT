#include "miniRT.h"

void	pixel_put(t_mlxdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main()
{
	t_minirt	*minirt;

	minirt = init();
	if (!minirt)
		return (ft_putstr_fd("init error\n", 2), 1);
	
	pixel_put(&minirt->data, 10,10,0x0000ff00);
	mlx_put_image_to_window(minirt->mlx, minirt->window, minirt->data.img, 0, 0);

	mlx_key_hook(minirt->window, keyboard_handler, minirt);
	mlx_hook(minirt->window, 17, 1L << 0, free_exit, minirt);
	mlx_loop(minirt->mlx);

	deinit(minirt);
}