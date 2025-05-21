# -------------------------
#       PROJECT SETUP
# -------------------------
# Compiler and flags
CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -std=c99 -Iinc -Ilibft

# Directories
INCDIR   := inc
SRCDIR   := src
LIBFTDIR := libft

# Files
MAIN_SRC    := cub3D.c
SRCS        := $(MAIN_SRC) $(wildcard $(SRCDIR)/*.c)
OBJS        := $(SRCS:.c=.o)
LIBFT_LIB   := $(LIBFTDIR)/libft.a

# Final executable
TARGET    := cub3D

# -------------------------
#         RULES
# -------------------------

.PHONY: all clean fclean re libft

# Default: build libft and then the main program
all: $(TARGET)

# Link everything
$(TARGET): libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(TARGET)

# Build libft (assumes libft/Makefile knows how to build libft.a)
libft:
	$(MAKE) -C $(LIBFTDIR)

# Compile each .c into .o
# This pattern works for both cub3D.c and any src/*.c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	@rm -f $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

# Remove everything including the executable and libft static lib
fclean: clean
	@rm -f $(TARGET)
	$(MAKE) -C $(LIBFTDIR) fclean

# Rebuild from scratch
re: fclean all
