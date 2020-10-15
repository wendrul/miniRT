/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:12:53 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/14 19:55:55 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTORS_H
# define RT_VECTORS_H

# include <math.h>

typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef t_point	t_vect;

float			norm(t_point vector);
float			norm_inf(t_vect a);
float			normsqrd(t_point vector);
t_point			normalize(t_point vector);
t_vect			square(t_vect v1);
t_point			vector(t_point v1, t_point v2);
t_vect			subtract(t_vect v1, t_vect v2);
t_vect			add(t_vect v1, t_vect v2);
float			dot(t_point v1, t_point v2);
float			distance(t_point p1, t_point p2);
t_vect			projection(t_vect u, t_vect base);
t_vect			new_vect(float x, float y, float z);
t_vect			true_vect(t_vect v1, t_vect v2);
t_vect			apply_rotation(t_vect u, t_vect ref, float theta);
t_vect			cross(t_vect a, t_vect b);
double			angle(t_vect v1, t_vect v2);

#endif
