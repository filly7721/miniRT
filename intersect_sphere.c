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

void add_intersection(t_intersection **head, t_shape *shape, double t)
{
    t_intersection *node;
    t_intersection *temp;

    node = malloc(sizeof(t_intersection));
    node->t = t;
    node->shape = shape;
    node->next = NULL;
    if(*head == NULL)
        *head = node;
    else
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = node;
    }
}
t_intersection *intersect_sphere(t_ray *ray, t_sphere *_sphere, t_intersection *intersections)
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
    { 
        // printf("No intersection: discriminant < 0\n");
        return intersections;
    }
    // printf("discriminant equals: %f\n", discriminant);
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    t_shape *shape = malloc(sizeof(t_shape));
    shape->type = sphere;
    shape->sphere = _sphere;
    // printf("t1: %f, t2: %f\n", t1, t2);
    if (t1 >= 0)
    {
        add_intersection(&intersections, shape, t1);
        // printf("Intersection at t1: %f\n", t1);
    }
    if (t2 >= 0)
    {
        add_intersection(&intersections, shape, t2);
        // printf("Intersection at t2: %f\n", t2);
    }
    return (intersections);
}
