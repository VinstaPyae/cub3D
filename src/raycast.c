#include "cub3D.h"

int isWall(int x, int y, t_game *game)
{
    if (x < 0 || x >= game->config->map_width || y < 0 || y >= game->config->map_height)
        return 1;
    return game->config->map[x][y] != 0;
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	set_frame_image_pixel(t_game *game, t_img *image, int x, int y)
{
	if (game->tex_pixels[y][x] > 0)
		set_image_pixel(image, x, y, game->tex_pixels[y][x]);
	else if (y < SCN_HEIGHT / 2)
		set_image_pixel(image, x, y, game->config->ceiling_color);
	else if (y < SCN_HEIGHT -1)
		set_image_pixel(image, x, y, game->config->floor_color);
}

void	render_frame(t_game *game)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(game, &image, SCN_WIDTH, SCN_HEIGHT);
	y = 0;
	while (y < SCN_HEIGHT)
	{
		x = 0;
		while (x < SCN_WIDTH)
		{
			set_frame_image_pixel(game, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}

int raycast(t_game *game)
{
    int x;
    t_ray *ray;
    t_player *player;

    x = 0;
    init_texture_pixels(game);
    init_ray(game->ray);
    ray = game->ray;
    player = game->plyr;
    while (x < SCN_WIDTH)
    {
        init_ray(ray);
        ray->camera_x = 2 * x / (double)SCN_WIDTH - 1;
        ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
        ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
        ray->mapX = (int)player->pos_x;
        ray->mapY = (int)player->pos_y;
        // delta dist calculate
        // if (ray->ray_dir_x == 0)
        //     ray->deltadist_x = 1e30;
        // else
            ray->deltadist_x = fabs(1 / ray->ray_dir_x);

        // if (ray->ray_dir_y == 0)
        //     ray->deltadist_y = 1e30;
        // else
            ray->deltadist_y = fabs(1 / ray->ray_dir_y);
        printf("ray camera_x: %f\n", ray->camera_x);
        printf("plane x: %f, plane y: %f\n", player->plane_x, player->plane_y);
        printf("ray dir: %f %f\n", ray->ray_dir_x, ray->ray_dir_y);
        printf("ray mapx: %d mapy: %d\n", ray->mapX, ray->mapY);
        printf("ray deltas: %f %f\n", ray->deltadist_x, ray->deltadist_y);
        printf("player pos: %f %f\n", player->pos_x, player->pos_y);
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
        printf("step_x: %d, step_y: %d\n", ray->step_x, ray->step_y);
        printf("sidedist_x: %f, sidedist_y: %f\n", ray->sidedist_x, ray->sidedist_y);
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

            // if (isWall(ray->mapX, ray->mapY, game))
            //     ray->hit = 1;
            if (ray->mapY < 0.25
			|| ray->mapX < 0.25
			|| ray->mapY > game->config->map_height - 0.25
			|| ray->mapX > game->config->map_width - 1.25)
			    break ;
            else if (game->config->map[ray->mapY][ray->mapX] > '0')
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
        printf("wall btm: %d\n", ray->wall_btm);
        printf("wall top: %d\n", ray->wall_top);
        printf("wall height: %d\n", ray->wall_height);

        // t_tex *tex = select_texture(game, game->ray);
        // double wall_x;

        if (ray->side == 0)
            ray->wall_x = player->pos_y + ray->pd_wall_dist * ray->ray_dir_y;
        else
            ray->wall_x = player->pos_x + ray->pd_wall_dist * ray->ray_dir_x;

        ray->wall_x -= floor(ray->wall_x);  // get only the fractional part (0.0–1.0)
        // printf("hehehhahaha\n");
        update_texture_pixels(game, game->texture, ray, x);
        printf("-----------------------------------------\n");
    x++;
    }
    return (0);
}
