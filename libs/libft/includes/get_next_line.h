/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 00:11:14 by joapedr2          #+#    #+#             */
/*   Updated: 2023/03/23 11:24:11 by joapedr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef FD_MAX
#  define FD_MAX 1024
# endif //FD_MAX

typedef struct s_character
{
	char				c;
	struct s_character	*next;
}	t_char;

typedef struct s_line
{
	t_char	*begin;
	int		size;	
}	t_line;

//get_next_line.c
char	*get_next_line(int fd);

//get_next_line_utils.c
int		t_char_new_node(char *buf, t_char **cur);
void	t_line_free(t_line **l);

#endif //GET_NEXT_LINE_H