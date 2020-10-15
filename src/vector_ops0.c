/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:36:49 by dhorvill          #+#    #+#             */
/*   Updated: 2020/10/14 19:48:51 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vectors.h"

float	norm(t_point vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

float	norm_inf(t_vect a)
{
	float max;

	max = fabs(a.x);
	if (max < fabs(a.y))
		max = fabs(a.y);
	if (max < fabs(a.z))
		max = fabs(a.z);
	return (max);
}

float	normsqrd(t_point vector)
{
	return (pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

t_vect	square(t_vect v1)
{
	t_point result;

	result.x = v1.x * v1.x;
	result.y = v1.y * v1.y;
	result.z = v1.z * v1.z;
	return (result);
}

t_point	vector(t_point v1, t_point v2)
{
	t_point result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;
	return (normalize(result));
}
