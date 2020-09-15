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


int		main(int argc, char **argv)
{
	t_vect		**ray_table;
	t_point		start;
	t_scene		scene;
	t_drawable	*drawables;
	t_r_stack	stack;

	if (argc != 2)
	{
		ft_putendl_fd("pls file", 1);
		return (0);
	}
	ray_table = init_tracer();
	init_win();
	drawables = NULL;
	add_drawable(&drawables, "sp", create_sphere);
	add_drawable(&drawables, "pl", create_plane);
	scene = parse_scene(argv[1], drawables);
	start = new_vect(0, 0, 0);
	stack = create_stack(MAX_RECURSION_DEPTH + 69, 1);
	clock_t begin = clock();

	render_frame(ray_table, scene, start, stack);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time Elapsed: %lf\n", time_spent);
	
	#ifndef USING_SDL
		mlx_key_hook(g_win.win, interact, NULL);
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
						return 0;
					}
				}
			}
		}
	#endif
	return (0);
}
