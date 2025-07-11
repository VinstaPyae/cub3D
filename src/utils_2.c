/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jace <jace@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:54:21 by pzaw              #+#    #+#             */
/*   Updated: 2025/07/11 22:34:48 by jace             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_in_bounds(int y, int x, t_config *cfg)
{
	return (y >= 0 && x >= 0 && y < cfg->map_height && x < cfg->map_width);
}

void	ft_clean_ray(t_ray *ray)
{
	if (ray)
	{
		free(ray);
		ray = NULL;
	}
}

void	ft_clean_config_arr(t_config *cfg)
{
	if (cfg->lines)
	{
		ft_free_arr((void **)cfg->lines);
		cfg->lines = NULL;
	}
	if (cfg->tex_pix)
	{
		ft_free_arr((void **)cfg->tex_pix);
		cfg->tex_pix = NULL;
	}
	if (cfg->map)
	{
		ft_free_arr((void **)cfg->map);
		cfg->map = NULL;
	}
}

void	ft_clean_config_tex(t_config *cfg)
{
	if (cfg->texture_no)
	{
		free(cfg->texture_no);
		cfg->texture_no = NULL;
	}
	if (cfg->texture_so)
	{
		free(cfg->texture_so);
		cfg->texture_so = NULL;
	}
	if (cfg->texture_ea)
	{
		free(cfg->texture_ea);
		cfg->texture_ea = NULL;
	}
	if (cfg->texture_we)
	{
		free(cfg->texture_we);
		cfg->texture_we = NULL;
	}
}

void	check_map_line(t_game *game)
{
	int	i;

	i = game->config->map_start_indx;
	while (game->config->lines[i])
	{
		check_empty_line(game->config->lines[i], game);
		i++;
	}
}
