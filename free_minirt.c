/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:50:29 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/28 11:48:45 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_shape(t_shape *shapes)
{
	if (shapes)
	{
		if (shapes->type == sphere && shapes->sphere)
			free(shapes->sphere);
		else if (shapes->type == plane && shapes->plane)
			free(shapes->plane);
		else if (shapes->type == cylinder && shapes->cylinder)
			free(shapes->cylinder);
		free(shapes);
	}
}

void	free_shapes(t_list **shapes)
{
	t_list	*current;
	t_list	*next;

	current = *shapes;
	while (current)
	{
		next = current->next;
		free_shape((t_shape *)current->content);
		free(current);
		current = next;
	}
	*shapes = NULL;
}

void	free_intersections(t_intersection *head)
{
	t_intersection	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		// free_shape(temp->shape);
		free(temp);
	}
}

void	free_env(t_environment *env)
{
	if (env)
	{
		free_shapes(&env->shapes);
		// free_light(&env->light);
		// free_camera(&env->camera);
		// free_ambient(&env->ambient);
		// free(env);
	}
}

void	free_minirt(t_minirt *minirt)
{
	if (minirt)
	{
		free_mlxdata(&minirt->data);
		free_env(minirt->env);
		free(minirt);
	}
}
