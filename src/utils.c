/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:54:28 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 20:54:29 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_clean_config(t_config *cfg)
{
	ft_clean_config_arr(cfg);
	ft_clean_config_tex(cfg);
	if (cfg)
	{
		free(cfg);
		cfg = NULL;
	}
}

static void	free_tex(t_tex *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
	if (textures)
	{
		free(textures);
		textures = NULL;
	}
}

void	ft_clean_up(t_game *game)
{
	if (game->config)
		ft_clean_config(game->config);
	if (game->texture)
		free_tex(game->texture);
	if (game->plyr)
		ft_clean_plyr(game->plyr);
	if (game->ray)
		ft_clean_ray(game->ray);
	if (game->tex_c)
		ft_free_arr((void **)game->tex_c);
	if (game->tex_pixels)
		ft_free_arr((void **)game->tex_pixels);
}

void	ft_clean_exit(t_game *game, int status)
{
	if (!game)
		exit(status);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
	ft_clean_up(game);
	exit(status);
}

int	show_err(char *detail, char *str, int code)
{
	ft_putstr_fd("Error\n", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}
