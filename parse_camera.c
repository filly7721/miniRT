/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:45:13 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/10 15:06:49 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int split_xyz(char* xyz, float* x, float* y, float* z)
{
    char** split_xyz;

    split_xyz = split_by_char(xyz, ',', 3);
    if (!split_xyz)
        return (0);
    *x = strtof(split_xyz[0], NULL);
    *y = strtof(split_xyz[1], NULL);
    *z = strtof(split_xyz[2], NULL);
    free_split(split_xyz);
    return (1);
}

int split_dir_xyz(char* dir_xyz, float* dir_x, float* dir_y, float* dir_z)
{
    char** split_dir_xyz;

    split_dir_xyz = split_by_char(dir_xyz, ',', 3);
    if (!split_dir_xyz)
        return (0);
    *dir_x = strtof(split_dir_xyz[0], NULL);
    *dir_y = strtof(split_dir_xyz[1], NULL);
    *dir_z = strtof(split_dir_xyz[2], NULL);
    free_split(split_dir_xyz);
    return (1);
}

void parse_camera(char* line, t_camera* camera)
{
    char** split;
    char* space_removed;

    (void) camera;
    space_removed  = remove_extra_spaces(line);
    if (!space_removed)
        return ;
    split = split_by_char(space_removed, ' ', 3);
    free(space_removed);
    if (!split)
        return ;
    camera->fov = ft_atoi(split[3]);
    printf("struct: %d\n", camera->fov);
    //Valiate camera(check the inputs)
    if (!split_xyz(split[2], &camera->x, &camera->y, &camera->z))
    {
        printf("Error: Invalid camera XYZ values.\n");
        free_split(split);
        return;
    }
    if (!split_dir_xyz(split[3], &camera->dir_x, &camera->dir_y, &camera->dir_z))
    {
        printf("Error: Invalid camera XYZ values.\n");
        free_split(split);
        return;
    }
    printf("Camera: x: %f, y: %f, z: %f\n", camera->x, camera->y, camera->z);
}
