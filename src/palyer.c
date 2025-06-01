#include "cub3D.h"

void	get_plyr_pos(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	while (game->config->map[x])
	{
		y = 0;
		while (game->config->map[x][y])
		{
			if (is_player_char(game->config->map[x][y]))
			{
				game->plyr->pos_x = (double)x;
				game->plyr->pos_y = (double)y;
				// printf("found\n");
			}
			y++;
		}
		x++;
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
	if (game->config->map[x][y] == 'N')
	{
		game->plyr->dir_x = 0;
		game->plyr->dir_y = -1;
		game->plyr->plane_x = 0.66;
		game->plyr->plane_y = 0;
	}
	if (game->config->map[x][y] == 'S')
	{
		game->plyr->dir_x = 0;
		game->plyr->dir_y = 1;
		game->plyr->plane_x = -0.66;
		game->plyr->plane_y = 0;
	}
	if (game->config->map[x][y] == 'E')
	{
		game->plyr->dir_x = 1;
		game->plyr->dir_y = 0;
		game->plyr->plane_x = 0;
		game->plyr->plane_y = 0.66;
	}
	if (game->config->map[x][y] == 'W')
	{
		game->plyr->dir_x = -1;
		game->plyr->dir_y = 0;
		game->plyr->plane_x = 0;
		game->plyr->plane_y = -0.66;
	}
	// printf("dirX: %f\n", game->plyr->dir_x);
	// printf("dirY: %f\n", game->plyr->dir_y);
}
