/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:19:17 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/24 12:59:09 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersection *intersect_cylinder(t_ray *ray, t_cylinder *cy, t_intersection *intersections)
{
	t_tuple sphere_to_ray;
	double discriminant;
	t_tuple center;

	// center = set_point(_sphere->x, _sphere->y, _sphere->z);
	
	sphere_to_ray = sub_tuples(ray->origin, center);
	double a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;
	double b = 2 * (ray->origin.x * ray->direction.x + ray->origin.z * ray->direction.z);
	double c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1;
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
