#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
# include <unistd.h> 

# include <ctype.h>  // !delete after adding ft_strtof
# include <stdbool.h>
# include <math.h>
# include <stdarg.h> //va_start

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

typedef struct s_ray
{
	t_tuple origin;
	t_tuple direction;
}	t_ray;


typedef struct s_mlxdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlxdata;
typedef struct s_camera
{
	float x;
	float y;
	float z;

	float dir_x;
	float dir_y;
	float dir_z;

	int fov; // Field of View (in degrees)
}	t_camera;

typedef struct s_light
{
	float x;
	float y;
	float z;

	float bright;

	int r;
	int g;
	int b;
}	t_light;

typedef struct s_ambient
{
	double intensity;
	int	r;
	int	g;
	int	b;
}	t_ambient;

typedef struct s_sphere
{
	float x;
	float y;
	float z;

	float diameter;

	int r;
	int g;
	int b;

}	t_sphere;

typedef struct s_plane
{
	float x;
	float y;
	float z;

	float norm_x;
	float norm_y;
	float norm_z;

	int r;
	int g;
	int b;
}	t_plane;

typedef struct s_cylinder
{
	float x;
	float y;
	float z;

	float axis_x;
	float axis_y;
	float axis_z;

	float radius;
	float height;

	int r;
	int g;
	int b;
}	t_cylinder;

typedef enum e_shapeType
{
	sphere,
	plane,
	cylinder
}	t_shapeType;

typedef struct s_shape
{
	t_shapeType	type;
	union
	{
		t_sphere	*sphere;
		t_plane		*plane;
		t_cylinder	*cylinder;
	};
}	t_shape;

typedef struct s_intersection
{
	double	t;
	t_shape* shape;
}	t_intersection;

typedef struct s_intersections
{
	t_intersection	data;
	struct s_intersections* next;
}	t_intersections;

typedef struct s_environment
{
	t_list		*shapes;
	t_light		light;
	t_ambient	ambient;
	t_camera	camera;
}	t_environment;

typedef struct s_minirt
{
	void		*mlx;
	void		*window;
	t_mlxdata	data;
	int			width;
	int			height;
	t_environment* env;
}	t_minirt;

t_minirt	*init(int width, int height);
void		deinit(t_minirt *minirt);
int			keyboard_handler(int keycode, t_minirt *miniRT);
int			free_exit(t_minirt *minirt);

// Parsing

// Lights
void parsing(t_environment* env, const char* file);
void parse_ambient(char* line, t_ambient* ambient);
char *remove_extra_spaces(const char *line);
char** split_by_char(char* space_removed, char delimiter, int expected_count);
int split_rgb(char* rgb, int* r, int* g, int* b);

void parse_camera(char* line, t_camera* camera);
void parse_light(char* line, t_light* light);
int split_xyz(char* xyz, float* x, float* y, float* z); //this fun was used in the camera and light parsig
void parse_plane(char* line, t_environment* env);
void parse_sphere(char* line, t_environment* env);
void parse_cylinder(char* line, t_environment* env);

// Debug fun, delete later
void print_environment(t_environment* env);

// free functions
void free_split(char **split);

//tuples
t_tuple	set_tuple(double x, double y, double z, double w);
t_tuple add_tuples(t_tuple t1, t_tuple t2);
t_tuple sub_tuples(t_tuple t1, t_tuple t2);
t_tuple mul_tuple(t_tuple t, double scalar);
t_tuple negate_tuple(t_tuple t);
double	dot_tuple(t_tuple t1, t_tuple t2);
t_tuple	cross_tuple(t_tuple t1, t_tuple t2);
double	mag_tuple(t_tuple t);
t_tuple normalize_tuple(t_tuple t);

bool eq(double f1, double f2);

//matrix
t_matrix create_mat(int size);
t_matrix identity_matrix(int size);
t_matrix mult_mat(t_matrix* a, t_matrix* b);
t_tuple mult_mat_tuple(t_tuple* tuple, t_matrix* mat);

void free_matrix(t_matrix* matrix);

double determinant_2x2(t_matrix* mat);
t_matrix allocate_submat(int size);
void fill_submatrix(t_matrix* mat, t_matrix* submat, int row, int col);
t_matrix submatrix(t_matrix* mat, int row, int col);
double determinant_3x3(t_matrix* mat);
double determinant_4x4(t_matrix* mat);
t_matrix* determinant(t_matrix* mat);

//Rays
t_ray create_ray(t_tuple origin, t_tuple direction);
t_tuple position(t_ray* ray, double t);
int sphere_equation(t_ray* ray, t_sphere* sphere, double* a, double* b, double* c);

#endif