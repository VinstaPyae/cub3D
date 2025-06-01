#include "cub3D.h"

void	init_config(t_config *config)
{
	config->lines = NULL;
	config->texture_no = NULL;
	config->texture_ea = NULL;
	config->texture_so = NULL;
	config->texture_we = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->map = NULL;
	config->map_height = 0;
	config->map_width = 0;
	config->map_start_indx = -1;
}

void init_player(t_player *player)
{
    player->pos_x = 0;
    player->pos_y = 0;
    player->dir_x = 0;
    player->dir_y = 0;
    player->plane_x = 0;
    player->plane_y = 0;
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
    ray->step_x = 0;
    ray->step_y = 0;
}

void	init_game(t_game *game)
{
	game->config = malloc(sizeof(t_config));
	game->plyr = malloc(sizeof(t_player));
	game->ray = malloc(sizeof(t_ray));
	init_config(game->config);
	init_player(game->plyr);
	init_ray(game->ray);
}
