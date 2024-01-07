/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:19:50 by macarval          #+#    #+#             */
/*   Updated: 2024/01/06 23:28:10 by macarval         ###   ########.fr       */
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

# define MLX_ERROR 1

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

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
}	t_data;

/* event.c */
int		handle_keypress(int keysym, t_data	*data);

/* maps.c */
int		validate_file(char *argv[]);
int		validate_open(char *file);
int		validate_extension(char *file);

/* util.c */
int		strcmp_mod(const char *s1, const char *s2);

/* window.c */
int		config_win(void);
int		close_window(t_data *data);

// /* Images */
// void	create_img(t_data *data);
// void	img_pix_put(t_data *data, int x, int y, int color);

#endif
