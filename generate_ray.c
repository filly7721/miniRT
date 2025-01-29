/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:28:37 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/26 10:04:06 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	apply_ray_transform(t_ray *old_ray, t_tuple translation)
{
	t_ray	new_ray;

	new_ray.origin = add_tuples(old_ray->origin, mul_tuple(translation, -1));
	new_ray.direction = mul_tuple(old_ray->direction, 1);
	return (new_ray);
}

t_ray	generate_ray(t_minirt *minirt, int x, int y)
{
	double	viewpoint_width;
	double	viewpoint_height;
	double	pixel_camera_x;
	double	pixel_camera_y;
	t_tuple	pixel_world;

	viewpoint_width = 2 * tan((minirt->env->camera.fov * (M_PI / 180.0)) / 2.0);
	viewpoint_height = viewpoint_width \
		/ ((double)minirt->width / minirt->height);
	pixel_camera_x = (2 * ((x + 0.5) / minirt->width) - 1)
		* viewpoint_width / 2.0;
	pixel_camera_y = (1 - 2 * ((y + 0.5) / minirt->height))
		* viewpoint_height / 2.0;
	pixel_world = add_tuples(
			add_tuples((scale_tuple(minirt->env->camera.right, pixel_camera_x)),
				scale_tuple(minirt->env->camera.up, pixel_camera_y)),
			minirt->env->camera.forward);
	return ((t_ray){
		set_tuple(minirt->env->camera.x,
			minirt->env->camera.y, minirt->env->camera.z, 1.0),
		normalize_tuple(pixel_world)});
}
