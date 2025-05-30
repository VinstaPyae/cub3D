# -------------------------
#       PROJECT SETUP
# -------------------------

# Compiler and flags
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror

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
SRCS     := $(MAIN_SRC) $(wildcard $(SRCDIR)/*.c)
OBJS     := $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRCS)))

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
