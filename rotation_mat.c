/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_mat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:39:46 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/31 12:36:41 by bmakhama         ###   ########.fr       */
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

t_matrix	create_rotation(t_tuple *tuple)
{
	t_matrix	mat;
	t_matrix	temp;
	t_matrix	rot_x;
	t_matrix	rot_y;
	t_matrix	rot_z;

	rot_x = rotation_x(tuple->x / 180 * M_PI);
	rot_y = rotation_y(tuple->y / 180 * M_PI);
	rot_z = rotation_z(tuple->z / 180 * M_PI);
	temp = mult_mat(&rot_x, &rot_y);
	mat = mult_mat(&temp, &rot_z);
	free_matrix(&temp);
	free_matrix(&rot_x);
	free_matrix(&rot_y);
	free_matrix(&rot_z);
	return (mat);
}
