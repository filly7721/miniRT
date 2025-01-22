/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_mat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:28:52 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 11:36:18 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix	translation(t_tuple *tuple)
{
	t_matrix	mat;

	mat = identity_matrix(4);
	mat.elem[0][3] = tuple->x;
	mat.elem[1][3] = tuple->y;
	mat.elem[2][3] = tuple->z;
	return (mat);
}
