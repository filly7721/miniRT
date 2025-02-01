/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:51:38 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 10:48:18 by bmakhama         ###   ########.fr       */
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
			ft_putstr_fd("Error: plane expected token\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

t_plane	*create_plane(void)
{
	t_plane	*plane;

	plane = ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		ft_putstr_fd("Error: Memory allocation failed for plane.\n", 2);
	return (plane);
}

int	parse_plane_values(char **split, t_plane *plane)
{
	if (!split_xyz(split[1], &plane->x, &plane->y, &plane->z))
	{
		ft_putstr_fd("Plane: Invalid XYZ values.\n", 2);
		return (0);
	}
	if (!split_xyz(split[2], &plane->norm_x, &plane->norm_y, &plane->norm_z))
	{
		ft_putstr_fd("Plane: Invalid NORM_XYZ values.\n", 2);
		return (0);
	}
	if (!split_rgb(split[3], &plane->r, &plane->g, &plane->b))
	{
		ft_putstr_fd("Plane: Invalid RGB values.\n", 2);
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
		ft_putstr_fd("Error: Memory allocation failed for shape.\n", 2);
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
		exit(1);
	}
	add_plane_to_env(env, plane);
	free_split (split);
}
