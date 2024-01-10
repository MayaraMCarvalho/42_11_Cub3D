/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:19:50 by macarval          #+#    #+#             */
/*   Updated: 2024/01/09 18:51:48 by macarval         ###   ########.fr       */
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

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "libft.h"
# include "error_msgs.h"

/* Window */
# define WIN_W 1200
# define WIN_H 800

/* Events */
// # define LEFT_CLICK 1
// # define MIDDLE_CLICK 2
// # define RIGHT_CLICK 3
// # define SCROLL_UP 4
// # define SCROLL_DOWN 5

typedef struct s_img
{
	void	*mlx_img;
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
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	t_color		floor;
	t_color		ceiling;
	int			**map;
}	t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			file;
	t_img		img;
	t_map		info;
	int			exit_code;
}	t_data;

void	inicialize(t_data *game);

/* event.c */
int		handle_keypress(int keysym, t_data	*data);

/* file.c */
void	validate_extension(char *file);
void	validate_open(char *file, t_data *game);
void	validations(char *argv[], t_data *game);

/* free.c */
void	free_game(t_data *game);
void	free_split(char ***split);
void	exit_err(char *line, t_data *game, int exit_code);

/* maps.c */
int		validate_map(t_data *game);

/* process.c */
void	process_file(t_data *game);
int		get_color(char	*line, t_color *color);
int		process_line(char *line, t_data *game);
int		set_variables(t_data *game, char **split);

/* util.c */
char	*strchr_rev(const char *str, int c);
int		strcmp_mod(const char *s1, const char *s2);

/* window.c */
void	config_win(t_data *data);
int		close_window(t_data *data);

// /* Images */
// void	create_img(t_data *data);
// void	img_pix_put(t_data *data, int x, int y, int color);

#endif
