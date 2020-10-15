/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/09/25 11:24:49 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			rgb_to_int(t_color color)
{
	color.red = color.red << 16;
	color.green = color.green << 8;
	return (color.red + color.green + color.blue);
}

int			fcolor_to_int(t_fcolor color)
{
	t_color rgb;

	rgb.red = color.red * 255.0;
	rgb.green = color.green * 255.0;
	rgb.blue = color.blue * 255.0;
	return (rgb_to_int(rgb));
}

t_color		rgb_color_intensity(t_color color, float intensity)
{
	color.red *= intensity;
	color.green *= intensity;
	color.blue *= intensity;
	return (color);
}

t_color		color_intensity(int color, float intensity)
{
	t_color	rgb;

	rgb = int_to_rgb(color);
	return (rgb_color_intensity(rgb, intensity));
}

int			weighted_average(t_color base, t_color reflected, float weight1)
{
	t_color	result;

	result.red = (int)(reflected.red * weight1)
				+ (int)(base.red * (1 - weight1));
	result.green = (int)(reflected.green * weight1)
				+ (int)(base.green * (1 - weight1));
	result.blue = (int)(reflected.blue * weight1)
				+ (int)(base.blue * (1 - weight1));
	return (rgb_to_int(result));
}
