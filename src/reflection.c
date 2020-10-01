/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 21:54:26 by dhorvill          #+#    #+#             */
/*   Updated: 2020/09/26 17:55:34 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	get_reflective_vector(t_figure figure, t_point inter, t_vect incident, t_vect start)
{
	t_vect normal;
	t_vect reflected;

	normal = figure.get_normal_at(inter, figure, start);
	reflected = scale(normal, 2.0 * dot(incident, normal));
	reflected = subtract(incident, reflected);
	return (reflected);
}

int figure_eclipses_light(t_vect inter, t_figure shape, t_vect light)
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
		return(0);
	return (1);
}
