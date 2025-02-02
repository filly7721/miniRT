/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:24:48 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 12:23:14 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_cylinder(char **split)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!split[i])
		{
			ft_putstr_fd("Error: cylinder expected token.\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

t_cylinder	*create_cylinder(void)
{
	t_cylinder	*cylinder;

	cylinder = ft_calloc(sizeof(t_cylinder), 1);
	if (!cylinder)
		ft_putstr_fd("Error: Memory allocation failed for plane.\n", 2);
	return (cylinder);
}

int	parse_cylinder_values(char **split, t_cylinder *cyl)
{
	if (!split_xyz(split[1], &cyl->x, &cyl->y, &cyl->z))
	{
		ft_putstr_fd("cylinder: Invalid XYZ values.\n", 2);
		return (0);
	}
	if (!split_xyz(split[2], &cyl->axis_x, &cyl->axis_y, &cyl->axis_z))
	{
		ft_putstr_fd("cylinder: Invalid Axis XYZ values.\n", 2);
		return (0);
	}
	if (!is_valid_float(split[3]) || !is_valid_float(split[4]))
	{
		ft_putstr_fd("Invalid cy radius or height\n", 2);
		return (0);
	}
	cyl->radius = ft_atof(split[3]);
	cyl->height = ft_atof(split[4]);
	if (!split_rgb(split[5], &cyl->r, &cyl->g, &cyl->b))
	{
		ft_putstr_fd("cylinder: Invalid RGB values.\n", 2);
		return (0);
	}
	return (1);
}

void	add_cylinder_to_env(t_environment*env, t_cylinder *_cylinder)
{
	t_shape	*shape;

	shape = malloc(sizeof(t_shape));
	if (!shape)
	{
		ft_putstr_fd("Error: Memory allocation failed for shape.\n", 2);
		free(_cylinder);
		return ;
	}
	shape->type = cylinder;
	shape->cylinder = _cylinder;
	ft_lstadd_back(&env->shapes, ft_lstnew(shape));
}

bool	parse_cylinder(char *line, t_environment *env)
{
	char		**split;
	char		*space_removed;
	t_cylinder	*cylinder;

	space_removed = remove_extra_spaces(line);
	if (!space_removed)
		return (ft_putstr_fd("Error\n", 2), false);
	split = split_by_char(space_removed, ' ', 6);
	free(space_removed);
	if (!split)
		return (ft_putstr_fd("Error\n", 2), false);
	if (!split || !validate_cylinder(split))
		return (ft_putstr_fd("Error\n", 2), free_split(split), false);
	cylinder = create_cylinder();
	if (!parse_cylinder_values(split, cylinder))
	{
		free(cylinder);
		free_split(split);
		return (false);
	}
	add_cylinder_to_env(env, cylinder);
	free_split(split);
	return (true);
}
