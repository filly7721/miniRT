/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:54:45 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/28 09:30:41 by bmakhama         ###   ########.fr       */
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

void	free_matrix(t_matrix *mat)
{
	int	i;

	if (!mat || !mat->elem)
		return ;
	i = 0;
	while (i < mat->size)
	{
		if (mat->elem[i])
			free(mat->elem[i]);
		i++;
	}
	free(mat->elem);
	mat->elem = NULL;
	mat->size = 0;
}

void	free_cylinder2(t_cylinder *cylinder, char **split)
{
	free(cylinder);
	free_split(split);
}
