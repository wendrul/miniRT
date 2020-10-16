/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:52:56 by agoodwin          #+#    #+#             */
/*   Updated: 2020/10/14 21:33:02 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			exit_hook(void)
{
	exit(0);
}

static void	animation_speed(int keycode, t_scene *scene)
{
	if (keycode == LEFT_ARROW)
	{
		scene->frame_duration += FRAME_DURATION_UNIT;
	}
	if (keycode == RIGHT_ARROW
		&& scene->frame_duration > FRAME_DURATION_UNIT)
	{
		scene->frame_duration -= FRAME_DURATION_UNIT;
	}
}

int			interact(int keycode, void *param)
{
	t_scene *scene;

	scene = (t_scene *)param;
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
		animation_speed(keycode, scene);
	if (keycode == 53 || keycode == ESC)
		exit(0);
	return (0);
}

int			loop(void *param)
{
	t_scene		*scene;
	static int	t = 0;

	t++;
	scene = (t_scene *)param;
	if (t >= scene->frame_duration && scene->animate)
	{
		t = 0;
		if (++scene->active_camera == scene->camera_count)
			scene->active_camera = 0;
	}
	render_frame(*scene);
	return (0);
}
