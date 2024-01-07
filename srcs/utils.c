/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:17:12 by macarval          #+#    #+#             */
/*   Updated: 2024/01/05 09:22:22 by macarval         ###   ########.fr       */
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
