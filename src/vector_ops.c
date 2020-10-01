/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:36:49 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/16 14:09:51 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	norm(t_point vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

float norm_inf(t_vect a)
{
    float n;

    n = ft_max(fabs(a.x), fabs(a.y));
    return (ft_max(n, fabs(a.z)));
}

float	normsqrd(t_point vector)
{
	return (pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

t_point normalize(t_point vector)
{
	float norme;
	norme = norm(vector);
	vector.x /= norme;
	vector.y /= norme;
	vector.z /= norme;
	return (vector);
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

t_vect	scale(t_vect v, float scalar)
{
	t_vect result;
	
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
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

float	dot(t_point v1, t_point v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2)));
}

double	angle(t_vect v1, t_vect v2)
{
	return(acos(dot(v1, v2) / (norm(v1) * norm(v2))));
}

t_vect projection(t_vect u, t_vect base)
{
	float t;

	base = normalize(base);
	t = dot(u, base);
	return(scale(base, t));
}

t_vect cross(t_vect a, t_vect b)
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

void print_vect(t_vect vect, char *str)
{
	printf("%s - x:%f, y:%f, z:%f\n", str, vect.x, vect.y, vect.z);
}