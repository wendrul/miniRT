/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:03:36 by ede-thom          #+#    #+#             */
/*   Updated: 2020/06/14 20:00:27 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char        **read_lines(int fd)
{
    char    buf[4097];
    char    *lines;
    char    *aux;
    char    **tab_lines;
    int     bytes;

    if ((lines = ft_strdup("")) == NULL)
        return (NULL);
    while ((bytes = read(fd, buf, 4096)))
    {
        buf[bytes] = 0;
        aux = lines;
        if (!(lines = ft_strjoin(lines, buf)))
        {
            free(aux);
            return (NULL);
        }
        free(aux);
    }
    tab_lines = ft_split(lines, '\n');
    free(lines);
    return (tab_lines);
}

void	add_drawable(t_drawable **drawables, char *name, t_figure (*create_func)(t_parse_args parsed))
{
	t_drawable *new;
	t_drawable *head;

	if (!(new = (t_drawable*)malloc(sizeof(t_drawable))))
		clean_exit(1, "malloc wtf");
	head = *drawables;
	new->next = NULL;
	new->name = name;
	new->create = create_func;
	if (!head)
	{
		*drawables = new;
		return ;
	}
	while (head->next)
	{
		head = head->next;
	}
	head->next = new;
}

int			name_cmp(char *fixed, char *var)
{
	return (ft_strncmp(fixed, var, ft_strlen(var)));
}

int		tab_del_return(char **tab, int ret)
{
    char **tmp;

    tmp = tab;
    while (*tab)
	{
        free(*tab++);
	}
	free(tmp);
    return (ret);
}

int		is_valid_figure(char *raw_line, t_drawable *drawables)
{
    char **line;

    if (!(line = ft_split_charset(raw_line, "\f\t\n\r\v ")))
        clean_exit(1, "Malloc failed");
    if (!line[0] || ft_indexof(line[0][0], "#RAcl") != -1)
        return (0);
    while(drawables)
    {
        if (ft_strncmp(drawables->name, line[0], ft_strlen(line[0])) == 0)
            return (tab_del_return(line, 1));
        drawables = drawables->next;
    }
	tab_del_return(line, 0);
	clean_exit(0, "Error parsing file: not a drawable shape.");
	return (0);
}

t_scene count_figures(char **lines, t_drawable *drawables)
{
    t_scene scene;

    scene.resolution = new_vect(WIN_WIDTH, WIN_HEIGHT, 0);
    scene.spotlight = new_vect(0, 0, 0);
    scene.light_color = new_vect(255, 255, 255);
	scene.light_ratio = 1;
	scene.amb_light_ratio = 0.6;
	scene.amb_light_color = new_vect(255, 255, 255);
    scene.camera = new_vect(0,0,0);
	scene.figure_count = 0;
    scene.figure_list = NULL;
    while(*lines)
    {
        if (is_valid_figure(*lines, drawables))
            scene.figure_count++;
        lines++;
    }
    return (scene);
}

t_scene check_light(t_scene scene, t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size != 7)
		clean_exit(0, "Wrong number of arguments for light source.");
	if (args[3] > 1 || args[3] < -1)
		clean_exit(0, "Light ratio is not in range (0, 1).");
	if (args[4] > 255 || args[5] > 255 || args[6] > 255 ||
		args[4] < 0   || args[5] < 0   || args[6] < 0)
		clean_exit(0, "Incorrect values for color in light (must be between 0 and 255 per color)");
	scene.spotlight = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
	scene.light_ratio = args[3];
	scene.light_color = new_vect(parsed.args[4], parsed.args[5], parsed.args[6]);
	return (scene);
}

t_scene check_amb_light(t_scene scene, t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size != 4)
		clean_exit(0, "Wrong number of arguments for Ambient light.");
	if (args[0] < 0 || args[0] > 1)
		clean_exit(0, "Ambient light ratio is not in range (0, 1)");
	if (args[1] > 255 || args[2] > 255 || args[3] > 255 ||
		args[1] < 0   || args[2] < 0   || args[3] < 0)
		clean_exit(0, "Incorrect values for color in ambient light (must be between 0 and 255 per color)");
	scene.amb_light_color = new_vect(parsed.args[1], parsed.args[2], parsed.args[3]);
	scene.amb_light_ratio = args[0];
	return (scene);
}

t_scene	check_camera(t_scene scene, t_parse_args parsed)
{
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size != 7)
		clean_exit(0, "Wrong number of arguments for camera.");
	if (args[3] > 1  || args[4] > 1  || args[5] > 1 ||
		args[3] < -1 || args[4] < -1 || args[5] < -1)
		clean_exit(0, "Camera orientation vector values not in range (-1, 1).");
	if (args[7] > 180 || args[7] < 0)
		clean_exit(0, "FOV is not in range (0, 180).");
	scene.camera = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
	scene.camera = new_vect(parsed.args[0], parsed.args[1], parsed.args[2]);
	scene.fov = args[7];
	return (scene);
}

t_scene check_resolution(t_scene scene, t_parse_args parsed)
{   
	float args[MAX_PARSE_FIGURE_ARGUMENTS];

	ft_memcpy(args, parsed.args, parsed.size * sizeof(float));
	if (parsed.size != 2)
		clean_exit(0, "Wrong number of arguments for resolution.");
	if (args[0] < 0 || args[1] < 0)
		clean_exit(0, "Negative resolution");
	scene.resolution = new_vect(parsed.args[0], parsed.args[1], 0);
	return (scene);
}

static t_scene parse_switch(t_scene scene, t_parse_args parsed, t_drawable *drawables)
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
				scene.figure_list[i] = figure;
				i++;
			}
			drawables = drawables->next;
		}
	}
	return (scene);
}

static t_scene parse_line(t_scene scene, char *raw_line, t_drawable *drawables)
{
	t_parse_args 	parsed;
	t_color			color;
	long			nb;
	char			**line;
	char			**line_ptr;

	if(!(line = ft_split_charset(raw_line, "\f\t\n\r\v ,")))
        clean_exit(1, "Failed to parse line (malloc wtf)");
	if (!line[0] || line[0][0] == '#')
	{
		tab_del_return(line, 0);
		return (scene);
	}
	ft_strlcpy(parsed.name, line[0], MAX_FIGURE_NAME_LENGTH);
	parsed.size = 0;
	line_ptr = line;
	while (*++line)
	{
		if (parsed.size > MAX_PARSE_FIGURE_ARGUMENTS)
			clean_exit(0, "Too many arguments.");
		if ((*line)[0] == '0' && (*line)[1] == 'x')
		{
			nb = ft_atoi_base((*line) + 2, "0123456789abcdef");
			color = int_to_rgb(nb);
			parsed.args[parsed.size]     = color.red;
			parsed.args[parsed.size + 1] = color.green;
			parsed.args[parsed.size + 2] = color.blue;
			parsed.size += 2;
		}
		else
			parsed.args[parsed.size] = ft_atof(*line);
		parsed.size++;
	}
	tab_del_return(line_ptr, 0);
	return (parse_switch(scene, parsed, drawables));
}

static t_scene build_scene(t_scene scene, char **lines, t_drawable *drawables)
{
	if (!(scene.figure_list = 
		(t_figure*)malloc(sizeof(t_figure) * scene.figure_count)))
        clean_exit(1, "Failed to build scene (malloc wtf)");
    while (*lines)
    {
        scene = parse_line(scene, *lines, drawables);
        free(*lines++);
    }
	return (scene);
}

t_scene   parse_scene(char *scene_path, t_drawable *drawables)
{
    int             fd;
    char            **lines;
    t_scene         scene;

    if ((fd = open(scene_path, O_RDONLY)) == -1)
        clean_exit(1, "Failed to open file");
    lines = read_lines(fd);
    scene = count_figures(lines, drawables);
	scene = build_scene(scene, lines, drawables);
	return (scene);
}