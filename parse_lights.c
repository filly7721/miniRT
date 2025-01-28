/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:32:08 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 11:15:01 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_ambient(t_ambient *ambient)
{
	if (ambient->intensity < 0.0 || ambient->intensity > 1.0)
	{
		printf("Error: Intensity out of range [0.0, 1.0].\n");
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
	if (!split)
		return ;
	ambient->intensity = strtof(split[1], NULL); //change to ft_strtof
	if (!validate_ambient(ambient))
	{
		free_split(split);
		return ;
	}
	if (!split_rgb(split[2], &ambient->r, &ambient->g, &ambient->b))
	{
		printf("Error: Invalid RGB values.\n");
		free_split(split);
		return ;
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
	if (!split)
		return ;
	light->bright = strtof(split[2], NULL);
	if (!split_xyz(split[1], &light->x, &light->y, &light->z))
	{
		printf("Light: Invalid XYZ values.\n");
		free_split(split);
		return ;
	}
	if (!split_rgb(split[3], &light->r, &light->g, &light->b))
	{
		printf("Light: Invalid RGB values.\n");
		free_split(split);
		return ;
	}
	free_split(split);
}
