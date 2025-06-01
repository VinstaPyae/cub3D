#ifndef UTILS_H
# define UTILS_H

typedef struct s_config t_config;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_game t_game;

int starts_with(const char *str, const char *prefix);
void	ft_free_strs(char **strs);
void    ft_clean_up(t_game *game);

#endif