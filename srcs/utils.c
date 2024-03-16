/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:17:12 by macarval          #+#    #+#             */
/*   Updated: 2024/03/16 00:04:22 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	strcmp_mod(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;

	if (s1 && s2)
	{
		i = 0;
		len = ft_strlen(s1);
		if (len != ft_strlen(s2))
			return (1);
		while (i < len)
		{
			if (s1[i] != s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
			{
				return ((unsigned char) s1[i] - (unsigned char) s2[i]);
			}
			i++;
		}
		return (0);
	}
	return (1);
}

char	*strchr_rev(const char *str, int c)
{
	int			i;
	const char	*temp;

	i = 0;
	temp = str;
	if (str != NULL)
	{
		while (*str != '\0')
		{
			if (*str == (char) c)
				return ((char *)ft_substr(temp, 0, i));
			i++;
			str++;
		}
		if ((char) c == '\0' && *str == '\0')
			return ((char *)str);
	}
	return (NULL);
}

void	process_error(char *line, t_data *game, char **split)
{
	if (!split[0])
	{
		free_split(&split);
		exit_err(line, game, 25, ERR_EMPTY);
	}
	else if (!split[1])
	{
		free_split(&split);
		exit_err(line, game, 7, ERR_SET);
	}
	else if (split[2])
	{
		free_split(&split);
		exit_err(line, game, 8, ERR_MORE);
	}
}

int	convert_color(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}
