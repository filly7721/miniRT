#include <stdio.h>
#include <stdlib.h>
#include  <math.h>
// #include "matrix.h" // Include your matrix header file here
typedef struct s_matrix
{
	int size;
	double** elem;
} t_matrix;

void free_matrix(t_matrix* matrix)
{ 
    for (int i = 0; i < matrix->size; ++i) 
    { 
        free(matrix->elem[i]);
    } 
    free(matrix->elem);
}

// t_matrix create_mat(int size)
// {
//     t_matrix mat;
//     int i;
//     int j;
    
//     mat.size = size;
//     mat.elem = malloc(size * sizeof(double*));
//     if (!mat.elem)
//     {
//         fprintf(stderr, "Memory allocation failed.\n");
//         exit(EXIT_FAILURE);
//     }
//     i = 0;
//     while (i < mat.size)
//     {
//         mat.elem[i] = malloc(size * sizeof(double));
//         j = 0;
//         while (j < mat.size)
//             mat.elem[i][j++] = 0;    
//         i++;
//     }
    
//     return (mat);
// }

// double determinant_2x2(t_matrix* mat)
// {
//     return ((mat->elem[0][0] * mat->elem[1][1]) - (mat->elem[0][1] * mat->elem[1][0]));
// }

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
    t_matrix submat = allocate_submat(mat->size - 1);

    fill_submatrix(mat, &submat, row, col);
    return (submat);
}

//     // Debug output
//     printf("Submatrix for element mat[%d][%d] (%f):\n", row, col, mat->elem[row][col]);
//     i = 0;
//     while (i < submat.size)
//     {
//         j = 0;
//         while (j < submat.size)
//         {
//             printf("%f ", submat.elem[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }

//     return submat;
// }

double determinant_2x2(t_matrix* mat)
{
    return ((mat->elem[0][0] * mat->elem[1][1]) - (mat->elem[0][1] * mat->elem[1][0]));
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

// // Helper function to print a test result
// void print_test_result(const char* test_name, double expected, double actual) {
//     if (fabs(expected - actual) < 1e-6) // Allow small numerical differences
//         printf("%s: Test passed (Expected: %.6f, Actual: %.6f)\n", test_name, expected, actual);
//     else
//         printf("%s: Test failed (Expected: %.6f, Actual: %.6f)\n", test_name, expected, actual);
// }

// int main() {
//     // Test case 1: Identity 4x4 matrix
//     t_matrix mat1 = create_mat(4);
//     mat1.elem[0][0] = 1; mat1.elem[0][1] = 0; mat1.elem[0][2] = 0; mat1.elem[0][3] = 0;
//     mat1.elem[1][0] = 0; mat1.elem[1][1] = 1; mat1.elem[1][2] = 0; mat1.elem[1][3] = 0;
//     mat1.elem[2][0] = 0; mat1.elem[2][1] = 0; mat1.elem[2][2] = 1; mat1.elem[2][3] = 0;
//     mat1.elem[3][0] = 0; mat1.elem[3][1] = 0; mat1.elem[3][2] = 0; mat1.elem[3][3] = 1;
//     double det1 = determinant_4x4(&mat1);
//     print_test_result("Identity 4x4 Matrix Determinant", 1.0, det1); // Expected: 1

//     // Test case 2: All elements are 1s
//     t_matrix mat2 = create_mat(4);
//     for (int i = 0; i < 4; i++)
//         for (int j = 0; j < 4; j++)
//             mat2.elem[i][j] = 1;
//     double det2 = determinant_4x4(&mat2);
//     print_test_result("4x4 Matrix with All 1s Determinant", 0.0, det2); // Expected: 0

//     // Test case 3: Diagonal 4x4 matrix with different values
//     t_matrix mat3 = create_mat(4);
//     mat3.elem[0][0] = 2; mat3.elem[0][1] = 0; mat3.elem[0][2] = 0; mat3.elem[0][3] = 0;
//     mat3.elem[1][0] = 0; mat3.elem[1][1] = 3; mat3.elem[1][2] = 0; mat3.elem[1][3] = 0;
//     mat3.elem[2][0] = 0; mat3.elem[2][1] = 0; mat3.elem[2][2] = 4; mat3.elem[2][3] = 0;
//     mat3.elem[3][0] = 0; mat3.elem[3][1] = 0; mat3.elem[3][2] = 0; mat3.elem[3][3] = 5;
//     double det3 = determinant_4x4(&mat3);
//     print_test_result("Diagonal 4x4 Matrix Determinant", 120.0, det3); // Expected: 2*3*4*5 = 120

//     // Free memory for all matrices
//     for (int i = 0; i < 4; i++) {
//         free(mat1.elem[i]);
//         free(mat2.elem[i]);
//         free(mat3.elem[i]);
//     }
//     free(mat1.elem);
//     free(mat2.elem);
//     free(mat3.elem);

//     return 0;
// }
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
    // For 2x2 matrices, no submatrix is required; directly return the element
    if (mat->size == 2) {
        // The cofactor is the value of the other diagonal element
        cofactor_val = sign * mat->elem[1 - row][1 - col];
    } else {
        // Use submatrices for 3x3 and larger matrices
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

    det = calculate_det(mat);
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

// int main() {
//     t_matrix mat = allocate_submat(2);

//     // Fill the matrix elements
//     mat.elem[0][0] = 6;  mat.elem[0][1] = 4;  
//     mat.elem[1][0] = 5;  mat.elem[1][1] = 5;  

//     // Check if invertible
//     double det = determinant_2x2(&mat);
//     if (det == 0) {
//         printf("Matrix is not invertible.\n");
//     } else {
//         printf("Matrix is invertible. Determinant = %f\n", det);
//         t_matrix inv = inverse(&mat);

//         // Print the inverse matrix
//         printf("Inverse Matrix:\n");
//         for (int i = 0; i < inv.size; i++) {
//             for (int j = 0; j < inv.size; j++) {
//                 printf("%f ", inv.elem[i][j]);
//             }
//             printf("\n");
//         }

//         // Free memory for the inverse matrix
//         for (int i = 0; i < inv.size; i++) {
//             free(inv.elem[i]);
//         }
//         free(inv.elem);
//     }

//     // Free memory for the original matrix
//     for (int i = 0; i < mat.size; i++) {
//         free(mat.elem[i]);
//     }
//     free(mat.elem);

//     return 0;
// }

// int main() {
//     t_matrix mat = allocate_submat(4);

// // Fill the matrix elements
// mat.elem[0][0] = 4;  mat.elem[0][1] = 7;  mat.elem[0][2] = 2;  mat.elem[0][3] = 3;
// mat.elem[1][0] = 3;  mat.elem[1][1] = 5;  mat.elem[1][2] = 6;  mat.elem[1][3] = 4;
// mat.elem[2][0] = 2;  mat.elem[2][1] = 1;  mat.elem[2][2] = 5;  mat.elem[2][3] = 8;
// mat.elem[3][0] = 6;  mat.elem[3][1] = 7;  mat.elem[3][2] = 3;  mat.elem[3][3] = 2;

// // Check if invertible
// double det = determinant_4x4(&mat);
// if (det == 0) {
//     printf("Matrix is not invertible.\n");
// } else {
//     printf("Matrix is invertible. Determinant = %f\n", det);
//     t_matrix inv = inverse(&mat);

//     // Print the inverse matrix
//     printf("Inverse Matrix:\n");
//     for (int i = 0; i < inv.size; i++) {
//         for (int j = 0; j < inv.size; j++) {
//             printf("%f ", inv.elem[i][j]);
//         }
//         printf("\n");
//     }

//     // Free memory for the inverse matrix
//     for (int i = 0; i < inv.size; i++) {
//         free(inv.elem[i]);
//     }
//     free(inv.elem);
// }

// // Free memory for the original matrix
// for (int i = 0; i < mat.size; i++) {
//     free(mat.elem[i]);
// }
// free(mat.elem);

// }
int main() {
    t_matrix mat = allocate_submat(3);

    // Fill the matrix elements
    mat.elem[0][0] = 2;  mat.elem[0][1] = -3;  mat.elem[0][2] = 1;
    mat.elem[1][0] = 2;  mat.elem[1][1] = 0;   mat.elem[1][2] = -1;
    mat.elem[2][0] = 1;  mat.elem[2][1] = 4;   mat.elem[2][2] = 5;

    // Compute determinant
    double det = determinant_3x3(&mat);
    printf("Determinant = %f\n", det);

    // Check if invertible and compute inverse
    if (det == 0) {
        printf("Matrix is not invertible.\n");
    } else {
        printf("Matrix is invertible.\n");
        t_matrix inv = inverse(&mat);

        printf("Inverse Matrix:\n");
        for (int i = 0; i < inv.size; i++) {
            for (int j = 0; j < inv.size; j++) {
                printf("%f ", inv.elem[i][j]);
            }
            printf("\n");
        }

        // Free memory for inverse
        for (int i = 0; i < inv.size; i++) {
            free(inv.elem[i]);
        }
        free(inv.elem);
    }

    // Free memory for the original matrix
    for (int i = 0; i < mat.size; i++) {
        free(mat.elem[i]);
    }
    free(mat.elem);

    return 0;
}
