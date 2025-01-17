# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
# include <unistd.h> 

typedef struct s_matrix
{
	int size;
	double** elem;
} t_matrix;

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

t_matrix translation(t_tuple* trans_tuple)
{
    t_matrix mat;

    mat = identity_matrix(4);
    mat.elem[0][3] = trans_tuple->x;
    mat.elem[1][3] = trans_tuple->y;
    mat.elem[2][3] = trans_tuple->z;
    return (mat);
}
// Test Translation with a Vector
// int main()
// {
//     t_tuple vector = {1, 2, 3, 0};  // Vector (1, 2, 3) with w = 0
//     t_tuple translation_vec = {5, -3, 2, 0};  // Translation vector (5, -3, 2)
    
//     t_matrix translation_matrix = translation(translation_vec);
//     t_tuple translated_vector = mult_mat_tuple(&vector, &translation_matrix);
    
//     // The vector should remain the same after translation.
//     printf("Translated Vector: (%f, %f, %f, %f)\n", translated_vector.x, translated_vector.y, translated_vector.z, translated_vector.w);
    
//     return 0;
// }

//  Apply the Translation Matrix to a Point
int main()
{
    t_tuple point = {1, 2, 3, 1};  // Point (1, 2, 3) with w = 1
    t_tuple translation_vec = {5, -3, 2, 0};  // Translation vector (5, -3, 2)
    
    t_matrix translation_matrix = translation(&translation_vec);
    t_tuple translated_point = mult_mat_tuple(&point, &translation_matrix);
    
    printf("Translated Point: (%f, %f, %f, %f)\n", translated_point.x, translated_point.y, translated_point.z, translated_point.w);
    
    return 0;
}

