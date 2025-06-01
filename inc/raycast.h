#ifndef RAYCAST_H
# define RAYCAST_H

typedef struct s_config t_config;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_game t_game;

int raycast(t_player *player, t_ray *ray, t_game *game);

#endif