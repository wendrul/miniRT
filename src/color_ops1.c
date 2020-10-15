/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/09/25 11:24:49 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		new_color(int r, int g, int b)
{
	t_color color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

int			filter_color(int color_int, int filter)
{
	t_color	fltr_rgb;
	t_color	color;
	t_vect	filter_percents;

	fltr_rgb = int_to_rgb(filter);
	color = int_to_rgb(color_int);
	filter_percents = new_vect(fltr_rgb.red, fltr_rgb.green, fltr_rgb.blue);
	filter_percents = scale(filter_percents, 1.0 / 256.0);
	color.red = filter_percents.x * color.red;
	color.green = filter_percents.y * color.green;
	color.blue = filter_percents.z * color.blue;
	return (rgb_to_int(color));
}

t_color		new_color_vect(t_vect v)
{
	t_color color;

	color.red = (int)v.x;
	color.green = (int)v.y;
	color.blue = (int)v.z;
	return (color);
}

t_fcolor	int_to_fcolor(int color_int)
{
	t_color		rgb;
	t_fcolor	f_rgb;

	rgb = int_to_rgb(color_int);
	f_rgb.red = (float)rgb.red / 255.0;
	f_rgb.green = (float)rgb.green / 255.0;
	f_rgb.blue = (float)rgb.blue / 255.0;
	return (f_rgb);
}

t_color		int_to_rgb(int color_int)
{
	t_color rgb;

	rgb.red = color_int >> 16;
	rgb.green = (color_int & 0xff00) >> 8;
	rgb.blue = color_int & 0xff;
	return (rgb);
}
