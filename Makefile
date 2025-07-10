# -------------------------
#       PROJECT SETUP
# -------------------------

# Compiler and flags
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -g

# Directories
SRCDIR   := src
INCDIR   := inc
OBJDIR   := obj
LIBFTDIR := libft
MLXDIR   := minilibx-linux

# Libraries
LIBFT_LIB := $(LIBFTDIR)/libft.a
MLX_LIB   := $(MLXDIR)/libmlx.a
LDLIBS    := $(LIBFT_LIB) $(MLX_LIB) -lX11 -lXext -lm

# Source files
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

# Target
TARGET   := cub3D

# Includes
INCLUDES := -I$(INCDIR) -I$(LIBFTDIR) -I$(MLXDIR)

# -------------------------
#         RULES
# -------------------------

.PHONY: all clean fclean re libft mlx

# Default rule
all: $(TARGET)

# Target build rule
$(TARGET): libft mlx $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/cub3D.o: cub3D.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create obj dir if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build libft
libft:
	$(MAKE) -C $(LIBFTDIR)

# Build MLX
mlx:
	$(MAKE) -C $(MLXDIR)

# Clean object files
clean:
	@rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

# Full cleanup
fclean: clean
	@rm -f $(TARGET)
	$(MAKE) -C $(LIBFTDIR) fclean

# Rebuild
re: fclean all
