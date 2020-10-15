/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:31:16 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/14 19:41:55 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vectors.h"

double	angle(t_vect v1, t_vect v2)
{
	return (acos(dot(v1, v2) / (norm(v1) * norm(v2))));
}

t_vect	cross(t_vect a, t_vect b)
{
	t_vect ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

t_vect	apply_rotation(t_vect u, t_vect rot, float theta)
{
	t_vect ret;

	if (norm(rot) < 0.001)
		return (u);
	rot = normalize(rot);
	ret.x = u.x * (cos(theta) + pow(rot.x, 2) * (1 - cos(theta)))
			+ u.y * (rot.x * rot.y * (1 - cos(theta)) - rot.z * sin(theta))
			+ u.z * (rot.x * rot.z * (1 - cos(theta)) + rot.y * sin(theta));
	ret.y = u.x * (rot.y * rot.x * (1 - cos(theta)) + rot.z * sin(theta))
			+ u.y * (cos(theta) + pow(rot.y, 2) * (1 - cos(theta)))
			+ u.z * (rot.y * rot.z * (1 - cos(theta)) - rot.x * sin(theta));
	ret.z = u.x * (rot.z * rot.x * (1 - cos(theta)) - rot.y * sin(theta))
			+ u.y * (rot.z * rot.y * (1 - cos(theta)) + rot.x * sin(theta))
			+ u.z * (cos(theta) + pow(rot.z, 2) * (1 - cos(theta)));
	return (ret);
}
