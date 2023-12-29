/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:21:17 by macarval          #+#    #+#             */
/*   Updated: 2023/12/29 14:36:26 by macarval         ###   ########.fr       */
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

# include "libft/libft.h"

# define MLX_ERROR 1

/* Window */
# define WIN_W 600
# define WIN_H 600

/* Events */
// # define LEFT_CLICK 1
// # define MIDDLE_CLICK 2
// # define RIGHT_CLICK 3
// # define SCROLL_UP 4
// # define SCROLL_DOWN 5

// typedef struct s_img
// {
// 	void	*mlx_img;
// 	char	*addr;
// 	int		bpp;
// 	int		line_len;
// 	int		endian;
// }	t_img;

// typedef struct s_fractol
// {
// 	double	min_r;
// 	double	max_r;
// 	double	min_i;
// 	double	max_i;
// 	double	pr;
// 	double	pi;
// 	double	zr;
// 	double	zi;
// }	t_fractol;

// typedef struct s_data
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	t_img		img;
// 	t_fractol	frac;
// 	int			type;
// 	int			j_type;
// 	int			click_color;
// 	int			color1;
// 	int			color2;
// 	int			n_iter;
// }	t_data;

int		validate_file(char *argv[]);
// /* Window */
// void	create_win(t_data *data);
// int		close_window(t_data *data);
// void	set_variables(t_data *data);
// int		config_win(int type, int j_type);

// /* Images */
// void	create_img(t_data *data);
// void	img_pix_put(t_data *data, int x, int y, int color);

#endif
