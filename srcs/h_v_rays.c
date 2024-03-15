/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_v_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:54:24 by macarval          #+#    #+#             */
/*   Updated: 2024/03/15 19:44:34 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_h_rays(t_raycast *ray, t_player *p)
{
	ray->a_tan = 1 / tan(ray->ang);
	if (ray->ang < M_PI)
	{
		ray->hor[1] = (((int)p->y >> 5) << 5) - 0.0001;
		ray->hor[0] = (p->y - ray->hor[1]) * ray->a_tan + p->x;
		ray->offset[1] = -SIZE;
		ray->offset[0] = -ray->offset[1] * ray->a_tan;
	}
	else if (ray->ang > M_PI)
	{
		ray->hor[1] = (((int)p->y >> 5) << 5) + SIZE;
		ray->hor[0] = (p->y - ray->hor[1]) * ray->a_tan + p->x;
		ray->offset[1] = SIZE;
		ray->offset[0] = -ray->offset[1] * ray->a_tan;
	}
	else if (ray->ang == 0 || ray->ang == M_PI)
	{
		ray->hor[0] = p->x;
		ray->hor[1] = p->y;
		ray->dof = ray->max_dof;
	}
}

void	h_rays(t_raycast *ray, t_player *p, t_map map)
{
	set_h_rays(ray, p);
	while (ray->dof < ray->max_dof)
	{
		ray->map[0] = (int)(ray->hor[0]) >> 5;
		ray->map[1] = (int)(ray->hor[1]) >> 5;
		if (ray->map[0] >= 0 && ray->map[1] >= 0
			&& ray->map[0] < map.width
			&& ray->map[1] < map.height
			&& map.map[ray->map[1]][ray->map[0]] == '1')
		{
			ray->hor[2] = cos(ray->ang) * (ray->hor[0] - p->x)
				- sin(ray->ang) * (ray->hor[1] - p->y);
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

static void	set_v_rays(t_raycast *ray, t_player *p)
{
	ray->a_tan = tan(ray->ang);
	if (ray->ang < M_PI / 2 || ray->ang > 3 * M_PI / 2)
	{
		ray->ver[0] = (((int)p->x >> 5) << 5) + SIZE;
		ray->ver[1] = (p->x - ray->ver[0]) * ray->a_tan + p->y;
		ray->offset[0] = SIZE;
		ray->offset[1] = -ray->offset[0] * ray->a_tan;
	}
	else if (ray->ang > M_PI / 2 && ray->ang < 3 * M_PI / 2)
	{
		ray->ver[0] = (((int)p->x >> 5) << 5) + -0.0001;
		ray->ver[1] = (p->x - ray->ver[0]) * ray->a_tan + p->y;
		ray->offset[0] = -SIZE;
		ray->offset[1] = -ray->offset[0] * ray->a_tan;
	}
	else if (ray->ang == M_PI / 2 || ray->ang == 3 * M_PI / 2)
	{
		ray->ver[0] = p->x;
		ray->ver[1] = p->y;
		ray->dof = ray->max_dof;
	}
}

void	v_rays(t_raycast *ray, t_player *p, t_map map)
{
	set_v_rays(ray, p);
	while (ray->dof < ray->max_dof)
	{
		ray->map[0] = (int)(ray->ver[0]) >> 5;
		ray->map[1] = (int)(ray->ver[1]) >> 5;
		if (ray->map[0] >= 0 && ray->map[1] >= 0
			&& ray->map[0] < map.width
			&& ray->map[1] < map.height
			&& map.map[ray->map[1]][ray->map[0]] == '1')
		{
			ray->ver[2] = cos(ray->ang) * (ray->ver[0] - p->x)
				- sin(ray->ang) * (ray->ver[1] - p->y);
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