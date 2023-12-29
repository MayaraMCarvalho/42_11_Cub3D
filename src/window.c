/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:17:55 by macarval          #+#    #+#             */
/*   Updated: 2023/12/29 17:30:36 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	config_win(void)
{
	t_data	data;

	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (MLX_ERROR);
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "*Cub3D*");
	if (data.win == NULL)
	{
		free(data.win);
		return (MLX_ERROR);
	}
	// create_img(&data);
	// mlx_loop_hook(data.mlx, &render, &data);
	mlx_key_hook(data.win, &handle_keypress, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, &close_window, &data);
	// mlx_mouse_hook(data.win, &handle_mouse, &data);
	mlx_loop(data.mlx);
	return (0);
}

int	close_window(t_data	*data)
{
	mlx_destroy_window(data->mlx, data->win);
	// mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit (0);
}
