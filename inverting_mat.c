/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverting_mat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:56:18 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/21 16:16:50 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void fill_submatrix(t_matrix* mat, t_matrix* submat, int row, int col)
{
    int i;
    int j;
    int c;
    int r;

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

t_matrix submatrix(t_matrix* mat, int row, int col)
{
    t_matrix submat;
    
    submat = allocate_submat (mat->size - 1);
    fill_submatrix(mat, &submat, row, col);
    return (submat);
}

int cofactor(t_matrix* mat, int row, int col)
{
    t_matrix submat;
    double cofactor_val;
    double sign;
    
    submat = submatrix(mat, row, col);
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

double calculate_det(t_matrix* mat)
{
    double det;

    printf("Matrix size in calculate_det fun: %d\n", mat->size);  // Debugging output

    if (mat->size == 2)
        det = determinant_2x2(mat);
    else if (mat->size == 3)
        det = determinant_3x3(mat);
    else if (mat->size == 4)
        det = determinant_4x4(mat);
    else
    {
        fprintf(stderr, "Inverse only implemented for 2x2, 3x3, and 4x4 matrices.\n");
        exit(EXIT_FAILURE);
    }
    if (det == 0)
    {
        fprintf(stderr, "Matrix is not invertible (determinant is 0).\n");
        exit(EXIT_FAILURE);
    }
    return (det);
}

t_matrix inverse(t_matrix* mat)
{
    double det;
    t_matrix inv;
    int col;
    int row;

    printf("Matrix size before calling inverse: %d\n", mat->size);
    printf("before calling calculate\n");
    det = calculate_det(mat);
    printf("after calling calculate\n");
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
