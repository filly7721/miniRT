/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:19:48 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 12:26:39 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	line_parsing(char *line, t_environment *env)
{
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line++;
	if (*line == '\0' || *line == '#')
		return (true);
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_ambient(line, &env->ambient));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (parse_camera(line, &env->camera));
	else if (ft_strncmp(line, "L", 1) == 0)
		return (parse_light(line, &env->light));
	else if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_plane(line, env));
	else if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_sphere(line, env));
	else if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_cylinder(line, env));
	else
	{
		ft_putstr_fd("Error: Unknown element type \n", 2);
		return (false);
	}
}

int	valid_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || \
		b < 0 || b > 255)
		return (0);
	return (1);
}

int	valid_rot(double x, double y, double z)
{
	if (x == 0 && y == 0 && z == 0)
		return (0);
	return (1);
}

int	valid_input(t_environment *env)
{
	t_shape	*sh;
	t_list	*current;

	current = env->shapes;
	if (!env->camera.fov || (env->camera.fov < 0 || env->camera.fov > 180))
		return (0);
	else if (!light_ratio(env))
		return (0);
	while (current)
	{
		sh = (t_shape *)current->content;
		if ((sh->type == cylinder) && !(valid_rgb(sh->cylinder->r, \
		sh->cylinder->g, sh->cylinder->b) && valid_rot(sh->cylinder->axis_x, \
		sh->cylinder->axis_y, sh->cylinder->axis_z)))
			return (0);
		else if ((sh->type == sphere) && !valid_rgb(sh->sphere->r, \
			sh->sphere->g, sh->sphere->b))
			return (0);
		else if ((sh->type == plane) && !(valid_rgb(sh->plane->r, \
			sh->plane->g, sh->plane->b) && valid_rot(sh->plane->norm_x, \
			sh->plane->norm_y, sh->plane->norm_z)))
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
		(ft_putstr_fd("Error opening file", 2), exit(1));
	line = get_next_line(fd);
	while (line)
	{
		if (line_parsing(line, env) == false)
			(free(line), free_env(env), exit(1));
		free(line);
		line = get_next_line(fd);
	}
	if (!valid_input(env))
	{
		ft_putstr_fd("Invalid input\n", 2);
		free_env(env);
		exit (1);
	}
	close(fd);
}
