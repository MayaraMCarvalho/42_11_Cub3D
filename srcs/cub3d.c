/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:15:03 by macarval          #+#    #+#             */
/*   Updated: 2024/01/06 23:27:44 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		printf("Enter a valid file\n");
		printf(ERR_ARG);
		exit (1);
	}
	return (0);
}
