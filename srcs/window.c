/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:17:55 by macarval          #+#    #+#             */
/*   Updated: 2024/03/17 15:46:44 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validation_window_alloc(t_data *game)
{
	if (game->mlx == NULL)
		exit_err(NULL, game, 2, ERR_MLX_INIT);
	else if (game->win == NULL)
		exit_err(NULL, game, 3, ERR_MLX_WIN);
	else if (game->img.img == NULL)
		exit_err(NULL, game, 4, ERR_MLX_IMG);
	else if (game->img.addr == NULL)
		exit_err(NULL, game, 5, ERR_MLX_ADDR);
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
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &key_press_esc, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &close_window, game);
	mlx_mouse_hook(game->win, &handle_mouse, game);
	mlx_loop(game->mlx);
}

int	handle_mouse(int button, int x, int y, t_data *game)
{
	if (button == 1 && y)
	{
		if (x <= WIN_W / 2)
			game->player.ang += 0.1;
		else
			game->player.ang -= 0.1;
		if (game->player.ang < 0)
			game->player.ang += 2 * M_PI;
		if (game->player.ang > (2 * M_PI -0.00001))
			game->player.ang -= 2 * M_PI;
		draw(game);
	}
	return (0);
}

int	close_window(t_data	*game)
{
	int	code;

	code = 0;
	if (game)
	{
		code = game->exit_code;
		if (game->mlx)
		{
			if (game->win)
				mlx_destroy_window(game->mlx, game->win);
			mlx_destroy_image(game->mlx, game->img.img);
			free_textures(game);
			mlx_destroy_display(game->mlx);
		}
		free_game(game);
	}
	exit (code);
}
