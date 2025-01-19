/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:36:53 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/19 15:44:50 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersections* create_node(t_shape* shape, double t)
{
    t_intersections* node;

    node = malloc(sizeof(t_intersections));
    if (!node)
    {
        printf("Failed allocation intersection node\n");
        return (NULL);
    }
    node->data.t = t;
    node->data.shape = shape;
    node->next = NULL;
    return (node);
}

void add_node(t_intersections** head, t_intersections* new_node)
{
    if (new_node)
    {
        new_node->next = *head;
        *head = new_node;
    }
}

// t_intersections* intersect(t_ray* ray, t_sphere* sphere)
// {
//     double a;
//     double b;
//     double c;
//     double discrim;
//     double sqrt_discrim;
    
//     sphere_equation(ray, sphere, &a, &b, &c);
//     discrim = (b * b) - (4 * a * c);
//     if (discrim < 0)
//         return (0);
//     sqrt_discrim = sqrt (discrim);
//     *t1 = (-b - sqrt_discrim) / (2 * a);
//     *t2 = (-b + sqrt_discrim) / (2 * a);
//     return (1);
// }

// t_intersections* intersect(t_ray* ray, t_sphere* sphere)
// {
//     double a, b, c, discrim, sqrt_discrim;
//     double t1, t2;

//     // Calculate quadratic equation coefficients
//     sphere_equation(ray, sphere, &a, &b, &c);

//     // Calculate the discriminant
//     discrim = (b * b) - (4 * a * c);
//     if (discrim < 0)
//         return NULL; // No intersections

//     // Calculate intersection points
//     sqrt_discrim = sqrt(discrim);
//     t1 = (-b - sqrt_discrim) / (2 * a);
//     t2 = (-b + sqrt_discrim) / (2 * a);

//     // Create the linked list of intersections
//     t_intersections* head = NULL;
    
//     // If t1 is valid, create the intersection node and add it to the list
//     if (t1 >= 0)
//     {
//         t_intersections* node = create_intersection_node(t1, (t_shape*)sphere);
//         add_intersection_to_list(&head, node);
//     }

//     // If t2 is valid, create the intersection node and add it to the list
//     if (t2 >= 0)
//     {
//         t_intersections* node = create_intersection_node(t2, (t_shape*)sphere);
//         add_intersection_to_list(&head, node);
//     }

//     return head;
// }
