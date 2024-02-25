/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:12:56 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/25 17:13:00 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	init_player(t_data *game)
{
	int		x;
	int		y;
	char	c;

	y = -1;
	while (++y < game->map.map_height)
	{
		x = -1;
		while (++x < game->map.map_width)
		{
			if(ft_isalpha(game->map.map[y][x]))
			{
				c = game->map.map[y][x];
				game->player.x = (x + 0.5) * SIZE;
				game->player.y = (y + 0.5) * SIZE;
				game->player.map[0] = x;
				game->player.map[1] = y;
			}
		}
	}
	if (c == 'N')
		game->player.ang = M_PI / 2;
	else if (c == 'S')
		game->player.ang = 3 * M_PI / 2;
	else if (c == 'W')
		game->player.ang = M_PI;
	else if (c == 'E')
		game->player.ang = 0;
}