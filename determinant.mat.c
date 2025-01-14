/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.mat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:50:50 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/14 13:42:33 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double determinant_2x2(t_matrix* mat)
{
    return ((mat->elem[0][0] * mat->elem[1][1]) - (mat->elem[0][1] * mat->elem[1][0]));
}

t_matrix allocate_submat(int size)
{
    t_matrix submat;
    int i;

    submat.size = size;
    submat.elem = (double**)malloc(sizeof(double*) * submat.size);
    if (!submat.elem)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    i = 0; 
    while (i < submat.size)
    { 
        submat.elem[i] = (double*)malloc(sizeof(double) * submat.size);
        if (!submat.elem[i])
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return (submat);
}

t_matrix submatrix(t_matrix* mat, int row, int col)
{
    t_matrix submat;
    int i;
    int j;
    int c;
    int r;
    
    submat.size = mat->size - 1;
    submat.elem = allocate_submat (mat->size - 1);
    i = 0;
    r = 0;
    while (i < mat->size)
    {
        if (i != row)
        {
            c = 0;
            j = 0;
            while (j < mat->size)
            {
                if (j != col)
                {
                    submat.elem[r][c] = mat->elem[i][j];
                    c++;
                }
                j++;
            }
            r++;
        }
        i++;
    }
    return (submat);
}

double determinant_3x3(t_matrix* mat)
{
    t_matrix submat;
    int i;
    double sign;
    double det;
    int j;

    i = 0;
    det = 0.0;
    while (i < mat->size)
    {
        submat = submatrix(mat, 0 , i);
        if (i % 2 == 0)
            sign = 1.0;
        else
            sign = -1.0;
        det += sign * mat->elem[0][i] * determinant_2x2(&submat);
        j = 0;
        while (j < submat.size)
            free(submat.elem[j++]);
        free(submat.elem);
        i++;
    }
    return (det);
}

double determinant_4x4(t_matrix* mat)
{
    t_matrix submat;
    int i;
    double sign;
    double det;
    int j;

    i = 0;
    det = 0.0;
    while (i < mat->size)
    {
        submat = submatrix(mat, 0, i);
        if (i % 2 == 0)
            sign = 1.0;
        else
            sign = -1.0;
        det += sign * mat->elem[0][i] * determinant_3x3(&submat);
        j = 0;
        while (j < submat.size)
            free(submat.elem[j++]);
        free(submat.elem);
        i++;
    }
    return (det);
}

t_matrix determinant(t_matrix* mat)
{
    if (mat->size == 2)
        determinant_2x2 (mat);
    else if (mat->size == 3)
        determinant_3x3(mat);
    else if (mat->size == 4)
        determinant_4x4(mat);
    return (mat);
}