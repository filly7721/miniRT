#include "miniRT.h"

// void	pixel_put(t_mlxdata *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int		per_pixel(t_minirt *minirt, int x, int y)
// {
// 	if (x > minirt->width / 4.0 && x < 3 * minirt->width / 4.0 && y > minirt->height / 4.0 && y < 3 * minirt->height / 4.0)
// 		return 0x0ffff000;
// 	return 0x00000fff;
// }

// void	trace_rays(t_minirt *minirt, int width, int height)
// {
// 	int	x;
// 	int	y;
// 	int	color;

// 	y = 0;
// 	while (y < height)
// 	{
// 		x = 0;
// 		while (x < width)
// 		{
// 			color = per_pixel(minirt, x, y);
// 			pixel_put(&minirt->data, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

int main(int arc, char** arv)
{
	if (arc != 2)
	{
		printf("The input must be 2!");
		return (1);
	}
	t_environment env;
	parsing(&env, arv[1]);
	print_environment(&env);
	// t_minirt	*minirt;

	// minirt = init(1920, 1080);
	// if (!minirt)
	// 	return (ft_putstr_fd("init error\n", 2), 1);
	
	// trace_rays(minirt, 1920, 1080);
	// mlx_put_image_to_window(minirt->mlx, minirt->window, minirt->data.img, 0, 0);

	// mlx_key_hook(minirt->window, keyboard_handler, minirt);
	// mlx_hook(minirt->window, 17, 1L << 0, free_exit, minirt);
	// mlx_loop(minirt->mlx);

	// deinit(minirt);
}