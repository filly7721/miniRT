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

bool	sphere_intersect_dist(t_ray *ray, t_sphere *sp, double *t1, double *t2)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_tuple	sphere_to_ray;

	sphere_to_ray = sub_tuples(ray->origin,
			set_point(sp->x, sp->y, sp->z));
	a = dot_tuple(ray->direction, ray->direction);
	b = 2 * dot_tuple(ray->direction, sphere_to_ray);
	c = dot_tuple(sphere_to_ray, sphere_to_ray)
		- (sp->diameter / 2 * sp->diameter / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		return (false);
	*t1 = (-b - sqrt(discriminant)) / (2 * a);
	*t2 = (-b + sqrt(discriminant)) / (2 * a);
	return (true);
}

t_intersection	*intersect_sphere(t_ray *ray, t_sphere *_sphere, \
	t_intersection *intersections)
{
	t_tuple	sphere_to_ray;
	double	discriminant;
	double	t1;
	double	t2;

	if (sphere_intersect_dist(ray, _sphere, &t1, &t2) == false)
		return (intersections);
	if (t1 >= 0)
		add_intersection(&intersections, create_shape_ref(_sphere, sphere), t1);
	if (t2 >= 0)
		add_intersection(&intersections, create_shape_ref(_sphere, sphere), t2);
	return (intersections);
}
