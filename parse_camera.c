/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:45:13 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/30 11:22:52 by bmakhama         ###   ########.fr       */
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
		if (!is_valid_number(split_xyz[i]))
		{
			printf("Invalid XYZ values: %s\n", split_xyz[i]);
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
		if (!is_valid_number(split_dir_xyz[i]))
		{
			printf("Invalid DIR_XYZ values: %s\n", split_dir_xyz[i]);
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

void	parse_camera(char *line, t_camera *cam)
{
	char	**split;
	char	*space_removed;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return ;
	split = split_by_char(space_removed, ' ', 4);
	free(space_removed);
	if (!split)
		return ;
	cam->fov = ft_atoi(split[3]);
	if (!split_xyz(split[1], &cam->x, &cam->y, &cam->z))
	{
		printf("Camera: Invalid XYZ values.\n");
		free_split(split);
		return ;
	}
	if (!split_dir_xyz(split[2], &cam->dir_x, &cam->dir_y, &cam->dir_z))
	{
		printf("Error: Invalid DIR_XYZ values.\n");
		free_split(split);
		return ;
	}
	free_split(split);
}
