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

int     tab_del(char **tab, int ret)
{
    char **tmp;

    tmp = tab;
    while (*tab)
        free(*tab++);
    free(tmp);
    return (ret);
}

static int    is_drawable(char *cur_line, t_drawable *drawables)
{
    char **line;

    if (cur_line[0] == '#')
        return (0);
    if(!(line = ft_split_charset(cur_line, "\f\t\n\r\v ")))
        clean_exit(1, "Malloc failed");
    if (!*line)
        return (0);
    while(drawables)
    {
        if (ft_strncmp(drawables->name, line[0], ft_strlen(line[0])) == 0)
            return (tab_del(line, 1));
        drawables = drawables->next;
    }
    return (tab_del(line, 0));
}

static t_scene     count_figures(char **lines, t_drawable *drawables)
{
    t_scene scene;

    scene.spotlight.x = 0;
    scene.spotlight.y = 0;
    scene.spotlight.z = 0;
    scene.figure_count = 0;
    scene.figure_list = NULL;
    while(*lines)
    {
        if (is_drawable(*lines, drawables))
            scene.figure_count++;
        lines++;
    }
    return (scene);
}

static t_scene    create_figure(t_scene scene, char *cur_line, t_drawable *drawables)
{
    t_figure    figure;
    char        **line;
    static      int i = 0;


    if (cur_line[0] == '#')
        return (scene);
    if(!(line = ft_split_charset(cur_line, "\f\t\n\r\v ")))
        clean_exit(1, "Failed to create figure (malloc wtf)");
    if (!*line)
        return (scene);
    while(drawables)
    {
        if (ft_strncmp(drawables->name, line[0], ft_strlen(line[0])) == 0)
        {
            figure = (drawables->create)(ft_atof(line[1]),
                                         ft_atof(line[2]),
                                         ft_atof(line[3]),
                                         ft_atof(line[4]),
                                         ft_atoi_base(line[5], "0123456789abcdef"),
										 ft_atof(line[6]));
            scene.figure_list[i] = figure;
            i++;
            break;
            //this segs if line[i] doesn't exist, should just put the value to 0 if that
        }
        if (ft_strncmp("Spotlight", line[0], ft_strlen(line[0])) == 0)
        {
            scene.spotlight.x = ft_atof(line[1]);
            scene.spotlight.y = ft_atof(line[2]);
            scene.spotlight.z = ft_atof(line[3]);
            break;
        }
        drawables = drawables->next;
    }
    tab_del(line, 0);
    return (scene);
}

static void build_scene(t_scene *scene, char **lines, t_drawable *drawables)
{
    t_scene s;

    s = *scene;
    if (!(s.figure_list = (t_figure*)malloc(sizeof(t_figure) * s.figure_count)))
        clean_exit(1, "Failed to build scene (malloc wtf)");
    while (*lines)
    {
        s = create_figure(s, *lines, drawables);
        free(*lines++);
    }
    *scene = s;
}

void	add_drawable(t_drawable **drawables, char *name, t_figure (*create_func)(CREATE_ARGS))
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
		head = head->next;
	head->next = new;
}

t_scene     parse_scene(char *scene_path, t_drawable *drawables)
{
    int     fd;
    char    **lines;
    t_scene scene;
    
    if ((fd = open(scene_path, O_RDONLY)) == -1)
        clean_exit(1, "Failed to open file");
    lines = read_lines(fd);
    scene = count_figures(lines, drawables);
    build_scene(&scene, lines, drawables);
    //printf("x: %f, y: %f, z: %f\n", scene.figure_list[0].x, scene.figure_list[0].y, scene.figure_list[0].z);
    free(lines);
    return (scene);
}
