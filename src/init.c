#include "cub3D.h"

void	init_img_reset(t_img *img)
{
	img->img = NULL;
	img->addr = 0;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_config(t_config *config)
{
	config->lines = NULL;
	config->texture_no = NULL;
	config->texture_ea = NULL;
	config->texture_so = NULL;
	config->texture_we = NULL;
	config->tex_pix = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->map = NULL;
	config->map_height = 0;
	config->map_width = 0;
	config->map_start_indx = -1;
}

void init_player(t_player *player)
{
	player->dir = '\0';
    player->pos_x = 0;
    player->pos_y = 0;
    player->dir_x = 0;
    player->dir_y = 0;
    player->plane_x = 0;
    player->plane_y = 0;
	player->p_moved = 0;
	player->move_x = 0;
	player->plane_y = 0;
	player->rotate = 0;
}

void init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->pd_wall_dist = 0;
	ray->wall_x = 0;
	ray->wall_top = 0;
	ray->wall_btm = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->hit = 0;
}

void	init_tex(t_tex *tex)
{
	tex->north = NULL;
	tex->south = NULL;
	tex->west = NULL;
	tex->east = NULL;
	tex->floor = 0;
	tex->ceiling = 0;
	tex->hex_floor = 0x0;
	tex->hex_ceiling = 0x0;
	tex->size = TEX_SIZE;
	tex->step = 0.0;
	tex->pos = 0.0;
	tex->x = 0;
	tex->y = 0;
}

static void init_game_keys(t_game *game)
{
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
}

static void *safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error\n", 2);
		perror("malloc failed for component");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

static void init_game_components(t_game *game)
{
	game->config = safe_malloc(sizeof(t_config));
	init_config(game->config);
	
	game->plyr = safe_malloc(sizeof(t_player));
	init_player(game->plyr);
	
	game->texture = safe_malloc(sizeof(t_tex));
	init_tex(game->texture);
	
	game->ray = safe_malloc(sizeof(t_ray));
	init_ray(game->ray);
}

void init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	
	init_game_components(game);
	init_game_keys(game);
	init_img_reset(&game->img);
	
	game->tex_pixels = NULL;
	game->tex_c = NULL;
}
