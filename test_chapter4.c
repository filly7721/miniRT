# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
# include <unistd.h> 
# include <stdarg.h>
# include <math.h>

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


t_matrix scaling(t_tuple* tuple)
{
    t_matrix mat;

    mat = identity_matrix(4);
    mat.elem[0][0] = tuple->x;
    mat.elem[1][1] = tuple->y;
    mat.elem[2][2] = tuple->z;
    return (mat);
}

t_matrix shearing(t_tuple* shear)
{
    t_matrix mat;

    mat = identity_matrix(4);
    mat.elem[0][1] = shear->x;
    mat.elem[0][2] = shear->y;
    mat.elem[1][0] = shear->z;
    mat.elem[1][2] = shear->w;
    mat.elem[2][0] = shear->a;
    mat.elem[2][1] = shear->r;
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

t_matrix chain_transformations(int count, ...)
{
    va_list args;
    t_matrix result;
    t_matrix temp;
    int i;

    if (count < 1)
        return identity_matrix(4);

    result = identity_matrix(4);
    va_start(args, count);

    for (i = 0; i < count; i++)
    {
        temp = va_arg(args, t_matrix);
        result = mult_mat(&temp, &result);
    }

    va_end(args);
    return result;
}
t_tuple set_tuple(double x, double y, double z, double w)
{
    t_tuple t = { .x = x, .y = y, .z = z, .w = w };
    return t;
}

t_tuple point(double x, double y, double z)
{
    return set_tuple(x, y, z, 1.0);
}

//  Chained Transformations
int main()
{
    t_tuple trans = set_tuple(10, 5, 7, 0);
    t_tuple scale = set_tuple(5, 5, 5, 0);
    t_tuple point_tuple = set_tuple(1, 0, 1, 1);

    t_matrix A = translation(&trans);
    t_matrix B = scaling(&scale);

    t_matrix result_mat = chain_transformations(2, A, B);
    t_tuple result_point = mult_mat_tuple(&point_tuple, &result_mat);

    printf("Result: (%f, %f, %f, %f)\n", result_point.x, result_point.y, result_point.z, result_point.w);
    return 0;
}

