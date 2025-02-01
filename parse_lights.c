/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:32:08 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 12:13:18 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	validate_ambient(t_ambient *ambient)
{
	if (ambient->intensity < 0.0 || ambient->intensity > 1.0)
	{
		ft_putstr_fd("Error: Intensity out of range [0.0, 1.0].\n", 2);
		return (false);
	}
	return (true);
}

bool	parse_ambient(char *line, t_ambient *ambient)
{
	char	**split;
	char	*space_removed;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return (ft_putstr_fd("Error\n", 2), false);
	split = split_by_char(space_removed, ' ', 3);
	free(space_removed);
	if (!split)
		return (ft_putstr_fd("Error\n", 2), false);
	if (!is_valid_number(split[1]))
		return (ft_putstr_fd("Invalid ambient intensity\n", 2),
			free_split(split), false);
	ambient->intensity = ft_atof(split[1]);
	if (!validate_ambient(ambient))
		return (ft_putstr_fd("Invalid values\n", 2), free_split(split), false);
	if (!split_rgb(split[2], &ambient->r, &ambient->g, &ambient->b))
		return (ft_putstr_fd("Invalid values\n", 2), free_split(split), false);
	free_split(split);
	return (true);
}

bool	parse_light(char *line, t_light *light)
{
	char	**split;
	char	*space_removed;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return (ft_putstr_fd("Error\n", 2), false);
	split = split_by_char(space_removed, ' ', 4);
	free(space_removed);
	if (!split)
		return (ft_putstr_fd("Error\n", 2), false);
	if (!is_valid_number(split[2]))
		return (free_split(split),
			ft_putstr_fd("Light: Invalid brightness.\n", 2), false);
	light->bright = ft_atof(split[2]);
	if (!split_xyz(split[1], &light->x, &light->y, &light->z))
		return (free_split(split),
			ft_putstr_fd("Light: Invalid coords.\n", 2), false);
	if (!split_rgb(split[3], &light->r, &light->g, &light->b))
		return (free_split(split),
			ft_putstr_fd("Light: Invalid colors.\n", 2), false);
	free_split(split);
	return (true);
}
