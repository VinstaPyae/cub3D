#include "cub3D.h"

void	raycast_init_raydata(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)SCN_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->mapX = (int)player->pos_x;
	ray->mapY = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->ray_dir_x);
	ray->deltadist_y = fabs(1 / ray->ray_dir_y);
}

void	raycast_calc_step(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->mapX) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->mapX + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->mapY) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->mapY + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

void	raycast_dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->mapX += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->mapY += ray->step_y;
			ray->side = 1;
		}
		if (ray->mapX < 0 || ray->mapX >= game->config->map_width
			|| ray->mapY < 0 || ray->mapY >= game->config->map_height)
		{
			ray->hit = 1;
			break ;
		}
		else if (game->config->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void	raycast_calc_wall(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->pd_wall_dist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->pd_wall_dist = ray->sidedist_y - ray->deltadist_y;
	ray->wall_height = (int)(SCN_HEIGHT / ray->pd_wall_dist);
	ray->wall_top = -(ray->wall_height) / 2 + SCN_HEIGHT / 2;
	if (ray->wall_top < 0)
		ray->wall_top = 0;
	ray->wall_btm = ray->wall_height / 2 + SCN_HEIGHT / 2;
	if (ray->wall_btm >= SCN_HEIGHT)
		ray->wall_btm = SCN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->pd_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->pd_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int	raycast(t_game *game)
{
	t_ray		*ray;
	t_player	*player;
	int			x;

	x = 0;
	init_texture_pixels(game);
	init_ray(game->ray);
	ray = game->ray;
	player = game->plyr;
	while (x < SCN_WIDTH)
	{
		init_ray(ray);
		raycast_init_raydata(ray, player, x);
		raycast_calc_step(ray, player);
		raycast_dda(ray, game);
		raycast_calc_wall(ray, player);
		update_texture_pixels(game, game->texture, ray, x);
		x++;
	}
	return (0);
}
