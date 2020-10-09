/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 22:07:25 by dhorvill          #+#    #+#             */
/*   Updated: 2020/06/13 18:57:40 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

void init_ray_tables(t_scene scene)
{
	while (scene.active_camera < scene.camera_count)
	{
		scene.camera_list[scene.active_camera].ray_table = init_tracer(scene);
		scene.active_camera++;
	}
	scene.active_camera = 0;
}

void init_buffers(t_scene scene)
{
	int i;
	t_camera c;

	i = 0;
	while (i < scene.camera_count)
	{
		scene.active_camera = i;
		c = scene.camera_list[i];
		c.buf = get_buffer(c.ray_table, scene, c.location, stack);
		scene.camera_list[i] = c;
		i++;
	}
	scene.active_camera = 0;
}

t_scene	parse_console_args(t_scene scene, int argc, char **argv)
{
	int i;
	scene.animate = 0;
	scene.frame_duration = FRAME_DURATION_UNIT * 3;
	scene.save_to_file = 0;
	
	i = 0;
	while (++i < argc)
	{
		if (name_cmp("--save", argv[i]) == 0)
		{
			ft_putstr_fd("Scene will be saved\n", 1);
			scene.save_to_file = 1;
		}
		if (name_cmp("-a", argv[i]) == 0)
		{
			scene.animate = 1;
			ft_putstr_fd("Scene will be animated\n", 1);
			if (i + 1 < argc && ft_isdigit(argv[i + 1][0]))
			{
				scene.frame_duration = FRAME_DURATION_UNIT * ft_atoi(argv[i + 1]);
			}
		}
	}
	return (scene);
}

int		exit_hook()
{
	exit(0);
}

int		main(int argc, char **argv)
{
	t_scene		scene;
	t_drawable	*drawables;

	if (argc < 2)
	{
		ft_putendl_fd("pls file", 1);
		return (0);
	}
	drawables = NULL;
	add_drawable(&drawables, "sp", create_sphere);
	add_drawable(&drawables, "pl", create_plane);
	add_drawable(&drawables, "hcy", create_hcyl);
	add_drawable(&drawables, "ci", create_circle);
	add_drawable(&drawables, "cy", create_cyl);
	add_drawable(&drawables, "sq", create_square);
	add_drawable(&drawables, "tr", create_triangle);
	scene = parse_scene(argv[1], drawables);
	scene = parse_console_args(scene, argc, argv);
	scene.scene_name = argv[1];
	scene.scene_name[MAX_FILE_NAME_SIZE - 1] = 0;
	init_ray_tables(scene);
	init_buffers(scene);
	stack = create_stack(MAX_RECURSION_DEPTH + 69, 1);
	if (!scene.save_to_file)
	{
		init_win(scene);
		mlx_hook(g_win.win, 33, 0, exit_hook, NULL);
		mlx_loop_hook(g_win.mlx, loop, (void*)&scene);
		mlx_key_hook(g_win.win, interact, (void*)&scene);
		mlx_loop(g_win.mlx);
	}
	else
	{
		save_to_bmp(scene);
	}
	return (0);
}
