/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:58:24 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/15 18:47:12 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	parse_switch(t_scene scene, t_parse_args parsed, t_drawable *drawables)
{
	t_figure	figure;
	static int	i = 0;

	if (name_cmp(parsed.name, "R") == 0)
		scene = check_resolution(scene, parsed);
	else if (name_cmp(parsed.name, "A") == 0)
		scene = check_amb_light(scene, parsed);
	else if (name_cmp(parsed.name, "c") == 0)
		scene = check_camera(scene, parsed);
	else if (name_cmp(parsed.name, "l") == 0)
		scene = check_light(scene, parsed);
	else
	{
		while (drawables)
		{
			if (name_cmp(parsed.name, drawables->name) == 0)
			{
				figure = drawables->create(parsed);
				scene.figure_list[i++] = figure;
				break ;
			}
			drawables = drawables->next;
		}
	}
	return (scene);
}

void	read_parse_args(char **line, t_parse_args *parsed)
{
	long	nb;
	t_color	color;

	while (*++line)
	{
		if (parsed->size > MAX_PARSE_FIGURE_ARGUMENTS)
			clean_exit(1, "A shape has too many arguments.");
		if ((*line)[0] == '0' && (*line)[1] == 'x')
		{
			nb = ft_atoi_base((*line) + 2, "0123456789abcdef");
			color = int_to_rgb(nb);
			parsed->args[parsed->size] = color.red;
			parsed->args[parsed->size + 1] = color.green;
			parsed->args[parsed->size + 2] = color.blue;
			parsed->size += 2;
		}
		else
			parsed->args[parsed->size] = ft_atof(*line);
		parsed->size++;
	}
}

t_scene	parse_line(t_scene scene, char *raw_line, t_drawable *drawables)
{
	t_parse_args	parsed;
	char			**line;

	if (!(line = ft_split_charset(raw_line, "\f\t\n\r\v ,")))
		clean_exit(1, "Failed to parse line, malloc failed");
	if (!line[0] || line[0][0] == '#')
	{
		tab_del_return(line, 0);
		return (scene);
	}
	ft_strlcpy(parsed.name, line[0], MAX_FIGURE_NAME_LENGTH);
	parsed.size = 0;
	read_parse_args(line, &parsed);
	tab_del_return(line, 0);
	return (parse_switch(scene, parsed, drawables));
}

t_scene	build_scene(t_scene scene, char **lines, t_drawable *drawables)
{
	if (!(scene.figure_list =
		(t_figure*)malloc(sizeof(t_figure) * scene.figure_count)))
		clean_exit(1, "Failed to build scene, malloc failed");
	scene.active_camera = 0;
	scene.camera_count = count_cameras(lines);
	scene.light_count = count_lights(lines);
	count_res_ambient(lines);
	if (!(scene.camera_list =
		(t_camera*)malloc(sizeof(t_camera) * scene.camera_count)))
		clean_exit(1, "Failed to build scene, malloc failed");
	if (!(scene.light_list =
		(t_light*)malloc(sizeof(t_light) * ft_max(scene.light_count, 1))))
		clean_exit(1, "Failed to build scene, malloc failed");
	while (*lines)
	{
		scene = parse_line(scene, *lines, drawables);
		free(*lines++);
	}
	if (scene.light_count > 0)
		return (scene);
	scene.light_list[0].pos = new_vect(0, 0, 0);
	scene.light_list[0].adj_color = rgb_to_int(rgb_color_intensity(
		new_color(255, 255, 255), scene.amb_light_ratio));
	return (scene);
}

t_scene	parse_scene(char *scene_path, t_drawable *drawables)
{
	int			fd;
	char		**lines;
	t_scene		scene;

	if ((fd = open(scene_path, O_RDONLY)) == -1)
		clean_exit(1, "Failed to open file");
	lines = read_lines(fd);
	scene = count_figures(lines, drawables);
	scene = build_scene(scene, lines, drawables);
	free(lines);
	return (scene);
}
