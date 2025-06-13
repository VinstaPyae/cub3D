#ifndef CUB3D_H
# define CUB3D_H

/* buffer size for simple reader */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define SCN_WIDTH 640
# define SCN_HEIGHT 480
# define TEX_SIZE 64

# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"

# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

/* system headers */
# include <unistd.h>   /* read, write, close */
# include <fcntl.h>    /* open flags */
# include <stdlib.h>   /* malloc, free, exit */
# include <stdio.h>    /* perror */
# include <math.h>
# include "libft.h"    /* your libft functions */
# include "mlx.h"
# include "utils.h"
# include "parser.h"
# include "init.h"
# include "player.h"
# include "raycast.h"

/*
 * Configuration structure: holds all parsed .cub data
 * (we'll fill it out more as you implement parsing)
 */
enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_config
{
    char    **lines;
    char    *texture_no;
    char    *texture_so;
    char    *texture_we;
    char    *texture_ea;
	char	**tex_pix;
    int     floor_color;
    int     ceiling_color;
    char    **map;
    int     map_width;
    int     map_height;
    int     map_start_indx;
}   t_config;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_tex
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_tex;

typedef struct s_player
{
	char	dir;
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
	int		p_moved;
	int		move_x;
	int		move_y;
	int		rotate;
} t_player;

typedef struct s_ray
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double deltadist_x;
	double deltadist_y;
	double sidedist_x;
	double sidedist_y;
	double pd_wall_dist;
	double wall_x;
	int wall_height;
	int wall_top;
	int wall_btm;
	int step_x;
	int step_y;
	int	side;
	int mapX;
	int mapY;
	int hit;
} t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int			**tex_pixels;
	int			**tex_c;
	t_config *config;
	t_player *plyr;
	t_ray	 *ray;
	t_tex *texture;
	t_img img;
}	t_game;

//texture
void	init_texture_pixels(t_game *game);
void	update_texture_pixels(t_game *game, t_tex *tex, t_ray *ray, int x);
#endif
