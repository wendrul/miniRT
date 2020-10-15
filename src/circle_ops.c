/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/09/25 11:24:49 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*check_circle_args(t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size < 10)
		return ("Not enough arguments for a circle.");
	if (args[3] > 1 || args[4] > 1 || args[5] > 1 ||
		args[3] < -1 || args[4] < -1 || args[5] < -1)
		return ("Circle orientation vector values not in range (-1, 1).");
	if (args[6] < 0)
		return ("Circle diameter is negative");
	if (args[7] > 255 || args[8] > 255 || args[9] > 255 ||
		args[7] < 0 || args[8] < 0 || args[9] < 0)
		return ("Invalid RGB values for circle (must be between 0 and 255).");
	return (NULL);
}

t_circle	create_circle(t_parse_args parsed)
{
	t_circle	circle;
	char		*msg;

	msg = check_circle_args(parsed);
	if (msg != NULL)
		clean_exit(1, msg);
	circle.x = parsed.args[0];
	circle.y = parsed.args[1];
	circle.z = parsed.args[2];
	circle.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
	circle.normal.x = parsed.args[3];
	circle.normal.y = parsed.args[4];
	circle.normal.z = parsed.args[5];
	circle.normal = normalize(circle.normal);
	circle.radius = parsed.args[6] / 2;
	circle.color = rgb_to_int(new_color(parsed.args[7],
								parsed.args[8], parsed.args[9]));
	circle.is_reflective = 0;
	if (parsed.size > 10)
		circle.is_reflective = parsed.args[10];
	circle.intersection = circle_intersection;
	circle.get_normal_at = get_circle_normal_vector;
	ft_memcpy(circle.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
	return (circle);
}

t_point		circle_intersection(t_circle circle, t_vect ray, t_point start)
{
	t_vect	result;
	t_vect	u;
	double	r1;

	result.x = RENDER_DISTANCE;
	result.y = RENDER_DISTANCE;
	result.z = RENDER_DISTANCE;
	if (dot(circle.normal, ray) == 0)
		return (result);
	r1 = (dot(circle.center, circle.normal) -
			dot(circle.normal, start)) / dot(circle.normal, ray);
	if (r1 <= 0)
		return (result);
	result.x = r1 * ray.x + start.x;
	result.y = r1 * ray.y + start.y;
	result.z = r1 * ray.z + start.z;
	u = subtract(result, circle.center);
	if (!(norm(u) < circle.radius))
	{
		result.x = RENDER_DISTANCE;
		result.y = RENDER_DISTANCE;
		result.z = RENDER_DISTANCE;
	}
	return (result);
}

t_vect		get_circle_normal_vector(t_vect inter,
										t_figure circle, t_point start)
{
	if (dot(subtract(inter, start), circle.normal) < 0)
		return (circle.normal);
	else
		return (scale(circle.normal, -1));
}
