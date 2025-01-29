/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:30:52 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/28 10:51:04 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	init_camera(t_camera *camera)
{
	camera->forward = normalize_tuple(
			set_tuple(camera->dir_x, camera->dir_y, camera->dir_z, 0.0));
	camera->up = set_tuple(0.0, 1.0, 0.0, 0.0);
	if (fabs(camera->forward.y) == 1.0)
		camera->up = normalize_tuple(set_tuple(1.0, 0.0, 0.0, 0.0));
	camera->right = normalize_tuple(cross_tuple(camera->up, camera->forward));
	camera->up = cross_tuple(camera->forward, camera->right);
}

t_intersection	*closest_hit(t_intersection	*list)
{
	t_intersection	*closest;
	t_intersection	*temp;

	temp = list;
	closest = list;
	while (temp->next)
	{
		temp = temp->next;
		if (temp->t > 0 && temp->t < closest->t)
			closest = temp;
	}
	return (closest);
}

bool	eq_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple	res;

	res = sub_tuples(t2, t1);
	if (res.x > 0.001 || res.y > 0.001 || res.z > 0.001)
		return (false);
	return (true);
}

double	get_brightness(t_minirt *minirt, t_tuple hit_point, t_tuple normal)
{
	t_tuple			lightsource;
	double			brightness;
	t_intersection	*intersections;
	t_ray			ray;

	ray.origin = set_point(
			minirt->env->light.x, minirt->env->light.y, minirt->env->light.z);
	ray.direction = normalize_tuple(sub_tuples(hit_point, ray.origin));
	intersections = intersect(&ray, minirt->env->shapes);
	t_tuple light_hit = add_tuples(mul_tuple(ray.direction, closest_hit(intersections)->t), ray.origin);
	free_intersections(intersections);
	if (eq_tuples(light_hit, hit_point) == false)
		return (minirt->env->ambient.intensity);
	lightsource = sub_tuples(ray.origin, hit_point);
	lightsource = normalize_tuple(lightsource);
	brightness = dot_tuple(lightsource, normal);
	if (brightness < 0)
		brightness = 0;
	return (brightness * minirt->env->light.bright * (1.0 - minirt->env->ambient.intensity)
		+ minirt->env->ambient.intensity);
}

t_tuple	get_sphere_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, t_sphere *sp)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;

	albedo = set_tuple(sp->r / 255.0, sp->g / 255.0, sp->b / 255.0, 0);
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	normal = normalize_tuple(sub_tuples(hp, set_point(sp->x, sp->y, sp->z)));
	return (mul_tuple(albedo, get_brightness(minirt, hp, normal)));
}

t_tuple	get_cylinder_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, t_cylinder *cy)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;
	// t_ray	newray;

	// newray = apply_ray_transform(ray, set_vector(cy->x, cy->y, cy->z));	
	albedo = set_tuple(cy->r / 255.0, cy->g / 255.0, cy->b / 255.0, 0);
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	normal = normalize_tuple(set_vector(hp.x, 0, hp.z));
	return (mul_tuple(albedo, get_brightness(minirt, hp, normal)));
}

t_tuple	get_color(t_minirt *minirt, t_ray *ray, t_intersection *intersection)
{
	t_tuple	color;

	if (intersection->shape->type == sphere)
		color = get_sphere_color(minirt, ray, intersection, intersection->shape->sphere);
	else if (intersection->shape->type == cylinder)
		color = get_cylinder_color(minirt, ray, intersection, intersection->shape->cylinder);
	else if (intersection->shape->type == plane)
		color = set_tuple(intersection->shape->plane->r / 255.0, \
			intersection->shape->plane->g / 255.0, \
			intersection->shape->plane->b / 255.0, 0);
	return (color);
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
