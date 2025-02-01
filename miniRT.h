/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:11:01 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/31 12:45:08 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
# include <unistd.h> 
# include <stdbool.h>
# include <math.h>

# define EPSILON 0.00001

typedef struct s_matrix
{
	int		size;
	double	**elem;
}	t_matrix;

typedef union u_tuple
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
		double	r;
		double	g;
		double	b;
		double	a;
	};
}	t_tuple;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
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
	float	x;
	float	y;
	float	z;
	float	dir_x;
	float	dir_y;
	float	dir_z;
	int		fov;
	t_tuple	up;
	t_tuple	forward;
	t_tuple	right;
}	t_camera;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	float	bright;
	int		r;
	int		g;
	int		b;
}	t_light;

typedef struct s_ambient
{
	double	intensity;
	int		r;
	int		g;
	int		b;
}	t_ambient;

typedef struct s_sphere
{
	float		x;
	float		y;
	float		z;
	float		diameter;
	int			r;
	int			g;
	int			b;
}	t_sphere;

typedef struct s_plane
{
	float		x;
	float		y;
	float		z;
	float		norm_x;
	float		norm_y;
	float		norm_z;
	int			r;
	int			g;
	int			b;
	t_matrix	transform;
	t_matrix	tp_transform;
}	t_plane;

typedef struct s_cylinder
{
	float		x;
	float		y;
	float		z;
	float		axis_x;
	float		axis_y;
	float		axis_z;
	float		radius;
	float		height;
	int			r;
	int			g;
	int			b;
	t_matrix	transform;
	t_matrix	tp_transform;
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
		void		*shape;
	};
}	t_shape;

typedef struct s_intersection
{
	double					t;
	t_shape					*shape;
	struct s_intersection	*next;
}	t_intersection;

typedef struct s_environment
{
	t_list		*shapes;
	t_light		light;
	t_ambient	ambient;
	t_camera	camera;
}	t_environment;

typedef struct s_minirt
{
	void			*mlx;
	void			*window;
	t_mlxdata		data;
	int				width;
	int				height;
	t_environment	*env;
}	t_minirt;

t_minirt		*init(int width, int height);
void			deinit(t_minirt *minirt);
int				per_pixel(t_minirt *minirt, int x, int y);
void			pixel_put(t_mlxdata *data, int x, int y, int color);
int				keyboard_handler(int keycode, t_minirt *miniRT);
int				free_exit(t_minirt *minirt);

// Parsing

// Lights
void			parsing(t_environment *env, const char *file);
double			ft_atof(char *str);
int				is_valid_number(char *str);
void			parse_ambient(char *line, t_ambient *ambient);
char			*remove_extra_spaces(const char *line);
char			**split_by_char(char *space_rem, char deli, int exp_count);
int				split_rgb(char *rgb, int *r, int *g, int *b);
int				rgbtoint(t_tuple color);

void			parse_camera(char *line, t_camera *camera);
void			parse_light(char *line, t_light *light);
int				split_xyz(char *xyz, float *x, float *y, float *z);
void			parse_plane(char *line, t_environment *env);
void			parse_sphere(char *line, t_environment *env);
t_sphere		*create_sphere(void);
void			parse_cylinder(char *line, t_environment *env);

// Debug fun, delete later
void			print_mat(t_matrix *mat);

// free functions
void			free_split(char **split);
void			free_cylinder2(t_cylinder *cylinder, char **split);
void			free_minirt(t_minirt *minirt);
void			free_env(t_environment *env);
void			free_intersections(t_intersection *head);
void			free_shapes(t_list **shapes);
void			free_shape(t_shape *shapes);
void			free_matrix(t_matrix *mat);
void			free_camera(t_camera *camera);
void			free_mlxdata(t_mlxdata *mlxdata);
void			free_light(t_light *light);
void			free_ambient(t_ambient *ambient);
void			free_ray(t_ray *ray);

//tuples
t_tuple			set_tuple(double x, double y, double z, double w);
t_tuple			set_point(double x, double y, double z);
t_tuple			set_vector(double x, double y, double z);
t_tuple			add_tuples(t_tuple t1, t_tuple t2);
t_tuple			sub_tuples(t_tuple t1, t_tuple t2);
t_tuple			mul_tuple(t_tuple t, double scalar);
t_tuple			negate_tuple(t_tuple t);
t_tuple			cross_tuple(t_tuple t1, t_tuple t2);
t_tuple			normalize_tuple(t_tuple t);
double			dot_tuple(t_tuple t1, t_tuple t2);
double			mag_tuple(t_tuple t);
t_tuple			scale_tuple(t_tuple tuple, double scalar);
bool			eq_tuples(t_tuple t1, t_tuple t2);
bool			eq(double f1, double f2);

//matrix
t_matrix		create_mat(int size);
t_matrix		identity_matrix(int size);
t_matrix		*copy_matrix(t_matrix *matrix);
t_matrix		mult_mat(t_matrix *a, t_matrix *b);
t_matrix		allocate_submat(int size);
t_matrix		submatrix(t_matrix *mat, int row, int col);
t_matrix		*determinant(t_matrix *mat);
t_matrix		inverse(t_matrix *mat);
t_matrix		transpose_mat(t_matrix *mat);
t_tuple			mult_mat_tuple(t_tuple *tuple, t_matrix *mat);
void			free_matrix(t_matrix *matrix);
void			fill_subm(t_matrix *mat, t_matrix *submat, int row, int col);
double			determinant_2x2(t_matrix *mat);
double			determinant_3x3(t_matrix *mat);
double			determinant_4x4(t_matrix *mat);
t_matrix		create_translation(t_tuple *tuple);
t_matrix		create_scaling(t_tuple *tuple);
t_matrix		create_rotation(t_tuple vec);
t_matrix		rotation_x(double agnle);
t_matrix		rotation_y(double agnle);
t_matrix		rotation_z(double agnle);


	// Rays
	t_ray *create_ray(t_tuple origin, t_tuple direction);
t_tuple			position(t_ray *ray, double t);
t_ray			transform_ray(t_ray ray, t_matrix matrix);
void			add_intersection(t_intersection **head, t_shape *shape, \
	double t);
t_shape			*create_shape_ref(void	*shape, t_shapeType type);
t_intersection	*intersect(t_ray *ray, t_list *shapelist);
t_intersection	*intersect_sphere(t_ray *ray, t_sphere *_sphere, \
	t_intersection *intersections);
t_intersection	*closest_hit(t_intersection	*list);
t_ray			generate_ray(t_minirt *minirt, int x, int y);
t_intersection	*intersect_cylinder(t_ray *ray, t_cylinder *cy, \
	t_intersection *intersections);
t_intersection	*intersect_plane(t_ray *ray, t_plane *plane, \
	t_intersection *head);
void			init_cylinder(t_cylinder *cy);
void			init_camera(t_camera *camera);
void			init_plane(t_plane *pl);
t_ray			apply_ray_transform(t_ray *old_ray, t_tuple translation);
double			get_brightness(t_minirt *minirt, t_tuple hit_point, t_tuple normal);
t_tuple			get_sphere_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_sphere *sp);
t_tuple			get_cylinder_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_cylinder *cy);
t_tuple			get_plane_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_plane *pl);
t_tuple			get_color(t_minirt *minirt, t_ray *ray, t_intersection *intersection);

#endif
