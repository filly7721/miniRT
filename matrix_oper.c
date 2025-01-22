/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_oper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:15:29 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 10:34:32 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix	create_mat(int size)
{
	t_matrix	mat;
	int			i;
	int			j;

	mat.size = size;
	mat.elem = malloc(size * sizeof(double *));
	if (!mat.elem)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < size)
	{
		mat.elem[i] = malloc(size * sizeof(double));
		j = 0;
		while (j < size)
			mat.elem[i][j++] = 0;
		i++;
	}
	return (mat);
}

t_matrix	identity_matrix(int size)
{
	t_matrix	mat;
	int			i;
	int			j;

	mat = create_mat(size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == j)
				mat.elem[i][j] = 1;
			else
				mat.elem[i][j] = 0;
			j++;
		}
		i++;
	}
	return (mat);
}

t_matrix	mult_mat(t_matrix *a, t_matrix *b)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	result = create_mat(a->size);
	i = 0;
	while (i < a->size)
	{
		j = 0;
		while (j < b->size)
		{
			k = 0;
			while (k < a->size)
			{
				result.elem[i][j] += a->elem[i][k] * b->elem[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple	mult_mat_tuple(t_tuple *tuple, t_matrix *mat)
{
	t_tuple	result;

	result.x = (mat->elem[0][0] * tuple->x) + (mat->elem[0][1] * tuple->y)
		+(mat->elem[0][2] * tuple->z) + (mat->elem[0][3] * tuple->w);
	result.y = (mat->elem[1][0] * tuple->x) + (mat->elem[1][1] * tuple->y)
		+(mat->elem[1][2] * tuple->z) + (mat->elem[1][3] * tuple->w);
	result.z = (mat->elem[2][0] * tuple->x) + (mat->elem[2][1] * tuple->y)
		+(mat->elem[2][2] * tuple->z) + (mat->elem[2][3] * tuple->w);
	result.w = (mat->elem[3][0] * tuple->x) + (mat->elem[3][1] * tuple->y)
		+ (mat->elem[3][2] * tuple->z) + (mat->elem[3][3] * tuple->w);
	return (result);
}

t_matrix	transpose_mat(t_matrix *mat)
{
	t_matrix	transposed;
	int			i;
	int			j;

	transposed = create_mat(mat->size);
	i = 0;
	while (i < mat->size)
	{
		j = 0;
		while (j < mat->size)
		{
			transposed.elem[i][j] = mat->elem[j][i];
			j++;
		}
		i++;
	}
	return (transposed);
}
