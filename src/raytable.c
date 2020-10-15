/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:42:46 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/15 12:43:03 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	**turn_ray_table(t_vect **ray_table, t_scene s,
			t_vect ref, float theta)
{
	int		i;
	int		j;

	i = -1;
	while (++i < s.resolution.y)
	{
		j = -1;
		while (++j < s.resolution.x)
		{
			ray_table[i][j] = apply_rotation(ray_table[i][j], ref, theta);
		}
	}
	return (ray_table);
}

t_vect	**finish_tracer(t_scene s, t_point start,
						t_vect step, t_vect **ray_table)
{
	int		i;
	int		j;
	float	theta;
	t_vect	rot_axis;

	i = -1;
	while (++i < s.resolution.y)
	{
		if (!(ray_table[i] = (t_vect*)malloc(sizeof(t_vect) * s.resolution.x)))
			clean_exit(1, "Malloc Failed");
		j = -1;
		while (++j < s.resolution.x)
		{
			ray_table[i][j].x = start.x + step.x * (float)j;
			ray_table[i][j].y = start.y + step.y * (float)i;
			ray_table[i][j].z = 1;
			ray_table[i][j] = normalize(ray_table[i][j]);
		}
	}
	i = s.active_camera;
	theta = angle(new_vect(0, 0, 1), s.camera_list[i].orientation);
	rot_axis = cross(new_vect(0, 0, 1), s.camera_list[i].orientation);
	if (norm(rot_axis) < EPSILON)
		rot_axis = new_vect(0, 1, 0);
	return (turn_ray_table(ray_table, s, rot_axis, theta));
}

t_vect	**init_tracer(t_scene s)
{
	t_vect	**ray_table;
	t_point	start;
	t_point end;
	t_vect	step;
	int		i;

	if (!(ray_table = (t_vect**)malloc(sizeof(t_vect*) * s.resolution.y)))
		clean_exit(1, "Malloc failed");
	i = s.active_camera;
	start = s.camera_list[i].orientation;
	start.x = -sin(s.camera_list[i].fov / 2);
	start.y = sin(s.camera_list[i].fov / 2 * (s.resolution.y / s.resolution.x));
	start.z = 1;
	end.x = sin(s.camera_list[i].fov / 2);
	end.y = -sin(s.camera_list[i].fov / 2 * (s.resolution.y / s.resolution.x));
	end.z = 1;
	step.x = ((end.x - start.x) / (float)s.resolution.x);
	step.y = ((end.y - start.y) / (float)s.resolution.y);
	return (finish_tracer(s, start, step, ray_table));
}
