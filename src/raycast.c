#include "cub3D.h"

int isWall(int x, int y, t_game *game)
{
    if (x < 0 || x >= game->config->map_width || y < 0 || y >= game->config->map_height)
        return 1;
    return game->config->map[x][y] != 0;
}

int raycast(t_player *player, t_ray *ray, t_game *game)
{
    int x;

    x = 0;
    init_texture_pixels(game);
    init_ray(game->ray);
    while (x < SCN_WIDTH)
    {
        ray->camera_x = 2 * x / (double)SCN_WIDTH - 1;
        ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
        ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
        ray->mapX = (int)player->pos_x;
        ray->mapY = (int)player->pos_y;

        // delta dist calculate
        if (ray->ray_dir_x == 0)
            ray->deltadist_x = 1e30;
        else
            ray->deltadist_x = fabs(1 / ray->ray_dir_x);

        if (ray->ray_dir_y == 0)
            ray->deltadist_y = 1e30;
        else
            ray->deltadist_y = fabs(1 / ray->ray_dir_y);

        // calculate step and initial sideDist
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

            if (isWall(ray->mapX, ray->mapY, game))
                ray->hit = 1;
        }

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
        
        // t_tex *tex = select_texture(game, game->ray);
        // double wall_x;

        if (ray->side == 0)
            ray->wall_x = player->pos_y + ray->pd_wall_dist * ray->ray_dir_y;
        else
            ray->wall_x = player->pos_x + ray->pd_wall_dist * ray->ray_dir_x;

        ray->wall_x -= floor(ray->wall_x);  // get only the fractional part (0.0–1.0)
        update_texture_pixels(game, game->texture, ray, x);
        // int tex_x = (int)(wall_x * (double)tex->width);

        // if ((game->ray->side == 0 && game->ray->ray_dir_x > 0) ||
        //     (game->ray->side == 1 && game->ray->ray_dir_y < 0))
        //     tex_x = tex->width - tex_x - 1;

        // double step = 1.0 * tex->height / game->ray->wall_height;
        // double tex_pos = (game->ray->wall_top - SCN_HEIGHT / 2 + game->ray->wall_height / 2) * step;

        // for (int y = game->ray->wall_top; y < game->ray->wall_btm; y++)
        // {
        //     int tex_y = (int)tex_pos & (tex->height - 1); // wrap/clamp
        //     tex_pos += step;

        //     int color = *(int *)(tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8)));
        //     draw_pixel_to_buffer(game, x, y, color);
        // }
    x++;
    }
    return (0);
}
