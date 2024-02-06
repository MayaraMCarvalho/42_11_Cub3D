/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:17:55 by macarval          #+#    #+#             */
/*   Updated: 2024/01/25 21:09:40 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void validation_window_alloc(t_data *game)
{
	if (game->mlx == NULL)
		game->exit_code = 2;
	else if (game->win == NULL)
		game->exit_code = 3;
	else if (game->img.img == NULL)
		game->exit_code = 4;
	else if (game->img.addr == NULL)
		game->exit_code = 5;
	if (game->exit_code != 0)
		close_window(game);
}

void	init_window(t_data *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "*** Cub3D ***");
	game->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.img, &(game->img.bpp),
			&(game->img.line_len), &(game->img.endian));
	validation_window_alloc(game);
}

void	exec_window(t_data *game)
{
	printf("\nCub3D running!!!\n\n");
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_key_hook(game->win, &handle_keypress, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &close_window, game);
	// mlx_mouse_hook(game->win, &handle_mouse, game);
	mlx_loop(game->mlx);
}

int	close_window(t_data	*game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_display(game->mlx);
	terminate(game);
	return (0);
}