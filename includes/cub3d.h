/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:19:50 by macarval          #+#    #+#             */
/*   Updated: 2024/02/29 08:27:58 by macarval         ###   ########.fr       */
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
# include "exec2d.h"
# include "keycode.h"

/* Window */
# define WIN_W		1200
# define WIN_H		800

/* Raycast */
# define FOV		66
# define MAX_RAYS	WIN_W
# define SIZE		32
# define SPEED		5

/* Events */
// # define LEFT_CLICK 1
// # define MIDDLE_CLICK 2
// # define RIGHT_CLICK 3
// # define SCROLL_UP 4
// # define SCROLL_DOWN 5
typedef struct s_player
{
	int		map[2];
	float	x;
	float	y;
	float	ang;
}	t_player;

typedef struct s_raycast
{
	float	hor[3];
	float	ver[3];
	float	offset[2];
	float	ang;
	float	a_tan;
	int		rays;
	int		dof;
	int		max_dof;
	int		map[2];
}	t_raycast;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	int		map_init;
	int		map_width;
	int		map_height;
	char	**map;
}	t_map;

typedef struct s_info
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
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

void	inicialize(t_data *game);

/* draw.c */
void	draw(t_data *game);
int		convert_color(t_color color);
void	draw_walls(t_img *img, int tam, int x, int color);
void	draw_background(t_img *img, int color, char local);

/* event.c */
int		key_press(int key, t_data *game);
int		verify_key(int key, t_data *game);
int		key_press_esc(int key, t_data *game);
int		update_ang(int key, t_player *player);
int		handle_keypress(int keysym, t_data	*data);

/* free.c */
void	free_map(t_data *game);
void	free_game(t_data *game);
void	free_split(char ***split);
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
char	*get_map_init(t_data *game, int final_set);
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
void	get_walls(t_data *game, t_raycast *ray);

/* raycast.c*/
void	raycast(t_data *game);
int		dist(int x1, int y1, int x2, int y2);

/* util.c */
char	*strchr_rev(const char *str, int c);
int		strcmp_mod(const char *s1, const char *s2);
void	terminate(t_data *game);

/* validation.c */
void	validate_map(t_data *game);
void	validate_extension(char *file);
void	validate_open(char *file, t_data *game);
void	validations(char *argv[], t_data *game);
int		validate_errors(t_data *game, int j, int i);

/* window.c */
void	init_window(t_data *game);
void	exec_window(t_data *game);
int		close_window(t_data *data);

#endif
