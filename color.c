/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:12:22 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 11:14:14 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	rgbtoint(t_tuple color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.r * 255);
	g = (int)(color.g * 255);
	b = (int)(color.b * 255);
	return (r << 16 | g << 8 | b);
}

int	light_ratio(t_environment *env)
{
	if (env->ambient.intensity < 0.0 || env->ambient.intensity > 1.0)
		return (0);
	else if (env->light.bright < 0.0 || env->light.bright > 1.0)
		return (0);
	return (1);
}
