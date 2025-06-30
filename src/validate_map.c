/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:54:30 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 21:03:46 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || is_player_char(c) || c == ' ');
}

static void	check_enclosure(t_game *game, int y, int x)
{
	int	dy[4];
	int	dx[4];
	int	i;
	int	ny;
	int	nx;

	init_direction_arrays(dy, dx);
	i = 0;
	while (i < 4)
	{
		ny = y + dy[i];
		nx = x + dx[i];
		if (!is_in_bounds(ny, nx, game->config)
			|| game->config->map[ny][nx] == ' ')
		{
			ft_putstr_fd("Error\nMap is not enclosed by walls\n", 2);
			ft_clean_exit(game, 1);
		}
		i++;
	}
}

void	ft_validater(char c, int x, int y, t_game *game)
{
	if (!is_valid_char(c))
		ft_clean_exit(game, show_err("Map validation",
				"Invalid character in map", 1));
	if (c == '0' || is_player_char(c))
		check_enclosure(game, y, x);
}

void	validate_map(t_game *game)
{
	char	c;
	int		y;
	int		x;
	int		player_count;

	y = 0;
	player_count = 0;
	while (y < game->config->map_height)
	{
		x = 0;
		while (x < game->config->map_width)
		{
			c = game->config->map[y][x];
			ft_validater(c, x, y, game);
			if (is_player_char(c))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		ft_clean_exit(game, show_err("Map validation",
				"Exactly one player character required", 1));
}
