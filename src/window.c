/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:50:37 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/14 23:02:26 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_win(t_scene scene)
{
	g_win.win = mlx_new_window(g_win.mlx, scene.resolution.x,
							scene.resolution.y, "miniRT");
	g_win.img = mlx_new_image(g_win.mlx, scene.resolution.x,
							scene.resolution.y);
	g_win.buffer = (int *)mlx_get_data_addr(g_win.img, &g_win.bpp,
							&g_win.s_l, &g_win.endian);
}

void	render_frame(t_scene scene)
{
	int i;
	int j;

	i = -1;
	while (++i < (int)scene.resolution.y)
	{
		j = -1;
		while (++j < (int)scene.resolution.x)
		{
			g_win.buffer[j + i * (int)scene.resolution.x] =
				scene.camera_list[scene.active_camera].
				buf[j + i * (int)scene.resolution.x];
		}
	}
	mlx_put_image_to_window(g_win.mlx, g_win.win, g_win.img, 0, 0);
}

t_scene	pre_init_mlx(t_scene scene)
{
	int x;
	int y;

	if (!(g_win.mlx = mlx_init()))
		clean_exit(1, "Failed to connect to the graphical system.");
	mlx_get_screen_size(g_win.mlx, &x, &y);
	if (scene.resolution.x > x)
		scene.resolution.x = x;
	if (scene.resolution.y > y)
		scene.resolution.y = y;
	return (scene);
}

int		*get_buffer(t_vect **ray_table, t_scene scene, t_point start)
{
	int		i;
	int		j;
	int		color;
	double	one_over_gamma;
	int		*buf;

	buf = malloc(sizeof(int) * scene.resolution.x * scene.resolution.y);
	one_over_gamma = 1 / SCREEN_GAMMA;
	i = -1;
	while (++i < (int)scene.resolution.y)
	{
		j = -1;
		while (++j < (int)scene.resolution.x)
		{
			color = trace_ray(ray_table[i][j], scene, start);
			buf[j + i * (int)scene.resolution.x] =
					gamma_corrected(color, one_over_gamma);
		}
	}
	return (buf);
}
