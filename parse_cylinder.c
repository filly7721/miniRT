/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:24:48 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/12 16:52:42 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int validate_cylinder(char** split)
{
    int i;

    i = 0;
    while (i < 6)
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

t_cylinder* create_cylinder()
{
    t_cylinder* cylinder;

    cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        printf("Error: Memory allocation failed for plane.\n");
    return (cylinder);
}

int parse_cylinder_values(char** split, t_cylinder* cylinder)
{

    if (!split_xyz(split[1], &cylinder->x, &cylinder->y, &cylinder->z))
    {
        printf("cylinder: Invalid XYZ values.\n");
        return (0);
    }
    if (!split_xyz(split[2], &cylinder->axis_x, &cylinder->axis_y, &cylinder->axis_z))
    {
        printf("cylinder: Invalid Axis XYZ values.\n");
        return (0);
    }
    cylinder->radius = strtof(split[3], NULL);
    cylinder->height = strtof(split[4], NULL);
    if (!split_rgb(split[5], &cylinder->r, &cylinder->g, &cylinder->b))
    {
        printf("cylinder: Invalid RGB values.\n");
        return (0);
    }
    return (1);
}

void add_cylinder_to_env(t_environment*env, t_cylinder* _cylinder)
{
    t_shape* shape;
    
    shape = malloc(sizeof(t_shape));
    if(!shape)
    {
        printf("Error: Memory allocation failed for shape.\n");
        free(_cylinder);
        return ;
    }
    shape->type = cylinder;
    shape->cylinder = _cylinder;
    ft_lstadd_back(&env->shapes, ft_lstnew(shape));
}

void parse_cylinder(char* line, t_environment* env)
{
    char** split;
    char* space_removed;
    t_cylinder* cylinder;
    
    space_removed = remove_extra_spaces(line);
    if (!space_removed)
        return ;
    split = split_by_char(space_removed, ' ', 6);
    free(space_removed);
    if (!split)
        return ;
    if (!split || !validate_cylinder(split))
    {
        free_split(split);
        return ;
    }
    cylinder = create_cylinder();
    if (!cylinder)
    {
        free_split(split);
        return;
    }
    if (!parse_cylinder_values(split, cylinder))
    {
        free(cylinder);
        free_split(split);
        return ;
    }
    add_cylinder_to_env(env, cylinder);
    free_split(split);
    // printf("cylinder: x: %f, y: %f, z: %f, Axis_x: %f, Axis_y: %f, Axis_z: %f, R: %f, H: %f, r: %i, g: %i, b: %i\n", 
    //     cylinder->x, cylinder->y, cylinder->z,
    //     cylinder->axis_x, cylinder->axis_y, cylinder->axis_z,
    //     cylinder->radius, cylinder->height,
    //     cylinder->r, cylinder->g, cylinder->b);
}
