/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:50:29 by bmakhama          #+#    #+#             */
/*   Updated: 2025/02/01 12:33:22 by bmakhama         ###   ########.fr       */
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
			(free_matrix(&shapes->plane->transform),
				free_matrix(&shapes->plane->tp_transform), free(shapes->plane));
		else if (shapes->type == cylinder && shapes->cylinder)
			(free_matrix(&shapes->cylinder->transform),
				free_matrix(&shapes->cylinder->tp_transform), \
				free(shapes->cylinder));
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
		free(temp->shape);
		free(temp);
	}
}

void	free_env(t_environment *env)
{
	if (env)
	{
		free_shapes(&env->shapes);
	}
}

void	free_minirt(t_minirt *minirt)
{
	if (minirt)
	{
		free_env(minirt->env);
		free(minirt);
	}
}
