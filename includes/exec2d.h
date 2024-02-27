/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:08:22 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/27 09:17:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC2D_H
# define EXEC2D_H

# include "cub3d.h"

typedef struct s_data		t_data;
typedef struct s_img		t_img;
typedef struct s_player		t_player;
typedef struct s_set		t_sat;
typedef struct s_raycast	t_raycast;

// typedef	struct s_raycast
// {
// 	float	hor[3];
// 	float	ver[3];
// 	float	offset[2];
// 	float	ang;
// 	float	aTan;
// 	int		rays;
// 	int		dof;
// 	int		max_dof;
// 	int		map[2];
// }	t_raycast;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
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

// void	run_2d_game(t_data *game);
void	put_pixel_img(t_img *img, int x, int y, int color);
// void	bresenham(t_img *img, t_point init, t_point dest);

// int		key_press(int key, t_data2d *data);
// // void	draw(t_data2d *data);
// void	draw_raycast(t_data2d *game);

// void	raising_the_walls(t_raycast *ray, t_player *p, t_img *img);

#endif //EXEC2D_H
