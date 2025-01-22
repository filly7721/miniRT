/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:21:18 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 10:21:59 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_minirt	*init(int width, int height)
{
	t_minirt	*minirt;

	minirt = ft_calloc(sizeof(t_minirt), 1);
	if (!minirt)
		return (NULL);
	minirt->mlx = mlx_init();
	if (!minirt->mlx)
		return (deinit(minirt), NULL);
	minirt->window = mlx_new_window(minirt->mlx, width, height, "example");
	if (!minirt->window)
		return (deinit(minirt), NULL);
	minirt->data.img = mlx_new_image(minirt->mlx, width, height);
	if (!minirt->data.img)
		return (deinit(minirt), NULL);
	minirt->data.addr = mlx_get_data_addr(minirt->data.img, \
		&minirt->data.bits_per_pixel, &minirt->data.line_length, \
		&minirt->data.endian);
	if (!minirt->data.addr)
		return (deinit(minirt), NULL);
	minirt->width = width;
	minirt->height = height;
	return (minirt);
}

void	deinit(t_minirt *minirt)
{
	if (minirt->data.img)
		mlx_destroy_image(minirt->mlx, minirt->data.img);
	if (minirt->window)
		mlx_destroy_window(minirt->mlx, minirt->window);
	free(minirt->mlx);
	free(minirt);
}

int	free_exit(t_minirt *minirt)
{
	deinit(minirt);
	exit(0);
	return (0);
}
