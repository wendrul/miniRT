/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 21:54:26 by dhorvill          #+#    #+#             */
/*   Updated: 2020/10/15 12:54:27 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	get_refl_vector(t_figure figure, t_point inter,
								t_vect incident, t_vect start)
{
	t_vect normal;
	t_vect reflected;

	normal = figure.get_normal_at(inter, figure, start);
	reflected = scale(normal, 2.0 * dot(incident, normal));
	reflected = subtract(incident, reflected);
	return (reflected);
}

int		figure_eclipses_light(t_vect inter, t_figure shape, t_vect light)
{
	t_vect	inter_to_light;
	t_vect	inter_to_shape;
	t_vect	shape_inter;

	if (shape.is_reflective > EPSILON)
		return (0);
	inter_to_light = subtract(light, inter);
	shape_inter = shape.intersection(shape, normalize(inter_to_light), inter);
	inter_to_shape = subtract(shape_inter, inter);
	if (norm(inter_to_light) < norm(inter_to_shape))
		return (0);
	return (1);
}

int		color_shade(float intensity, t_figure figure, int reflective_color)
{
	t_color base;
	t_color	reflective_rgb;

	base = color_intensity(figure.color, intensity);
	reflective_rgb = int_to_rgb(0);
	if (figure.is_reflective > 0)
		reflective_rgb = int_to_rgb(reflective_color);
	if (figure.is_reflective == 0)
		return (rgb_to_int(base));
	return (weighted_average(base, reflective_rgb, figure.is_reflective));
}

float	get_lum_intensity(t_figure figure, t_point inter,
							t_point spotlight, t_point start)
{
	t_point	normal;
	t_point	ray_to_light;
	float	result;

	normal = figure.get_normal_at(inter, figure, start);
	ray_to_light = vector(inter, spotlight);
	if ((result = dot(normal, ray_to_light)) > 0)
		return (result);
	return (0);
}
