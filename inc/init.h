#ifndef INIT_H
# define INIT_H

typedef struct s_config t_config;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_game t_game;

void	init_config(t_config *config);
void	init_player(t_player *player);
void	init_ray(t_ray *ray);
void	init_game(t_game *game);

#endif