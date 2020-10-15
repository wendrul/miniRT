/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:03:36 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/14 20:28:45 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**read_lines(int fd)
{
	char	buf[4097];
	char	*lines;
	char	*aux;
	char	**tab_lines;
	int		bytes;

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

void	add_drawable(t_drawable **drawables, char *name,
				t_figure (*create_func)(t_parse_args parsed))
{
	t_drawable *new;
	t_drawable *head;

	if (!(new = (t_drawable*)malloc(sizeof(t_drawable))))
		clean_exit(1, "Malloc failed");
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

int		is_valid_figure(char *raw_line, t_drawable *drawables)
{
	char **line;

	if (!(line = ft_split_charset(raw_line, "\f\t\n\r\v ")))
		clean_exit(1, "Malloc failed");
	if (!line[0]
		|| line[0][0] == '#'
		|| (ft_indexof(line[0][0], "RAcl") != -1 && line[0][1] == '\0'))
		return (tab_del_return(line, 0));
	while (drawables)
	{
		if (name_cmp(drawables->name, line[0]) == 0)
			return (tab_del_return(line, 1));
		drawables = drawables->next;
	}
	tab_del_return(line, 0);
	clean_exit(1, "Could not parse file: unknown shape identifier.");
	return (0);
}

t_scene	count_figures(char **lines, t_drawable *drawables)
{
	t_scene scene;

	scene.resolution = new_vect(WIN_WIDTH, WIN_HEIGHT, 0);
	scene.spotlight = new_vect(0, 0, 0);
	scene.light_color = new_vect(255, 255, 255);
	scene.light_ratio = 1;
	scene.amb_light_ratio = 0.6;
	scene.amb_light_color = new_vect(255, 255, 255);
	scene.figure_count = 0;
	scene.figure_list = NULL;
	while (*lines)
	{
		if (is_valid_figure(*lines, drawables))
			scene.figure_count++;
		lines++;
	}
	return (scene);
}

void	count_res_ambient(char **lines)
{
	int rcount;
	int acount;

	rcount = 0;
	acount = 0;
	while (*lines)
	{
		if ((*lines)[0] == 'R' && ft_indexof((*lines)[1], " \t") > -1)
			rcount++;
		if ((*lines)[0] == 'A' && ft_indexof((*lines)[1], " \t") > -1)
			acount++;
		lines++;
	}
	if (rcount != 1)
		clean_exit(1, "There must be one R argument in the scene");
	if (acount != 1)
		clean_exit(1, "There must be one A argument in the scene");
}
