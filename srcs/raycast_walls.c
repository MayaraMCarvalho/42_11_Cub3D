/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:50:49 by joapedr2          #+#    #+#             */
/*   Updated: 2024/03/07 23:13:36 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_walls(t_data *game, t_raycast *ray)
{
	float	max;
	float	tam;
	float	distance;
	double	ang_abs;//

	distance = ray->ver[2];
	if (distance > ray->hor[2])
		distance = ray->hor[2];
	max = (float) WIN_H;
	if (max < WIN_W)
		max = WIN_W;
	distance *= cos(game->player.ang - ray->ang);
	tam = ((1.2 * max) - 20) * (max - 0.1) / (distance - 0.1) / 100;
	if (tam - floor(tam) > 0.4)
		tam += 1.0;
	//
	ang_abs = fmod((fmod(game->player.ang, 2 * 3.14159265359)
				+ ray->ang), 2 * 3.14159265359);
	if (ang_abs >= 0 && ang_abs < PI / 2)
		distance = 2;
	else if (ang_abs >= PI / 2 && ang_abs < PI)
		distance = 1;
	else if (ang_abs >= PI && ang_abs < 3 * PI / 2)
		distance = 4;
	else
		distance = 3;
	//
	draw_walls(game, tam, ray->rays, distance);
}
