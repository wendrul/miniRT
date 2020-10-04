/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:15:30 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/16 17:12:38 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect **turn_ray_table(t_vect **ray_table, t_scene scene, t_vect ref, float theta)
{
	int		i;
	int		j;

	i = -1;
	while (++i < scene.resolution.y)
	{
		j = -1;
		while (++j < scene.resolution.x)
		{
			ray_table[i][j] = apply_rotation(ray_table[i][j], ref, theta);
		}
	}
	return (ray_table);
}

t_vect	**init_tracer(t_scene scene)
{
	t_vect	**ray_table;
	t_point	start;
	t_point end;
	t_vect	step;
	t_vect	def_rot;
	int		i;
	int		j;

	if (!(ray_table = (t_vect**)malloc(sizeof(t_vect*) * scene.resolution.y)))
		exit(0);
	i = scene.active_camera;
	start = scene.camera_list[i].orientation;
	start.x = -sin(scene.camera_list[i].fov / 2);
	start.y = sin(scene.camera_list[i].fov / 2* (scene.resolution.y / scene.resolution.x));	
	start.z = 1;
	end.x = sin(scene.camera_list[i].fov / 2);
	end.y = -sin(scene.camera_list[i].fov / 2 * (scene.resolution.y / scene.resolution.x));
	end.z = 1;
	step.x = ((end.x - start.x) / (float)scene.resolution.x);
	step.y = ((end.y - start.y) / (float)scene.resolution.y);
	i = -1;
	while (++i < scene.resolution.y)
	{
		if (!(ray_table[i] = (t_vect*)malloc(sizeof(t_vect) * scene.resolution.x)))
			exit(0);
		j = -1;
		while (++j < scene.resolution.x)
		{
			ray_table[i][j].x = start.x + step.x * (float)j;
			ray_table[i][j].y = start.y + step.y * (float)i; //daniel doubts, Etienne owns
			ray_table[i][j].z = 1;
			ray_table[i][j] = normalize(ray_table[i][j]);
		}
	}
	def_rot = new_vect(0, 0, 1);
	i = scene.active_camera;
	float theta = acos(dot(def_rot, scene.camera_list[i].orientation) / (norm(def_rot) * norm(scene.camera_list[i].orientation))); 
	ray_table = turn_ray_table(ray_table, scene, cross(def_rot, scene.camera_list[i].orientation), theta);
	return (ray_table);
}

int		color_shade(float intensity, t_figure figure, int reflective_color)
{
	t_color base;
	t_color	reflective_rgb;
	
	base = color_intensity(figure.color, intensity);
	reflective_rgb = int_to_rgb(0);
	if (figure.is_reflective > 0)
		reflective_rgb = int_to_rgb(reflective_color);
	if (figure.is_reflective == 0)
		return (rgb_to_int(base));
	return (weighted_average(base, reflective_rgb, figure.is_reflective));

}

float	get_lum_intensity(t_figure figure, t_point inter, t_point spotlight, t_point start)
{
	t_point	normal;
	t_point	ray_to_light;
	float	result;

	normal = figure.get_normal_at(inter, figure, start);
	ray_to_light = vector(inter, spotlight);
	if ((result = dot(normal, ray_to_light)) > 0)
		return (result);
	return (0);
}

int		trace_ray(t_vect ray, t_scene scene, t_point start, int prev_index, int ignore, t_r_stack stack) //ignored index is to be changed (last_HIT_index)
{
	int			i;
	int			index;
	float		lum_intensity;
	float		closest_distance;
	float		distance;
	int			reflective_color;

	static int 	current_recursion_depth = 0;
	t_point		intersection;
	t_point		closest_intersection;
	t_vect		reflected_dir;
	t_vect		modified_start;

	if (++current_recursion_depth > MAX_RECURSION_DEPTH)
	{
		current_recursion_depth--;
		return (0);
	}
	closest_distance = RENDER_DISTANCE;
	i = -1;
	while (++i < scene.figure_count)
	{
		if (i == prev_index && ignore)
			continue;
		
		intersection = scene.figure_list[i].intersection(scene.figure_list[i], ray, start);
		if ((distance = norm(true_vect(start, intersection))) < closest_distance && distance > MIN_RENDER_DIST)
		{
			index = i;
			closest_distance = distance;
			closest_intersection = intersection;
		}
	}
	if (closest_distance < RENDER_DISTANCE)
	{
		if (scene.figure_list[index].is_reflective > 0 && index != peek_index(stack))
		{
			reflected_dir = get_reflective_vector(scene.figure_list[index], closest_intersection, ray, start);
			modified_start = add(closest_intersection, scale(reflected_dir, EPSILON)); 
			reflective_color = trace_ray(reflected_dir, scene, modified_start, index, 0, stack);
		}
		lum_intensity = get_lum_intensity(scene.figure_list[index], closest_intersection, scene.spotlight, start);
		lum_intensity = (1 - scene.amb_light_ratio) * lum_intensity + scene.amb_light_ratio;
		i = -1;
		while (++i < scene.figure_count)
		{
			if (i == index)
				continue;
			if (figure_eclipses_light(closest_intersection, scene.figure_list[i], scene.spotlight))
			{
				lum_intensity = scene.amb_light_ratio;
				break;
			}
		}
		current_recursion_depth--;
		return (filter_color(color_shade(lum_intensity, scene.figure_list[index], reflective_color), scene.adj_light_color));
	}
	current_recursion_depth--;
	return (rgb_to_int(new_color(scene.amb_light_color.x, scene.amb_light_color.y, scene.amb_light_color.z)));
}
