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

void init_camera(t_camera *camera)
{
    camera->forward = normalize_tuple(set_tuple(camera->dir_x, camera->dir_y, camera->dir_z, 0.0));
	camera->up = set_tuple(0.0, 1.0, 0.0, 0.0); // Assume world up
	if (fabs(camera->forward.y) == 1.0)
		camera->up = normalize_tuple(set_tuple(1.0, 0.0, 0.0, 0.0));
	camera->right = normalize_tuple(cross_tuple(camera->up, camera->forward));
	camera->up = cross_tuple(camera->forward, camera->right);
}

t_intersection	*closest_hit(t_intersection	*list)
{
	t_intersection	*closest;
	t_intersection	*temp;

	temp = list;
	closest = list;
	while (temp->next)
	{
		temp = temp->next;
		if (temp->t > 0 && temp->t < closest->t)
			closest = temp;
	}
	return (closest);
}
bool	eq_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple	res;
	
	res = sub_tuples(t2, t1);
	if (res.x > 0.001 || res.y > 0.001 || res.z > 0.001)
		return (false);
	return (true);
}

double	get_brightness(t_minirt *minirt, t_tuple hit_point, t_tuple normal)
{
	t_tuple			lightsource;
	double			brightness;
	t_intersection	*intersections;
	t_ray			ray;

	ray.origin = set_point(minirt->env->light.x, minirt->env->light.y, minirt->env->light.z);
	ray.direction = normalize_tuple(sub_tuples(hit_point, ray.origin));
	intersections = intersect(&ray, minirt->env->shapes);
	if (eq_tuples(
		add_tuples(
		mul_tuple(ray.direction, closest_hit(intersections)->t),
		ray.origin),
		hit_point)
		 == false)
		return minirt->env->ambient.intensity;
	lightsource = sub_tuples(lightsource, hit_point);
	lightsource = normalize_tuple(lightsource);
	brightness = dot_tuple(lightsource, normal);
	if (brightness < 0)
		brightness = 0;
	return (brightness * (1.0 - minirt->env->ambient.intensity) + minirt->env->ambient.intensity);
}

t_tuple	get_sphere_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, t_sphere *sp)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;

	albedo = set_tuple(sp->r / 255.0, sp->g / 255.0, sp->b / 255.0, 0);
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	normal = normalize_tuple(sub_tuples(hp, set_point(sp->x, sp->y, sp->z)));

	return mul_tuple(albedo, get_brightness(minirt, hp, normal));
}

t_tuple	get_color(t_minirt *minirt, t_ray *ray, t_intersection *intersection)
{
	t_tuple	color;

	if (intersection->shape->type == sphere)
		color = get_sphere_color(minirt, ray, intersection, intersection->shape->sphere);
	else if (intersection->shape->type == cylinder)
		color = set_tuple(intersection->shape->cylinder->r / 255.0, intersection->shape->cylinder->g / 255.0, intersection->shape->cylinder->b / 255.0, 0);
	else if (intersection->shape->type == plane)
		color = set_tuple(intersection->shape->plane->r / 255.0, intersection->shape->plane->g / 255.0, intersection->shape->plane->b / 255.0, 0);
	return (color);
}

void    trace_rays(t_minirt *minirt)
{
    int x;
    int y;
    t_ray ray;
    t_intersection *intersections;
    t_shape *current_shape;

    init_camera(&minirt->env->camera);
    y = 0;
    while (y < minirt->height)
    {
        x = 0;
        while (x < minirt->width)
        {
            ray = generate_ray(minirt, x, y);
            // ray.direction = mul_tuple(ray.direction, -1);
            // dprintf(2, "(%.2f, %.2f, %.2f) ", ray.direction.x, ray.direction.y, ray.direction.z);
            intersections = intersect(&ray, minirt->env->shapes);
            if (intersections != NULL)
			{
				t_tuple color = get_color(minirt, &ray, closest_hit(intersections));
                pixel_put(&minirt->data, x, y, rgbtoint(color));
                // write_pixel(&minirt->data, x, y, minirt->width, minirt->height, (t_color){1, 0, 0});
			}
            else
                pixel_put(&minirt->data, x, y, 0x00000000);
                // write_pixel(&minirt->data, x, y, minirt->width, minirt->height, (t_color){0, 0, 0});
            //! free intersections
            x++;

        }
        // dprintf(2, "\n");
        y++;
    }

    mlx_put_image_to_window(minirt->mlx, minirt->window, minirt->data.img, 0, 0);
}

int main(int arc, char** arv)
{
    if (arc != 2) {
        printf("The input must be 2!");
        return (1);
    }
    t_environment env;
    env.shapes = NULL;
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
