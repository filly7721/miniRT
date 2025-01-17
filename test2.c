#include <stdio.h>
#include <stdlib.h>
#include  <math.h>

// here i have tested:
//1. What happens when you invert the identity matrix?
// 2. What do you get when you multiply a matrix by its inverse?
// 3. Is there any difference between the inverse of the transpose of a matrix,
// and the transpose of the inverse?
// 4. Remember how multiplying the identity matrix by a tuple gives you the
// tuple, unchanged? Now, try changing any single element of the identity
// matrix to a different num


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

// Function prototypes
t_matrix create_mat(int size);
t_matrix identity_matrix(int size);
t_matrix inverse(t_matrix* mat);
void print_matrix(t_matrix* mat);
t_matrix submatrix(t_matrix* mat, int row, int col);

t_matrix create_mat(int size)
{
    t_matrix mat;
    int i;
    int j;
    
    mat.size = size;
    mat.elem = malloc(size * sizeof(double*));
    if (!mat.elem)
    {
        fprintf(stderr, "Memory allocation failed.\n");
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
    int j;

    mat = create_mat(size);
    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            if (i == j)
                mat.elem[i][j] = 1;
            else
                mat.elem[i][j] = 0; 
            j++;
        }
        i++;
    }
    return (mat);
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

t_matrix determinant(t_matrix* mat)
{
    if (mat->size == 2)
        determinant_2x2 (mat);
    else if (mat->size == 3)
        determinant_3x3(mat);
    else if (mat->size == 4)
        determinant_4x4(mat);
    return (*mat);
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

void print_matrix(t_matrix* mat) {
    for (int i = 0; i < mat->size; i++) {
        for (int j = 0; j < mat->size; j++) {
            printf("%lf ", mat->elem[i][j]);
        }
        printf("\n");
    }
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

// int main() {
//     // Define the size of the identity matrix
//     int size = 3;

//     // Create the identity matrix
//     t_matrix identity = identity_matrix(size);

//     // Print the original identity matrix
//     printf("Original Identity Matrix:\n");
//     print_matrix(&identity);

//     // Calculate the inverse of the identity matrix
//     t_matrix inv_identity = inverse(&identity);
//     m
//     // Print the inverted identity matrix
//     printf("Inverted Identity Matrix:\n");
//     print_matrix(&inv_identity);

//     // Free the allocated memory
//     free_matrix(&identity);
//     free_matrix(&inv_identity);

//     return 0;
// }


// int main() {
//     // Define the size of the matrix
//     int size = 3;

//     // Create a sample matrix
//     t_matrix mat = create_mat(size);
//     mat.elem[0][0] = 2; mat.elem[0][1] = -1; mat.elem[0][2] = 0;
//     mat.elem[1][0] = -1; mat.elem[1][1] = 2; mat.elem[1][2] = -1;
//     mat.elem[2][0] = 0; mat.elem[2][1] = -1; mat.elem[2][2] = 2;

//     // Print the original matrix
//     printf("Original Matrix:\n");
//     print_matrix(&mat);

//     // Calculate the inverse of the matrix
//     t_matrix inv = inverse(&mat);

//     // Print the inverse matrix
//     printf("Inverse Matrix:\n");
//     print_matrix(&inv);

//     // Multiply the matrix by its inverse
//     t_matrix result = mult_mat(&mat, &inv);

//     // Print the result of the multiplication
//     printf("Result of multiplying the matrix by its inverse:\n");
//     print_matrix(&result);

//     // Free the allocated memory
//     free_matrix(&mat);
//     free_matrix(&inv);
//     free_matrix(&result);

//     return 0;
// }


typedef union	u_tuple
{
	struct
	{
		double	x;
		double	y;
		double	z;
		double	w;
	};
	struct
	{
		double	a;
		double	r;
		double	g;
		double	b;
	};
}	t_tuple;

t_tuple mult_mat_tuple(t_tuple* tuple, t_matrix* mat)
{
    t_tuple result;
    
    result.x = (mat->elem[0][0] * tuple->x )+ (mat->elem[0][1] * tuple->y) +
                (mat->elem[0][2] * tuple->z) + (mat->elem[0][3] * tuple->w);
    result.y = (mat->elem[1][0] * tuple->x )+ (mat->elem[1][1] * tuple->y) +
                (mat->elem[1][2] * tuple->z) + (mat->elem[1][3] * tuple->w);
    result.z = (mat->elem[2][0] * tuple->x) + (mat->elem[2][1] * tuple->y) +
                (mat->elem[2][2] * tuple->z) + (mat->elem[2][3] * tuple->w);
    result.w = (mat->elem[3][0] * tuple->x) + (mat->elem[3][1] * tuple->y) +
                (mat->elem[3][2] * tuple->z) + (mat->elem[3][3] * tuple->w);
    return (result);
}
void print_tuple(t_tuple* tuple) { printf("(%lf, %lf, %lf, %lf)\n", tuple->x, tuple->y, tuple->z, tuple->w); }
int main() {
    // Define the size of the matrix
    int size = 4;

    // Create a 4x4 identity matrix
    t_matrix identity = identity_matrix(size);

    // Create a sample tuple
    t_tuple tuple = {1, 2, 3, 1};

    // Print the original tuple
    printf("Original Tuple:\n");
    print_tuple(&tuple);

    // Multiply the identity matrix by the tuple
    t_tuple result = mult_mat_tuple(&tuple, &identity);

    // Print the result
    printf("Result of multiplying the identity matrix by the tuple:\n");
    print_tuple(&result);

    // Change an element of the identity matrix
    identity.elem[1][2] = 5.0;

    // Multiply the modified identity matrix by the tuple
    result = mult_mat_tuple(&tuple, &identity);

    // Print the result of the modified multiplication
    printf("Result of multiplying the modified identity matrix by the tuple:\n");
    print_tuple(&result);

    // Free the allocated memory
    free_matrix(&identity);

    return 0;
}







