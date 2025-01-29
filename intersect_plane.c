/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:41:25 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/29 15:09:34 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// t_intersection	*intersect_plane(t_ray *ray, t_plane *pl, \
// 	t_intersection *head)
// {
// 	double	dn;
// 	t_tuple	pl_to_origin;
// 	double	t;

// 	dn = dot_tuple(ray->direction, (t_tuple) \
// 		{pl->norm_x, pl->norm_y, pl->norm_z, 0});
// 	pl_to_origin = sub_tuples(set_point(pl->x, pl->y, pl->z), ray->origin);
// 	t = dot_tuple(pl_to_origin, (t_tuple)
// 		{pl->norm_x, pl->norm_y, pl->norm_z, 0}) / dn;
// 	printf("t: %f\n", t);
// 	if (t <= 0.0000001)
// 		return (head);
// 	add_intersection(&head, create_shape_ref(pl, plane), t);
// 	return (head);
// }

// t_intersection *intersect_plane(t_ray *ray, t_plane *pl, t_intersection *head)
// {
//     double denom;
//     t_tuple pl_to_origin;
//     double t;

//     denom = dot_tuple(ray->direction, set_vector(pl->norm_x, pl->norm_y, pl->norm_z));
// // 	printf("denom: %f\n", denom);
// // 	printf("Ray Direction: (%f, %f, %f)\n", ray->direction.x, ray->direction.y, ray->direction.z);
// // printf("Plane Normal: (%f, %f, %f)\n", pl->norm_x, pl->norm_y, pl->norm_z);

//     if (denom > 0.0000001)
//     {
//         pl_to_origin = sub_tuples(set_point(pl->x, pl->y, pl->z), ray->origin);
// 		// printf("Plane Position: (%f, %f, %f)\n", pl->x, pl->y, pl->z);

//         t = dot_tuple(pl_to_origin, set_vector(pl->norm_x, pl->norm_y, pl->norm_z)) / denom;
//         // printf("t: %f\n", t);

//         if (t < 0.0000001)
//         {
// 			//  printf("Intersection found at t = %f\n", t);
//             add_intersection(&head, create_shape_ref(pl, plane), t);
//         }
//     }
//     return (head);
// }
t_intersection *intersect_plane(t_ray *ray, t_plane *pl, t_intersection *head)
{
	double	t;

	dprintf(2, "(%f, %f)", ray->direction.x, ray->direction.y);
	if (ray->direction.y < 0.001 && ray->direction.y > -0.001)
		return (head);
	t = -ray->origin.y / ray->direction.y;
	if (t > 0.0001)
		add_intersection(&head, create_shape_ref(pl, plane), t);
    return (head);
}