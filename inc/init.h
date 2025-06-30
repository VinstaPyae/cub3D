#ifndef INIT_H
# define INIT_H

typedef struct s_config t_config;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_game t_game;
typedef struct s_tex t_tex;
typedef struct s_img t_img;

void	init_config(t_config *config);
void	init_player(t_player *player);
void	init_ray(t_ray *ray);
void	init_game(t_game *game);
void init_direction_arrays(int dy[4], int dx[4]);

void    init_mlx(t_game *game);
void	init_texture_img(t_game *game, t_img *image, char *path);
void	init_textures(t_game *game);
void	init_img_reset(t_img *img);
void	init_texture_img(t_game *game, t_img *image, char *path);
void	init_img(t_game *game, t_img *image, int width, int height);

#endif