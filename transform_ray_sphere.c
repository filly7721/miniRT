/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_ray_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:53:19 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 11:48:52 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	transform_ray_object(t_ray *ray, t_matrix *transform)
{
	t_matrix	inverse_trans;
	t_ray		trans_ray;

	inverse_trans = inverse(transform);
	if (!(inverse_trans.size == 0))
		return (*ray);
	trans_ray = transform_ray(*ray, inverse_trans);
	free_matrix(&inverse_trans);
	return (trans_ray);
}

t_intersection	*perform_intersection(t_ray ray, t_sphere *_sphere)
{
	double			t1;
	double			t2;
	t_intersection	*head;
	t_intersection	*node;
	t_shape			shape;

	head = NULL;
	shape.type = sphere;
	shape.sphere = _sphere;
	if (!cal_inter(&ray, _sphere, &t1, &t2))
		return (NULL);
	if (t1 >= 0)
	{
		node = create_node(&shape, t1);
		add_node(&head, node);
	}
	if (t2 >= 0)
	{
		node = create_node(&shape, t2);
		add_node(&head, node);
	}
	return (head);
}

t_intersection	*intersect(t_sphere *sphere)
{
	t_ray			trans_ray;
	t_intersection	*intersect;

	trans_ray = transform_ray_object(&trans_ray, &sphere->transform);
	intersect = perform_intersection(trans_ray, sphere);
	return (intersect);
}
