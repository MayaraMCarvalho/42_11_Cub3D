/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:26:45 by macarval          #+#    #+#             */
/*   Updated: 2023/12/29 14:36:42 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	if (argc == 2)
		validate_file(argv);
	else
	{
		printf("Usage: ./cub3D [*.cub]\nArgs: a map in format *.cub\n\n");
		return (2);
	}
	return (0);
}

int	validate_file(char *argv[])
{
	char	*map;
	int		fd;

	map = argv[1];
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		printf("\nUsage: ./cub3D [*.cub]\nArgs: a map in format *.cub\n\n");
		return (1);
	}
	// validar mapa
	close(fd);
	return (0);
}
