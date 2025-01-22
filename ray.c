/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:27:20 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 12:09:08 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	*create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
	{
		printf("Failed ray allocation\n");
		return (NULL);
	}
	ray->origin = origin;
	ray->direction = direction;
	return (ray);
}

t_tuple	position(t_ray *ray, double t)
{
	return (add_tuples(ray->origin, mul_tuple(ray->direction, t)));
}

int	sphere_eq(t_ray *ray, t_sphere *sphere)
{
	t_tuple	sphere_to_ray;

	sphere_to_ray = sub_tuples(ray->origin, \
		set_tuple(sphere->x, sphere->y, sphere->z, 0));
	sphere->a = dot_tuple(ray->direction, ray->direction);
	sphere->b = 2 * dot_tuple(ray->direction, sphere_to_ray);
	sphere->c = dot_tuple(sphere_to_ray, sphere_to_ray) - \
		(sphere->diameter / 2) * (sphere->diameter / 2);
	return (1);
}
