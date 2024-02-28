/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:50:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/28 10:47:14 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_walls(t_data *game, t_raycast *rays)
{
	float	ray;
	float	max;
	float	tam;
	float	distance;

	ray = rays->ver[2];
	if (ray > rays->hor[2])
		ray = rays->hor[2];
	max = (float) WIN_H;
	if (max < WIN_W)
		max = WIN_W;
	distance = cos(rays->ang) * ray;
	tam = ((1.2 * max) - 20) * (max - 0.1) / (distance - 0.1) / 100;
	draw_walls(&game->img, tam, rays->rays, 0x111e99);
}
