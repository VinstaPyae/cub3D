/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:09:54 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 21:10:25 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_config	t_config;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_game	t_game;

int		is_player_char(char c);
void	get_plyr_pos(t_game *game);
void	get_plyr_dir(t_game *game);

#endif