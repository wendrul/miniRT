/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:13:03 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/12 20:32:04 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_STUFF_H
# define MLX_STUFF_H

# include "rt_objs.h"

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define ESC 65307
# define FRAME_DURATION_UNIT 5000
# define MAX_FILE_NAME_SIZE 512

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*buffer;
	int			bpp;
	int			endian;
	int			s_l;
}				t_window;

t_window	g_win;

void			init_win(t_scene scene);
int				interact(int keycode, void *param);
int				loop(void *param);
int				exit_hook(void);
t_scene			pre_init_mlx(t_scene scene);
void			mlx_init_win(t_scene scene);
void			mlx_render_frame(t_scene scene);
int				*get_buffer(t_vect **ray_table, t_scene scene, t_point start);

#endif
