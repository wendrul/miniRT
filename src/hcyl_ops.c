/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hcyl_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/09/26 17:55:50 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*check_hcyl_args(t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size < 11)
		return ("Not enough arguments for an hcylinder.");
	if (args[3] > 1 || args[4] > 1 || args[5] > 1 ||
		args[3] < -1 || args[4] < -1 || args[5] < -1)
		return ("HCylinder orientation vector values not in range (-1, 1).");
	if (args[6] < 0)
		return ("HCylinder diameter is negative");
	if (args[7] < 0)
		return ("HCylinder height is negative");
	if (args[8] > 255 || args[9] > 255 || args[10] > 255 ||
		args[8] < 0 || args[9] < 0 || args[10] < 0)
		return ("Invalid RGB values for hcyl (must be between 0 and 255).");
	return (NULL);
}

t_hcyl		create_hcyl(t_parse_args parsed)
{
	t_hcyl	hcyl;
	char	*msg;

	msg = check_hcyl_args(parsed);
	if (msg != NULL)
		clean_exit(1, msg);
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
	hcyl.color = rgb_to_int(new_color(parsed.args[8],
							parsed.args[9], parsed.args[10]));
	hcyl.is_reflective = 0;
	if (parsed.size > 11)
		hcyl.is_reflective = parsed.args[11];
	hcyl.intersection = hcyl_intersection;
	hcyl.get_normal_at = get_hcyl_normal_vector;
	ft_memcpy(hcyl.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
	return (hcyl);
}

t_point		solve_hcyl_equa(t_polynome equa, t_figure hcyl, t_vect r, t_vect s)
{
	t_vect	result;
	float	t;

	if ((equa.delta = equa.b * equa.b - 4 * equa.a * equa.c) > EPSILON)
	{
		equa.sqrt_delta = sqrt(equa.delta);
		t = ((-equa.b + equa.sqrt_delta) / (2 * equa.a)) * -1;
		if (t > 0)
		{
			result = new_vect(s.x + t * r.x, s.y + t * r.y, s.z + t * r.z);
			t = dot(subtract(result, hcyl.center), hcyl.normal);
			if (t < hcyl.length && t > 0)
				return (result);
		}
		t = ((-equa.b - equa.sqrt_delta) / (2 * equa.a)) * -1;
		if (t > 0)
		{
			result = new_vect(s.x + t * r.x, s.y + t * r.y, s.z + t * r.z);
			t = dot(subtract(result, hcyl.center), hcyl.normal);
			if (t < hcyl.length && t > 0)
				return (result);
		}
	}
	result = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
	return (result);
}

t_point		hcyl_intersection(t_hcyl hcyl, t_vect r, t_point s)
{
	t_polynome	equa;
	t_vect		v1;
	t_vect		v2;

	v1 = subtract(projection(s, hcyl.normal), s);
	v2 = subtract(hcyl.center, projection(hcyl.center, hcyl.normal));
	v2 = add(v1, v2);
	v1 = subtract(r, projection(r, hcyl.normal));
	equa.a = pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2);
	equa.b = 2 * (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	equa.c = pow(v2.x, 2) + pow(v2.y, 2) + pow(v2.z, 2) - pow(hcyl.radius, 2);
	return (solve_hcyl_equa(equa, hcyl, r, s));
}

t_vect		get_hcyl_normal_vector(t_vect inter, t_figure hcyl, t_point s)
{
	t_vect normal;
	t_vect projected;
	t_vect u;

	u = subtract(inter, hcyl.center);
	projected = projection(u, hcyl.normal);
	normal = normalize(subtract(u, projected));
	if (dot(subtract(inter, s), normal) < 0)
		return (normal);
	else
		return (scale(normal, -1));
}
