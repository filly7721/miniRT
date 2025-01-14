/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverting_mat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:56:18 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/14 12:55:49 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//cofactor(t_matrix* mat, int row, int col) – To calculate the cofactor of a specific element in the matrix.
// inverse(t_matrix* mat) – To compute the inverse of the matrix using the cofactor and determinant (for 2x2, 3x3, and 4x4).