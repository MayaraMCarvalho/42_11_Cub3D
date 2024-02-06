/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:42:33 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/05 22:00:46 by joapedr2         ###   ########.fr       */
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
	while (dest.y < player.y + 5)
	{
		bresenham(img, init, dest);
		init.y++;
		dest.y++;
	}
	init.x = player.x + 2;
	init.y = player.y + 2;
	dest.x = player.x + (cos(player.ang) * 15) + 2;
	dest.y = player.y + (sin(player.ang) * 15) + 2;
	bresenham(img, init, dest);
}

void	init_player(t_data *game,int x, int y, t_img *img)
{
	if (game->info.data.map[y][x] == 'N')
		game->player.ang = M_PI / 2;
	else if (game->info.data.map[y][x] == 'S')
		game->player.ang = 3 * M_PI / 2;
	else if (game->info.data.map[y][x] == 'W')
		game->player.ang = M_PI;
	else if (game->info.data.map[y][x] == 'E')
		game->player.ang = 0;
	game->player.x = (x + 0.5) * SIZE;
	game->player.y = (y + 0.5) * SIZE;
	draw_player(game->player, img);
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
	init_player(game, 7, 12, data.img);
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
		game->player.y += sin(game->player.ang) * SPEED;
		game->player.x += cos(game->player.ang) * SPEED;
	}
	if (key == S_KEY)
	{
		game->player.y -= sin(game->player.ang) * SPEED;
		game->player.x -= cos(game->player.ang) * SPEED;
	}
	if (key == A_KEY)
		game->player.x += SPEED;
	if (key == D_KEY)
		game->player.x -= SPEED;
	if (key == LEFT_KEY)
		game->player.ang -= 0.1;
	if (key == RIGHT_KEY)
		game->player.ang += 0.1;

	if (game->player.ang < 0)
		game->player.ang += 2 * M_PI;
	if (game->player.ang > 2 * M_PI)
		game->player.ang -= 2 * M_PI;
	draw(data);
	return (0);
}

/***************************************************/
// Raycast
#define FOV			M_PI/3
#define HALF_FOV	FOV/2
#define MAX_RAYS	480
#define MAX_DELPH	560

// void	draw_raycast(t_data2d *data)
// {
// 	// t_raycast	ray;
// 	float		x_map = data->game->player.x / SIZE;
// 	// float		y_map = data->game->player.y / SIZE;
// 	float		px = data->game->player.x;
// 	float		py = data->game->player.y;
// 	float		ray_ang = data->game->player.ang - HALF_FOV + 0.0001;
// 	float		sin_a;
// 	float		cos_a;
// 	float			dx;
// 	float			dy;
// 	float		ddepth;
// 	float		depth_ver;
// 	// float		depth_hor;

// 	for (int i = 0; i < MAX_RAYS; i++)
// 	{
// 		sin_a = sin(ray_ang);
// 		cos_a = cos(ray_ang);

// 		//left
// 		float x_ver = (cos_a > 0) ? x_map + 1 : x_map - 0.00001;
// 		dx = (cos_a > 0) ? 1 : -1;
		
// 		depth_ver = (x_ver - px) / cos_a;
// 		float y_ver = py + depth_ver * sin_a;

// 		ddepth = dx / cos_a;
// 		dy = ddepth * sin_a;
// 		printf("dx: %f - dy: %f\n", dx, dy);
// 		for (int j = 0; j < MAX_DELPH; j++)
// 		{
// 			printf("x_v: %d - %f\n", (int)(x_ver / SIZE),x_ver);
// 			printf("y_v: %d - %f\n", (int)(y_ver / SIZE),y_ver);
// 			if ((int)(x_ver / SIZE) >= 15 || (int)(y_ver / SIZE) >= 15)
// 				break;
// 			x_ver += dx;
// 			y_ver += dy;
					
// 		}
// 		ray_ang += (FOV / MAX_RAYS);
// 			t_point	init;
// 			t_point	dest;
// 			init.x = data->game->player.x;
// 			init.y = data->game->player.y;
// 			dest.x = (int)x_ver;
// 			dest.y = (int)y_ver;
// 			bresenham(data->img, init, dest);
// 	}
// }

		// t_point	init;
		// t_point	dest;
		
		// init.x = data->game->player.x;
		// init.y = data->game->player.y;
		// dest.x = cos_a + 50000;
		// dest.y = sin_a + 50000;
		// bresenham(data->img, init, dest);
float degToRad(int a) { return a*M_PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

void	draw_raycast(t_data2d *data)
{
	// int r,mx,my,mp,dof,side;
	// float vx,vy,rx,ry,ra,xo,yo,disV,disH;
	// float px,py,pa;
	
	int r;
	float rx,ry,ra,xo,yo;
	float px,py,pa;
	
	pa = data->game->player.ang;
	px = data->game->player.x;
	py = data->game->player.y;
	ra = data->game->player.ang;

	for(r=0;r<60;r++)
	{
		printf("ang: %f\n", ra);
		(void)pa;
		(void)yo;

		//---Vertical--- 
		// dof=0; side=0; disV=100000;
		float aTan = -1 / tan(ra);
		if(ra > M_PI)
		{
			ry = (((int)py>>5)<<5) -0.0001;
			rx = (py-ry) * aTan + px;
			xo = -SIZE;
			yo = -xo*aTan;
		}//looking left
		if(ra < M_PI){
			printf("here\n");
			ry = (((int)px>>5)<<5) + SIZE;
			rx = (py-ry) * aTan + px;
			yo = SIZE;
			xo = -yo * aTan;
		}//looking right
		if (ra == 0 || ra == M_PI) {
			rx=px;
			ry=py;
			// dof=8;
		}//looking up or down. no hit  

	// while(dof<8) 
	// { 
	// mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
	// if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
	// else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	// } 
	// 	vx=rx; vy=ry;
	
		// while(dof<8) 
		// { 
		// 	mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
		// 	if(mp>0 && mp<mapX*mapY && map[mp]==1)
		// 	{
		// 		dof=8;
		// 		disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);
		// 	}//hit         
		// 	else
		// 	{
		// 		rx+=xo;
		// 		ry+=yo;
		// 		dof+=1;
		// 	}//check next horizontal
		// }

		t_point	init;
		t_point	dest;
		init.x = data->game->player.x + 2;
		init.y = data->game->player.y + 2;
		dest.x = rx + 2;
		dest.y = ry + 2;
		bresenham(data->img, init, dest);
		break;
	}
}
