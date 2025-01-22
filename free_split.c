/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:41:19 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 11:47:48 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_matrix(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (i < matrix->size)
	{
		free(matrix->elem[i]);
		i++;
	}
	free(matrix->elem);
	free(matrix);
}

void	free_cylinder(t_cylinder *cylinder, char **split)
{
	free(cylinder);
	free_split(split);
}
