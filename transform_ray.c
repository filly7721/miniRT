/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:58:06 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/21 13:51:08 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray transform_ray(t_ray ray, t_matrix matrix)
{
    t_ray trans_ray;

    trans_ray.origin = mult_mat_tuple(&ray.origin, &matrix);
    trans_ray.direction = mult_mat_tuple(&ray.direction, &matrix);
    return (trans_ray);
}
t_matrix* copy_matrix(t_matrix* matrix)
{
    if (!matrix)
        return NULL;

    t_matrix* copy = malloc(sizeof(t_matrix));
    if (!copy)
        return NULL;

    copy->size = matrix->size;
    copy->elem = malloc(copy->size * sizeof(double*));
    for (int i = 0; i < copy->size; i++)
    {
        copy->elem[i] = malloc(copy->size * sizeof(double));
        for (int j = 0; j < copy->size; j++)
            copy->elem[i][j] = matrix->elem[i][j];
    }
    return copy;
}
int is_identity_matrix(t_matrix* matrix)
{
    if (matrix->size != 4) // Assuming you are working with 4x4 matrices
        return 0;

    // Check if the matrix is an identity matrix
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            if (i == j && matrix->elem[i][j] != 1.0)
                return 0;
            if (i != j && matrix->elem[i][j] != 0.0)
                return 0;
        }
    }
    return 1;  // It's an identity matrix
}

void set_transform(t_sphere* sphere, t_matrix* transform)
{
    if (!sphere || !transform)
        return ;
    
    // Check if the transform is already the identity matrix (or any default matrix state)
    if (is_identity_matrix(&sphere->transform))
        free_matrix(&sphere->transform);
    
    // Copy the new transform matrix
    sphere->transform = *copy_matrix(transform);
}

