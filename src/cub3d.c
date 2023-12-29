/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:26:45 by macarval          #+#    #+#             */
/*   Updated: 2023/12/29 17:31:59 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// talvez mandar uma struct para validate_file e assim setar qualquer
// informação necessária do mapa
int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (validate_file(argv))
		{
			printf("\nCub3D running!!!\n\n");
			config_win();
		}
	}
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

	map = ft_strjoin("maps/", argv[1]);
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		printf("\nUsage: ./cub3D [*.cub]\nArgs: a map in format *.cub\n\n");
		return (0);
	}
	// validate_map
	// struct map = process_map
	close(fd);
	free (map);
	return (1);
}
