/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:15:23 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 10:30:49 by bmakhama         ###   ########.fr       */
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

void	add_intersection(t_intersection **head, t_shape *shape, double t)
{
	t_intersection	*node;
	t_intersection	*temp;

	node = malloc(sizeof(t_intersection));
	node->t = t;
	node->shape = shape;
	node->next = NULL;
	if (*head == NULL)
		*head = node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}

t_intersection	*intersect(t_ray *ray, t_list *shapelist)
{
	t_intersection	*intersection;
	t_list			*temp;
	t_shape			*shape;

	temp = shapelist;
	intersection = NULL;
	while (temp)
	{
		shape = temp->content;
		if (shape->type == sphere)
			intersection = intersect_sphere(ray, shape->sphere, intersection);
		if (shape->type == cylinder)
			intersection = intersect_cylinder(ray, shape->cylinder,
					intersection);
		if (shape->type == plane)
		{
			intersection = intersect_plane(ray, shape->plane, intersection);
		}
		temp = temp->next;
	}
	return (intersection);
}

t_intersection	*closest_hit(t_intersection	*list)
{
	t_intersection	*closest;
	t_intersection	*temp;

	temp = list;
	closest = list;
	while (temp->next)
	{
		temp = temp->next;
		if (temp->t > 0 && temp->t < closest->t)
			closest = temp;
	}
	return (closest);
}
