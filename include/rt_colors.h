/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_colors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:12:55 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/12 20:31:35 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_COLORS_H
# define RT_COLORS_H

# include "rt_vectors.h"

typedef	struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef	struct	s_fcolor
{
	double			red;
	double			green;
	double			blue;
}				t_fcolor;

int				weighted_average(t_color base, t_color reflect, float weight);
t_color			new_color_vect(t_vect v);
int				filter_color(int color, int filter);
t_color			new_color(int r, int g, int b);
t_color			int_to_rgb(int color_int);
t_fcolor		int_to_fcolor(int color_int);
int				fcolor_to_int(t_fcolor color);
int				rgb_to_int(t_color color);
t_color			rgb_color_intensity(t_color color, float intensity);
t_color			color_intensity(int color, float intensity);

#endif
