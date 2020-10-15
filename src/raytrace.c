/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:15:30 by dhorvill          #+#    #+#             */
/*   Updated: 2020/10/15 20:20:42 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_inters	get_closest(t_scene s, t_vect ray, t_vect start)
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

static int		get_inter_color(t_scene s, t_inters closest,
							t_vect start, int light)
{
	float	lum_intensity;
	int		i;

	lum_intensity = get_lum_intensity(s.figure_list[closest.index],
					closest.pos, s.light_list[light].pos, start);
	lum_intensity = (1 - s.amb_light_ratio) * lum_intensity + s.amb_light_ratio;
	i = -1;
	while (++i < s.figure_count)
	{
		if (i == closest.index)
			continue;
		if (figure_eclipses_light(closest.pos,
					s.figure_list[i], s.light_list[light].pos))
		{
			lum_intensity = s.amb_light_ratio;
			break ;
		}
	}
	return (filter_color(color_shade(lum_intensity,
			s.figure_list[closest.index], closest.refl_color),
			s.light_list[light].adj_color));
}

static int		mix_colors(t_scene s, t_inters closest, t_vect start)
{
	int		i;
	int		flag;
	int		color;
	t_color total;
	t_color tmp;

	i = -1;
	total = new_color(0, 0, 0);
	flag = 0;
	while (++i < s.light_count)
	{
		color = get_inter_color(s, closest, start, i);
		tmp = int_to_rgb(color);
		total.red += tmp.red;
		total.blue += tmp.blue;
		total.green += tmp.green;
	}
	total.red /= s.light_count;
	total.blue /= s.light_count;
	total.green /= s.light_count;
	return (rgb_to_int(total));
}

int				get_refl_color(t_scene s, t_inters closest,
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

int				trace_ray(t_vect ray, t_scene s, t_point start)
{
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
		closest.refl_color = get_refl_color(s, closest, ray, start);
		current_recursion_depth--;
		return (mix_colors(s, closest, start));
	}
	current_recursion_depth--;
	return (rgb_to_int(new_color(s.amb_light_color.x,
			s.amb_light_color.y, s.amb_light_color.z)));
}
