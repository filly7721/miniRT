/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:19:48 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 11:20:40 by bmakhama         ###   ########.fr       */
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
	close(fd);
}
