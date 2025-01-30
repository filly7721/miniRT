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
	t_tuple	sphere_to_ray;
	double	discriminant;
	t_tuple	center;
	t_ray	newray;

	newray = apply_ray_transform(ray, set_vector(cy->x, cy->y, cy->z));	
	sphere_to_ray = sub_tuples(newray.origin, center);
	double a = newray.direction.x * newray.direction.x + newray.direction.z * newray.direction.z;
	double b = 2 * (newray.origin.x * newray.direction.x + newray.origin.z * newray.direction.z);
	double c = newray.origin.x * newray.origin.x + newray.origin.z * newray.origin.z - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return intersections;
	double t1 = (-b - sqrt(discriminant)) / (2 * a);
	double t2 = (-b + sqrt(discriminant)) / (2 * a);
	 if (t1 >= 0)
		add_intersection(&intersections, create_shape_ref(cy, cylinder), t1);
	if (t2 >= 0)
		add_intersection(&intersections, create_shape_ref(cy, cylinder), t2);
	return (intersections);
}
