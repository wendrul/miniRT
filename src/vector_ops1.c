/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:33:04 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/14 19:39:18 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vectors.h"

t_vect	true_vect(t_point v1, t_point v2)
{
	t_point result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;
	return (result);
}

t_vect	subtract(t_vect v1, t_vect v2)
{
	t_vect result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vect	add(t_vect v1, t_vect v2)
{
	t_vect result;

	result.x = v2.x + v1.x;
	result.y = v2.y + v1.y;
	result.z = v2.z + v1.z;
	return (result);
}

t_vect	new_vect(float x, float y, float z)
{
	t_vect	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_point	normalize(t_point vector)
{
	float norme;

	norme = norm(vector);
	vector.x /= norme;
	vector.y /= norme;
	vector.z /= norme;
	return (vector);
}
