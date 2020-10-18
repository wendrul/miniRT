/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:42:46 by agoodwin          #+#    #+#             */
/*   Updated: 2020/10/18 20:25:53 by ede-thom         ###   ########.fr       */
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

t_vect	rotate_vect(t_vect ori, t_vect ret)
{
	ret = normalize(ret);
	ret = apply_rotation(ret, new_vect(1, 0, 0), M_PI * ori.x);
	ret = apply_rotation(ret, new_vect(0, 1, 0), M_PI * ori.y);
	ret = apply_rotation(ret, new_vect(0, 0, 1), M_PI * ori.z);
	return (ret);
}

t_vect	**finish_tracer(t_scene s, t_point start,
						t_vect step, t_vect **ray_table)
{
	int		i;
	int		j;
	t_vect	ori;

	ori = s.camera_list[s.active_camera].orientation;
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
			ray_table[i][j] = rotate_vect(ori, ray_table[i][j]);
		}
	}
	return (ray_table);
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
