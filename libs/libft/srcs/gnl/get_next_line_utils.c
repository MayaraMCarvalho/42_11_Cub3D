/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 21:11:03 by joapedr2          #+#    #+#             */
/*   Updated: 2023/03/23 11:23:25 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	t_char_new_node(char *buf, t_char **cur)
{
	t_char	*new;
	t_char	*temp;

	new = (t_char *)malloc(sizeof(t_char));
	if (!new)
		return (FALSE);
	new->c = buf[0];
	new->next = NULL;
	if (*cur)
	{
		temp = *cur;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*cur = new;
	return (TRUE);
}

void	t_line_free(t_line **l)
{
	t_char	*aux;
	t_char	*temp;

	aux = (*l)->begin;
	while (aux)
	{
		temp = NULL;
		if (aux->next)
			temp = aux->next;
		free(aux);
		aux = temp;
	}
	free(*l);
}
