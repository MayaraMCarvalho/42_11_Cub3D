/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:25:22 by macarval          #+#    #+#             */
/*   Updated: 2024/03/12 11:01:05 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSGS_H
# define ERROR_MSGS_H

/* Arguments Erros*/
# define ERR_ARG "\nUsage: ./cub3D [*.cub]\nArgs: a map in format *.cub\n\n"

/* Maps erros */
# define ERR_MAP_OPEN "\nError\nMap is open\n\n"
# define ERR_MAP_SET "\nError\nInvalid Map Settings\n\n"
# define ERR_MAP_MISS "\nError\nMap without identifier\n\n"
# define ERR_MAP_MORE "\nError\nMore than one map identifier\n\n"
# define ERR_MAP_DISALLOW "\nError\nMap with disallowed identifier\n\n"
# define ERR_MAP_LOCAL "\nError\nMap indicator location is incorrect\n\n"

/* Settings erros */
# define ERR_EMPTY "\nError\nFile empty\n\n"
# define ERR_MISS "\nError\nConfiguration items are missing\n\n"
# define ERR_SET "\nError\nInvalid Settings\n\n"
# define ERR_COLOR "\nError\nInvalid Color Settings\n\n"
# define ERR_TEX "\nError\nInvalid Texture Settings\n\n"
# define ERR_MORE "\nError\nConfiguration items are more\n\n"
# define ERR_XPM "\nError\nTexture not found\n\n"

/* MLX errors*/
# define ERR_MLX_WIN "\nError\nError creating mlx window\n\n"
# define ERR_MLX_IMG "\nError\nError creating mlx image\n\n"
# define ERR_MLX_INIT "\nError\nMlx initialization error\n\n"
# define ERR_MLX_ADDR "\nError\nError in mlx addr data collection\n\n"

#endif
