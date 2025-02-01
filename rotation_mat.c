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

t_tuple quat_from_axis_angle(t_tuple axis, double theta)
{
	t_tuple q;
	double sin_half_theta;

	sin_half_theta = sin(theta / 2);
	q.x = axis.x * sin_half_theta;
	q.y = axis.y * sin_half_theta;
	q.z = axis.z * sin_half_theta;
	q.w = cos(theta / 2);
	return (q);
}

void set_mat_row(t_matrix *mat, int row, t_tuple tuple)
{
	mat->elem[row][0] = tuple.x;
	mat->elem[row][1] = tuple.y;
	mat->elem[row][2] = tuple.z;
	mat->elem[row][3] = tuple.w;
}

t_matrix mat4_from_quat(t_tuple q)
{
	t_matrix ret;
	t_tuple x;
	t_tuple y;
	t_tuple z;
	t_tuple w;

	ret = identity_matrix(4);
	x = set_tuple(q.x * q.x, q.x * q.y, q.x * q.z, 0);
	y = set_tuple(0, q.y * q.y, q.y * q.z, 0);
	z = set_tuple(0, 0, q.z * q.z, 0);
	w = set_tuple(q.w * q.x, q.w * q.y, q.w * q.z, 0);
	set_mat_row(&ret, 0, set_vector(1 - 2 * (y.y + z.z), 2 * (x.y - w.z), 2 * (x.z + w.y)));
	set_mat_row(&ret, 1, set_vector(2 * (x.y + w.z), 1 - 2 * (x.x + z.z), 2 * (y.z - w.x)));
	set_mat_row(&ret, 2, set_vector(2 * (x.z - w.y), 2 * (y.z + w.x), 1 - 2 * (x.x + y.y)));
	set_mat_row(&ret, 3, set_point(0, 0, 0));
	return (ret);
}

t_matrix create_rotation(t_tuple vec)
{
	t_tuple angle;
	t_tuple rot_axis;
	t_tuple quat;
	double theta;

	if (vec.x == 0 && fabs(vec.y - 1) < EPSILON && vec.z == 0)
		return (identity_matrix(4));
	if (vec.x == 0 && fabs(vec.y + 1) < EPSILON && vec.z == 0)
		return (rotation_x(M_PI));
	vec = normalize_tuple(vec);
	rot_axis = cross_tuple(set_vector(0, 1, 0), vec);
	if (mag_tuple(rot_axis) < EPSILON)
		return (identity_matrix(4));
	rot_axis = normalize_tuple(rot_axis);
	theta = acos(fmax(-1.0f, fmin(1.0f, dot_tuple(vec, set_vector(0, 1, 0)))));
	quat = quat_from_axis_angle(rot_axis, theta);
	return (mat4_from_quat(quat));
}
