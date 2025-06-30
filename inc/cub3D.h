#ifndef CUB3D_H
# define CUB3D_H

/* buffer size for simple reader */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define SCN_WIDTH 1080
# define SCN_HEIGHT 720
# define TEX_SIZE 64

# define MOVE_SPEED 0.015
# define ROT_SPEED 0.025

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define Wall_Bounce 0.1


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
# include <stdbool.h>
# include <X11/keysym.h>

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
	int key_w;
	int key_a;
	int key_s;
	int key_d;
	int key_left;
	int key_right;
}	t_game;

//texture
void	init_texture_pixels(t_game *game);
void	update_texture_pixels(t_game *game, t_tex *tex, t_ray *ray, int x);

//key
void setup_hooks(t_game *game);
int key_press(int key, t_game *game);
int close_window(t_game *game);
int key_release(int key, t_game *game);
void handle_movement(t_game *game);
void rotate_l_or_r(t_player *player, double angle);

int render_loop(t_game *game);
#endif
