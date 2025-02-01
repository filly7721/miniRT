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

	newray.direction = mult_mat_tuple(&ray->direction, &pl->transform);
	newray.origin = mult_mat_tuple(&ray->origin, &pl->transform);
	if (newray.direction.y < EPSILON && newray.direction.y > -EPSILON)
		return (head);
	if (newray.direction.y > EPSILON)
		return (head);
	t = -newray.origin.y / newray.direction.y;
	if (t > 0.0001)
		add_intersection(&head, create_shape_ref(pl, plane), t);
	return (head);
}

void	init_plane(t_plane *pl)
{
	t_tuple tuple;
	t_matrix translation_matrix;
	t_matrix rotation_matrix;
	t_matrix temp;

	tuple = set_vector(pl->x, pl->y, pl->z);
	translation_matrix = create_translation(&tuple);
	tuple = set_vector(pl->norm_x, pl->norm_y, pl->norm_z);
	rotation_matrix = create_rotation(tuple);
	pl->transform = mult_mat(&translation_matrix, &rotation_matrix);
	temp = pl->transform;
	pl->transform = inverse(&pl->transform);
	free_matrix(&temp);
	free_matrix(&rotation_matrix);
	free_matrix(&translation_matrix);
	pl->tp_transform = transpose_mat(&pl->transform);
}
