#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "utility.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_HEIGHT 700
# define EPSILON 0.0001
# define WIN_WIDTH 700
# define RENDER_DISTANCE 100000000
# define MIN_RENDER_DIST 0.001
# define AMBIENCE_LIGHTING 0.03
# define SKY_COLOR 0x1a3766
# define FOV_H M_PI / 2
# define FOV_W M_PI / 2
# define MAX_RECURSION_DEPTH 50
# define SCREEN_GAMMA 2.2
# define ZERO_FLOAT_PRECISION 0.0001
# define MAX_PARSE_FIGURE_ARGUMENTS 20
# define MAX_FIGURE_NAME_LENGTH 10
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define ESC 65307


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
	float		length;
	float		x;
	float		y;
	float		z;
	char		name[MAX_FIGURE_NAME_LENGTH];
	t_material	material;
	t_point		center;
	t_vect      normal;
	t_point		third;
	t_box		box;
	t_vect		(*intersection)(struct s_figure self, t_vect ray, t_point start);
	t_vect		(*get_normal_at)(t_vect inter, struct s_figure self, t_point start);
	int			(*eclipses)(t_point intersection, struct s_figure self, t_point light);
}				t_figure;

typedef t_figure	t_hcyl;
typedef t_figure	t_cyl;
typedef t_figure	t_sphere;
typedef t_figure	t_plane;
typedef t_figure	t_circle;
typedef t_figure	t_square;
typedef t_figure	t_triangle;

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
	t_r_stack	stack;
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

void		init_win(t_scene scene);
void 		print_vect(t_vect vect, char *str); // dont kep lpplz
int			interact(int keycode, void *thing);


t_sphere	create_sphere(t_parse_args parsed);
t_plane		create_plane(t_parse_args parsed);
t_hcyl		create_hcyl(t_parse_args parsed);
t_cyl		create_cyl(t_parse_args parsed);
t_circle	create_circle(t_parse_args parsed);
t_square	create_square(t_parse_args parsed);
t_triangle	create_triangle(t_parse_args parsed);

t_point		sphere_intersection(t_sphere sphere, t_vect ray, t_point start);
t_point		plane_intersection(t_plane plane, t_vect ray, t_point start);
t_point		hcyl_intersection(t_hcyl hcyl, t_vect ray, t_point start);
t_point		cyl_intersection(t_cyl cyl, t_vect ray, t_point start);
t_point		circle_intersection(t_circle circle, t_vect ray, t_point start);
t_point		square_intersection(t_square square, t_vect ray, t_point start);
t_point		triangle_intersection(t_triangle triangle, t_vect ray, t_point start);

t_vect 		get_sphere_normal_vector(t_vect inter, t_figure sphere, t_point start);
t_vect		get_plane_normal_vector(t_vect inter, t_figure plane, t_point start);
t_vect		get_hcyl_normal_vector(t_vect inter, t_figure hcyl, t_point start);
t_vect		get_cyl_normal_vector(t_vect inter, t_figure cyl, t_point start);
t_vect		get_circle_normal_vector(t_vect inter, t_figure circle, t_point start);
t_vect		get_square_normal_vector(t_vect inter, t_figure square, t_point start);
t_vect		get_triangle_normal_vector(t_vect inter, t_figure triangle, t_point start);

int			sphere_eclipses_light(t_point intersection, t_sphere, t_point spot);
int			plane_eclipses_light(t_point intersection, t_plane plane, t_point light);
int			hcyl_eclipses_light(t_point intersection, t_hcyl hcyl, t_point spot);
int			cyl_eclipses_light(t_point intersection, t_cyl cyl, t_point spot);
int			circle_eclipses_light(t_point intersection, t_circle circle, t_point spot);
int			square_eclipses_light(t_point intersection, t_square square, t_point spot);
int			triangle_eclipses_light(t_point intersection, t_triangle triangle, t_point spot);

float		norm(t_point vector);
float		norm_inf(t_vect a);
float		normsqrd(t_point vector);
t_point		normalize(t_point vector);
t_vect		square(t_vect v1);
t_point		vector(t_point v1, t_point v2);
t_vect		subtract(t_vect v1, t_vect v2);
t_vect		add(t_vect v1, t_vect v2);
float		dot(t_point v1, t_point v2);
float		distance(t_point p1, t_point p2);
t_vect 		projection(t_vect u, t_vect base);
void		render_frame(t_scene scene);
t_vect		**init_tracer(t_scene scene);
t_vect		scale(t_vect v, float scalar);
int			figure_eclipses_light(t_vect inter, t_figure shape, t_vect light);

t_vect		get_reflective_vector(t_sphere sphere, t_point inter, t_vect incident, t_point start);

t_vect		new_vect(float x, float y, float z);
t_vect		true_vect(t_vect v1, t_vect v2);
t_vect		apply_rotation(t_vect u, t_vect ref, float theta);
t_vect		cross(t_vect a, t_vect b);

t_color		new_color_vect(t_vect v);
int			filter_color(int color, int filter);
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

void		mlx_init_win(t_scene scene);
void		mlx_render_frame(t_scene scene);
int			*get_buffer(t_vect **ray_table, t_scene scene, t_point start, t_r_stack stack);

#endif
