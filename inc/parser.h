#ifndef PARSER_H
# define PARSER_H

void	parse_texture(char *line, char **destination);
void	parse_color(char *line, int *color_out);
char **read_file_lines(int fd);

#endif