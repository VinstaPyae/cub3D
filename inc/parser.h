#ifndef PARSER_H
# define PARSER_H

typedef struct s_config
{
    char    *texture_no;
    char    *texture_so;
    char    *texture_we;
    char    *texture_ea;
    int     floor_color;
    int     ceiling_color;
    char    **map;
    int     map_width;
    int     map_height;
    int     map_start_indx;
}   t_config;

void	parse_texture(char *line, char **destination);
void	parse_color(char *line, int *color_out);
void	parse_map(char **lines, int start, t_config *cfg);
void	validate_map(t_config *cfg);
char	**read_file_lines(int fd);

#endif