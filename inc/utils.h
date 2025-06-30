#ifndef UTILS_H
# define UTILS_H

typedef struct s_config t_config;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_img t_img;
typedef struct s_tex t_tex;
typedef struct s_game t_game;

int starts_with(const char *str, const char *prefix);
void	ft_free_arr(void **strs);
void    ft_clean_up(t_game *game);
void    ft_clean_exit(t_game *game, int status);
int     show_err(char *detail, char *str, int code);
void handle_error(char *msg, char **parts, t_game *game, char *line);
void ft_clean_config_arr(t_config *cfg);
void ft_clean_config_tex(t_config *cfg);
void    ft_clean_ray(t_ray *ray);
void    ft_clean_plyr(t_player *plyr);
int	is_in_bounds(int y, int x, t_config *cfg);
#endif