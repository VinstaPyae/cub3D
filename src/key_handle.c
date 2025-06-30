/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:29:23 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 20:53:31 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->plyr->pos_x + game->plyr->dir_x * MOVE_SPEED;
	new_y = game->plyr->pos_y + game->plyr->dir_y * MOVE_SPEED;
	if (!is_wall(new_x + game->plyr->dir_x * Wall_Bounce,
			game->plyr->pos_y, game))
		game->plyr->pos_x = new_x;
	if (!is_wall(game->plyr->pos_x,
			new_y + game->plyr->dir_y * Wall_Bounce, game))
		game->plyr->pos_y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->plyr->pos_x - game->plyr->dir_x * MOVE_SPEED;
	new_y = game->plyr->pos_y - game->plyr->dir_y * MOVE_SPEED;
	if (!is_wall(new_x - game->plyr->dir_x * Wall_Bounce,
			game->plyr->pos_y, game))
		game->plyr->pos_x = new_x;
	if (!is_wall(game->plyr->pos_x,
			new_y - game->plyr->dir_y * Wall_Bounce, game))
		game->plyr->pos_y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->plyr->pos_x + game->plyr->dir_y * MOVE_SPEED;
	new_y = game->plyr->pos_y - game->plyr->dir_x * MOVE_SPEED;
	if (!is_wall(new_x + game->plyr->dir_y * Wall_Bounce,
			game->plyr->pos_y, game))
		game->plyr->pos_x = new_x;
	if (!is_wall(game->plyr->pos_x,
			new_y - game->plyr->dir_x * Wall_Bounce, game))
		game->plyr->pos_y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->plyr->pos_x - game->plyr->dir_y * MOVE_SPEED;
	new_y = game->plyr->pos_y + game->plyr->dir_x * MOVE_SPEED;
	if (!is_wall(new_x - game->plyr->dir_y * Wall_Bounce,
			game->plyr->pos_y, game))
		game->plyr->pos_x = new_x;
	if (!is_wall(game->plyr->pos_x,
			new_y + game->plyr->dir_x * Wall_Bounce, game))
		game->plyr->pos_y = new_y;
}

void	handle_movement(t_game *game)
{
	if (game->key_w)
		move_forward(game);
	if (game->key_s)
		move_backward(game);
	if (game->key_a)
		move_left(game);
	if (game->key_d)
		move_right(game);
	if (game->key_left)
		rotate_l_or_r(game->plyr, -ROT_SPEED);
	if (game->key_right)
		rotate_l_or_r(game->plyr, ROT_SPEED);
}
