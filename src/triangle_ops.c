/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/10/14 19:23:27 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*check_triangle_args(t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size < 12)
		return ("Not enough arguments for a triangle.");
	if (args[9] > 255 || args[10] > 255 || args[11] > 255 ||
		args[9] < 0 || args[10] < 0 || args[11] < 0)
		return ("Invalid RGB values for triangle(must between 0 and 255).");
	return (NULL);
}

t_triangle	create_triangle(t_parse_args parsed)
{
	t_triangle	triangle;
	char		*msg;

	msg = check_triangle_args(parsed);
	if (msg != NULL)
		clean_exit(1, msg);
	triangle.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
	triangle.normal = new_vect(parsed.args[3], parsed.args[4], parsed.args[5]);
	triangle.third = new_vect(parsed.args[6], parsed.args[7], parsed.args[8]);
	triangle.color = rgb_to_int(new_color(parsed.args[9],
						parsed.args[10], parsed.args[11]));
	triangle.is_reflective = 0;
	if (parsed.size > 12)
		triangle.is_reflective = parsed.args[12];
	triangle.intersection = triangle_intersection;
	triangle.get_normal_at = get_triangle_normal_vector;
	ft_memcpy(triangle.name, parsed.name,
				sizeof(char) * ft_strlen(parsed.name));
	return (triangle);
}

t_point		triangle_intersection(t_triangle t, t_vect ray, t_point start)
{
	t_vect		q;
	double		r1;
	t_vect		render;
	t_vect		n;

	render = new_vect(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
	n = get_triangle_normal_vector(t.center, t, start);
	if (norm(n) < EPSILON)
		return (render);
	if (dot(n, ray) == 0)
		return (render);
	r1 = (dot(t.center, n) - dot(n, start)) / dot(n, ray);
	if (r1 <= 0)
		return (render);
	q = new_vect(start.x + r1 * ray.x, start.y + r1 * ray.y,
							start.z + r1 * ray.z);
	if (dot(cross(subtract(t.normal, t.center), subtract(q, t.center)), n) >= 0
	&& dot(cross(subtract(t.third, t.normal), subtract(q, t.normal)), n) >= 0
	&& dot(cross(subtract(t.center, t.third), subtract(q, t.third)), n) >= 0)
		return (q);
	if (dot(cross(subtract(t.normal, t.center), subtract(q, t.center)), n) <= 0
	&& dot(cross(subtract(t.third, t.normal), subtract(q, t.normal)), n) <= 0
	&& dot(cross(subtract(t.center, t.third), subtract(q, t.third)), n) <= 0)
		return (q);
	return (render);
}

t_vect		get_triangle_normal_vector(t_vect inter, t_figure tri, t_point s)
{
	t_vect product;

	product = cross(true_vect(tri.center, tri.normal),
						true_vect(tri.center, tri.third));
	if (norm(product) < EPSILON)
		return (new_vect(0, 0, 0));
	product = normalize(product);
	if (dot(subtract(inter, s), product) < 0)
		return (product);
	else
		return (scale(product, -1));
}
