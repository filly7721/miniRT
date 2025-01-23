/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:41:19 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/23 12:05:56 by bmakhama         ###   ########.fr       */
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

void free_matrix(t_matrix *mat) {
    if (!mat || !mat->elem) return;

    for (int i = 0; i < mat->size; i++) {
        if (mat->elem[i]) {
            free(mat->elem[i]);
        }
    }
    free(mat->elem);
    mat->elem = NULL;
}


void	free_cylinder(t_cylinder *cylinder, char **split)
{
	free(cylinder);
	free_split(split);
}
