/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:19:17 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/30 13:29:53 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersection	*intersect_sphere(t_ray *ray, t_sphere *_sphere, \
	t_intersection *intersections)
{
	t_tuple sphere_to_ray;
	double discriminant;
	t_tuple center;

	center = set_point(_sphere->x, _sphere->y, _sphere->z);
	
	sphere_to_ray = sub_tuples(ray->origin, center);
	double a = dot_tuple(ray->direction, ray->direction);
	double b = 2 * dot_tuple(ray->direction, sphere_to_ray);
	double c = dot_tuple(sphere_to_ray, sphere_to_ray) - (_sphere->diameter / 2 * _sphere->diameter / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return intersections;
	double t1 = (-b - sqrt(discriminant)) / (2 * a);
	double t2 = (-b + sqrt(discriminant)) / (2 * a);
	 if (t1 >= 0)
		add_intersection(&intersections, create_shape_ref(_sphere, sphere), t1);
	if (t2 >= 0)
		add_intersection(&intersections, create_shape_ref(_sphere, sphere), t2);
	return (intersections);
}
