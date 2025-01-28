/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:19:48 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/28 11:47:08 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	line_parsing(char *line, t_environment *env)
{
	if (ft_strncmp(line, "A", 1) == 0)
		parse_ambient(line, &env->ambient);
	else if (ft_strncmp(line, "C", 1) == 0)
		parse_camera(line, &env->camera);
	else if (ft_strncmp(line, "L", 1) == 0)
		parse_light(line, &env->light);
	else if (ft_strncmp(line, "pl", 2) == 0)
		parse_plane(line, env);
	else if (ft_strncmp(line, "sp", 2) == 0)
		parse_sphere(line, env);
	else if (ft_strncmp(line, "cy", 2) == 0)
		parse_cylinder(line, env);
	else
		printf("Error: Unknown element type in line: %s\n", line);
}

int	light_ratio(t_environment *env)
{
	if (env->ambient.intensity < 0.0 || env->ambient.intensity > 1.0)
		return (0);
	else if (env->light.bright < 0.0 || env->light.bright > 1.0)
		return (0);
	return (1);
}

int	valid_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || \
		b < 0 || b > 255)
		return (0);
	return (1);
}

int	valid_input(t_environment *env)
{
	t_shape	*shape;
	t_list	*current;

	current = env->shapes;
	if (!env->camera.fov)
		return (0);
	else if (!light_ratio(env))
		return (0);
	while (current)
	{
		shape = (t_shape *)current->content;
		if ((shape->type == cylinder) && !valid_rgb(shape->cylinder->r, \
			shape->cylinder->g, shape->cylinder->b))
			return (0);
		else if ((shape->type == sphere) && !valid_rgb(shape->sphere->r, \
			shape->sphere->g, shape->sphere->b))
			return (0);
		else if ((shape->type == plane) && !valid_rgb(shape->plane->r, \
			shape->plane->g, shape->plane->b))
			return (0);
		current = current->next;
	}
	return (1);
}

void	parsing(t_environment *env, const char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		line_parsing(line, env);
		free(line);
		line = get_next_line(fd);
	}
	if (!valid_input(env))
	{
		printf ("Invalid input\n");
		free_env(env);
		exit (1);
	}
	close(fd);
}
