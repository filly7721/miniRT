/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:29:53 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/10 14:38:13 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// #include  <string.h> 
// #include <ctype.h> 

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char *remove_extra_spaces(const char *line)
{
    int i = 0, j = 0;
    char *removed;

    removed = ft_calloc(ft_strlen(line) + 1, sizeof(char));
    if (!removed)
        return (NULL);
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

char** split_by_char(char* space_removed, char delimiter, int expected_count)
{
    char**split;
    int i;
    
    i = 0;
    split = ft_split(space_removed, delimiter);
    if (!split)
    {
        printf("Error: ft_split returned NULL.\n");
        return NULL;
    }
    while (i < expected_count)
    {
        if (!split[i])
        {
            printf("Error: Missing expected token at position %d.\n", i + 1);
            free_split(split);
            return NULL;
        }
        i++;
    }
    return (split);
}

int split_rgb(char* rgb, int* r, int* g, int* b)
{
    char** split_rgb;

    split_rgb = split_by_char(rgb, ',', 3);
    if (!split_rgb)
        return (0);
    *r = ft_atoi(split_rgb[0]);
    *g = ft_atoi(split_rgb[1]);
    *b = ft_atoi(split_rgb[2]);
    free(split_rgb);
    return (1);
}
