/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palyer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:44:43 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 19:45:39 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_plyr_pos(t_game *game)
{
	int	x;
	int	y;

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
			}
			x++;
		}
		y++;
	}
}

static void	set_dir_north_south(t_game *game, char tile)
{
	if (tile == 'N')
	{
		game->plyr->dir_x = 0;
		game->plyr->dir_y = -1;
		game->plyr->plane_x = 0.66;
		game->plyr->plane_y = 0;
	}
	if (tile == 'S')
	{
		game->plyr->dir_x = 0;
		game->plyr->dir_y = 1;
		game->plyr->plane_x = -0.66;
		game->plyr->plane_y = 0;
	}
}

static void	set_dir_east_west(t_game *game, char tile)
{
	if (tile == 'E')
	{
		game->plyr->dir_x = 1;
		game->plyr->dir_y = 0;
		game->plyr->plane_x = 0;
		game->plyr->plane_y = 0.66;
	}
	if (tile == 'W')
	{
		game->plyr->dir_x = -1;
		game->plyr->dir_y = 0;
		game->plyr->plane_x = 0;
		game->plyr->plane_y = -0.66;
	}
}

void	get_plyr_dir(t_game *game)
{
	int		x;
	int		y;
	char	tile;

	x = 0;
	y = 0;
	tile = 0;
	x = (int)game->plyr->pos_x;
	y = (int)game->plyr->pos_y;
	tile = game->config->map[y][x];
	set_dir_north_south(game, tile);
	set_dir_east_west(game, tile);
}
