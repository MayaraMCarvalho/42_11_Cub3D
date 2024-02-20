/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:42:33 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/20 15:12:36 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec2d.h"

#define MAP2D	680
#define SIZE	32
#define SPEED	5

void	draw_wall(int x, int y, t_img *img)
{
	int i = x;
	while (++i < x + SIZE)
	{
		int j = y;
		while (++j < y + SIZE)
			put_pixel_img(img, i, j, 0xFFFFFFFF);
	}
}

void	draw_player(t_player player, t_img *img)
{
	t_point	init;
	t_point	dest;

	init.x = player.x;
	init.y = player.y;
	dest.x = player.x + 5;
	dest.y = player.y;
	dest.color = 0;
	while (dest.y < player.y + 5)
	{
		bresenham(img, init, dest);
		init.y++;
		dest.y++;
	}
	init.x = player.x + 2;
	init.y = player.y + 2;
	dest.x = player.x + (cos(player.ang) * 15) + 2;
	dest.y = player.y + (-sin(player.ang) * 15) + 2;
	bresenham(img, init, dest);
}

void	init_player(t_data *game)
{
	int		x;
	int		y;
	char	c;

	y = -1;
	while (++y < game->info.data.map_height)
	{
		x = -1;
		while (++x < game->info.data.map_width)
		{
			if(ft_isalpha(game->info.data.map[y][x]))
			{
				c = game->info.data.map[y][x];
				game->player.x = (x + 0.5) * SIZE;
				game->player.y = (y + 0.5) * SIZE;
			}
		}
	}
	if (c == 'N')
		game->player.ang = M_PI / 2;
	else if (c == 'S')
		game->player.ang = 3 * M_PI / 2;
	else if (c == 'W')
		game->player.ang = 0.0001;
	else if (c == 'E')
		game->player.ang = 0.00001;
}

void	draw_map(t_data *game, t_img *img)
{
	int y = 0;
	int	i = -1;

	while(++i < game->info.data.map_height)
	{
		int j = -1;
		int x = 0;
		while (++j < game->info.data.map_width)
		{
			if (game->info.data.map[i][j] == '1')
				draw_wall(x, y, img);
			x += SIZE;
		}
		y += SIZE;
	}
}

int	exit_button(t_data2d *e)
{
	mlx_loop_end(e->mlx);
	mlx_destroy_window(e->mlx, e->window);
	return (0);
}

void	run_2d_game(t_data *game)
{
	t_data2d	data;

	data.game = game;
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, MAP2D, MAP2D, "cub2D");
	data.img->img = mlx_new_image(data.mlx, MAP2D, MAP2D);
	data.img->addr = mlx_get_data_addr(data.img->img, &(data.img->bpp),
			&(data.img->line_len), &(data.img->endian));
	init_player(data.game);
	draw(&data);

	mlx_hook(data.window, 17, 0L, &exit_button, data.window);
	mlx_hook(data.window, 02, 1L << 0, key_press, &data);

	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.img->img);
	free(data.mlx);
}
/***************************************************/
//Draw

void	draw_background(t_img *img)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIN_W)
	{
		y = -1;
		while (++y <= WIN_H)
			put_pixel_img(img, x, y, 0x0);
	}
}

void	draw(t_data2d *data)
{
	draw_background(data->img);
	draw_map(data->game, data->img);
	draw_player(data->game->player, data->img);
	draw_raycast(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img->img, 0, 0);
}

/***************************************************/
//Movimento

int	key_press(int key, t_data2d *data)
{
	t_data *game = data->game;

	if (key == ESC_KEY)
		exit_button(data);
	if (key == W_KEY)
	{
		game->player.y += -sin(game->player.ang) * SPEED;
		game->player.x += cos(game->player.ang) * SPEED;
	}
	if (key == S_KEY)
	{
		game->player.y -= -sin(game->player.ang) * SPEED;
		game->player.x -= cos(game->player.ang) * SPEED;
	}
	if (key == A_KEY)
		game->player.x -= SPEED;
	if (key == D_KEY)
		game->player.x += SPEED;
	if (key == LEFT_KEY)
		game->player.ang += 0.1;
	if (key == RIGHT_KEY)
		game->player.ang -= 0.1;

	if (game->player.ang < 0)
		game->player.ang += 2 * M_PI;
	if (game->player.ang > (2 * M_PI -0.00001))
		game->player.ang -= 2 * M_PI;

	draw(data);
	return (0);
}

/***************************************************/
// Raycast
#define FOV			66
#define HALF_FOV	FOV/2
#define MAX_RAYS	1200
#define MAX_DELPH	560
#define WALL_HEIGHT	700

int dist(int x1,int y1, int x2,int y2)
{
	return (sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
}
// 1 1 1 1 0 0 0 0
void	h_rays(t_raycast *ray, t_player *p, t_sat map)
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
			&& ray->map[0] < map.data.map_width		\
			&& ray->map[1] < map.data.map_height	\
			&& map.data.map[ray->map[1]][ray->map[0]] == '1')
		{
			// ray->hor[2] = cos(ray->ang) * (ray->hor[0] - p->x) - sin(ray->ang) * (ray->hor[1] - p->y);
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

void	v_rays(t_raycast *ray, t_player *p, t_sat map)
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
			&& ray->map[0] < map.data.map_width		\
			&& ray->map[1] < map.data.map_height	\
			&& map.data.map[ray->map[1]][ray->map[0]] == '1')
		{
			// ray->ver[2] = cos(ray->ang) * (ray->ver[0] - p->x) - sin(ray->ang) * (ray->ver[1] - p->y);
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
	if (data->game->info.data.map_height > data->game->info.data.map_width)
		ray->max_dof = data->game->info.data.map_height;
	else
		ray->max_dof = data->game->info.data.map_width;
}

void	reset_params(t_raycast *ray, t_data2d *data)
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
	int ang = 0;//
	int control = 0;//
	while (ray.rays < MAX_RAYS)
	{
		reset_params(&ray, data);
		h_rays(&ray, &(data->game)->player, data->game->info);
		v_rays(&ray, &(data->game)->player, data->game->info);
		ray.ang -= 0.017453 / (MAX_RAYS / FOV);
		ray.rays++;

		t_point	init;
		t_point	dest;
		init.x = data->game->player.x + 2;
		init.y = data->game->player.y + 2;
		if (ray.ver[2] < ray.hor[2])
		{
			dest.x = ray.ver[0] + 2;
			dest.y = ray.ver[1] + 2;
			dest.color = 0xe83c25;
		}
		else {
			dest.x = ray.hor[0] + 2;
			dest.y = ray.hor[1] + 2;
			dest.color = 0xe85e25;
		}
		bresenham(data->img, init, dest);
		//
		float h;
		h = ray.ver[2];
		if (h > ray.hor[2])
			h = ray.hor[2];
		fprintf(fopen("dados.txt", "a+"),"%f\n", cos(ray.ang) * h);//
		printf("ray: %f\n", ray.ang);//

		if ((int)ray.ang != ang && ray.ang > 0)
		{
			control++;
			if (control > 4)
				control = 1;
		}
		fprintf(fopen("color.txt", "a+"),"%d\n", control);//
		ang = ray.ang;
		//

		// raising_the_walls(&ray, &(data->game)->player, &(data->game)->img);
		// raising_the_walls(&ray, &(data->game)->player, data->img);
	}
}

// void	raising_the_walls(t_raycast *ray, t_player *p, t_img *img)
// {
// 	t_point	init;
// 	t_point	dest;
// 	float	disH = ray->hor[2] * cos(p->ang - ray->ang);
// 	int		hor_size = WIN_W / MAX_RAYS;
// 	int		ver_line = (WIN_H * WIN_W / WALL_HEIGHT) / disH;
// 	int		lineH = (SIZE * WIN_W) / (disH);
// 	int		lineOff = WIN_H - (lineH>>1);

// 	init.x = ray->rays * hor_size;
// 	dest.x = ray->rays * hor_size + hor_size;
// 	dest.x--;
// 	for (int i = 0; i < ver_line; i++)
// 	{
// 		init.y = i + lineOff;
// 		dest.y = i + lineOff;
// 		if(ray->ver[2] < ray->hor[2])
// 			dest.color = 0xe83c25;
// 		else
// 			dest.color = 0xe85e25;
// 		bresenham(img, init, dest);
// 	}
// }
