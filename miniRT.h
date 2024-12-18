#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <stdlib.h>


typedef struct	s_mlxdata {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlxdata;

typedef struct s_mlx
{
	void		*instance;
	void		*window;
	t_mlxdata	data;
}	t_mlx;

#endif