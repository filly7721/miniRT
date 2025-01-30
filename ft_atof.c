/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmakhama <bmakhama@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:34:57 by bmakhama          #+#    #+#             */
/*   Updated: 2025/01/30 13:28:47 by bmakhama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_atof(char *str)
{
	double	whole;
	double	dec;
	double	sign;
	int		i;
	int		j;

	whole = 0;
	dec = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		whole = whole * 10 + str[i++] - '0';
	if (str[i++] != '.')
		return (sign * whole);
	j = i;
	while (str[i] >= '0' && str[i] <= '9')
		dec = dec * 10 + str[i++] - '0';
	while (i-- > j)
		dec /= 10;
	return (sign * (whole + dec));
}
