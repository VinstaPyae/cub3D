#ifndef PARSER_H
# define PARSER_H

typedef struct s_config t_config;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_game t_game;

void	parse_texture(char *line, char **destination, t_game *game);
void	parse_color(char *line, int *color_out, t_game *game);
void	parse_map(char **lines, int start, t_game *game);
void	validate_map(t_game *game);
char	**read_file_lines(int fd);

#endif