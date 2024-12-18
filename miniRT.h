#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>


typedef struct	s_mlxdata {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlxdata;

typedef struct s_minirt
{
	void		*mlx;
	void		*window;
	t_mlxdata	data;
}	t_minirt;

t_minirt	*init();
void		deinit(t_minirt *minirt);


#endif