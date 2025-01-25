/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:28:37 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/25 12:49:43 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray generate_ray(t_camera *camera, int x, int y, int width, int height)
{
	double aspect_ratio;
	double fov_radians;
	
	double viewpoint_width;
	double viewpoint_height;
	
	double pixel_ndc_x;
	double pixel_ndc_y;
	
	double pixel_camera_x;
	double pixel_camera_y;
	
	t_tuple forward;
	t_tuple right;
	t_tuple up;
	
	t_tuple pixel_world;
	t_tuple direction;
	t_tuple origin;

	aspect_ratio = (double)width / height;
	fov_radians = camera->fov * (M_PI / 180.0);
	
	// viewpoint_width = 2 * tan(fov_radians / 2.0);
	viewpoint_width = 1;
	// viewpoint_height = viewpoint_width / aspect_ratio;
	viewpoint_height = 1 / aspect_ratio;
	
	pixel_ndc_x = (x + 0.5) / width;
	pixel_ndc_y = (y + 0.5) / height;
	
	// pixel_camera_x = (2 * pixel_ndc_x - 1) * viewpoint_width / 2.0;
	pixel_camera_x = (2 * pixel_ndc_x - 1) ;
	// pixel_camera_y = (1 - 2 * pixel_ndc_y) * viewpoint_height / 2.0;
	pixel_camera_y = (1 - 2 * pixel_ndc_y);
	
	forward = normalize_tuple(set_tuple(camera->dir_x, camera->dir_y, camera->dir_z, 0.0));
	up = set_tuple(0.0, 1.0, 0.0, 0.0); // Assume world up
	if (fabs(forward.y) == 1.0)
		up = normalize_tuple(set_tuple(1.0, 0.0, 0.0, 0.0));
	right = normalize_tuple(cross_tuple(up, forward));
	up = cross_tuple(forward, right);

	pixel_world = add_tuples(
		add_tuples((scale_tuple(right, pixel_camera_x)), scale_tuple(up, pixel_camera_y)), forward);

	direction = normalize_tuple(pixel_world);
	origin = set_tuple(camera->x, camera->y, camera->z, 1.0);
	return (t_ray){origin, direction};
}
