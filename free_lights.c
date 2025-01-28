/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:15:48 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/28 09:29:34 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_ray(t_ray *ray)
{
	if (ray)
		free(ray);
}

void	free_ambient(t_ambient *ambient)
{
	if (ambient)
		free(ambient);
}

void	free_light(t_light *light)
{
	if (light)
		free(light);
}

void	free_mlxdata(t_mlxdata *mlxdata)
{
	if (mlxdata)
		free(mlxdata);
}

void	free_camera(t_camera *camera)
{
	if (camera)
		free(camera);
}
