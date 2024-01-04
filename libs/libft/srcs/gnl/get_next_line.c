/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:35:14 by joapedr2          #+#    #+#             */
/*   Updated: 2023/07/24 19:06:59 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(t_line *l)
{
	char	*line;
	t_char	*aux;
	int		i;

	i = -1;
	if (l->begin == NULL)
		return (NULL);
	line = malloc(sizeof(char) * l->size + 1);
	if (!line)
		return (NULL);
	aux = l->begin;
	while (aux)
	{
		line[++i] = aux->c;
		aux = aux->next;
	}
	line[++i] = '\0';
	return (line);
}

static t_line	*get_buffer(int fd)
{
	t_line	*l;
	char	buffer[1];

	l = (t_line *)malloc(sizeof(t_line));
	l->size = 0;
	l->begin = NULL;
	while (read(fd, buffer, 1) > 0)
	{
		if (!t_char_new_node(buffer, &(l)->begin))
		{
			t_line_free(&l);
			return (NULL);
		}
		l->size++;
		if (buffer[0] == '\n')
			break ;
	}
	return (l);
}

char	*get_next_line(int fd)
{
	t_line	*l;
	char	*line;

	if (fd < 0)
		return (NULL);
	l = get_buffer(fd);
	line = get_line(l);
	t_line_free(&l);
	return (line);
}
