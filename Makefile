# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jace <jace@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/12 12:07:19 by jace              #+#    #+#              #
#    Updated: 2025/07/12 12:08:08 by jace             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -g
SRCDIR   := src
INCDIR   := inc
OBJDIR   := obj
LIBFTDIR := libft
MLXDIR   := minilibx-linux
LIBFT_LIB := $(LIBFTDIR)/libft.a
MLX_LIB   := $(MLXDIR)/libmlx.a
LDLIBS := $(LIBFT_LIB) $(MLX_LIB) -lX11 -lXext -lm

MAIN_SRC := cub3D.c
SRC_FILES := init.c \
	init_1.c \
	init_mlx.c \
	init_textures.c \
	key_handle.c \
	key_handle_1.c \
	palyer.c \
	parser.c \
	parser_1.c \
	parser_color.c \
	parser_map.c \
	parser_map_1.c \
	parser_texture.c \
	raycast.c \
	raycast_1.c \
	texture.c \
	utils.c \
	utils_1.c \
	utils_2.c \
	utils_main.c \
	validate_map.c

SRCS := $(MAIN_SRC) $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRCS)))

TARGET   := cub3D

INCLUDES := -I$(INCDIR) -I$(LIBFTDIR) -I$(MLXDIR)

.PHONY: all clean fclean re libft mlx

all: $(TARGET)

$(TARGET): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/cub3D.o: cub3D.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFTDIR)

libft: $(LIBFT_LIB)

$(MLX_LIB):
	$(MAKE) -C $(MLXDIR)

mlx: $(MLX_LIB)

clean:
	@rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	@rm -f $(TARGET)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
