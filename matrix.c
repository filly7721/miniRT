/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:15:29 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/13 15:30:12 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void free_matrix(t_matrix* matrix)
{ 
    for (int i = 0; i < matrix->size; ++i) 
    { 
        free(matrix->elem[i]);
    } 
    free(matrix->elem);
}

t_matrix create_mat(int size)
{
    t_matrix mat;
    int i;
    int j;
    
    mat.size = size;
    mat.elem = malloc(size * sizeof(double*));
    if (!mat.elem)
    {
        fprintf(stderr, "Memory allocation failed for rows.\n");
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

t_matrix identity_matrix(int size)
{
    t_matrix mat;
    int i;

    mat = create_mat(size);
    i = 0;
    while (i < 2)
    {
        mat.data[i][i] = 1;
        i++;
    }
    return (mat);
}

t_matrix compaire_mat(t_matrix* a, t_matrix* b)
{
    t_matrix result;

    
}

t_matrix mult_mat(t_matrix* a, t_matrix* b)
{
    t_matrix result;
    int i;
    int j;
    int k;

    result = create_mat(a->size);
    i = 0;
    while (i < a->size)
    {
        j = 0;
        while(j < b->size)
        {
            k = 0;
            while(k < a->size)
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

t_tuple mult_mat_tuple(t_tuple* tuple, t_matrix* matrix)
{
    
}
t_matrix add_mat(t_matrix* a, t_matrix* b)
{
    
}

t_matrix sub_mat(t_matrix* a, t_matrix* b)
{
    
}
