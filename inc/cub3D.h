#ifndef CUB3D_H
# define CUB3D_H

/* buffer size for simple reader */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define SCN_WIDTH 640
# define SCN_HEIGHT 480
# define texWidth 64
# define texHeight 64

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


typedef struct s_config
{
    char    **lines;
    char    *texture_no;
    char    *texture_so;
    char    *texture_we;
    char    *texture_ea;
    int     floor_color;
    int     ceiling_color;
    char    **map;
    int     map_width;
    int     map_height;
    int     map_start_indx;
}   t_config;

typedef struct s_texture {
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_player
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
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
	t_config *config;
	t_player *plyr;
	t_ray	 *ray;
	t_texture texture[4];
}	t_game;

void	start_game(t_game *game);
void	load_texture(t_game *game, t_texture *tex, char *path);

#endif /* CUB3D_H */
