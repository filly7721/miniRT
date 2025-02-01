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
