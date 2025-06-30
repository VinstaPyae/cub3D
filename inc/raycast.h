/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:08:18 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 21:09:42 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_config	t_config;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_game	t_game;

int		raycast(t_game *game);
void	render_frame(t_game *game);
int		is_wall(int x, int y, t_game *game);
#endif