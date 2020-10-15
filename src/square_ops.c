/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/10/14 19:05:38 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*check_square_args(t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size < 10)
		return ("Not enough arguments for a square.");
	if (args[3] > 1 || args[4] > 1 || args[5] > 1 ||
		args[3] < -1 || args[4] < -1 || args[5] < -1)
		return ("Square orientation vector values not in range (-1, 1).");
	if (args[6] < 0)
		return ("Square diameter is negative");
	if (args[7] > 255 || args[8] > 255 || args[9] > 255 ||
		args[7] < 0 || args[8] < 0 || args[9] < 0)
		return ("Invalid RGB values for square(must between 0 and 255).");
	return (NULL);
}

t_square	create_square(t_parse_args parsed)
{
	t_square	square;
	char		*msg;

	msg = check_square_args(parsed);
	if (msg != NULL)
		clean_exit(1, msg);
	square.x = parsed.args[0];
	square.y = parsed.args[1];
	square.z = parsed.args[2];
	square.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
	square.normal.x = parsed.args[3];
	square.normal.y = parsed.args[4];
	square.normal.z = parsed.args[5];
	square.normal = normalize(square.normal);
	square.length = parsed.args[6];
	square.color = rgb_to_int(new_color(parsed.args[7],
				parsed.args[8], parsed.args[9]));
	square.is_reflective = 0;
	if (parsed.size > 10)
		square.is_reflective = parsed.args[10];
	square.intersection = square_intersection;
	square.get_normal_at = get_square_normal_vector;
	ft_memcpy(square.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
	return (square);
}

static int	final_square_condition(t_vect u, t_vect width, t_vect h, t_figure s)
{
	return ((dot(u, width) < s.length
			&& dot(u, width) > 0
			&& dot(u, h) < s.length
			&& dot(u, h) > 0));
}

t_point		square_intersection(t_square square, t_vect ray, t_point start)
{
	t_vect	result;
	t_vect	u;
	t_vect	width;
	t_vect	height;
	double	r1;

	result = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
	if (dot(square.normal, ray) == 0)
		return (result);
	if ((r1 = (dot(square.center, square.normal)
			- dot(square.normal, start)) / dot(square.normal, ray)) <= 0)
		return (result);
	result = new_vect(start.x + r1 * ray.x, start.y + r1 * ray.y,
							start.z + r1 * ray.z);
	u = subtract(result, square.center);
	if (square.normal.x != 0)
		width = normalize(new_vect((square.normal.z) / square.normal.x, 0, -1));
	else if (square.normal.z != 0)
		width = normalize(new_vect((square.normal.x) / square.normal.z, 0, -1));
	else
		width = new_vect(1, 0, 0);
	height = cross(square.normal, width);
	if (!final_square_condition(u, width, height, square))
		result = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
	return (result);
}

t_vect		get_square_normal_vector(t_vect inter, t_figure square, t_point s)
{
	if (dot(subtract(inter, s), square.normal) < 0)
		return (square.normal);
	else
		return (scale(square.normal, -1));
}
