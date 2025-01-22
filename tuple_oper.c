/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:38:48 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 11:39:25 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_tuple	negate_tuple(t_tuple t)
{
	return (set_tuple(-t.x, -t.y, -t.z, -t.w));
}

double	dot_tuple(t_tuple t1, t_tuple t2)
{
	return (t1.x * t2.x + t1.y * t2.y + t1.z * t2.z + t1.w * t2.w);
}

t_tuple	cross_tuple(t_tuple t1, t_tuple t2)
{
	return (
		set_tuple(t1.y * t2.z - t1.z * t2.y, \
		t1.z * t2.x - t1.x * t2.z, \
		t1.x * t2.y - t1.y * t2.x, \
		0));
}

double	mag_tuple(t_tuple t)
{
	return (sqrt(dot_tuple(t, t)));
}

t_tuple	normalize_tuple(t_tuple t)
{
	return (mul_tuple(t, 1 / mag_tuple(t)));
}
