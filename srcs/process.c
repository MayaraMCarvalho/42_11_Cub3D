/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:58:34 by macarval          #+#    #+#             */
/*   Updated: 2024/03/07 17:48:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_settings(t_data *game)
{
	char	*line;
	int		control;
	int		final_set;

	line = get_next_line(game->fd);
	control = 0;
	final_set = 0;
	while (line && control < 6)
	{
		final_set++;
		if (strcmp_mod(line, "\n"))
			control += process_line(line, game);
		free(line);
		if (control < 6)
			line = get_next_line(game->fd);
	}
	if (control == 0)
		exit_err(line, game, 6, ERR_EMPTY);
	return (final_set);
}

int	process_line(char *line, t_data *game)
{
	char	**split;
	int		control;

	control = 0;
	split = ft_split(line, ' ');
	if (!split[1])
	{
		free_split(&split);
		exit_err(line, game, 7, ERR_SET);
	}
	if (split[2])
	{
		free_split(&split);
		exit_err(line, game, 8, ERR_MORE);
	}
	control = set_variables(game, split, line);
	free_split(&split);
	if (control == 1)
		exit_err(line, game, 9, ERR_MORE);
	if (control == 2)
		exit_err(line, game, 10, ERR_COLOR);
	return (1);
}

int	set_variables(t_data *game, char **split, char *line)
{
	int		control;

	control = 0;
	if (!strcmp_mod(split[0], "\n") || !strcmp_mod(split[1], "\n"))
	{
		free_split(&split);
		exit_err(line, game, 11, ERR_MISS);
	}
	if (get_textures(game, split))
		control = 0;
	else if (!strcmp_mod(split[0], "F"))
		control = get_color(split[1], &game->info.floor);
	else if (!strcmp_mod(split[0], "C"))
		control = get_color(split[1], &game->info.ceiling);
	else
	{
		free_split(&split);
		exit_err(line, game, 12, ERR_TEX);
	}
	return (control);
}

int	get_textures(t_data *game, char **split)
{
	int		control;
	char	*texture;

	control = 1;
	texture = strchr_rev(split[1], '\n');
	if (!game->info.north.file && !strcmp_mod(split[0], "NO"))
		game->info.north.file = ft_strdup(texture);
	else if (!game->info.south.file && !strcmp_mod(split[0], "SO"))
		game->info.south.file = ft_strdup(texture);
	else if (!game->info.west.file && !strcmp_mod(split[0], "WE"))
		game->info.west.file = ft_strdup(texture);
	else if (!game->info.east.file && !strcmp_mod(split[0], "EA"))
		game->info.east.file = ft_strdup(texture);
	else
		control = 0;
	free(texture);
	return (control);
}

int	get_color(char	*line, t_color *color)
{
	char	**split;

	if (color->r != -1 || color->g != -1 || color->b != -1)
		return (1);
	split = ft_split(line, ',');
	if (!split[0] || !split[1] || !split[2])
	{
		free_split(&split);
		return (2);
	}
	if (split[3])
	{
		free_split(&split);
		return (1);
	}
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	free_split(&split);
	return (0);
}
