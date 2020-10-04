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

int		main(int argc, char **argv)
{
	t_scene		scene;
	t_drawable	*drawables;

	if (argc != 2)
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
	init_ray_tables(scene);
	init_win(scene);
	init_buffers(scene);
	stack = create_stack(MAX_RECURSION_DEPTH + 69, 1);
	clock_t begin = clock();

	render_frame(scene);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time Elapsed: %lf\n", time_spent);
	
	#ifndef USING_SDL
		mlx_key_hook(g_win.win, interact, (void*)&scene);
		mlx_loop(g_win.mlx);
	#endif
	#ifdef USING_SDL
		while (1)
		{
			while(SDL_PollEvent(&g_sdl_win.event))
			{
				if(g_sdl_win.event.type == SDL_KEYDOWN)
				{
					if(g_sdl_win.event.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_DestroyWindow(g_sdl_win.window);
						SDL_Quit();
						clean_exit(0, NULL);
						return (0);
					}
				}
			}
		}
	#endif
	return (0);
}
