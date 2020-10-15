/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 12:54:07 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/15 14:44:21 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_atof(char *nb)
{
	float	i;
	float	d;
	float	mult;
	int		neg;

	i = 0.0;
	d = 0.0;
	mult = 0.1;
	neg = 1;
	if (*nb == '-')
	{
		neg = -1;
		nb++;
	}
	while (*nb && *nb != '.' && ft_isdigit(*nb))
		i = i * 10 + (*(nb++) - '0');
	if (*nb == '.')
		nb++;
	while (*nb && ft_isdigit(*nb))
	{
		d += (*(nb++) - '0') * mult;
		mult *= 0.1;
	}
	return ((i + d) * neg);
}

int		name_cmp(char *fixed, char *var)
{
	int len;

	len = ft_max(ft_strlen(var), ft_strlen(fixed));
	return (ft_strncmp(fixed, var, len));
}

int		tab_del_return(char **tab, int ret)
{
	char **tmp;

	tmp = tab;
	while (*tab)
	{
		free(*tab++);
	}
	free(tmp);
	return (ret);
}

int		gamma_corrected(int color, double one_over_gamma)
{
	t_fcolor rgb;

	rgb = int_to_fcolor(color);
	rgb.red = pow(rgb.red, one_over_gamma);
	rgb.green = pow(rgb.green, one_over_gamma);
	rgb.blue = pow(rgb.blue, one_over_gamma);
	return (fcolor_to_int(rgb));
}
