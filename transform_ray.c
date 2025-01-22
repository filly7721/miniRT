/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:58:06 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 11:35:54 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	transform_ray(t_ray ray, t_matrix matrix)
{
	t_ray	trans_ray;

	trans_ray.origin = mult_mat_tuple(&ray.origin, &matrix);
	trans_ray.direction = mult_mat_tuple(&ray.direction, &matrix);
	return (trans_ray);
}

t_matrix	*copy_matrix(t_matrix *matrix)
{
	t_matrix	*copy;
	int			i;
	int			j;

	if (!matrix)
		return (NULL);
	copy = malloc(sizeof(t_matrix));
	if (!copy)
		return (NULL);
	copy->size = matrix->size;
	copy->elem = malloc(copy->size * sizeof(double *));
	i = 0;
	while (i < copy->size)
	{
		copy->elem[i] = malloc(copy->size * sizeof(double));
		j = 0;
		while (j < copy->size)
		{
			copy->elem[i][j] = matrix->elem[i][j];
			j++;
		}
		i++;
	}
	return (copy);
}

int	is_identity_matrix(t_matrix *matrix)
{
	int			i;
	int			j;

	if (matrix->size != 4)
		return (0);
	i = 0;
	while (i < matrix->size)
	{
		j = 0;
		while (j < matrix->size)
		{
			if (i == j && matrix->elem[i][j] != 1.0)
				return (0);
			if (i != j && matrix->elem[i][j] != 0.0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	set_transform(t_sphere *sphere, t_matrix *transform)
{
	if (!sphere || !transform)
		return ;
	if (is_identity_matrix(&sphere->transform))
		free_matrix(&sphere->transform);
	sphere->transform = *copy_matrix(transform);
}
