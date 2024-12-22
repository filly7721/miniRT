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
	int			width;
	int			height;
}	t_minirt;

t_minirt	*init(int width, int height);
void		deinit(t_minirt *minirt);
int			keyboard_handler(int keycode, t_minirt *miniRT);
int			free_exit(t_minirt *minirt);


#endif