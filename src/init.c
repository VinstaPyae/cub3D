/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jace <jace@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:25:33 by pzaw              #+#    #+#             */
/*   Updated: 2025/07/10 22:18:00 by jace             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static void	init_game_keys(t_game *game)
{
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
}

static void	*safe_malloc(size_t size, t_game *game)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error\n", 2);
		perror("malloc failed for component");
		ft_clean_exit(game, 1);
	}
	return (ptr);
}

static void	init_game_components(t_game *game)
{
	game->config = safe_malloc(sizeof(t_config), game);
	init_config(game->config);
	game->plyr = safe_malloc(sizeof(t_player), game);
	init_player(game->plyr);
	game->texture = safe_malloc(sizeof(t_tex), game);
	init_tex(game->texture);
	game->ray = safe_malloc(sizeof(t_ray), game);
	init_ray(game->ray);
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	init_game_components(game);
	init_game_keys(game);
	init_img_reset(&game->img);
	game->tex_pixels = NULL;
	game->tex_c = NULL;
}
