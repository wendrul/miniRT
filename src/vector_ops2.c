/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:32:01 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/14 19:40:35 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vectors.h"

float	dot(t_point v1, t_point v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p2.x - p1.x, 2)
			+ pow(p2.y - p1.y, 2)
			+ pow(p2.z - p1.z, 2)));
}

t_vect	scale(t_vect v, float scalar)
{
	t_vect result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

t_vect	projection(t_vect u, t_vect base)
{
	float t;

	base = normalize(base);
	t = dot(u, base);
	return (scale(base, t));
}
