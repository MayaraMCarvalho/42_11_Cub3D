/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:12:16 by macarval          #+#    #+#             */
/*   Updated: 2023/12/29 16:42:25 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_keypress(int keysym, t_data	*data)
{
	if (keysym == XK_Escape)
		close_window(data);
	// move_frac(keysym, data, 0.1); // move pixel
	return (0);
}

// int	handle_mouse(int button, int x, int y, t_data	*data)
// {
// 	if (button == LEFT_CLICK)
// 		change_color(data);
// 	if (button == RIGHT_CLICK && data->type == JULIA)
// 	{
// 		if (data->j_type == '4')
// 			data->j_type = '1';
// 		else
// 			data->j_type++;
// 	}
// 	if (button == SCROLL_UP || button == SCROLL_DOWN)
// 	{
// 		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
// 		if (button == SCROLL_UP)
// 			zoom_frac(0.5, data);
// 		else
// 			zoom_frac(2, data);
// 		move_zoom(x, y, data);
// 		create_img(data);
// 	}
// 	return (0);
// }

// void	move_frac(int keysym, t_data *data, double dist)
// {
// 	double	r_center;
// 	double	i_center;

// 	r_center = data->frac.max_r - data->frac.min_r;
// 	i_center = data->frac.max_i - data->frac.min_i;
// 	if (keysym == XK_Left)
// 	{
// 		data->frac.min_r += r_center * dist;
// 		data->frac.max_r += r_center * dist;
// 	}
// 	else if (keysym == XK_Right)
// 	{
// 		data->frac.min_r -= r_center * dist;
// 		data->frac.max_r -= r_center * dist;
// 	}
// 	else if (keysym == XK_Up)
// 	{
// 		data->frac.min_i += i_center * dist;
// 		data->frac.max_i += i_center * dist;
// 	}
// 	else if (keysym == XK_Down)
// 	{
// 		data->frac.min_i -= i_center * dist;
// 		data->frac.max_i -= i_center * dist;
// 	}
// }

// void	zoom_frac(double zoom, t_data	*data)
// {
// 	double	r_center;
// 	double	i_center;

// 	r_center = data->frac.min_r - data->frac.max_r;
// 	i_center = data->frac.max_i - data->frac.min_i;
// 	data->frac.min_r = data->frac.max_r + zoom * r_center;
// 	data->frac.max_r = data->frac.max_r + (r_center - zoom * r_center) / 2;
// 	data->frac.max_i = data->frac.min_i + zoom * (i_center);
// 	data->frac.min_i = data->frac.min_i + (i_center - zoom * i_center) / 2;
// }

// void	move_zoom(int x, int y, t_data	*data)
// {
// 	x -= WIN_W / 2;
// 	y -= WIN_H / 2;
// 	if (x < 0)
// 		move_frac(XK_Right, data, 1 - (double)x / WIN_W);
// 	else if (x > 0)
// 		move_frac(XK_Left, data, (double)x / WIN_W + 0.1);
// 	if (y < 0)
// 		move_frac(XK_Down, data, -(double)y / WIN_H);
// 	else if (y > 0)
// 		move_frac(XK_Up, data, 1 + (double)y / WIN_H);
// }
