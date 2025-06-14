#include "cub3D.h"

void	get_plyr_pos(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->config->map[y])
	{
		x = 0;
		while (game->config->map[y][x])
		{
			if (is_player_char(game->config->map[y][x]))
			{
				game->plyr->pos_x = (double)x + 0.5;
				game->plyr->pos_y = (double)y + 0.5;
				// printf("found\n");
			}
			x++;
		}
		y++;
	}
	// printf("x: %f\n", game->plyr->pos_x);
	// printf("y: %f\n", game->plyr->pos_y);
}

void	get_plyr_dir(t_game *game)
{
	int	x;
	int	y;

	x = (int)game->plyr->pos_x;
	y = (int)game->plyr->pos_y;
	if (game->config->map[y][x] == 'N')
	{
		game->plyr->dir_x = 0;
		game->plyr->dir_y = -1;
		game->plyr->plane_x = 0.66;
		game->plyr->plane_y = 0;
	}
	if (game->config->map[y][x] == 'S')
	{
		game->plyr->dir_x = 0;
		game->plyr->dir_y = 1;
		game->plyr->plane_x = -0.66;
		game->plyr->plane_y = 0;
	}
	if (game->config->map[y][x] == 'E')
	{
		game->plyr->dir_x = 1;
		game->plyr->dir_y = 0;
		game->plyr->plane_x = 0;
		game->plyr->plane_y = 0.66;
	}
	if (game->config->map[y][x] == 'W')
	{
		game->plyr->dir_x = -1;
		game->plyr->dir_y = 0;
		game->plyr->plane_x = 0;
		game->plyr->plane_y = -0.66;
	}
	// printf("dirX: %f\n", game->plyr->dir_x);
	// printf("dirY: %f\n", game->plyr->dir_y);
}
