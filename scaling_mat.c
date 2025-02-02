/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:55:32 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/02 09:49:45 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix	create_scaling(t_tuple *tuple)
{
	t_matrix	mat;

	mat = identity_matrix(4);
	mat.elem[0][0] = tuple->x;
	mat.elem[1][1] = tuple->y;
	mat.elem[2][2] = tuple->z;
	return (mat);
}
