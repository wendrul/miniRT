/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_objs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:12:47 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/15 14:34:49 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJS_H
# define RT_OBJS_H

# include "rt_vectors.h"
# include "rt_colors.h"

# define WIN_HEIGHT 700
# define EPSILON 0.0001
# define WIN_WIDTH 700
# define RENDER_DISTANCE 100000000
# define MIN_RENDER_DIST 0.001
# define AMBIENCE_LIGHTING 0.03
# define SKY_COLOR 0x1a3766
# define MAX_RECURSION_DEPTH 50
# define SCREEN_GAMMA 2.2
# define ZERO_FLOAT_PRECISION 0.0001
# define MAX_PARSE_FIGURE_ARGUMENTS 20
# define MAX_FIGURE_NAME_LENGTH 10

# include "utility.h"

typedef struct	s_material
{
	float		is_reflective;
	float		attenuation_coef;
}				t_material;

typedef struct	s_figure
{
	int			color;
	float		is_reflective;
	float		radius;
	float		length;
	float		x;
	float		y;
	float		z;
	char		name[MAX_FIGURE_NAME_LENGTH];
	t_material	material;
	t_point		center;
	t_vect		normal;
	t_point		third;
	t_vect		(*intersection)(struct s_figure slf, t_vect r, t_point strt);
	t_vect		(*get_normal_at)(t_vect intr, struct s_figure slf, t_point s);
	int			(*eclipses)(t_point intr, struct s_figure slf, t_point light);
}				t_figure;

typedef struct	s_camera
{
	t_point		location;
	t_vect		orientation;
	float		fov;
	t_vect		**ray_table;
	int			*buf;
}				t_camera;

typedef struct	s_polynome
{
	float		a;
	float		b;
	float		c;
	float		delta;
	float		sqrt_delta;
}				t_polynome;

typedef struct	s_scene
{
	char		*scene_name;
	t_vect		resolution;
	t_point		spotlight;
	t_vect		light_color;
	int			adj_light_color;
	float		light_ratio;
	t_vect		amb_light_color;
	float		amb_light_ratio;
	t_camera	*camera_list;
	int			camera_count;
	int			active_camera;
	t_figure	*figure_list;
	int			figure_count;
	int			animate;
	int			frame_duration;
	int			save_to_file;
}				t_scene;

typedef struct	s_inters
{
	t_vect	pos;
	float	distance;
	int		index;
}				t_inters;

typedef struct	s_drawable
{
	char				*name;
	t_figure			(*create)(t_parse_args parsed);
	struct s_drawable	*next;
}				t_drawable;

typedef struct	s_poubelle
{
	t_scene			scene;
	int				h;
	int				w;
	int				cam_no;
	int				fd;
	unsigned char	*img;
	t_color			color;
}				t_poubelle;

typedef t_figure	t_hcyl;
typedef t_figure	t_cyl;
typedef t_figure	t_sphere;
typedef t_figure	t_plane;
typedef t_figure	t_circle;
typedef t_figure	t_square;
typedef t_figure	t_triangle;

t_scene			check_light(t_scene scene, t_parse_args parsed);
t_scene			check_amb_light(t_scene scene, t_parse_args parsed);
t_scene			check_camera(t_scene scene, t_parse_args parsed);
t_scene			check_resolution(t_scene scene, t_parse_args parsed);
t_scene			count_figures(char **lines, t_drawable *drawables);
int				count_cameras(char **lines);
void			count_res_ambient(char **lines);
char			**read_lines(int fd);
t_scene			parse_switch(t_scene s, t_parse_args p, t_drawable *drawa);
t_scene			parse_line(t_scene scene, char *raw, t_drawable *draw);
t_scene			build_scene(t_scene scene, char **l, t_drawable *draw);
#endif
