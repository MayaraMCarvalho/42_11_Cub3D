/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:50:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/29 13:53:25 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_walls(t_data *game, t_raycast *ray)
{
	float	max;
	float	tam;
	float	distance;
	int		color;

	distance = ray->ver[2];
	color = 0x111e99;
	if (distance > ray->hor[2])
	{
		color = 0x7202b8;
		distance = ray->hor[2];
	}
	max = (float) WIN_H;
	if (max < WIN_W)
		max = WIN_W;
	distance *= cos(game->player.ang - ray->ang);
	tam = ((1.2 * max) - 20) * (max - 0.1) / (distance - 0.1) / 100;
	if (tam - floor(tam) > 0.4)
		tam += 1.0;
	draw_walls(&game->img, tam, ray->rays, color);
}
