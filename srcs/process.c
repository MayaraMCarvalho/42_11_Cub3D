/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:58:34 by macarval          #+#    #+#             */
/*   Updated: 2024/01/09 18:51:43 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_file(t_data *game)
{
	char	*line;
	int		control;

	line = get_next_line(game->file);
	control = 0;
	while (line)
	{
		if (strcmp_mod(line, "\n"))
		{
			if (control < 6)
				control += process_line(line, game);
			else
			{
			}
				// process_map();
		}
		free(line);
		line = get_next_line(game->file);
	}
	close(game->file);
}

int	process_line(char *line, t_data *game)
{
	char	**split;
	int		control;

	control = 0;
	split = ft_split(line, ' ');
	if (!split[1] || split[2])
	{
		free_split(&split);
		exit_err(line, game, 6);
	}
	control = set_variables(game, split);
	if (control)
		exit_err(line, game, 7);
	return (1);
}

int	set_variables(t_data *game, char **split)
{
	int		control;

	control = 0;
	if (!strcmp_mod(split[0], "NO"))
		game->info.north = ft_strdup(split[1]);
	else if (!strcmp_mod(split[0], "SO"))
		game->info.south = ft_strdup(split[1]);
	else if (!strcmp_mod(split[0], "WE"))
		game->info.west = ft_strdup(split[1]);
	else if (!strcmp_mod(split[0], "EA"))
		game->info.east = ft_strdup(split[1]);
	else if (!strcmp_mod(split[0], "F"))
		control = get_color(split[1], &game->info.floor);
	else if (!strcmp_mod(split[0], "C"))
		control = get_color(split[1], &game->info.ceiling);
	free_split(&split);
	return(control);
}

int	get_color(char	*line, t_color *color)
{
	char	**split;

	split = ft_split(line, ',');
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		printf(ERR_SET);
		free_split(&split);
		return (1);
	}
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	free_split(&split);
	return (0);
}
