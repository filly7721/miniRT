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

t_intersection	*intersect_cylinder(t_ray *ray, t_cylinder *cy, \
	t_intersection *intersections)
{
	double	discriminant;
	t_tuple	center;
	t_ray	newray;

	newray.direction = mult_mat_tuple(&ray->direction, &cy->transform);
	newray.origin = mult_mat_tuple(&ray->origin, &cy->transform);	
	double a = newray.direction.x * newray.direction.x + newray.direction.z * newray.direction.z;
	double b = 2 * (newray.origin.x * newray.direction.x + newray.origin.z * newray.direction.z);
	double c = newray.origin.x * newray.origin.x + newray.origin.z * newray.origin.z - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return intersections;
	double t1 = (-b - sqrt(discriminant)) / (2 * a);
	double t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 >= 0 && fabs(add_tuples(mul_tuple(newray.direction, t1), newray.origin).y) < cy->height / 2)
		add_intersection(&intersections, create_shape_ref(cy, cylinder), t1);
	if (t2 >= 0  && fabs(add_tuples(mul_tuple(newray.direction, t2), newray.origin).y) < cy->height / 2)
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

	tuple = set_vector(cy->x, cy->y, cy->z);
	translation_matrix = create_translation(&tuple);
	tuple = set_vector(cy->radius, cy->radius, cy->radius);
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
