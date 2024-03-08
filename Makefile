NAME			= cub3D

CFLAGS			= -g3 -g -Wall -Werror -Wextra
LFLAGS			= -lft -lmlx -lX11 -lXext -lm -MMD -MP
INCLUDES		= -I./includes -I$(LIBFT_INC) -I$(MLX_PATH)
LIBS			= -L./libs/libft -L./libs/minilibx

# -fsanitize=address -lbsd verificar a necessidade dessas flags

#libft
LIBFT_PATH		= ./libs/libft
LIBFT_INC		= $(LIBFT_PATH)/includes
LIBFT			= $(LIBFT_PATH)/libft.a

#minilibx
MLX_PATH		= ./libs/minilibx
MLX_LINUX		= $(MLX_PATH)/libmlx_Linux.a
MLX				= $(MLX_PATH)/libmlx.a

#list path
WINDOW_PATH		= window/
RENDER_PATH		= render/
RAYCAST_PATH	= raycasting/
INIT_PATH		= init/

#source codes
SRC_DIR			=	./srcs/
SRC_LIST		=	cub3d.c data.c draw.c events.c exec2d.c free.c h_v_rays.c maps.c \
					player.c process.c raycast_walls.c raycast.c textures.c \
					utils.c utils2d.c window.c \


SRCS			= $(addprefix $(SRC_DIR),$(SRC_LIST))

#objects
OBJS_DIR		= ./objects/
OBJS			= $(addprefix $(OBJS_DIR),$(SRC_LIST:%.c=%.o))

#colors
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
CYAN			= \033[0;36m
RESET			= \033[0m

#dependencies
DEP = $(OBJ:.o=.d)
-include $(DEP)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	@printf "\n"
	@cc $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBS) -o $(NAME)
	@echo " $(CYAN)$(NAME): $(GREEN)Done!"
	@echo -n "$(RESET)"

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(MLX):
	@make -sC $(MLX_PATH)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(addprefix $(OBJS_DIR)/,$(WINDOW_PATH))
	@mkdir -p $(addprefix $(OBJS_DIR)/,$(RENDER_PATH))
	@mkdir -p $(addprefix $(OBJS_DIR)/,$(RAYCAST_PATH))
	@mkdir -p $(addprefix $(OBJS_DIR)/,$(INIT_PATH))

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@cc $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(YELLOW)Generating $(CYAN)$(NAME) $(YELLOW)objects... %-33.33s\r" $@

clean:
	@make -sC $(LIBFT_PATH) clean
#	@make -sC $(MLX_PATH) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make -sC $(LIBFT_PATH) fclean
	@rm -f $(NAME)

re: fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all -q ./$(NAME)

coffee:
	@make -sC $(LIBFT_PATH) coffee

.PHONY: all clean fclean re coffee val
