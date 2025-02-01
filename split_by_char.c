/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:29:53 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 12:32:36 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r');
}

char	*remove_extra_spaces(const char *line)
{
	int		i;
	int		j;
	char	*removed;

	removed = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!removed)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!(ft_isspace(line[i]) && (i == 0 || ft_isspace(line[i - 1]))))
		{
			if (ft_isspace(line[i]))
				removed[j++] = ' ';
			else
				removed[j++] = line[i];
		}
		i++;
	}
	if (j > 0 && removed[j - 1] == ' ')
		removed[j - 1] = '\0';
	return (removed);
}

char	**split_by_char(char *space_rem, char deli, int exp_count)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(space_rem, deli);
	if (!split)
	{
		ft_putstr_fd("Error: ft_split returned NULL.\n", 2);
		return (NULL);
	}
	while (i < exp_count)
	{
		if (!split[i])
		{
			ft_putstr_fd("Error: Not enough tokens.\n", 2);
			free_split(split);
			exit(1);
		}
		i++;
	}
	return (split);
}

bool	split_rgb(char *rgb, int *r, int *g, int *b)
{
	char	**split_rgb;
	int		i;

	split_rgb = split_by_char(rgb, ',', 3);
	if (!split_rgb)
		return (false);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_number(split_rgb[i]))
		{
			ft_putstr_fd("Invalid RGB values.\n", 2);
			free_split(split_rgb);
			return (false);
		}
		i++;
	}
	*r = ft_atoi(split_rgb[0]);
	*g = ft_atoi(split_rgb[1]);
	*b = ft_atoi(split_rgb[2]);
	free_split(split_rgb);
	return (true);
}

bool	is_valid_number( char *str)
{
	int		i;
	bool	has_dot;

	i = 0;
	if (!str || !str[i])
		return (false);
	if (str[i] == '-')
		i++;
	has_dot = false;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (false);
			has_dot = true;
		}
		else if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
