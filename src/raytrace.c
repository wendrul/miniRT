/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:15:30 by dhorvill          #+#    #+#             */
/*   Updated: 2020/10/15 12:55:03 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inters	get_closest(t_scene s, t_vect ray, t_vect start)
{
	int			i;
	t_inters	inter;
	t_inters	closest;

	closest.distance = RENDER_DISTANCE;
	i = -1;
	while (++i < s.figure_count)
	{
		inter.pos = s.figure_list[i].intersection(s.figure_list[i], ray, start);
		if ((inter.distance = norm(true_vect(start, inter.pos)))
								< closest.distance
			&& inter.distance > MIN_RENDER_DIST)
		{
			inter.index = i;
			closest = inter;
		}
	}
	return (closest);
}

int			get_inter_color(t_scene s, t_inters closest,
							t_vect start, int refl_col)
{
	float	lum_intensity;
	int		i;

	lum_intensity = get_lum_intensity(s.figure_list[closest.index],
					closest.pos, s.spotlight, start);
	lum_intensity = (1 - s.amb_light_ratio) * lum_intensity + s.amb_light_ratio;
	i = -1;
	while (++i < s.figure_count)
	{
		if (i == closest.index)
			continue;
		if (figure_eclipses_light(closest.pos, s.figure_list[i], s.spotlight))
		{
			lum_intensity = s.amb_light_ratio;
			break ;
		}
	}
	return (filter_color(color_shade(lum_intensity,
			s.figure_list[closest.index], refl_col), s.adj_light_color));
}

int			get_refl_color(t_scene s, t_inters closest,
							t_vect ray, t_vect start)
{
	int		refl_col;
	t_vect	refl_dir;

	refl_col = 0;
	if (s.figure_list[closest.index].is_reflective > 0)
	{
		refl_dir = get_refl_vector(
				s.figure_list[closest.index], closest.pos, ray, start);
		refl_col = trace_ray(
				refl_dir, s, add(closest.pos, scale(refl_dir, EPSILON)));
	}
	return (refl_col);
}

int			trace_ray(t_vect ray, t_scene s, t_point start)
{
	int			refl_col;
	static int	current_recursion_depth = 0;
	t_inters	closest;

	if (++current_recursion_depth > MAX_RECURSION_DEPTH)
	{
		current_recursion_depth--;
		return (0);
	}
	closest = get_closest(s, ray, start);
	if (closest.distance < RENDER_DISTANCE)
	{
		refl_col = get_refl_color(s, closest, ray, start);
		current_recursion_depth--;
		return (get_inter_color(s, closest, start, refl_col));
	}
	current_recursion_depth--;
	return (rgb_to_int(new_color(s.amb_light_color.x,
			s.amb_light_color.y, s.amb_light_color.z)));
}
