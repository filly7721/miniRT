/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:36:29 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/25 10:04:11 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_tuple	set_tuple(double x, double y, double z, double w)
{
	t_tuple	t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = w;
	return (t);
}

t_tuple	add_tuples(t_tuple t1, t_tuple t2)
{
	return (set_tuple(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w));
}

t_tuple	sub_tuples(t_tuple t1, t_tuple t2)
{
	return (set_tuple(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w));
}

t_tuple	mul_tuple(t_tuple t, double scalar)
{
	return (set_tuple(t.x * scalar, t.y * scalar, t.z * scalar, t.w * scalar));
}

t_tuple scale_tuple(t_tuple tuple, double scalar)
{
    t_tuple scaled;

    scaled.x = tuple.x * scalar;
    scaled.y = tuple.y * scalar;
    scaled.z = tuple.z * scalar;
    scaled.w = tuple.w * scalar;
    return scaled;
}

