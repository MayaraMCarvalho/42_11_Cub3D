/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:20:14 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/26 19:05:34 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int dist(int x1,int y1, int x2,int y2)
{
	return (sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
}

void	h_rays(t_raycast *ray, t_player *p, t_map map)
{
	ray->aTan = 1 / tan(ray->ang);
	if(ray->ang < M_PI){
		ray->hor[1] = (((int)p->y>>5)<<5) -0.0001;
		ray->hor[0] = (p->y - ray->hor[1]) * ray->aTan + p->x;
		ray->offset[1] = -SIZE;
		ray->offset[0] = -ray->offset[1] * ray->aTan;
	}
	else if (ray->ang > M_PI)
	{ 
		ray->hor[1] = (((int)p->y>>5)<<5)+SIZE;
		ray->hor[0] = (p->y - ray->hor[1]) * ray->aTan + p->x;
		ray->offset[1]= SIZE;
		ray->offset[0] = -ray->offset[1] * ray->aTan;
	}
	else if (ray->ang == 0 || ray->ang == M_PI)
	{
		ray->hor[0] = p->x;
		ray->hor[1] = p->y;
		ray->dof = ray->max_dof;
	}
	
	while (ray->dof < ray->max_dof)
	{
		ray->map[0] = (int)(ray->hor[0])>>5;
		ray->map[1] = (int)(ray->hor[1])>>5;
		if (ray->map[0] >= 0 && ray->map[1] >= 0	\
			&& ray->map[0] < map.map_width		\
			&& ray->map[1] < map.map_height	\
			&& map.map[ray->map[1]][ray->map[0]] == '1')
		{
			ray->hor[2] = dist(p->x, p->y, ray->hor[0], ray->hor[1]); 
			ray->dof = ray->max_dof;
		}
		else
		{
			ray->hor[0] += ray->offset[0];
			ray->hor[1] += ray->offset[1];
			ray->dof++;
		}
	}
}

void	v_rays(t_raycast *ray, t_player *p, t_map map)
{
	ray->aTan = tan(ray->ang);
	if(ray->ang < M_PI / 2 || ray->ang > 3 * M_PI / 2){
		ray->ver[0] = (((int)p->x>>5)<<5) + SIZE;
		ray->ver[1] = (p->x - ray->ver[0]) * ray->aTan + p->y;
		ray->offset[0] = SIZE;
		ray->offset[1] = -ray->offset[0] * ray->aTan;
	}
	else if (ray->ang > M_PI / 2 && ray->ang < 3 * M_PI / 2)
	{ 
		ray->ver[0] = (((int)p->x>>5)<<5) + -0.0001;
		ray->ver[1] = (p->x - ray->ver[0]) * ray->aTan + p->y;
		ray->offset[0] = -SIZE;
		ray->offset[1] = -ray->offset[0] * ray->aTan;
	}
	else if (ray->ang == M_PI / 2 || ray->ang == 3 * M_PI / 2)
	{
		ray->ver[0] = p->x;
		ray->ver[1] = p->y;
		ray->dof = ray->max_dof;
	}
	while (ray->dof < ray->max_dof)
	{
		ray->map[0] = (int)(ray->ver[0])>>5;
		ray->map[1] = (int)(ray->ver[1])>>5;
		if (ray->map[0] >= 0 && ray->map[1] >= 0	\
			&& ray->map[0] < map.map_width		\
			&& ray->map[1] < map.map_height	\
			&& map.map[ray->map[1]][ray->map[0]] == '1')
		{
			ray->ver[2] = dist(p->x, p->y, ray->ver[0], ray->ver[1]);
			ray->dof = ray->max_dof;
		}
		else
		{
			ray->ver[0] += ray->offset[0];
			ray->ver[1] += ray->offset[1];
			ray->dof++;
		}
	}
}

void	init_raycast(t_raycast *ray, t_data *game)
{
	ray->rays = -1;
	ray->ang = game->player.ang + (M_PI / 6);
	if (game->map.map_height > game->map.map_width)
		ray->max_dof = game->map.map_height;
	else
		ray->max_dof = game->map.map_width;
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
	ray->aTan = 0;
	ray->dof = 0;
	if (ray->ang < 0)
		ray->ang += 2 * M_PI;
	if (ray->ang > 2 * M_PI)
		ray->ang -= 2 * M_PI;
}

void	raycast(t_data *game)
{
	t_raycast ray;
	
	init_raycast(&ray, game);
	while (++ray.rays < MAX_RAYS)
	{
		
		reset_params(&ray, game);
		h_rays(&ray, &(game)->player, game->map);
		v_rays(&ray, &(game)->player, game->map);
		ray.ang -= 0.017453 / (MAX_RAYS / FOV);
		get_walls(game, &ray);
	}
}
