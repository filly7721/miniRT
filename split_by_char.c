/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:29:53 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/30 12:49:04 by bmakhama         ###   ########.fr       */
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
		printf("Error: ft_split returned NULL.\n");
		return (NULL);
	}
	while (i < exp_count)
	{
		if (!split[i])
		{
			printf("Error: Not enough tokens.\n");
			free_split(split);
			exit(1);
		}
		i++;
	}
	return (split);
}

int	split_rgb(char *rgb, int *r, int *g, int *b)
{
	char	**split_rgb;
	int		i;

	split_rgb = split_by_char(rgb, ',', 3);
	if (!split_rgb)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_number(split_rgb[i]))
		{
			printf("Invalid RGB values. %s\n", split_rgb[i]);
			free_split(split_rgb);
			return (0);
		}
		i++;
	}
	*r = ft_atoi(split_rgb[0]);
	*g = ft_atoi(split_rgb[1]);
	*b = ft_atoi(split_rgb[2]);
	free_split(split_rgb);
	return (1);
}

int is_valid_number( char *str)
{
    int i;
    int has_dot;

	i = 0;
    if (!str || !str[i])
        return (0);
    if (str[i] == '-')
        i++;
	has_dot = 0;
    while (str[i])
    {
        if (str[i] == '.')
        {
            if (has_dot)
                return (0);
            has_dot = 1;
        }
        else if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}
