/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_mat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:39:46 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 11:24:12 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix	rotation_x(double agnle)
{
	t_matrix	mat;
	double		sin_theta;
	double		cos_theta;

	mat = identity_matrix(4);
	sin_theta = sin(agnle);
	cos_theta = cos(agnle);
	mat.elem[1][1] = cos_theta;
	mat.elem[1][2] = -sin_theta;
	mat.elem[2][1] = sin_theta;
	mat.elem[2][2] = cos_theta;
	return (mat);
}

t_matrix	rotation_y(double agnle)
{
	t_matrix	mat;
	double		sin_theta;
	double		cos_theta;

	mat = identity_matrix(4);
	sin_theta = sin(agnle);
	cos_theta = cos(agnle);
	mat.elem[0][0] = cos_theta;
	mat.elem[0][2] = sin_theta;
	mat.elem[2][0] = -sin_theta;
	mat.elem[2][2] = cos_theta;
	return (mat);
}

t_matrix	rotation_z(double agnle)
{
	t_matrix	mat;
	double		sin_theta;
	double		cos_theta;

	mat = identity_matrix(4);
	sin_theta = sin(agnle);
	cos_theta = cos(agnle);
	mat.elem[0][0] = cos_theta;
	mat.elem[0][1] = -sin_theta;
	mat.elem[1][0] = sin_theta;
	mat.elem[1][1] = cos_theta;
	return (mat);
}
