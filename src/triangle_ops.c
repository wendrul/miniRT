/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:01:17 by dhorvill          #+#    #+#             */
/*   Updated: 2020/09/25 11:24:49 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char*	check_triangle_args(t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size < 12 )
		return ("Not enough arguments for a triangle.");
	if (args[8] > 255 || args[9] > 255 || args[10] > 255 ||
		args[8] < 0   || args[9] < 0   || args[10] < 0)
		return ("Invalid RGB color values for triangle (must be values between 0 and 255 per color).");
	return (NULL);
}

t_triangle	create_triangle(t_parse_args parsed)
{
	t_triangle	triangle;
	char *msg;
	msg = check_triangle_args(parsed);
	if (msg != NULL)
		clean_exit(0, msg);

	triangle.center = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
    triangle.normal = new_vect(parsed.args[3], parsed.args[4], parsed.args[5]);
    triangle.third = new_vect(parsed.args[6], parsed.args[7], parsed.args[8]);
	triangle.color = rgb_to_int(new_color(parsed.args[9], parsed.args[10], parsed.args[11]));
	triangle.is_reflective = 0;
	if (parsed.size > 12)
		triangle.is_reflective = parsed.args[12];
	triangle.intersection = triangle_intersection;
	triangle.get_normal_at = get_triangle_normal_vector;
	triangle.eclipses = triangle_eclipses_light;
	ft_memcpy(triangle.name, parsed.name, sizeof(char) * ft_strlen(parsed.name));
	return (triangle);
}

t_point     triangle_intersection(t_triangle triangle, t_vect ray, t_point start)
{
    t_vect        result;
    t_vect      u;
    double      r1;

    result.x = RENDER_DISTANCE;
    result.y = RENDER_DISTANCE;
    result.z = RENDER_DISTANCE;
    if (dot(triangle.normal, ray) == 0)
        return (result);
    r1 = (dot(triangle.center, triangle.normal) - dot(triangle.normal, start)) / dot(triangle.normal, ray);
    if (r1 <= 0)
        return (result);
    result.x = r1 * ray.x + start.x;
    result.y = r1 * ray.y + start.y;
    result.z = r1 * ray.z + start.z;
    u = substract(result, triangle.center);
    if (!(norm_inf(u) < triangle.length))
    {
      result.x = RENDER_DISTANCE;
      result.y = RENDER_DISTANCE;
      result.z = RENDER_DISTANCE;
    }        
    return (result);
}


t_vect      get_triangle_normal_vector(t_vect inter, t_figure triangle, t_point start)
{
	if (dot(substract(inter, start), triangle.normal) < 0)
		return (triangle.normal);
	else
		return(scale(triangle.normal, -1));
}

int			triangle_eclipses_light(t_point inter, t_triangle triangle, t_point light)
{
	return (figure_eclipses_light(inter, triangle, light));
}

