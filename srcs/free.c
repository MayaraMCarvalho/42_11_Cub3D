/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:58:38 by macarval          #+#    #+#             */
/*   Updated: 2024/03/15 23:01:50 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char ***split)
{
	int		i;
	char	**temp;

	i = -1;
	temp = *split;
	while (temp[++i])
		free(temp[i]);
	free(*split);
}

void	free_game(t_data *game)
{
	if (game->file_name)
		free(game->file_name);
	if (game->info.north.file)
		free(game->info.north.file);
	if (game->info.south.file)
		free(game->info.south.file);
	if (game->info.west.file)
		free(game->info.west.file);
	if (game->info.east.file)
		free(game->info.east.file);
	if (game->map.map)
		free_map(game);
	if (game->mlx)
		free(game->mlx);
}

void	free_textures(t_data *game)
{
	if (game->info.north.tex.img)
		mlx_destroy_image(game->mlx, game->info.north.tex.img);
	if (game->info.south.tex.img)
		mlx_destroy_image(game->mlx, game->info.south.tex.img);
	if (game->info.east.tex.img)
		mlx_destroy_image(game->mlx, game->info.east.tex.img);
	if (game->info.west.tex.img)
		mlx_destroy_image(game->mlx, game->info.west.tex.img);
}

void	free_map(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->map.height)
		free(game->map.map[i]);
	free(game->map.map);
}

void	exit_err(char *line, t_data *game, int exit_code, char *err)
{
	if (errno == -1)
		perror("general error");
	else
		ft_putstr_fd(err, 2);
	if (line)
		free(line);
	if (game)
	{
		game->exit_code = exit_code;
		if (game->mlx)
			close_window(game);
	}
	exit (exit_code);
}
