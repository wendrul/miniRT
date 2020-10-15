/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:09:06 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/15 20:18:37 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	check_light(t_scene scene, t_parse_args parsed)
{
	float		args[MAX_PARSE_FIGURE_ARGUMENTS];
	static int	i = 0;

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size != 7)
		clean_exit(1, "Wrong number of arguments for light source.");
	if (args[3] > 1 || args[3] < -1)
		clean_exit(1, "Light ratio is not in range [0, 1].");
	if (args[4] > 255 || args[5] > 255 || args[6] > 255 ||
		args[4] < 0 || args[5] < 0 || args[6] < 0)
		clean_exit(1, "RGB values for light must be between 0 and 255");
	scene.light_list[i].pos = new_vect(args[0], args[1], args[2]);
	scene.light_list[i].ratio = args[3];
	scene.light_list[i].color = new_vect(parsed.args[4],
						parsed.args[5], parsed.args[6]);
	scene.light_list[i].adj_color = rgb_to_int(rgb_color_intensity(
		new_color_vect(scene.light_list[i].color), scene.light_list[i].ratio));
	i++;
	return (scene);
}

t_scene	check_amb_light(t_scene scene, t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size != 4)
		clean_exit(1, "Wrong number of arguments for Ambient light.");
	if (args[0] < 0 || args[0] > 1)
		clean_exit(1, "Ambient light ratio is not in range [0, 1]");
	if (args[1] > 255 || args[2] > 255 || args[3] > 255 ||
		args[1] < 0 || args[2] < 0 || args[3] < 0)
		clean_exit(1, "RGB values for amb-light must be between 0 and 255");
	scene.amb_light_color = new_vect(parsed.args[1],
							parsed.args[2], parsed.args[3]);
	scene.amb_light_ratio = args[0];
	return (scene);
}

t_scene	check_camera(t_scene scene, t_parse_args parsed)
{
	static int	i = 0;
	float		args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size != 7)
		clean_exit(1, "Wrong number of arguments for camera.");
	if (args[3] > 1 || args[4] > 1 || args[5] > 1 ||
		args[3] < -1 || args[4] < -1 || args[5] < -1)
		clean_exit(1, "Camera orientation vector values not in range [-1, 1].");
	if (args[6] > 180 || args[6] < 0)
		clean_exit(1, "FOV is not in range [0, 180].");
	scene.camera_list[i].location =
					new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
	scene.camera_list[i].orientation =
					new_vect(parsed.args[3], parsed.args[4], parsed.args[5]);
	scene.camera_list[i].fov = args[6];
	if (norm(scene.camera_list[i].orientation) < EPSILON)
		clean_exit(1, "Camera orientation cannot be zero vector");
	scene.camera_list[i].orientation =
					normalize(scene.camera_list[i].orientation);
	scene.camera_list[i].fov = args[6] * M_PI / 180;
	i++;
	return (scene);
}

t_scene	check_resolution(t_scene scene, t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size != 2)
		clean_exit(1, "Wrong number of arguments for resolution.");
	if (args[0] < 0 || args[1] < 0)
		clean_exit(1, "Negative resolution");
	scene.resolution = new_vect(parsed.args[0], parsed.args[1], 0);
	return (scene);
}
