/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:15:23 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/24 11:52:06 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_shape	*create_shape_ref(void	*shape, t_shapeType type)
{
	t_shape	*ref;
	ref = malloc(sizeof(t_shape));
	if (!ref)
		return (NULL);
	ref->shape = shape;
	ref->type = type;
	return (ref);
}

t_intersection	*intersect(t_ray *ray, t_list *shapelist)
{
	t_intersection	*intersection;
	t_sphere	*_sphere;

	t_list *temp;

	temp = shapelist;
	intersection = NULL;
	while (temp)
	{
		t_shape *shape = temp->content;
		if(shape->type == sphere)
		{
			_sphere = shape->sphere;
			intersection = intersect_sphere(ray, _sphere, intersection);
		}
		temp = temp->next;
	}
	return (intersection);
}