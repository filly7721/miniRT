/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:21:10 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/22 10:21:13 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	keyboard_handler(int keycode, t_minirt *miniRT)
{
	if (keycode == 53)
		(deinit(miniRT), exit(1));
	return (0);
}
