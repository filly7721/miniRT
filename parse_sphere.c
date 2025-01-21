/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:19:16 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/21 16:24:06 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int validate_sphere(char** split)
{
    int i;

    i = 0;
    while (i < 4)
    {
        //here can add more validation
        if (!split[i])
        {
            printf("Error: Missing expected token at position %d.\n", i + 1);
            return (0);
        }
        i++;
    }
    return (1);
}
t_sphere* create_sphere()
{
    t_sphere* sphere;

    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        printf("Error: Memory allocation failed for sphere.\n");
    return (sphere);
}

int parse_sphere_values(char** split, t_sphere* sphere)
{
    sphere->diameter = strtof(split[2], NULL);
    if (!split_xyz(split[1], &sphere->x, &sphere->y, &sphere->z))
    {
        printf("sphere: Invalid XYZ values.\n");
        return (0);
    }
    if (!split_rgb(split[3], &sphere->r, &sphere->g, &sphere->b))
    {
        printf("sphere: Invalid RGB values.\n");
        return (0);
    }
    return (1);
}

void add_sphere_to_env(t_environment* env, t_sphere* _sphere)
{
    t_shape* shape;
    
    shape = malloc(sizeof(t_shape));
    if(!shape)
    {
        printf("Error: Memory allocation failed for shape.\n");
        free(_sphere);
        return ;
    }
    shape->type = sphere;
    shape->sphere = _sphere;
    ft_lstadd_back(&env->shapes, ft_lstnew(shape));
}

void parse_sphere(char* line, t_environment* env)
{
    char** split;
    char* space_removed;
    t_sphere* sphere;

    space_removed = remove_extra_spaces(line);
    if (!space_removed)
        return ;
    split = split_by_char(space_removed, ' ', 4);
    free(space_removed);
    if (!split)
        return ;
    if (!split || !validate_sphere(split))
        return (free_split(split));
    sphere = create_sphere();
    if(!sphere)
        return (free_split(split));
    if (!parse_sphere_values(split, sphere))
        return (free(sphere), free_split(split));
    add_sphere_to_env(env, sphere);
    free_split(split);
    printf("Shpere: x: %f, y: %f, z: %f, D: %f, r: %i, g: %i, b: %i\n", 
        sphere->x, sphere->y, sphere->z, sphere->diameter, 
        sphere->r, sphere->g, sphere->b);
}
