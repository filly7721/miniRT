/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:19:16 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 12:23:54 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_sphere(char **split)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!split[i])
		{
			ft_putstr_fd("Error: sphere expected token\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

t_sphere	*create_sphere(void)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		ft_putstr_fd("Error: Memory allocation failed for sphere.\n", 2);
	return (sphere);
}

int	parse_sphere_values(char **split, t_sphere *sphere)
{
	if (!is_valid_number(split[2]))
	{
		ft_putstr_fd("Invalid sphere diameter", 2);
		return (0);
	}
	sphere->diameter = ft_atof(split[2]);
	if (!split_xyz(split[1], &sphere->x, &sphere->y, &sphere->z))
	{
		ft_putstr_fd("sphere: Invalid XYZ values.\n", 2);
		return (0);
	}
	if (!split_rgb(split[3], &sphere->r, &sphere->g, &sphere->b))
	{
		ft_putstr_fd("sphere: Invalid RGB values.\n", 2);
		return (0);
	}
	return (1);
}

void	add_sphere_to_env(t_environment *env, t_sphere *_sphere)
{
	t_shape	*shape;

	shape = malloc(sizeof(t_shape));
	if (!shape)
	{
		ft_putstr_fd("Error: Memory allocation failed for shape.\n", 2);
		free(_sphere);
		return ;
	}
	shape->type = sphere;
	shape->sphere = _sphere;
	ft_lstadd_back(&env->shapes, ft_lstnew(shape));
}

bool	parse_sphere(char *line, t_environment *env)
{
	char		**split;
	char		*space_removed;
	t_sphere	*sphere;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return (ft_putstr_fd("Error\n", 2), false);
	split = split_by_char(space_removed, ' ', 4);
	free(space_removed);
	if (!split)
		return (ft_putstr_fd("Error\n", 2), false);
	if (!split || !validate_sphere(split))
		return (ft_putstr_fd("Error\n", 2), free_split(split), false);
	sphere = create_sphere();
	if (!sphere)
		return (ft_putstr_fd("Error\n", 2), free_split(split), false);
	if (!parse_sphere_values(split, sphere))
		return (free(sphere), free_split(split), false);
	add_sphere_to_env(env, sphere);
	free_split(split);
	return (true);
}
