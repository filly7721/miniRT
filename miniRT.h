#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>

typedef struct s_mlxdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlxdata;

typedef struct s_minirt
{
	void		*mlx;
	void		*window;
	t_mlxdata	data;
	int			width;
	int			height;
}	t_minirt;

typedef struct s_camera
{
}	t_camera;

typedef struct s_light
{
}	t_light;

typedef struct s_sphere
{
}	t_sphere;

typedef struct s_plane
{
}	t_plane;

typedef struct s_cylinder
{
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

typedef struct s_environment
{
	t_list		*shapes;
	t_light		light;
	t_camera	camera;
}	t_environment;

t_minirt	*init(int width, int height);
void		deinit(t_minirt *minirt);
int			keyboard_handler(int keycode, t_minirt *miniRT);
int			free_exit(t_minirt *minirt);

#endif