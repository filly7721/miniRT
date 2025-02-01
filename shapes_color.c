
#include "miniRT.h"

double	get_brightness(t_minirt *minirt, t_tuple hit_point, t_tuple normal)
{
	t_tuple			lightsource;
	double			brightness;
	t_intersection	*intersections;
	t_ray			ray;

	ray.origin = hit_point;
	ray.direction = set_point(
			minirt->env->light.x, minirt->env->light.y, minirt->env->light.z);
	ray.direction = normalize_tuple(sub_tuples(ray.direction, ray.origin));
	intersections = intersect(&ray, minirt->env->shapes);
	lightsource = set_point(minirt->env->light.x, minirt->env->light.y, \
		minirt->env->light.z);
	if (intersections && closest_hit(intersections)->t
		< mag_tuple(sub_tuples(lightsource, ray.origin)) + 0.001)
		return (minirt->env->ambient.intensity);
	brightness = dot_tuple(ray.direction, normal);
	if (brightness < 0)
		brightness = 0;
	return (brightness * minirt->env->light.bright
		* (1.0 - minirt->env->ambient.intensity)
		+ minirt->env->ambient.intensity);
}

t_tuple	get_sphere_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_sphere *sp)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;

	albedo = set_tuple(sp->r / 255.0, sp->g / 255.0, sp->b / 255.0, 0);
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	normal = normalize_tuple(sub_tuples(hp, set_point(sp->x, sp->y, sp->z)));
	hp = add_tuples(hp, mul_tuple(ray->direction, -EPSILON));
	return (mul_tuple(albedo, get_brightness(minirt, hp, normal)));
}

t_tuple	get_cylinder_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_cylinder *cy)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;
	t_ray	newray;

	newray.direction = mult_mat_tuple(&ray->direction, &cy->transform);
	newray.origin = mult_mat_tuple(&ray->origin, &cy->transform);
	albedo = set_tuple(cy->r / 255.0, cy->g / 255.0, cy->b / 255.0, 0);
	hp = add_tuples(mul_tuple(newray.direction, inter->t), newray.origin);
	normal = normalize_tuple(set_vector(hp.x, 0, hp.z));
	normal = mult_mat_tuple(&normal, &cy->tp_transform);
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	hp = add_tuples(hp, mul_tuple(ray->direction, -EPSILON));
	return (mul_tuple(albedo, get_brightness(minirt, hp, normal)));
}

t_tuple	get_plane_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_plane *pl)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;
	albedo = set_tuple(pl->r / 255.0, pl->g / 255.0, pl->b / 255.0, 0);
	normal = normalize_tuple(set_vector(pl->norm_x, pl->norm_y, pl->norm_z));
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	hp = add_tuples(hp, mul_tuple(ray->direction, -EPSILON));
	return (mul_tuple(albedo, get_brightness(minirt, hp, normal)));
}

t_tuple	get_color(t_minirt *minirt, t_ray *ray, t_intersection *intersection)
{
	t_tuple	color;

	if (intersection->shape->type == sphere)
		color = get_sphere_color(minirt, ray, intersection, \
			intersection->shape->sphere);
	else if (intersection->shape->type == cylinder)
		color = get_cylinder_color(minirt, ray, intersection, \
			intersection->shape->cylinder);
	else if (intersection->shape->type == plane)
		color = get_plane_color(minirt, ray, intersection, \
			intersection->shape->plane);
	return (color);
}
