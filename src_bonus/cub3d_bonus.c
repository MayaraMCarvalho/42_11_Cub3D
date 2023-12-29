/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:26:45 by macarval          #+#    #+#             */
/*   Updated: 2023/12/29 11:48:57 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	char	*map;
	int		fd;

	if (argc == 2)
	{
		map = argv[1];
		fd = open(map, O_RDONLY);
		if (fd == -1)
		{
			perror(argv[1]);
			return (1);
		}
		// validar mapa
		close(fd);
	}
	else
	{
		printf("Usage: ./cub3D [*.cub]\nArgs: a map in format *.cub\n");
		return (2);
	}
	return (0);
}
