/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:38 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/29 15:11:01 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_plane(char **split)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!split[i])
		{
			printf("Error: Missing expected token at position %d.\n", i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

t_plane	*create_plane(void)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		printf("Error: Memory allocation failed for plane.\n");
	return (plane);
}

int	parse_plane_values(char **split, t_plane *plane)
{
	if (!split_xyz(split[1], &plane->x, &plane->y, &plane->z))
	{
		printf("Plane: Invalid XYZ values.\n");
		return (0);
	}
	if (!split_xyz(split[2], &plane->norm_x, &plane->norm_y, &plane->norm_z))
	{
		printf("Plane: Invalid NORM_XYZ values.\n");
		return (0);
	}
	if (!split_rgb(split[3], &plane->r, &plane->g, &plane->b))
	{
		printf("Plane: Invalid RGB values.\n");
		return (0);
	}
	return (1);
}

void	add_plane_to_env(t_environment *env, t_plane *_plane)
{
	t_shape	*shapes;

	shapes = malloc(sizeof(t_shape));
	if (!shapes)
	{
		printf("Error: Memory allocation failed for shape.\n");
		free(_plane);
		return ;
	}
	shapes->type = plane;
	shapes->plane = _plane;
	ft_lstadd_back(&env->shapes, ft_lstnew(shapes));
}

void	parse_plane(char *line, t_environment *env)
{
	char	**split;
	char	*space_removed;
	t_plane	*plane;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return ;
	split = split_by_char(space_removed, ' ', 4);
	free(space_removed);
	if (!split)
		return ;
	if (!split || !validate_plane(split))
		return (free_split(split));
	plane = create_plane();
	if (!plane)
		return (free_split(split));
	if (!parse_plane_values(split, plane))
	{
		free(plane);
		free_split(split);
		return ;
	}
	add_plane_to_env(env, plane);
	// printf("plane: x: %f, y: %f, z: %f, norm_x: %f, norm_y: %f, norm_z: %f \n", plane->x, plane->y, plane->z, plane->norm_x, plane->norm_y, plane->norm_z);
	free_split (split);
}
