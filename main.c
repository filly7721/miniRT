#include "miniRT.h"

void	pixel_put(t_mlxdata *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		per_pixel(t_minirt *minirt, int x, int y)
{
	if (x > minirt->width / 4.0 && x < 3 * minirt->width / 4.0 && y > minirt->height / 4.0 && y < 3 * minirt->height / 4.0)
		return 0x0ffff000;
	return 0x00000fff;
}

// void	trace_rays(t_minirt *minirt, int width, int height)
// {
// 	int	x;
// 	int	y;
// 	int	color;

// 	y = 0;
// 	while (y < height)
// 	{
// 		x = 0;
// 		while (x < width)
// 		{
// 			color = per_pixel(minirt, x, y);
// 			pixel_put(&minirt->data, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }





t_minirt *init_minirt(int width, int height, t_environment *env)
{
    t_minirt *minirt;

    minirt = malloc(sizeof(t_minirt));
    if (!minirt)
        return (NULL);
    minirt->mlx = mlx_init();
    if (!minirt->mlx)
        return (free(minirt), NULL);
    minirt->window = mlx_new_window(minirt->mlx, width, height, "MiniRT");
    // if (!minirt->window)
    //     return (mlx_destroy_display(minirt->mlx), free(minirt), NULL);
    minirt->data.img = mlx_new_image(minirt->mlx, width, height);
    if (!minirt->data.img)
        return (mlx_destroy_window(minirt->mlx, minirt->window), free(minirt), NULL);
    minirt->data.addr = mlx_get_data_addr(minirt->data.img, &minirt->data.bits_per_pixel,
                                          &minirt->data.line_length, &minirt->data.endian);
    minirt->width = width;
    minirt->height = height;
    minirt->env = env;
    return (minirt);
}
//debug fun

void print_minirt(t_minirt *minirt)
{
    if (!minirt)
    {
        printf("Minirt is not initialized!\n");
        return;
    }

    // Print MLX details
    printf("MLX Initialized: %p\n", minirt->mlx);
    printf("Window: %p\n", minirt->window);
    printf("Width: %d\n", minirt->width);
    printf("Height: %d\n", minirt->height);

    // Print image data
    printf("Image Address: %p\n", minirt->data.addr);
    printf("Bits Per Pixel: %d\n", minirt->data.bits_per_pixel);
    printf("Line Length: %d\n", minirt->data.line_length);
    printf("Endianness: %d\n", minirt->data.endian);

    // Print environment details (assuming the structure is non-null)
    if (minirt->env)
    {
        printf("Environment Details:\n");

        // Ambient light details
        printf("Ambient light - Intensity: %.2f, Color: (%d, %d, %d)\n",
               minirt->env->ambient.intensity,
               minirt->env->ambient.r, minirt->env->ambient.g, minirt->env->ambient.b);

        // Camera details
        printf("Camera - Position: (%.2f, %.2f, %.2f), Direction: (%.2f, %.2f, %.2f), FOV: %d\n",
               minirt->env->camera.x, minirt->env->camera.y, minirt->env->camera.z,
               minirt->env->camera.dir_x, minirt->env->camera.dir_y, minirt->env->camera.dir_z,
               minirt->env->camera.fov);

        // Light details
        printf("Light - Position: (%.2f, %.2f, %.2f), Brightness: %.2f, Color: (%d, %d, %d)\n",
               minirt->env->light.x, minirt->env->light.y, minirt->env->light.z,
               minirt->env->light.bright,
               minirt->env->light.r, minirt->env->light.g, minirt->env->light.b);

        // Loop through all shapes in the environment and print each
        t_list *shape_node = minirt->env->shapes;
        while (shape_node != NULL)
        {
            t_shape *shape = (t_shape *)shape_node->content;
            switch (shape->type)
            {
                case sphere:
                    printf("Sphere - Position: (%.2f, %.2f, %.2f), Diameter: %.2f, Color: (%d, %d, %d)\n",
                           shape->sphere->x, shape->sphere->y, shape->sphere->z,
                           shape->sphere->diameter,
                           shape->sphere->r, shape->sphere->g, shape->sphere->b);
                    break;
                case plane:
                    printf("Plane - Position: (%.2f, %.2f, %.2f), Normal: (%.2f, %.2f, %.2f), Color: (%d, %d, %d)\n",
                           shape->plane->x, shape->plane->y, shape->plane->z,
                           shape->plane->norm_x, shape->plane->norm_y, shape->plane->norm_z,
                           shape->plane->r, shape->plane->g, shape->plane->b);
                    break;
                case cylinder:
                    printf("Cylinder - Position: (%.2f, %.2f, %.2f), Axis: (%.2f, %.2f, %.2f), Radius: %.2f, Height: %.2f, Color: (%d, %d, %d)\n",
                           shape->cylinder->x, shape->cylinder->y, shape->cylinder->z,
                           shape->cylinder->axis_x, shape->cylinder->axis_y, shape->cylinder->axis_z,
                           shape->cylinder->radius, shape->cylinder->height,
                           shape->cylinder->r, shape->cylinder->g, shape->cylinder->b);
                    break;
                default:
                    printf("Unknown shape type!\n");
                    break;
            }
            shape_node = shape_node->next;
        }
    }
    else
    {
        printf("No environment data linked to minirt.\n");
    }
}


// int main(int arc, char** arv)
// {
// 	if (arc != 2)
// 	{
// 		printf("The input must be 2!");
// 		return (1);
// 	}
// 	t_environment env;
// 	parsing(&env, arv[1]);
// 	// print_environment(&env);
// 	t_minirt	*minirt;

// 	minirt = init_minirt(1920, 1080, &env);
// 	if (!minirt)
// 		return (ft_putstr_fd("init error\n", 2), 1);
// 	print_minirt(minirt); // debug print
// 	// trace_rays(minirt, minirt->width, minirt->height);
// 	trace_rays(minirt);
// 	mlx_put_image_to_window(minirt->mlx, minirt->window, minirt->data.img, 0, 0);

// 	mlx_key_hook(minirt->window, keyboard_handler, minirt);
// 	mlx_hook(minirt->window, 17, 1L << 0, free_exit, minirt);
// 	mlx_loop(minirt->mlx);

// 	deinit(minirt);
// }

void trace_rays(t_minirt *minirt) {
    int canvas_pixels = 1000;
    double wall_z = 10.0;
    double wall_size = 7.0;
    double pixel_size = wall_size / canvas_pixels;
    double half = wall_size / 2.0;
    t_tuple ray_origin = set_tuple(0, 0, -5, 1);

    for (int y = 0; y < canvas_pixels; y++) {
        double world_y = half - pixel_size * y;

        for (int x = 0; x < canvas_pixels; x++) {
            double world_x = -half + pixel_size * x;

            t_tuple position = set_tuple(world_x, world_y, wall_z, 1);
            t_ray ray;
            ray.origin = ray_origin;
            ray.direction = normalize_tuple(sub_tuples(position, ray_origin));

            // // Debug print for the ray's origin and direction
            // printf("Ray Origin: (%.2f, %.2f, %.2f), Direction: (%.2f, %.2f, %.2f)\n",
            //        ray.origin.x, ray.origin.y, ray.origin.z,
            //        ray.direction.x, ray.direction.y, ray.direction.z);

            int r,g,b;
            // r = ray.direction.x * 255;
            // g = ray.direction.y * 255;
            // b = ray.direction.z * 255;
            ray.direction.w = 1;
            pixel_put(&minirt->data, x, y, rgbtoint(ray.direction));

            continue;
            t_intersection *intersections = NULL;
            t_list *current = minirt->env->shapes;

            // Traverse all shapes and find intersections
            while (current != NULL) {
                t_shape *shape = current->content;

                if (shape->type == sphere) {
                    printf("Checking intersection with sphere: center=(%.2f, %.2f, %.2f), radius=%.2f\n",
                           shape->sphere->x, shape->sphere->y, shape->sphere->z,
                           shape->sphere->diameter / 2.0);

                    t_intersection *hit_intersection = intersect(shape->sphere);
                    if (hit_intersection != NULL) {
                        add_node(&intersections, hit_intersection);
                        printf("Intersection found at t=%.2f\n", hit_intersection->t);
                    } else {
                        printf("No intersection found with sphere.\n");
                    }
                }

                current = current->next;
            }

            t_intersection *closest = hit(intersections);

            if (closest != NULL) {
                printf("Closest hit at t=%.2f for pixel (%d, %d)\n",
                       closest->t, x, y);
                pixel_put(&minirt->data, x, y, 0xFF0000);
            } else {
                printf("No hit at pixel (%d, %d)\n", x, y);
                pixel_put(&minirt->data, x, y, 0x000000);
            }

            // Free the intersections list after processing
            // free_intersections(intersections);
        }
    }
}


int main(int arc, char** arv) {
    if (arc != 2) {
        printf("The input must be 2!");
        return (1);
    }
    t_environment env;
    parsing(&env, arv[1]);
    t_minirt *minirt = init_minirt(1000, 1000, &env);
    if (!minirt) {
        return (ft_putstr_fd("init error\n", 2), 1);
    }
    // print_minirt(minirt); // debug print
    trace_rays(minirt);
    mlx_put_image_to_window(minirt->mlx, minirt->window, minirt->data.img, 0, 0);

    mlx_key_hook(minirt->window, keyboard_handler, minirt);
    mlx_hook(minirt->window, 17, 1L << 0, free_exit, minirt);
    mlx_loop(minirt->mlx);

    deinit(minirt);
}
