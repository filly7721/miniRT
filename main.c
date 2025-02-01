/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:30:52 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 10:40:21 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_minirt	*init_minirt(int width, int height, t_environment *env)
{
	t_minirt	*minirt;

	minirt = malloc(sizeof(t_minirt));
	if (!minirt)
		return (NULL);
	minirt->mlx = mlx_init();
	if (!minirt->mlx)
		return (free(minirt), NULL);
	minirt->window = mlx_new_window(minirt->mlx, width, height, "MiniRT");
	// if (!minirt->window)
	//     return (mlx_destroy_display(minirt->mlx), free(minirt), NULL);
	minirt->data.img = mlx_new_image(minirt->mlx, width, height);
	if (!minirt->data.img)
		return (mlx_destroy_window(minirt->mlx, minirt->window), \
			free(minirt), NULL);
	minirt->data.addr = mlx_get_data_addr(minirt->data.img, \
		&minirt->data.bits_per_pixel, &minirt->data.line_length, \
			&minirt->data.endian);
	minirt->width = width;
	minirt->height = height;
	minirt->env = env;
	return (minirt);
}

void	trace_rays(t_minirt *minirt)
{
	int				x;
	int				y;
	t_ray			ray;
	t_intersection	*intersections;
	t_shape			*current_shape;

	init_camera(&minirt->env->camera);
	y = 0;
	while (y < minirt->height)
	{
		x = 0;
		while (x < minirt->width)
		{
			ray = generate_ray(minirt, x, y);
			intersections = intersect(&ray, minirt->env->shapes);
			if (intersections != NULL)
			{
				t_tuple color = get_color(minirt, &ray, closest_hit(intersections));
				pixel_put(&minirt->data, x, y, rgbtoint(color));
			}
			else
				pixel_put(&minirt->data, x, y, 0x00000000);
			free_intersections(intersections);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->window, minirt->data.img, 0, 0);
}

void	init_shapes(t_minirt *minirt)
{
	t_list	*curr;

	curr = minirt->env->shapes;
	while (curr)
	{
		if (((t_shape *)curr->content)->type == cylinder)
			init_cylinder(((t_shape *)curr->content)->cylinder);
		else if (((t_shape *)curr->content)->type == plane)
			init_plane(((t_shape *)curr->content)->plane);
		curr = curr->next;
	}
}

int	main(int arc, char **arv)
{
	t_environment	env;
	t_minirt		*minirt;

	if (arc != 2)
	{
		ft_putstr_fd("The input must be 2!", 2);
		return (1);
	}
	env.shapes = NULL;
	env.camera.fov = 0;
	parsing(&env, arv[1]);
	minirt = init_minirt(2000, 1000, &env);
	if (!minirt)
		return (ft_putstr_fd("init error\n", 2), 1);
	init_shapes(minirt);
	trace_rays(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->window, \
		minirt->data.img, 0, 0);
	mlx_key_hook(minirt->window, keyboard_handler, minirt);
	mlx_hook(minirt->window, 17, 1L << 0, free_exit, minirt);
	mlx_loop(minirt->mlx);
	deinit(minirt);
	free_minirt(minirt);
	return (0);
}
