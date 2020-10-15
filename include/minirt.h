/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:17:20 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/15 14:30:20 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft.h"
# include "mlx.h"
# include "rt_vectors.h"
# include "rt_colors.h"
# include "mlx_stuff.h"
# include "utility.h"

t_sphere	create_sphere(t_parse_args parsed);
t_plane		create_plane(t_parse_args parsed);
t_hcyl		create_hcyl(t_parse_args parsed);
t_cyl		create_cyl(t_parse_args parsed);
t_circle	create_circle(t_parse_args parsed);
t_square	create_square(t_parse_args parsed);
t_triangle	create_triangle(t_parse_args parsed);

t_point		sphere_intersection(t_sphere s, t_vect ray, t_point start);
t_point		plane_intersection(t_plane p, t_vect ray, t_point start);
t_point		hcyl_intersection(t_hcyl hc, t_vect ray, t_point start);
t_point		cyl_intersection(t_cyl c, t_vect ray, t_point start);
t_point		circle_intersection(t_circle c, t_vect ray, t_point start);
t_point		square_intersection(t_square s, t_vect ray, t_point start);
t_point		triangle_intersection(t_triangle t, t_vect ray, t_point start);

t_vect		get_sphere_normal_vector(t_vect inter, t_sphere s, t_point start);
t_vect		get_plane_normal_vector(t_vect inter, t_plane p, t_point start);
t_vect		get_hcyl_normal_vector(t_vect inter, t_hcyl hc, t_point start);
t_vect		get_cyl_normal_vector(t_vect inter, t_figure cyl, t_point start);
t_vect		get_circle_normal_vector(t_vect inter, t_circle c, t_point start);
t_vect		get_square_normal_vector(t_vect inter, t_square s, t_point start);
t_vect		get_triangle_normal_vector(t_vect inter, t_triangle t, t_point st);

void		render_frame(t_scene scene);
t_vect		**init_tracer(t_scene scene);
t_vect		scale(t_vect v, float scalar);
int			figure_eclipses_light(t_vect inter, t_figure shape, t_vect light);

t_vect		get_refl_vector(t_figure f, t_point inter,
									t_vect incident, t_point start);

void		clean_exit(int status, char *msg);
t_scene		parse_scene(char *scene_file_path, t_drawable *drawable_list);
void		add_drawable(t_drawable **drawables, char *name,
							t_figure (*create_func)(t_parse_args parsed));

int			color_shade(float intensity, t_figure figure, int reflective_color);
float		get_lum_intensity(t_figure figure, t_point inter,
							t_point spotlight, t_point start);

int			trace_ray(t_vect ray, t_scene scene, t_point start);
int			save_to_bmp(t_scene scene);
void		write_img(t_scene scene, int cam_no, int fd);

#endif
