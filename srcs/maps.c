/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:03:43 by macarval          #+#    #+#             */
/*   Updated: 2024/01/16 17:05:36 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map(t_data *game, int final_set)
{
	char	*line;
	int		width;

	line = get_map_init(game, final_set);
	game->info.data.map_height = 1;
	game->info.data.map_width = ft_strlen(line) - 1;
	while (line)
	{
		if (!strcmp_mod(line, "\n"))
			exit_err(line, game, 13, ERR_MAP_OPEN);
		width = ft_strlen(line) - 1;
		if (width > game->info.data.map_width)
			game->info.data.map_width = width;
		game->info.data.map_height++;
		free(line);
		line = get_next_line(game->fd);
	}
	if (line)
		free(line);
	close(game->fd);
}

char	*get_map_init(t_data *game, int final_set)
{
	char	*line;

	line = get_next_line(game->fd);
	game->info.data.map_init = 1;
	while (line && !strcmp_mod(line, "\n"))
	{
		game->info.data.map_init++;
		free(line);
		line = get_next_line(game->fd);
	}
	if (line[0] == 'F' || line[0] == 'C')
		exit_err(line, game, 14, ERR_COLOR);
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		exit_err(line, game, 15, ERR_TEX);
	game->info.data.map_init += final_set;
	return (line);
}

void	get_map(t_data *game)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	alloc_map(game);
	game->fd = open(game->file_name, O_RDONLY);
	line = get_next_line(game->fd);
	while (line && ++i < game->info.data.map_init)
	{
		free(line);
		line = get_next_line(game->fd);
	}
	j = 0;
	while (line)
	{
		i = -1;
		while (line[++i] && line[i] != '\n')
			game->info.data.map[j][i] = line[i];
		j++;
		free(line);
		line = get_next_line(game->fd);
	}
}

void	alloc_map(t_data *game)
{
	int	i;

	game->info.data.map = (char **) ft_calloc
		(game->info.data.map_height + 1, sizeof(char *));
	i = -1;
	while (++i < game->info.data.map_height)
	{
		game->info.data.map[i] = (char *) ft_calloc
			(game->info.data.map_width + 1, sizeof(char));
	}
}

int	check_neighbors(t_data *game, int j, int i, char *pattern)
{
	char	**map;

	map = game->info.data.map;
	if (j - 1 < 0 || j + 1 >= game->info.data.map_height
		|| i - 1 < 0 || i + 1 >= game->info.data.map_width
		|| !map[j][i + 1] || !map[j + 1][i])
		return (0);
	if (!ft_strchr("01NSEW\t\n ", map[j][i + 1])
		|| !ft_strchr("01NSEW\t\n ", map[j + 1][i]))
		exit_err(NULL, game, 17, ERR_MAP_DISALLOW);
	if (!ft_strchr(pattern, map[j][i - 1])
		|| !ft_strchr(pattern, map[j][i + 1])
		|| !ft_strchr(pattern, map[j - 1][i])
		|| !ft_strchr(pattern, map[j + 1][i]))
		return (0);
	return (1);
}
