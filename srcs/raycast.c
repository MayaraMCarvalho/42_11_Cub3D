/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:20:14 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/25 17:22:24 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int dist(int x1,int y1, int x2,int y2)
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
	ray->dof = 0;
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
	ray->dof = 0;
}

void	init_raycast(t_raycast *ray, t_data2d *data)
{
	ray->ang = data->game->player.ang + (M_PI / 6);
	ray->rays = 0;
	if (data->game->map.map_height > data->game->map.map_width)
		ray->max_dof = data->game->map.map_height;
	else
		ray->max_dof = data->game->map.map_width;
}

static void	reset_params(t_raycast *ray, t_data2d *data)
{
	ray->hor[0] = data->game->player.x;
	ray->hor[1] = data->game->player.y;
	ray->hor[2] = 1000000000;
	ray->ver[0] = data->game->player.x;
	ray->ver[1] = data->game->player.y;
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

void	draw_raycast(t_data2d *data)
{
	t_raycast ray;
	
	init_raycast(&ray, data);
	while (ray.rays < MAX_RAYS)
	{
		reset_params(&ray, data);
		h_rays(&ray, &(data->game)->player, data->game->map);
		v_rays(&ray, &(data->game)->player, data->game->map);
		ray.ang -= 0.017453 / (MAX_RAYS / FOV);
		ray.rays++;
		
		t_point	init;
		t_point	dest;
		init.x = data->game->player.x + 2;
		init.y = data->game->player.y + 2;
		if(ray.ver[2] < ray.hor[2])
		{		
			dest.x = ray.ver[0] + 2;
			dest.y = ray.ver[1] + 2;
			dest.color = 0xe83c25;
		}
		else{
			dest.x = ray.hor[0] + 2;
			dest.y = ray.hor[1] + 2;
			dest.color = 0xe85e25;
		}
	}
}