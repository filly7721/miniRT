/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:32:08 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 10:50:38 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_ambient(t_ambient *ambient)
{
	if (ambient->intensity < 0.0 || ambient->intensity > 1.0)
	{
		ft_putstr_fd("Error: Intensity out of range [0.0, 1.0].\n", 2);
		return (0);
	}
	return (1);
}

void	parse_ambient(char *line, t_ambient *ambient)
{
	char	**split;
	char	*space_removed;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return ;
	split = split_by_char(space_removed, ' ', 3);
	free(space_removed);
	if (!is_valid_number(split[1]))
	{
		ft_putstr_fd("Invalid ambient intensity\n", 2);
		exit(1);
	}
	ambient->intensity = ft_atof(split[1]);
	if (!validate_ambient(ambient))
	{
		free_split(split);
		exit(1);
	}
	if (!split_rgb(split[2], &ambient->r, &ambient->g, &ambient->b))
	{
		free_split(split);
		exit(1);
	}
	free_split(split);
}

void	parse_light(char *line, t_light *light)
{
	char	**split;
	char	*space_removed;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return ;
	split = split_by_char(space_removed, ' ', 4);
	free(space_removed);
	if (!is_valid_number(split[2]))
	{
		ft_putstr_fd("Light: Invalid brightness.\n", 2);
		exit(1);
	}
	light->bright = ft_atof(split[2]);
	if (!split_xyz(split[1], &light->x, &light->y, &light->z))
	{
		free_split(split);
		exit(1);
	}
	if (!split_rgb(split[3], &light->r, &light->g, &light->b))
	{
		free_split(split);
		exit(1);
	}
	free_split(split);
}
