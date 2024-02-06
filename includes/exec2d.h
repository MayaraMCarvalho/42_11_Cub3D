/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:08:22 by joapedr2          #+#    #+#             */
/*   Updated: 2024/01/30 19:01:10 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC2D_H
# define EXEC2D_H

# include "cub3d.h"

typedef struct s_data	t_data;
typedef struct s_img	t_img;
typedef struct s_player	t_player;

typedef struct s_raycast{
	int		color;
	float	ang;
	float	x;
	float	y;
	int		world_limit;
	int		in_world;
	float	offset_x;
	float	offset_y;
	float	delta_ver;
	float	delta_hor;
}	t_raycast;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_bres
{
	int	x;
	int	y;
	int	sign_x;
	int	sign_y;
	int	dx;
	int	dy;
	int	color;
	int	p;
}	t_bres;

typedef struct s_data2d
{
	void	*mlx;
	void	*window;
	t_img	*img;
	t_data	*game;
}	t_data2d;

void	run_2d_game(t_data *game);
void	put_pixel_img(t_img *img, int x, int y, int color);
void	bresenham(t_img *img, t_point init, t_point dest);

int		key_press(int key, t_data2d *data);
void	draw(t_data2d *data);
void	draw_raycast(t_data2d *game);

#endif //EXEC2D_H