/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 21:54:26 by dhorvill          #+#    #+#             */
/*   Updated: 2020/09/04 10:30:58 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	get_reflective_vector(t_figure figure, t_point inter, t_vect incident)
{
	t_vect normal;
	t_vect reflected;

	normal = figure.get_normal_at(inter, figure);
	reflected = scale(normal, 2.0 * dot(incident, normal));
	reflected = substract(incident, reflected);
	return (reflected);
}
