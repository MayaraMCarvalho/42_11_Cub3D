/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:03:32 by joapedr2          #+#    #+#             */
/*   Updated: 2024/02/13 11:31:36 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x > WIN_W || y > WIN_H || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	bres_define(t_bres *b, t_point *init, t_point *dest)
{
	b->dx = abs(dest->x - init->x);
	b->dy = abs(dest->y - init->y);
	b->p = b->dx - b->dy;
	b->x = init->x;
	b->y = init->y;
	b->sign_x = 1;
	b->sign_y = 1;
	b->color = 0xFA8218;
	if (init->x > dest->x)
		b->sign_x = -1;
	if (init->y > dest->y)
		b->sign_y = -1;
	if (dest->color)
		b->color = dest->color;
}

void	bresenham(t_img *img, t_point init, t_point dest)
{
	t_bres	bres;
	int		p;

	bres_define(&bres, &init, &dest);
	while (bres.x != dest.x || bres.y != dest.y)
	{
		put_pixel_img(img, bres.x, bres.y, bres.color);
		p = bres.p;
		if (p * 2 > -bres.dy)
		{
			bres.p -= bres.dy;
			bres.x += bres.sign_x;
		}
		if (p * 2 < bres.dx)
		{
			bres.p += bres.dx;
			bres.y += bres.sign_y;
		}
	}
}