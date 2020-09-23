/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hcyl_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
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
	if (parsed.size < 7 )
		return ("Not enough arguments for a hollow cylinder.");
	if (args[3] < 0)
		return ("Hollow cylinder radius is negative");
	if (args[4] > 255 || args[5] > 255 || args[6] > 255 ||
		args[4] < 0   || args[5] < 0   || args[6] < 0)
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
	hcyl.radius = parsed.args[3];
	hcyl.color = rgb_to_int(new_color(parsed.args[4], parsed.args[5], parsed.args[6]));
	if (parsed.size > 7)
		hcyl.is_reflective = parsed.args[7];
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
	t_vect		subbed;
	float		t;

	subbed = substract(hcyl.center, start);
	equa.a = 1;
	equa.b = 2 * dot(ray, subbed);
	equa.c = subbed.x * subbed.x + subbed.y * subbed.y 
		+ subbed.z * subbed.z - hcyl.radius * hcyl.radius;
	//printf("x:%f     y:%f     z:%f \n", hcyl.center.x, hcyl.center.y, hcyl.center.z);

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

    normal = scale(true_vect(hcyl.center, inter), 1.0 / hcyl.radius);
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
