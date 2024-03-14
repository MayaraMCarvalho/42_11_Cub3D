/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:19:50 by macarval          #+#    #+#             */
/*   Updated: 2024/03/14 19:01:22 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "libft.h"
# include "error_msgs.h"
# include "keycode.h"

/* Window */
# define WIN_W		1200
# define WIN_H		720

/* Raycast */
# define FOV		66
# define MAX_RAYS	600
# define SIZE		32
# define SPEED		3

/* Walls */
# define PI			3.14159265359
# define EAST		1
# define NORTH		2
# define WEST		3
# define SOUTH		4

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_player
{
	int		map[2];
	float	x;
	float	y;
	float	ang;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	char		*file;
	int			width;
	int			height;
	t_img		tex;
}	t_tex;

typedef struct s_raycast
{
	float	hor[3];
	float	ver[3];
	float	offset[2];
	float	distance;
	float	ang;
	float	a_tan;
	int		rays;
	int		dof;
	int		max_dof;
	int		map[2];
	int		pixel[2];
	t_tex	tex;
}	t_raycast;


typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	int		init;
	int		width;
	int		height;
	char	**map;
}	t_map;

typedef struct s_info
{
	t_tex		north;
	t_tex		south;
	t_tex		west;
	t_tex		east;
	t_color		floor;
	t_color		ceiling;
}	t_info;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			fd;
	char		*file_name;
	int			exit_code;
	char		*exit_str;
	t_img		img;
	t_info		info;
	t_player	player;
	t_map		map;
}	t_data;

typedef struct s_new_ray
{
	float	distance;
	int		ray_horizontal_size;
	int		vertical_line;
	float	cast_angle;
	int		line_off;
	int		line_y;
}	t_newRay;

void	inicialize(t_data *game);

/* data.c */
void	validate_map(t_data *game);
void	validate_extension(char *file);
void	validate_open(char *file, t_data *game);
void	get_data(char *argv[], t_data *game);
int		validate_errors(t_data *game, int j, int i);

/* draw.c */
void	draw(t_data *game);
void	put_pixel_img(t_img *img, int x, int y, int color);
void	draw_background(t_img *img, int color, char local);

/* event.c */
int		key_press(int key, t_data *game);
int		verify_key(int key, t_data *game);
int		key_press_esc(int key, t_data *game);
int		handle_keypress(int keysym, t_data	*data);

/* free.c */
void	free_map(t_data *game);
void	free_game(t_data *game);
void	free_split(char ***split);
void	free_textures(t_data *game);
void	exit_err(char *line, t_data *game, int exit_code, char *err);

/* h_raycast.c */
void	set_h_rays(t_raycast *ray, t_player *p);
void	set_v_rays(t_raycast *ray, t_player *p);
void	h_rays(t_raycast *ray, t_player *p, t_map map);
void	v_rays(t_raycast *ray, t_player *p, t_map map);

/* maps.c */
void	get_map(t_data *game);
void	alloc_map(t_data *game);
void	process_map(t_data *game, int final_set);
char	*get_init(t_data *game, int final_set);
int		check_neighbors(t_data *game, int j, int i, char *pattern);

/* player.c */
void	init_player(t_data *game);
void	verify_player(t_player *player, char c);

/* process.c */
int		process_settings(t_data *game);
int		get_color(char	*line, t_color *color);
int		process_line(char *line, t_data *game);
int		get_textures(t_data *game, char **split);
int		set_variables(t_data *game, char **split, char *line);

/* raycast_walls.c */
int		get_guide(t_raycast *ray);
void	get_walls(t_data *game, t_raycast *ray);
void	set_3d_cast(t_data *game, t_newRay *new, t_raycast *ray);
void	draw_rectangle(t_data *game, t_point start, t_point end, int guide);

/* raycast.c*/
void	raycast(t_data *game);
int		dist(int x1, int y1, int x2, int y2);

/* textures.c */
int		convert_color(t_color color);
// t_tex	define_texture(t_data *game, int guide);
void	get_data_textures(t_data *game, t_tex *tex);
int		get_pixel_color(t_data *game, int x, int y, int guide);

/* util.c */
char	*strchr_rev(const char *str, int c);
int		strcmp_mod(const char *s1, const char *s2);
void	terminate(t_data *game);

/* window.c */
void	init_window(t_data *game);
void	exec_window(t_data *game);
int		close_window(t_data *data);

#endif
