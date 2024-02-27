/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:50:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/27 09:23:28 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_walls(t_data *game, t_raycast *ray)
{
	float	ray_max;
	float	max;
	float	tam;
	float	distance;

	ray_max = ray->ver[2];
	if (ray_max > ray->hor[2])
		ray_max = ray->hor[2];
	max = (float) WIN_H;
	if (max < WIN_W)
		max = WIN_W;
	distance = cos(ray->ang) * ray_max;
	tam = ((1.2 * max) - 20) * (max - 0.1) / (distance - 0.1) / 100;
	draw_walls(&game->img, tam, ray->rays, 0x111e99);
}
