/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:30:52 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/29 15:31:33 by bmakhama         ###   ########.fr       */
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

	ray.origin = hit_point;
	ray.direction = set_point(
			minirt->env->light.x, minirt->env->light.y, minirt->env->light.z);
	ray.direction = normalize_tuple(sub_tuples(ray.direction, ray.origin));
	ray.origin = add_tuples(ray.origin, mul_tuple(ray.direction, EPSILON));
	intersections = intersect(&ray, minirt->env->shapes);
	lightsource = set_point(minirt->env->light.x, minirt->env->light.y, minirt->env->light.z);
	if (intersections && closest_hit(intersections)->t < mag_tuple(sub_tuples(lightsource, ray.origin)) + 0.001)
		return (minirt->env->ambient.intensity);
	brightness = dot_tuple(ray.direction, normal);
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
	t_ray	newray;

	newray.direction = mult_mat_tuple(&ray->direction, &cy->transform);
	newray.origin = mult_mat_tuple(&ray->origin, &cy->transform);
	albedo = set_tuple(cy->r / 255.0, cy->g / 255.0, cy->b / 255.0, 0);
	hp = add_tuples(mul_tuple(newray.direction, inter->t), newray.origin);
	normal = normalize_tuple(set_vector(hp.x, 0, hp.z));
	normal = mult_mat_tuple(&normal, &cy->tp_transform);
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin );
	return (mul_tuple(albedo, get_brightness(minirt, hp, normal)));
}

t_tuple	get_plane_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, t_plane *pl)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;

	albedo = set_tuple(pl->r / 255.0, pl->g / 255.0, pl->b / 255.0, 0);
	normal = set_vector(0, 1, 0);
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);

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
		color = get_plane_color(minirt, ray, intersection, intersection->shape->plane);
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

t_tuple quat_from_axis_angle(t_tuple axis, double theta)
{
	t_tuple	q;
	double	sin_half_theta;

	sin_half_theta = sin(theta / 2);
	q.x = axis.x * sin_half_theta;
	q.y = axis.y * sin_half_theta;
	q.z = axis.z * sin_half_theta;
	q.w = cos(theta / 2);
	return (q);
}

void	set_mat_row(t_matrix *mat, int row, t_tuple tuple)
{
	mat->elem[row][0] = tuple.x;
	mat->elem[row][1] = tuple.y;
	mat->elem[row][2] = tuple.z;
	mat->elem[row][3] = tuple.w;
}

t_matrix	mat4_from_quat(t_tuple q)
{
	t_matrix	ret;
	t_tuple		x;
	t_tuple		y;
	t_tuple		z;
	t_tuple		w;

	ret = identity_matrix(4);
	x = set_tuple(q.x * q.x, q.x * q.y, q.x * q.z, 0);
	y = set_tuple(0, q.y * q.y, q.y * q.z, 0);
	z = set_tuple(0, 0, q.z * q.z, 0);
	w = set_tuple(q.w * q.x, q.w * q.y, q.w * q.z, 0);
	set_mat_row(&ret, 0, set_vector(1 - 2 * (y.y + z.z), 2 * (x.y - w.z), 2 * (x.z + w.y)));
	set_mat_row(&ret, 1, set_vector(2 * (x.y + w.z), 1 - 2 * (x.x + z.z), 2 * (y.z - w.x)));
	set_mat_row(&ret, 2, set_vector(2 * (x.z - w.y), 2 * (y.z + w.x), 1 - 2 * (x.x + y.y)));
	set_mat_row(&ret, 3, set_point(0, 0, 0));
	return (ret);
}

t_matrix	create_rotation(t_tuple vec)
{
	t_tuple	angle;
	t_tuple	rot_axis;
	t_tuple	quat;
	double	theta;

	if (vec.x == 0 && fabs(vec.y - 1) < EPSILON && vec.z == 0)
		return (identity_matrix(4));
	if (vec.x == 0 && fabs(vec.y + 1) < EPSILON && vec.z == 0)
		return (rotation_x(M_PI));
	rot_axis = cross_tuple(set_vector(0, 1, 0), vec);
	if (mag_tuple(rot_axis) < EPSILON)
		return (identity_matrix(4));
	rot_axis = normalize_tuple(rot_axis);
	theta = acos(fmax(-1.0f, fmin(1.0f, dot_tuple(vec, set_vector(0, 1, 0)))));
	quat = quat_from_axis_angle(rot_axis, theta);
	return (mat4_from_quat(quat));
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
	tuple = set_vector(cy->radius, cy->radius, cy->radius);
	scaling_matrix = create_scaling(&tuple);
	cy->transform = mult_mat(&translation_matrix, &scaling_matrix);
	tuple = set_vector(cy->axis_x, cy->axis_y, cy->axis_z);
	tuple = normalize_tuple(tuple);
	rotation_matrix = create_rotation(tuple);
	temp = cy->transform;
	cy->transform = mult_mat(&cy->transform, &rotation_matrix);
	free_matrix(&temp);
	temp = cy->transform;
	cy->transform = inverse(&cy->transform);
	free_matrix(&temp);
	free_matrix(&rotation_matrix);
	free_matrix(&scaling_matrix);
	free_matrix(&translation_matrix);
	cy->tp_transform = transpose_mat(&cy->transform);
}

void	init_shapes(t_minirt *minirt)
{
	t_list *curr;
	
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
