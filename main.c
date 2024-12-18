#include "miniRT.h"

void	pixel_put(t_mlxdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main()
{
	
	t_mlx mlx;

	mlx.instance = mlx_init();
	mlx.window = mlx_new_window(mlx.instance, 1920, 1080, "example");

	mlx.data.img = mlx_new_image(mlx.instance, 1920, 1080);
	mlx.data.addr = mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel, &mlx.data.line_length, &mlx.data.endian);

	pixel_put(&mlx.data, 10,10,0x0000ff00);
	mlx_put_image_to_window(mlx.instance, mlx.window, mlx.data.img, 0, 0);

	mlx_loop(mlx.instance);

	mlx_destroy_image(mlx.instance, mlx.data.img);
	mlx_destroy_window(mlx.instance, mlx.window);
	free(mlx.instance);
}