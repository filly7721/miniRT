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

int color_to_int(t_color color)
{
    int r = (int)(color.r * 255);
    int g = (int)(color.g * 255);
    int b = (int)(color.b * 255);
    return (r << 16) | (g << 8) | b;
}
t_tuple normalize(t_tuple v)
{
    double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return set_tuple(v.x / magnitude, v.y / magnitude, v.z / magnitude, v.w);
}

void write_pixel(t_mlxdata *data, int x, int y, int width, int height, t_color color)
{
    int bytes_per_pixel = data->bits_per_pixel / 8;

    if (x < 0 || y < 0 || x >= width || y >= height)
        return; // Prevent out-of-bounds writes

    int offset = (y * data->line_length) + (x * bytes_per_pixel);
    data->addr[offset] = (int)(color.b * 255);        // Blue channel
    data->addr[offset + 1] = (int)(color.g * 255);    // Green channel
    data->addr[offset + 2] = (int)(color.r * 255);    // Red channel
}

void print_tuple(char* str, t_tuple *tuple)
{
    printf("%s"": (x: %f, y: %f, z: %f, w: %f)\n", str, tuple->x, tuple->y, tuple->z, tuple->w);
}
void print_shape_type(t_shape *shape)
{
    switch (shape->type)
    {
        case sphere:
            printf("Shape type: Sphere\n");
            break;
        case plane:
            printf("Shape type: Plane\n");
            break;
        case cylinder:
            printf("Shape type: Cylinder\n");
            break;
        default:
            printf("Shape type: Unknown\n");
            break;
    }
}

void trace_rays(t_minirt *minirt)
{
    int     x, y;
    double  world_x, world_y;
    t_ray   *ray;
    t_tuple ray_origin, target, direction;
    t_intersection *intersections, *hit_intersection;
    t_color red = {1, 0, 0};
    t_color black = {0, 0, 0};
    double  wall_z = 10.0;
    double  wall_size = 7.0;
    double  pixel_size = wall_size / minirt->width;
    double  half = wall_size / 2.0;
    t_shape *shape;

    ray_origin = set_tuple(0, 0, -5, 1); // Camera position
    print_tuple("ray_origin: ", &ray_origin);
        printf("minirt->height:%d, minirt->width: %d \n", minirt->height, minirt->width);
    // for (y = 0; y < minirt->height; y++)
    for (y = 0; y < 10; y++)
    {
        world_y = half - pixel_size * y;
        // for (x = 0; x < minirt->width; x++)
        for (x = 0; x < 10; x++)
        {
            world_x = -half + pixel_size * x;
            target = set_tuple(world_x, world_y, wall_z, 1);
            // print_tuple("target: ", &target);

            direction = normalize(sub_tuples(target, ray_origin));
            // print_tuple("direction: ", &direction);
            ray = create_ray(ray_origin, direction);
    
            shape = (t_shape *)(minirt->env->shapes->content);
            // print_shape_type(shape);
            if (shape->type == sphere)
            {
                printf("Shape is a sphere (type: %d)\n", shape->type);
                // Create transformation matrix for the sphere if not already done
                if (shape->sphere->transform.size == 0)
                {
                    printf("here\n");
                    t_tuple translation_vector = set_tuple(0, 0, 0, 0); // No translation
                    shape->sphere->transform = translation(&translation_vector);
                }

                intersections = intersect(shape->sphere, ray);
                hit_intersection = hit(intersections);
                if (hit_intersection)
                {
                    printf("red\n");
                    write_pixel(&minirt->data, x, y, minirt->width, minirt->height, (t_color){1, 0, 0}); // Drawing red pixels across the screen
                }
                else
                {
                    printf("black\n");
                    write_pixel(&minirt->data, x, y, minirt->width, minirt->height, (t_color){0, 1, 0}); // Drawing red pixels across the screen
                }
            }
            else
            {
                write_pixel(&minirt->data, x, y, minirt->width, minirt->height, (t_color){1, 0, 0}); // Drawing red pixels across the screen 
                printf("out of the if cond\n");
            }

        }
    }
}

void trace_rays2(t_minirt *minirt)
{
    for (int y = 0; y < minirt->height; y++)
    {
        for (int x = 0; x < minirt->width; x++)
        {
            write_pixel(&minirt->data, x, y, minirt->width, minirt->height, (t_color){1, 0, 0}); // Drawing red pixels across the screen
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
    t_minirt *minirt = init_minirt(2000, 1000, &env);
    if (!minirt) {
        return (ft_putstr_fd("init error\n", 2), 1);
    }
    trace_rays(minirt);
    mlx_put_image_to_window(minirt->mlx, minirt->window, minirt->data.img, 0, 0);

    mlx_key_hook(minirt->window, keyboard_handler, minirt);
    mlx_hook(minirt->window, 17, 1L << 0, free_exit, minirt);
    mlx_loop(minirt->mlx);

    deinit(minirt);
}
