/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:17:55 by macarval          #+#    #+#             */
/*   Updated: 2024/01/09 18:39:45 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	config_win(t_data *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		printf(ERR_MLX_INIT);
		game->exit_code = 2;
		close_window(game);
	}
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "*** Cub3D ***");
	if (game->win == NULL)
	{
		printf(ERR_MLX_WIN);
		game->exit_code = 3;
		close_window(game);
	}
	// create_img(game);
	// mlx_loop_hook(game->mlx, &render, game);
	game->exit_code = 0;
	printf("\nCub3D running!!!\n\n");
	mlx_key_hook(game->win, &handle_keypress, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &close_window, game);
	// mlx_mouse_hook(game->win, &handle_mouse, game);
	mlx_loop(game->mlx);
}

int	close_window(t_data	*game)
{
	mlx_destroy_window(game->mlx, game->win);
	// mlx_destroy_image(game->mlx, game->img.mlx_img);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game(game);
	exit (game->exit_code);
}
