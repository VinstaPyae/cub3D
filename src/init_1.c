/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:20:09 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 19:21:55 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_img_reset(t_img *img)
{
	img->img = NULL;
	img->addr = 0;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_config(t_config *config)
{
	config->lines = NULL;
	config->texture_no = NULL;
	config->texture_ea = NULL;
	config->texture_so = NULL;
	config->texture_we = NULL;
	config->tex_pix = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->map = NULL;
	config->map_height = 0;
	config->map_width = 0;
	config->map_start_indx = -1;
}

void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->p_moved = 0;
	player->move_x = 0;
	player->plane_y = 0;
	player->rotate = 0;
}

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->pd_wall_dist = 0;
	ray->wall_x = 0;
	ray->wall_top = 0;
	ray->wall_btm = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->hit = 0;
}
