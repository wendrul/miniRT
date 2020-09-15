#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "utility.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_HEIGHT 1000
# define EPSILON 0.0001
# define WIN_WIDTH 1000
# define RENDER_DISTANCE 100000000
# define AMBIENCE_LIGHTING 0.03
# define SKY_COLOR 0x000000
# define FOV_H M_PI / 2
# define FOV_W M_PI / 2
# define MAX_RECURSION_DEPTH 50
# define SCREEN_GAMMA 2.2
# define ZERO_FLOAT_PRECISION 0.0001
# define MAX_PARSE_FIGURE_ARGUMENTS 20
# define MAX_FIGURE_NAME_LENGTH 10


typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef t_point t_vect;

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

typedef struct	s_box
{
	int			to_check;
	t_point		ulf;
	t_point		urf;
	t_point		ulc;
	t_point		urc;
	t_point		dlf;
	t_point		drf;
	t_point		dlc;
	t_point		drc;
}				t_box;

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
	float		x;
	float		y;
	float		z;
	char		name[MAX_FIGURE_NAME_LENGTH];
	t_material	material;
	t_point		center;
	t_vect      normal;
	t_box		box;
	t_vect		(*intersection)(struct s_figure self, t_vect ray, t_point start);
	t_vect		(*get_normal_at)(t_vect inter, struct s_figure self);
	int			(*eclipses)(t_point intersection, struct s_figure self, t_point light);
}				t_figure;

typedef t_figure	t_sphere;
typedef t_figure	t_plane;

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
	t_vect		resolution;
	t_point		spotlight;
	t_vect		light_color;
	float		light_ratio;
	t_vect		amb_light_color;
	float		amb_light_ratio;
	t_point		camera;
	t_vect		cam_rotation;
	float		fov;
	t_figure	*figure_list;
	int			figure_count;
}	            t_scene;

typedef struct	s_parse_args
{
	char	name[MAX_FIGURE_NAME_LENGTH];
	float	args[MAX_PARSE_FIGURE_ARGUMENTS + 5];
	int		size;
}				t_parse_args;

typedef struct	s_drawable
{
	char				*name;
	t_figure			(*create)(t_parse_args parsed);
	struct s_drawable	*next;
}				t_drawable;

# ifndef USING_SDL
#   include "mlx.h"
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
# endif

# ifdef USING_SDL
#   include "SDL2/SDL.h"
	typedef struct	s_sdl_win
	{
			SDL_Window *window;
			SDL_Surface *screen;
			SDL_Surface *used;
	    	SDL_Event event;	
	}		t_sdl_win;

	t_sdl_win g_sdl_win;
# endif

void		init_win(void);

t_sphere	create_sphere(t_parse_args parsed);
t_plane		create_plane(t_parse_args parsed);

t_point		sphere_intersection(t_sphere sphere, t_vect ray, t_point start);
t_point		plane_intersection(t_plane plane, t_vect ray, t_point start);

t_vect 		get_sphere_normal_vector(t_vect inter, t_figure sphere);
t_vect		get_plane_normal_vector(t_vect inter, t_figure plane);

int			sphere_eclipses_light(t_point intersection, t_sphere, t_point spot);
int			plane_eclipses_light(t_point intersection, t_plane plane, t_point light);

float		norm(t_point vector);
float		normsqrd(t_point vector);
t_point		normalize(t_point vector);
t_vect		square(t_vect v1);
t_point		vector(t_point v1, t_point v2);
t_vect		substract(t_vect v1, t_vect v2);
t_vect		add(t_vect v1, t_vect v2);
float		dot(t_point v1, t_point v2);
float		distance(t_point p1, t_point p2);
void		render_frame(t_vect **ray_table, t_scene scene, t_point start, t_r_stack stack);
t_vect		**init_tracer();
t_vect		scale(t_vect v, float scalar);

t_vect		get_reflective_vector(t_sphere sphere, t_point inter, t_vect incident);

t_vect		new_vect(float x, float y, float z);
t_vect		true_vect(t_vect v1, t_vect v2);

t_color		new_color(int r, int g, int b);
t_fcolor	new_fcolor(int r, int g, int b);
t_color		int_to_rgb(int color_int);
t_fcolor	int_to_fcolor(int color_int);
int			fcolor_to_int(t_fcolor color);
int			rgb_to_int(t_color color);
t_color		rgb_color_intensity(t_color, float intensity);
t_color		color_intensity(int color, float intensity);
int			weighted_average(t_color base, t_color reflected, float weight1);

void		clean_exit(int status, char *msg);
t_scene		parse_scene(char *scene_file_path, t_drawable *drawable_list);
float		ft_atof(char *nb);
void		add_drawable(t_drawable **drawables, char *name, t_figure (*create_func)(t_parse_args parsed));
int			trace_ray(t_vect ray, t_scene scene, t_point start, int	prev_index, int ignore, t_r_stack stack);
double		angle(t_vect v1, t_vect v2);

#endif
