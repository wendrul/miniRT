/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/10/14 19:08:35 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*check_sphere_args(t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size < 7)
		return ("Not enough arguments for a sphere.");
	if (args[3] < 0)
		return ("Sphere diameter is negative");
	if (args[4] > 255 || args[5] > 255 || args[6] > 255 ||
		args[4] < 0 || args[5] < 0 || args[6] < 0)
		return ("Invalid RGB values for sphere (must be between 0 and 255).");
	return (NULL);
}

t_sphere	create_sphere(t_parse_args parsed)
{
	t_sphere	sphere;
	char		*msg;

	msg = check_sphere_args(parsed);
	if (msg != NULL)
		clean_exit(1, msg);
	sphere.x = parsed.args[0];
	sphere.y = parsed.args[1];
	sphere.z = parsed.args[2];
	sphere.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
	sphere.radius = parsed.args[3] / 2;
	sphere.color = rgb_to_int(new_color(parsed.args[4],
					parsed.args[5], parsed.args[6]));
	sphere.is_reflective = 0;
	if (parsed.size > 7)
		sphere.is_reflective = parsed.args[7];
	sphere.intersection = sphere_intersection;
	sphere.get_normal_at = get_sphere_normal_vector;
	ft_memcpy(sphere.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
	return (sphere);
}

t_point		solve_equa(t_polynome equa, t_vect result, t_vect ray, t_vect start)
{
	float	t;

	if ((equa.delta = equa.b * equa.b - 4 * equa.a * equa.c) > 0)
	{
		equa.sqrt_delta = sqrt(equa.delta);
		t = ((-equa.b + equa.sqrt_delta) / (2 * equa.a)) * -1;
		if (t > 0)
		{
			result = new_vect(start.x + t * ray.x, start.y + t * ray.y,
							start.z + t * ray.z);
			return (result);
		}
		t = ((-equa.b - equa.sqrt_delta) / (2 * equa.a)) * -1;
		if (t > 0)
		{
			result = new_vect(start.x + t * ray.x, start.y + t * ray.y,
							start.z + t * ray.z);
			return (result);
		}
	}
	result = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
	return (result);
}

t_point		sphere_intersection(t_sphere sphere, t_vect ray, t_point start)
{
	t_polynome	equa;
	t_vect		result;
	t_vect		subbed;

	result = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
	subbed = subtract(sphere.center, start);
	equa.a = 1;
	equa.b = 2 * dot(ray, subbed);
	equa.c = subbed.x * subbed.x + subbed.y * subbed.y
		+ subbed.z * subbed.z - sphere.radius * sphere.radius;
	return (solve_equa(equa, result, ray, start));
}

t_vect		get_sphere_normal_vector(t_vect inter, t_figure s, t_point start)
{
	t_vect	normal;

	normal = scale(true_vect(s.center, inter), 1.0 / s.radius);
	if (dot(subtract(inter, start), normal) < 0)
		return (normal);
	else
		return (scale(normal, -1));
}
