
#include "miniRT.h"

#include <stdio.h>
#include <stdlib.h>

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
        mat.elem[i][i] = 1;
        i++;
    }
    return (mat);
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
// Function to free the memory of a matrix
void free_matrix(t_matrix* matrix) {
    for (int i = 0; i < matrix->size; ++i) {
        free(matrix->elem[i]);
    }
    free(matrix->elem);
}

int main() {
    // Initialize matrices A and B
    t_matrix A = create_mat(3);
    t_matrix B = create_mat(3);

    // Assign values to matrix A
    A.elem[0][0] = 1; A.elem[0][1] = 2; A.elem[0][2] = 3;
    A.elem[1][0] = 4; A.elem[1][1] = 5; A.elem[1][2] = 6;
    A.elem[2][0] = 7; A.elem[2][1] = 8; A.elem[2][2] = 9;

    // Assign values to matrix B
    B.elem[0][0] = 9; B.elem[0][1] = 8; B.elem[0][2] = 7;
    B.elem[1][0] = 6; B.elem[1][1] = 5; B.elem[1][2] = 4;
    B.elem[2][0] = 3; B.elem[2][1] = 2; B.elem[2][2] = 1;

    // Multiply matrices A and B
    t_matrix C = mult_mat(&A, &B);

    // Print the resulting matrix
    printf("Resulting Matrix:\n");
    for (int i = 0; i < C.size; ++i) {
        for (int j = 0; j < C.size; ++j) {
            printf("%.2f ", C.elem[i][j]);
        }
        printf("\n");
    }

    // Free the memory of matrices
    free_matrix(&A);
    free_matrix(&B);
    free_matrix(&C);

    return 0;
}
