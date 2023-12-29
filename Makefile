# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 00:40:38 by macarval          #+#    #+#              #
#    Updated: 2023/12/29 15:15:33 by macarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D

FILE			= cub3d.c events.c window.c
FILE_BONUS		= cub3d_bonus.c

FILE_PATH		= src
FILE_PATH_BONUS	= src_bonus
OBJS_PATH		= obj
HEADERS			= cub3d.h
CFLAGS			= -Wall -Wextra -Werror -I.
LFLAGS			= -lmlx -Ilmlx -lXext -lX11 -O3
CC				= cc
RM				= rm -rf
LIBFT			= libft/libft.a
LIB_DIR			= libft
LIBS			= -lreadline

OBJS			= $(addprefix $(OBJS_PATH)/, $(FILE:.c=.o))
OBJS_BONUS		= $(addprefix $(OBJS_PATH)/, $(FILE_BONUS:.c=.o))

all:			$(NAME)

bonus:			$(OBJS_PATH) $(OBJS_BONUS)
				@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LFLAGS) -o $(NAME)
				@echo "Cub3D Bonus created!!"

$(NAME):		$(OBJS_PATH) $(OBJS) $(LIBFT)
				@printf "Compiling $(NAME)\n"
				@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME) $(LIBFT) $(LIBS)
				@echo "Cub3D created!!"

$(OBJS_PATH):
				@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: $(FILE_PATH)/%.c $(HEADERS)
				@$(CC) -g $(CFLAGS) $(LFLAGS) -c $< -o $@

$(OBJS_PATH)/%.o: $(FILE_PATH_BONUS)/%.c $(HEADERS)
				@$(CC) -g $(CFLAGS) $(LFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIB_DIR)

clean:
				@$(RM) $(OBJS) $(OBJS_BONUS)
				@$(MAKE) -C $(LIB_DIR) clean
				@echo "clean Done!"

fclean:			clean
				@$(RM) $(NAME) $(OBJS_PATH)
				@echo "fclean Done!"

re:				fclean all

.PHONY: 		all bonus clean fclean re
