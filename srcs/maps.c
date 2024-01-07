/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:00:14 by macarval          #+#    #+#             */
/*   Updated: 2024/01/06 23:27:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_file(char *argv[])
{
	if (!validate_extension(argv[1]) || !validate_open(argv[1]))
		return (0);
	// validate_map
	// struct map = process_map
	return (1);
}

int	validate_open(char *file)
{
	char	*map;
	int		fd;

	map = ft_strjoin("maps/", file);
	fd = open(map, O_RDONLY);
	free (map);
	if (fd == -1)
	{
		perror(file);
		printf(ERR_ARG);
		return (0);
	}
	close(fd);
	return (1);
}

int	validate_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (strcmp_mod(extension, ".cub"))
	{
		printf("%s: Extension not supported\n", file);
		printf(ERR_ARG);
		return (0);
	}
	return (1);
}
