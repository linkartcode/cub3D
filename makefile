NAME		= cub3D
NAME_B		= cub3D_bonus
LIBFT 		= libft.a
MINILIBX	= libmlx.a
# PATHS
LIBFT_PATH		= ./libft
MINILIBX_PATH 	= ./minilibx
SRC_PATH		= ./src
INCL_PATH		= ./incl
# SRCS
SRCS		= 	$(SRC_PATH)/main.c		$(SRC_PATH)/game.c \
				$(SRC_PATH)/game_move.c	$(SRC_PATH)/draw.c	\
				$(SRC_PATH)/decor.c	 	$(SRC_PATH)/decor_fill.c \
				$(SRC_PATH)/buffer.c 	$(SRC_PATH)/game_draw.c \
				$(SRC_PATH)/map.c	 		$(SRC_PATH)/map_check.c \
				$(SRC_PATH)/camera.c 	$(SRC_PATH)/game_dda.c
				
SRCS_B		=	
# HEADERS
HEADER		=	$(INCL_PATH)/cub3D.h
HEADER_B	=	$(INCL_PATH)/cub3D_bonus.h
#
OBJ			=	$(patsubst %.c, %.o, $(SRCS))
OBJ_B		=	$(patsubst %.c, %.o, $(SRCS_B))
# FLAGS
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM 			=	rm -f
MLX_LNK		= 	-lmlx -framework OpenGL -framework Appkit
##############################################
.PHONY	:	all clean fclean re bonus force
#
all	:  $(NAME)
#
$(NAME)	: $(LIBFT_PATH)/$(LIBFT) $(MINILIBX_PATH)/$(MINILIBX) $(OBJ)
	$(CC) -L$(LIBFT_PATH) -lft -L$(MINILIBX_PATH) $(MLX_LNK) -o $@ $(OBJ)
#
$(LIBFT_PATH)/$(LIBFT) : force
	$(MAKE) -C $(LIBFT_PATH)/
#
$(MINILIBX_PATH)/$(MINILIBX) : force
	$(MAKE) -C $(MINILIBX_PATH)/
#
force : ;
#
$(filter %.o,$(OBJ)): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCL_PATH) -I $(LIBFT_PATH)
#
bonus : $(NAME_B)
#
$(NAME_B) : $(LIBS_PATH)/$(LIBFT) $(OBJ_B)
	$(CC) -L$(LIBS_PATH) -lft $(LMX) -o $@ $(OBJ_B)
#
$(filter %.o,$(OBJ_B)): %.o: %.c $(HEADER_B)
	$(CC) $(CFLAGS) -c $< -o $@
#
clean :
	$(MAKE) -C $(LIBFT_PATH)/ clean
	$(MAKE) -C $(MINILIBX_PATH)/ clean
	$(RM) $(OBJ) $(OBJ_B)
#
fclean	:	clean
	$(MAKE) -C $(LIBFT_PATH)/ fclean
	$(RM) $(NAME) $(NAME_B)
#
re	:	fclean all
#
