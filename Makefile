# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/16 11:37:36 by mlecuyer          #+#    #+#              #
#    Updated: 2021/04/20 18:05:08 by mlecuyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_DIR	=	./minilibx-linux
MLX 	=	-L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext

NAME	=	cub3D

CC		=	clang -Wall -Wextra -Werror -g3

INC 	= -I./includes

SRCS	=	cub3d.c \
			parser/p_utils.c \
			utils/struct_init.c \
			parser/p_checkmap.c \
			parser/p_check_param.c \
			parser/p_get_resolution.c \
			parser/p_error.c \
			parser/p_get_path.c \
			parser/p_get_floor.c \
			parser/p_get_ceiling.c \
			parser/p_get_map.c \
			parser/p_get_map_inside.c \
			parser/p_utils_bis.c \
			build_game.c \
			raycast/keys_action.c \
			raycast/raycast.c \
			raycast/player_move.c \
			raycast/raycast_utils.c \
			raycast/draw_texture.c \
			raycast/sprite_utils.c \
			raycast/sprite.c \
			utils/save_bmp.c \
			utils/bonus_utils.c \
			raycast/print_mlx.c \


			

FIL = 		$(addprefix srcs/, $(SRCS))

OBJ = 		$(FIL:.c=.o)

BIN = 		$(addsuffix .o, $(SRCS))

.c.o:
			@${CC} ${INC} -c $< -o ${<:.c=.o}

all:		$(NAME)

${NAME}:	$(OBJ)
				make -s -C ./libft
				make -s -C $(MLX_DIR)
				$(CC) $(INC) $(OBJ) -Llibft -lft $(MLX) -o $(NAME)


clean:
			make -s clean -C ./libft
			make -s clean -C $(MLX_DIR)
			rm -rf $(OBJ)
			
			
fclean:		clean
				make -s fclean -C ./libft
				rm -f $(NAME)
			
				

re:			fclean all

.PHONY:		all clean fclean re