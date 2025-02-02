/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:45:13 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/02 09:48:31 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	split_xyz(char *xyz, float *x, float *y, float *z)
{
	char	**split_xyz;
	int		i;

	split_xyz = split_by_char(xyz, ',', 3);
	if (!split_xyz)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_float(split_xyz[i]))
		{
			ft_putstr_fd("Invalid XYZ values\n", 2);
			free_split(split_xyz);
			return (0);
		}
		i++;
	}
	*x = ft_atof(split_xyz[0]);
	*y = ft_atof(split_xyz[1]);
	*z = ft_atof(split_xyz[2]);
	free_split(split_xyz);
	return (1);
}

int	split_dir_xyz(char *dir_xyz, float *dir_x, float *dir_y, float *dir_z)
{
	char	**split_dir_xyz;
	int		i;

	split_dir_xyz = split_by_char(dir_xyz, ',', 3);
	if (!split_dir_xyz)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_float(split_dir_xyz[i]))
		{
			free_split(split_dir_xyz);
			return (0);
		}
		i++;
	}
	*dir_x = ft_atof(split_dir_xyz[0]);
	*dir_y = ft_atof(split_dir_xyz[1]);
	*dir_z = ft_atof(split_dir_xyz[2]);
	free_split(split_dir_xyz);
	return (1);
}

bool	parse_camera(char *line, t_camera *cam)
{
	char	**split;
	char	*space_removed;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return (false);
	split = split_by_char(space_removed, ' ', 4);
	free(space_removed);
	if (!split)
		return (ft_putstr_fd("Error\n", 2), false);
	if (!is_valid_float(split[3]))
		return (ft_putstr_fd("Camera: Invalid FOV\n", 2), false);
	cam->fov = ft_atof(split[3]);
	if (!split_xyz(split[1], &cam->x, &cam->y, &cam->z))
		return (ft_putstr_fd("Camera: Invalid XYZ values.\n", 2),
			free_split(split), false);
	if (!split_dir_xyz(split[2], &cam->dir_x, &cam->dir_y, &cam->dir_z))
		return (ft_putstr_fd("Error: Invalid DIR_XYZ values.\n", 2),
			free_split(split), false);
	free_split(split);
	return (true);
}

bool	validate_camera(t_environment *env)
{
	t_tuple	camera_dir;

	if (!is_valid_rot(env->camera.dir_x, env->camera.dir_y, env->camera.dir_z))
		return (ft_putstr_fd("invalid camera values\n", 2), false);
	if (env->camera.fov > 180 || env->camera.fov <= 0)
		return (ft_putstr_fd("invalid camera values\n", 2), false);
	camera_dir = normalize_tuple(camera_dir);
	camera_dir = set_vector(env->camera.dir_x,
			env->camera.dir_y, env->camera.dir_z);
	env->camera.dir_x = camera_dir.x;
	env->camera.dir_y = camera_dir.y;
	env->camera.dir_z = camera_dir.z;
	return (true);
}
