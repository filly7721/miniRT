/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:41:25 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/30 13:29:40 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

t_intersection	*intersect_plane(t_ray *ray, t_plane *pl, t_intersection *head)
{
	double	t;
	t_ray	newray;

	newray = apply_ray_transform(ray, set_vector(pl->x, pl->y, pl->z));
	if (newray.direction.y < 0.001 && newray.direction.y > -0.001)
		return (head);
	t = -newray.origin.y / newray.direction.y;
	if (t > 0.0001)
		add_intersection(&head, create_shape_ref(pl, plane), t);
	return (head);
}
