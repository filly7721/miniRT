/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:30:52 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/31 12:41:37 by bmakhama         ###   ########.fr       */
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

void	init_cylinder(t_cylinder *cy)
{
	t_tuple		tuple;
	t_matrix	translation_matrix;
	t_matrix	scaling_matrix;
	t_matrix	rotation_matrix;
	t_matrix	temp;

	tuple = set_vector(cy->x, cy->y, cy->z);
	translation_matrix = create_translation(&tuple);
	tuple = set_vector(cy->radius, 1, cy->radius);
	scaling_matrix = create_scaling(&tuple);
	cy->transform = mult_mat(&translation_matrix, &scaling_matrix);
	tuple = set_vector(cy->axis_x, cy->axis_y, cy->axis_z);
	rotation_matrix = create_rotation(&tuple);
	temp = cy->transform;
	cy->transform = mult_mat(&cy->transform, &rotation_matrix);
	print_mat(&cy->transform);
	free_matrix(&temp);
	temp = cy->transform;
	cy->transform = inverse(&cy->transform);
	print_mat(&cy->transform);
	free_matrix(&temp);
	free_matrix(&rotation_matrix);
	free_matrix(&scaling_matrix);
	free_matrix(&translation_matrix);
	cy->tp_transform = transpose_mat(&cy->transform);
}

void	init_shapes(t_minirt *minirt)
{
	t_list	*curr;

	curr = minirt->env->shapes;
	while (curr)
	{
		if (((t_shape *)curr->content)->type == cylinder)
			init_cylinder(((t_shape *)curr->content)->cylinder);
		curr = curr->next;
	}
}

int	main(int arc, char** arv)
{
	t_environment	env;
	t_minirt		*minirt;

	if (arc != 2)
	{
		printf("The input must be 2!");
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
