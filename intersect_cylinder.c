/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:19:17 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/30 13:29:25 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	cylinder_intersect_dist(t_ray *ray, double *t1, double *t2)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = ray->direction.x * ray->direction.x
		+ ray->direction.z * ray->direction.z;
	b = 2 * (ray->origin.x * ray->direction.x
			+ ray->origin.z * ray->direction.z);
	c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1;
	disc = b * b - 4 * a * c;
	if (disc < EPSILON)
		return (false);
	*t1 = (-b - sqrt(disc)) / (2 * a);
	*t2 = (-b + sqrt(disc)) / (2 * a);
	return (true);
}

t_intersection	*intersect_cylinder(t_ray *ray, t_cylinder *cy, \
	t_intersection *intersections)
{
	double	discriminant;
	t_tuple	center;
	t_ray	newray;
	double	t1;
	double	t2;

	newray.direction = mult_mat_tuple(&ray->direction, &cy->transform);
	newray.origin = mult_mat_tuple(&ray->origin, &cy->transform);
	if (cylinder_intersect_dist(&newray, &t1, &t2) == false)
		return (intersections);
	if (t1 >= 0 && fabs(add_tuples(mul_tuple(newray.direction, t1),
				newray.origin).y) < cy->height / 2)
		add_intersection(&intersections, create_shape_ref(cy, cylinder), t1);
	if (t2 >= 0 && fabs(add_tuples(mul_tuple(newray.direction, t2),
				newray.origin).y) < cy->height / 2)
		add_intersection(&intersections, create_shape_ref(cy, cylinder), t2);
	return (intersections);
}

void	init_cylinder(t_cylinder *cy)
{
	t_tuple		tuple;
	t_matrix	translation_matrix;
	t_matrix	scaling_matrix;
	t_matrix	rotation_matrix;
	t_matrix	temp;

	cy->radius /= 2;
	tuple = set_vector(cy->x, cy->y, cy->z);
	translation_matrix = create_translation(&tuple);
	tuple = set_vector(cy->radius, 1, cy->radius);
	scaling_matrix = create_scaling(&tuple);
	cy->transform = mult_mat(&translation_matrix, &scaling_matrix);
	tuple = set_vector(cy->axis_x, cy->axis_y, cy->axis_z);
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
