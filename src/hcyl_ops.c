/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hcyl_ops.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/13 19:55:00 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char*		check_hcyl_args(t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size < 11)
		return ("Not enough arguments for a hollow cylinder.");
    if (args[3] > 1  || args[4] > 1  || args[5] > 1 ||
		args[3] < -1 || args[4] < -1 || args[5] < -1)
		return ("Hollow cylinder orientation vector values not in range (-1, 1).");
	if (args[6] < 0)
		return ("Hollow cylinder diameter is negative");
    if (args[7] < 0)
		return ("Hollow cylinder height is negative");
	if (args[8] > 255 || args[9] > 255 || args[10] > 255 ||
		args[8] < 0   || args[9] < 0   || args[10] < 0)
		return ("Invalid RGB color values for hollow cylinder (must be values between 0 and 255 per color).");
	return (NULL);
}

t_hcyl	create_hcyl(t_parse_args parsed)
{
	t_hcyl	hcyl;
	char *msg;
	msg = check_hcyl_args(parsed);
	if (msg != NULL)
		clean_exit(0, msg);
	hcyl.x = parsed.args[0];
	hcyl.y = parsed.args[1];
	hcyl.z = parsed.args[2];
	hcyl.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
    hcyl.normal.x = parsed.args[3];
	hcyl.normal.y = parsed.args[4];
	hcyl.normal.z = parsed.args[5];
    hcyl.normal = normalize(hcyl.normal);
	hcyl.radius = parsed.args[6] / 2;
    hcyl.length = parsed.args[7];
	hcyl.color = rgb_to_int(new_color(parsed.args[8], parsed.args[9], parsed.args[10]));
	if (parsed.size > 11)
		hcyl.is_reflective = parsed.args[11];
	hcyl.intersection = hcyl_intersection;
	hcyl.get_normal_at = get_hcyl_normal_vector;
	hcyl.eclipses = hcyl_eclipses_light;
	ft_memcpy(hcyl.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
	return (hcyl);
}

t_point		hcyl_intersection(t_hcyl hcyl, t_vect ray, t_point start)
{
	t_polynome	equa;
	t_vect		result;
	t_vect		v1;
	t_vect		v2;
	float		t;

	v1 = substract(start, hcyl.center);//just using v1 as a tmp
	v2 = substract(v1, dot(v1, hcyl.normal));
	v1 = substract(ray, dot(ray, hcyl.normal));
	equa.a = pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2);
	equa.b = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	equa.c = pow(v2.x, 2) + pow(v2.y, 2) + pow(v2.z, 2) - pow(hcyl.radius, 2);	
	if ((equa.delta = equa.b * equa.b - 4 * equa.a * equa.c) > 0)
	{
		equa.sqrt_delta = sqrt(equa.delta);
		t = ((-equa.b + equa.sqrt_delta) / (2 * equa.a)) * -1;
		if (t > 0)
		{
			result.x = start.x + t * ray.x;
			result.y = start.y + t * ray.y;
			result.z = start.z + t * ray.z;
			return (result);
		}
		t = ((-equa.b - equa.sqrt_delta) / (2 * equa.a)) * -1;
		if (t > 0)
		{
			result.x = start.x + t * ray.x;
			result.y = start.y + t * ray.y;
			result.z = start.z + t * ray.z;
			return (result);
		}
	}
	result.x = RENDER_DISTANCE;
	result.y = RENDER_DISTANCE;
	result.z = RENDER_DISTANCE;
	return (result);
}

t_vect  get_hcyl_normal_vector(t_vect inter, t_figure hcyl)
{
    t_vect normal;
	t_vect projected;

	projected = substract(inter, hcyl.center);
	normal = normalize(substract(inter, projected));
    return (normal);
}

int		hcyl_eclipses_light(t_point intersection, t_hcyl hcyl, t_point spot)
{
	t_vect	intersection_to_spot;

	if (hcyl.is_reflective)
		return (0);
	intersection_to_spot = normalize(vector(intersection, spot));
	intersection_to_spot = scale(intersection_to_spot, distance(intersection, hcyl.center));
	intersection_to_spot = add(intersection, intersection_to_spot);
	if (distance(intersection_to_spot, hcyl.center) < hcyl.radius)
	{
		if (distance(intersection, spot) > distance(intersection, hcyl.center))
			return (1);
	}
	return (0);
}
