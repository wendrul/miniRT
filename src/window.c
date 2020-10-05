#include "minirt.h"
	
	
	
int	gamma_corrected(int color, double one_over_gamma)
{
	t_fcolor	rgb;

	rgb = int_to_fcolor(color);

	rgb.red = pow(rgb.red, one_over_gamma);
	rgb.green = pow(rgb.green, one_over_gamma);
	rgb.blue = pow(rgb.blue, one_over_gamma);
	
	return (fcolor_to_int(rgb));
}
#ifdef USING_SDL
	void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
	{
		Uint32 *pixels = (Uint32 *)surface ->pixels;
		pixels[y * surface->w + x] = pixel;
	}

	void sdl_init_win(t_scene scene)
	{
		g_sdl_win.screen = NULL;
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError() ) ;
		else
			g_sdl_win.window = SDL_CreateWindow( "Raytracing in a bad language", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scene.resolution.x, scene.resolution.y, SDL_WINDOW_SHOWN);
		g_sdl_win.screen = SDL_GetWindowSurface(g_sdl_win.window);
	}

	void	sdl_render_frame(t_vect **ray_table, t_scene scene, t_point start, t_r_stack stack)
	{
		int	i;
		int	j;
		int color;
		double one_over_gamma;

		one_over_gamma = 1 / SCREEN_GAMMA;
		i = -1;
		while (++i < scene.resolution.y)
		{
			j = -1;
			while (++j < scene.resolution.x)
			{
				color = trace_ray(ray_table[i][j], scene, start, -1, 0, stack);
				put_pixel32(g_sdl_win.screen, j, i, gamma_corrected(color, one_over_gamma));
			}
		}
		SDL_UpdateWindowSurface(g_sdl_win.window);
	}
#endif

void	init_win(t_scene scene)
{
	#ifndef USING_SDL
		mlx_init_win(scene);
	#endif
	#ifdef USING_SDL
		sdl_init_win(scene);
	#endif
}

void	render_frame(t_scene scene)
{
	#ifndef USING_SDL
		mlx_render_frame(scene);
	#endif
	#ifdef USING_SDL
		sdl_render_frame(ray_table, scene, start, stack);
	#endif
}

#ifndef USING_SDL
	int	interact(int keycode, void *param)
	{
		t_scene *scene;

		scene = (t_scene*)param;
		ft_putnbr_fd(keycode, 1);
		ft_putchar_fd('\n', 1);
		if (!scene->animate)
		{
			if (keycode == LEFT_ARROW && scene->camera_count != 1)
			{
				if (--scene->active_camera == -1)
					scene->active_camera = scene->camera_count - 1;
				render_frame(*scene);
			}
			if (keycode == RIGHT_ARROW && scene->camera_count != 1)
			{
				if (++scene->active_camera == scene->camera_count)
					scene->active_camera = 0;
				render_frame(*scene);
			}
		}
		else
		{
			if (keycode == LEFT_ARROW)
			{
				scene->frame_duration += FRAME_DURATION_UNIT;
			}
			if (keycode == RIGHT_ARROW && scene->frame_duration > FRAME_DURATION_UNIT)
			{
				scene->frame_duration -= FRAME_DURATION_UNIT;
			}
		}
		
		if (keycode == 53 || keycode == ESC)
			exit(0);
		return (0);
	}

	int loop(void *param)
	{
		t_scene *scene;
		static int t = 0;

		t++; 
		scene = (t_scene*)param;
		if (t >= scene->frame_duration && scene->animate)
		{
			t = 0;
			if (++scene->active_camera == scene->camera_count)
				scene->active_camera = 0;
			render_frame(*scene);
		}
		return (0);
	}

	void	mlx_init_win(t_scene scene)
	{
		if (!(g_win.mlx = mlx_init()))
			clean_exit(1, "Failed to set up the connection to the graphical system.");
		g_win.win = mlx_new_window(g_win.mlx, scene.resolution.y, scene.resolution.x, "miniRT");
		g_win.img = mlx_new_image(g_win.mlx, scene.resolution.y, scene.resolution.x);
		g_win.buffer = (int*)mlx_get_data_addr(g_win.img, &g_win.bpp, &g_win.s_l, &g_win.endian);
	}

	int		*get_buffer(t_vect **ray_table, t_scene scene, t_point start, t_r_stack stack)
	{
		int	i;
		int	j;
		int color;
		double one_over_gamma;
		int *buf;

		buf = malloc(sizeof(int) * scene.resolution.x * scene.resolution.y);
		one_over_gamma = 1 / SCREEN_GAMMA;
		i = -1;
		while (++i < (int)scene.resolution.y)
		{
			j = -1;
			while (++j < (int)scene.resolution.x)
			{
				color = trace_ray(ray_table[i][j], scene, start, -1, 0, stack);
				buf[j + i * (int)scene.resolution.y] = gamma_corrected(color, one_over_gamma);
			}
		}
		return (buf);
	}

	void	mlx_render_frame(t_scene scene)
	{
		int i;
		int j;

		i = -1;
		while (++i < (int)scene.resolution.y)
		{
			j = -1;
			while (++j < (int)scene.resolution.x)
			{
				g_win.buffer[j + i * (int)scene.resolution.y] = scene.camera_list[scene.active_camera].buf[j + i * (int)scene.resolution.y];
			}
		}
		mlx_put_image_to_window(g_win.mlx, g_win.win, g_win.img, 0, 0);
	}
#endif