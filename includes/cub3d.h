/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:20:45 by joapedr2          #+#    #+#             */
/*   Updated: 2024/01/03 22:20:51 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H


# include "mlx.h"	//minilibx
# include "libft.h"

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_length;
	int		endian;
}	t_image;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_image		img;
}	t_data;


#endif //CUB3D_H
