/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:41:19 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/19 11:42:42 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void free_split(char **split)
{ 
    int i = 0; 
    while (split[i] != NULL) 
    {
        free(split[i]); 
        i++; 
    } 
    free(split);
}

void free_matrix(t_matrix* matrix)
{ 
    for (int i = 0; i < matrix->size; ++i) 
    { 
        free(matrix->elem[i]);
    } 
    free(matrix->elem);
}
