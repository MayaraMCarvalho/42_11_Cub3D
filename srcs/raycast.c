/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:20:14 by joapedr2          #+#    #+#             */
/*   Updated: 2024/03/15 19:42:11 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycast(t_raycast *ray, t_data *game)
{
	ray->rays = -1;
	ray->ang = game->player.ang + (M_PI / 6);
	if (game->map.height > game->map.width)
		ray->max_dof = game->map.height;
	else
		ray->max_dof = game->map.width;
}

static void	reset_params(t_raycast *ray, t_data *game)
{
	ray->hor[0] = game->player.x;
	ray->hor[1] = game->player.y;
	ray->hor[2] = 1000000000;
	ray->ver[0] = game->player.x;
	ray->ver[1] = game->player.y;
	ray->ver[2] = 1000000000;
	ray->offset[0] = 0;
	ray->offset[1] = 0;
	ray->a_tan = 0;
	ray->dof = 0;
	if (ray->ang < 0)
		ray->ang += 2 * M_PI;
	if (ray->ang > 2 * M_PI)
		ray->ang -= 2 * M_PI;
}

void	raycast(t_data *game)
{
	t_raycast	ray;

	init_raycast(&ray, game);
	while (++ray.rays < MAX_RAYS)
	{
		reset_params(&ray, game);
		h_rays(&ray, &(game)->player, game->map);
		v_rays(&ray, &(game)->player, game->map);
		get_walls(game, &ray);
		ray.ang -= 0.017453 / (MAX_RAYS / FOV);
	}
}
