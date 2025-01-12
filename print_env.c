#include "miniRT.h"

void print_camera(t_camera* camera)
{
    printf("Camera: x: %.2f, y: %.2f, z: %.2f, dir_x: %.2f, dir_y: %.2f, dir_z: %.2f, fov: %d\n",
           camera->x, camera->y, camera->z, camera->dir_x, camera->dir_y, camera->dir_z, camera->fov);
}

void print_light(t_light* light)
{
    printf("Light: x: %.2f, y: %.2f, z: %.2f, brightness: %.2f, r: %d, g: %d, b: %d\n",
           light->x, light->y, light->z, light->bright, light->r, light->g, light->b);
}

void print_ambient(t_ambient* ambient)
{
    printf("Ambient: intensity: %.2f, r: %d, g: %d, b: %d\n",
           ambient->intensity, ambient->r, ambient->g, ambient->b);
}

void print_sphere(t_sphere* sphere)
{
    printf("Sphere: x: %.2f, y: %.2f, z: %.2f, diameter: %.2f, r: %d, g: %d, b: %d\n",
           sphere->x, sphere->y, sphere->z, sphere->diameter, sphere->r, sphere->g, sphere->b);
}

void print_plane(t_plane* plane)
{
    printf("Plane: x: %.2f, y: %.2f, z: %.2f, norm_x: %.2f, norm_y: %.2f, norm_z: %.2f, r: %d, g: %d, b: %d\n",
           plane->x, plane->y, plane->z, plane->norm_x, plane->norm_y, plane->norm_z, plane->r, plane->g, plane->b);
}

void print_cylinder(t_cylinder* cylinder)
{
    printf("Cylinder: x: %.2f, y: %.2f, z: %.2f, axis_x: %.2f, axis_y: %.2f, axis_z: %.2f, radius: %.2f, height: %.2f, r: %d, g: %d, b: %d\n",
           cylinder->x, cylinder->y, cylinder->z, cylinder->axis_x, cylinder->axis_y, cylinder->axis_z, 
           cylinder->radius, cylinder->height, cylinder->r, cylinder->g, cylinder->b);
}

void print_environment(t_environment* env)
{
    printf("Environment:\n");

    // Print Light
    print_light(&env->light);

    // Print Ambient
    print_ambient(&env->ambient);

    // Print Camera
    print_camera(&env->camera);

    // Print Shapes
    t_list* shape_node = env->shapes;
    while (shape_node)
    {
        t_shape* shape = (t_shape*)shape_node->content;
        if (shape->type == sphere)
        {
            print_sphere(shape->sphere);
        }
        else if (shape->type == plane)
        {
            print_plane(shape->plane);
        }
        else if (shape->type == cylinder)
        {
            print_cylinder(shape->cylinder);
        }
        shape_node = shape_node->next;
    }
}
