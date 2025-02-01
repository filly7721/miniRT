/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverting_mat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:56:18 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 10:34:24 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	fill_subm(t_matrix *mat, t_matrix *submat, int row, int col)
{
	int	i;
	int	j;
	int	c;
	int	r;

	r = 0;
	i = 0;
	while (i < mat->size)
	{
		if (i != row)
		{
			c = 0;
			j = 0;
			while (j < mat->size)
			{
				if (j != col)
					submat->elem[r][c++] = mat->elem[i][j];
				j++;
			}
			r++;
		}
		i++;
	}
}

t_matrix	submatrix(t_matrix *mat, int row, int col)
{
	t_matrix	submat;

	submat = allocate_submat (mat->size - 1);
	fill_subm(mat, &submat, row, col);
	return (submat);
}

double	cofactor(t_matrix *mat, int row, int col)
{
	t_matrix	submat;
	double		cofactor_val;
	double		sign;

	if ((row + col) % 2 == 0)
		sign = 1.0;
	else
		sign = -1.0;
	if (mat->size == 2)
		cofactor_val = sign * mat->elem[1 - row][1 - col];
	else
	{
		submat = submatrix(mat, row, col);
		if (mat->size == 3)
			cofactor_val = sign * determinant_2x2(&submat);
		else if (mat->size == 4)
			cofactor_val = sign * determinant_3x3(&submat);
		free_matrix(&submat);
	}
	return (cofactor_val);
}

double	calculate_det(t_matrix *mat)
{
	double	det;

	if (mat->size == 2)
		det = determinant_2x2(mat);
	else if (mat->size == 3)
		det = determinant_3x3(mat);
	else if (mat->size == 4)
		det = determinant_4x4(mat);
	else
	{
		ft_putstr_fd("Inverse only 2x2, 3x3, and 4x4 matrices.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (det == 0)
	{
		ft_putstr_fd("Matrix is not invertible (determinant is 0).\n", 2);
		exit(EXIT_FAILURE);
	}
	return (det);
}

t_matrix	inverse(t_matrix *mat)
{
	double		det;
	t_matrix	inv;
	int			col;
	int			row;

	det = calculate_det(mat);
	inv = allocate_submat(mat->size);
	row = 0;
	while (row < mat->size)
	{
		col = 0;
		while (col < mat->size)
		{
			inv.elem[col][row] = (cofactor(mat, row, col) / det);
			col++;
		}
		row++;
	}
	return (inv);
}
