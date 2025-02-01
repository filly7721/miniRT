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
