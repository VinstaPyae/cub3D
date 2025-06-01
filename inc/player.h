#ifndef PLAYER_H
# define PLAYER_H

int		is_player_char(char c);
typedef struct s_config t_config;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_game t_game;

void	get_plyr_pos(t_game *game);
void	get_plyr_dir(t_game *game);

#endif