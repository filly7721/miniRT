
// #include "miniRT.h"

#include <stdio.h>
#include <stdlib.h>
// Define your types here
typedef struct s_matrix {
    int size;
    double **elem;
} t_matrix;

typedef struct s_tuple {
    double x, y, z, w;
} t_tuple;
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
            mat.elem[i][j++] = 1;    
        i++;
    }
    
    return (mat);
}

t_matrix identity_matrix(int size)
{
    t_matrix mat;
    int i;
    int j;

    mat = create_mat(size);
    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            if (i == j)
                mat.elem[i][j] = 1;  // Set diagonal elements to 1 for identity matrix
            else
                mat.elem[i][j] = 0; 
            j++;
        }
        i++;
    }
    return (mat);
}

t_matrix transpose_mat(t_matrix* mat)
{
    t_matrix transposed;
    int i;
    int j;

    transposed = create_mat(mat->size);
    i = 0;
    while (i < mat->size)
    {
        j = 0;
        while( j < mat->size)
        {
            transposed.elem[i][j] = mat->elem[j][i];
            j++;
        }
        i++;
    }
    return (transposed);
}



// Function declarations (as given earlier)
t_matrix create_mat(int size);
t_matrix identity_matrix(int size);
t_tuple mult_mat_tuple(t_tuple* tuple, t_matrix* mat);
// void free_matrix(t_matrix* matrix);
void print_matrix(t_matrix* mat)
{
    for (int i = 0; i < mat->size; i++) {
        for (int j = 0; j < mat->size; j++) {
            printf("%.2f ", mat->elem[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    t_matrix mat, transposed;
    
    // Create a 3x3 matrix
    mat = create_mat(3);
    
    // Print original matrix
    printf("Original matrix:\n");
    print_matrix(&mat);
    
    // Transpose the matrix
    transposed = transpose_mat(&mat);
    
    // Print transposed matrix
    printf("\nTransposed matrix:\n");
    print_matrix(&transposed);
    
    // Free the allocated memory (not shown in previous steps)
    for (int i = 0; i < mat.size; i++) {
        free(mat.elem[i]);
        free(transposed.elem[i]);
    }
    free(mat.elem);
    free(transposed.elem);
    
    return 0;
}

