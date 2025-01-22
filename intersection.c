/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:36:53 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 12:08:39 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersection	*create_node(t_shape *shape, double t)
{
	t_intersection	*node;

	node = malloc(sizeof(t_intersection));
	if (!node)
	{
		printf("Failed allocation intersection node\n");
		return (NULL);
	}
	node->t = t;
	node->shape = shape;
	node->next = NULL;
	return (node);
}

void	add_node(t_intersection **head, t_intersection *new_node)
{
	if (new_node)
	{
		new_node->next = *head;
		*head = new_node;
	}
}

int	cal_inter(t_ray *ray, t_sphere *sphere, double *t1, double *t2)
{
	double	discrim;
	double	sqrt_discrim;

	sphere_eq(ray, sphere);
	discrim = (sphere->b * sphere->b) - (4 * sphere->a * sphere->c);
	if (discrim < 0)
		return (0);
	sqrt_discrim = sqrt (discrim);
	*t1 = (-(sphere->b) - sqrt_discrim) / (2 * sphere->a);
	*t2 = (-(sphere->b) + sqrt_discrim) / (2 * sphere->a);
	return (1);
}

// t_intersection* intersect(t_ray* ray, t_sphere* _sphere)
// {
//     double t1;
//     double t2;
//     t_intersection* head;
//     t_intersection* node;
//     t_shape shape;

//     head = NULL;
//     shape.type = sphere;
//     shape.sphere = _sphere;
//     ray->direction = normalize_tuple(ray->direction);
//     if(!calculate_intersect(ray, sphere, &t1, &t2))
//         return (NULL);
//     if (t1 >= 0)
//     {
//         node = create_node(&shape, t1);
//         add_node(&head, node);
//     }
//     if(t2 >= 0)
//     {
//         node = create_node(&shape, t2);
//         add_node(&head, node);
//     }
//     return (head);
// }

t_intersection	*hit(t_intersection *inter)
{
	t_intersection	*current;
	t_intersection	*hit;

	current = inter;
	hit = NULL;
	while (current != NULL)
	{
		if (current->t >= 0 && (hit == NULL || current->t < hit->t))
			hit = current;
		current = current->next;
	}
	return (hit);
}
