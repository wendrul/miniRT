/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/13 19:55:00 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char*	check_plane_args(t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size < 9 )
		return ("Not enough arguments for a plane.");
	if (args[3] > 1  || args[4] > 1  || args[5] > 1 ||
		args[3] < -1 || args[4] < -1 || args[5] < -1)
		return ("Plane orientation vector values not in range (-1, 1).");
	if (args[6] > 255 || args[7] > 255 || args[8] > 255 ||
		args[6] < 0   || args[7] < 0   || args[8] < 0)
		return ("Invalid RGB color values for plane (must be values between 0 and 255 per color).");
	return (NULL);
}

t_plane	create_plane(t_parse_args parsed)
{
	t_plane	plane;
	char *msg;
	msg = check_plane_args(parsed);
	if (msg != NULL)
		clean_exit(0, msg);

	plane.x = parsed.args[0];
	plane.y = parsed.args[1];
	plane.z = parsed.args[2];
	plane.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
    plane.normal.x = parsed.args[3];
	plane.normal.y = parsed.args[4];
	plane.normal.z = parsed.args[5];
    plane.normal = normalize(plane.normal);
	plane.color = rgb_to_int(new_color(parsed.args[6], parsed.args[7], parsed.args[8]));
	if (parsed.size > 9)
		plane.is_reflective = parsed.args[9];
	plane.intersection = plane_intersection;
	plane.get_normal_at = get_plane_normal_vector;
	plane.eclipses = plane_eclipses_light;
	ft_memcpy(plane.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
	return (plane);
}

t_point		plane_intersection(t_plane plane, t_vect ray, t_point start)
{
	t_vect		result;
    double      r1;

	result.x = RENDER_DISTANCE;
	result.y = RENDER_DISTANCE;
	result.z = RENDER_DISTANCE;
	if (dot(plane.normal, ray) == 0)
        return (result);
    r1 = (dot(plane.center, plane.normal) - dot(plane.normal, start)) / dot(plane.normal, ray);
    if (r1 <= 0)
        return (result);
    result.x = r1 * ray.x + start.x;
    result.y = r1 * ray.y + start.y;
    result.z = r1 * ray.z + start.z;
    return (result);
}

int			get_plane_side(t_point point, t_plane plane)
{
	float dist;
	float norm_point_dist;
	t_vect norm_point;

	dist = distance(plane.center, point);
	norm_point = add(plane.center, plane.normal);
	norm_point_dist = distance(norm_point, point);
	return (dist < norm_point_dist ? -1 : 1);
}

t_vect      get_plane_normal_vector(t_vect inter, t_figure plane)
{
	(void)inter;
    return (plane.normal);
	//should return the opposed vector if coming from the other side
}

int			plane_eclipses_light(t_point intersection, t_plane plane, t_point light)
{
	return (get_plane_side(intersection, plane) != get_plane_side(light, plane));
}

