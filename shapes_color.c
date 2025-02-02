/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:04:51 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 10:53:12 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_brightness(t_minirt *minirt, t_tuple hit_point, t_tuple normal)
{
	t_tuple			lightsource;
	double			brightness;
	t_intersection	*intersects;
	t_ray			ray;

	ray.origin = set_point(
			minirt->env->light.x, minirt->env->light.y, minirt->env->light.z);
	ray.direction = normalize_tuple(sub_tuples(hit_point, ray.origin));
	ray.origin = add_tuples(ray.origin, mul_tuple(ray.direction, EPSILON));
	intersects = intersect(&ray, minirt->env->shapes);
	if (intersects && closest_hit(intersects)->t
		< mag_tuple(sub_tuples(hit_point, ray.origin)))
		return (free_intersections(intersects), 0);
	free_intersections(intersects);
	brightness = dot_tuple(mul_tuple(ray.direction, -1), normal);
	if (brightness < 0)
		brightness = 0;
	return (brightness * minirt->env->light.bright
		* (1.0 - minirt->env->ambient.intensity));
}

t_tuple	get_sphere_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_sphere *sp)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;
	t_tuple	ambient;

	albedo = set_tuple(sp->r / 255.0, sp->g / 255.0, sp->b / 255.0, 0);
	ambient = set_tuple(minirt->env->ambient.r / 255.0,
			minirt->env->ambient.g / 255.0,
			minirt->env->ambient.b / 255.0, 0);
	ambient = mul_tuple(ambient, minirt->env->ambient.intensity);
	ambient.x *= albedo.x;
	ambient.y *= albedo.y;
	ambient.z *= albedo.z;
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	normal = normalize_tuple(sub_tuples(hp, set_point(sp->x, sp->y, sp->z)));
	hp = add_tuples(hp, mul_tuple(ray->direction, -EPSILON));
	return (add_tuples(
			mul_tuple(albedo, get_brightness(minirt, hp, normal)), ambient));
}

t_tuple	get_cylinder_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_cylinder *cy)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;
	t_ray	newray;
	t_tuple	ambient;

	albedo = set_tuple(cy->r / 255.0, cy->g / 255.0, cy->b / 255.0, 0);
	ambient = set_tuple(minirt->env->ambient.r / 255.0,
			minirt->env->ambient.g / 255.0,
			minirt->env->ambient.b / 255.0, 0);
	ambient = mul_tuple(ambient, minirt->env->ambient.intensity);
	ambient.x *= albedo.x;
	ambient.y *= albedo.y;
	ambient.z *= albedo.z;
	newray.direction = mult_mat_tuple(&ray->direction, &cy->transform);
	newray.origin = mult_mat_tuple(&ray->origin, &cy->transform);
	hp = add_tuples(mul_tuple(newray.direction, inter->t), newray.origin);
	normal = normalize_tuple(set_vector(hp.x, 0, hp.z));
	normal = mult_mat_tuple(&normal, &cy->tp_transform);
	normal = normalize_tuple(normal);
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	hp = add_tuples(hp, mul_tuple(ray->direction, -EPSILON));
	return (add_tuples(
			mul_tuple(albedo, get_brightness(minirt, hp, normal)), ambient));
}

t_tuple	get_plane_color(t_minirt *minirt, t_ray *ray, t_intersection *inter, \
	t_plane *pl)
{
	t_tuple	albedo;
	t_tuple	hp;
	t_tuple	normal;
	t_tuple	ambient;

	albedo = set_tuple(pl->r / 255.0, pl->g / 255.0, pl->b / 255.0, 0);
	ambient = set_tuple(minirt->env->ambient.r / 255.0,
			minirt->env->ambient.g / 255.0,
			minirt->env->ambient.b / 255.0, 0);
	ambient = mul_tuple(ambient, minirt->env->ambient.intensity);
	ambient.x *= albedo.x;
	ambient.y *= albedo.y;
	ambient.z *= albedo.z;
	normal = normalize_tuple(set_vector(pl->norm_x, pl->norm_y, pl->norm_z));
	hp = add_tuples(mul_tuple(ray->direction, inter->t), ray->origin);
	hp = add_tuples(hp, mul_tuple(ray->direction, -EPSILON));
	return (add_tuples(
			mul_tuple(albedo, get_brightness(minirt, hp, normal)), ambient));
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
