/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jace <jace@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:10:46 by pzaw              #+#    #+#             */
/*   Updated: 2025/07/10 22:31:55 by jace             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_config	t_config;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_game	t_game;

void	parse_texture(char *line, char **destination, t_game *game);
void	parse_color(char *line, int *color_out, t_game *game);
void	parse_map(char **lines, int start, t_game *game);
void	validate_map(t_game *game);
char	**read_file_lines(int fd, t_game *game);
char	*get_next_line(char **pos, t_game *game);
void	copy_line_content(char *line, char *start, size_t len);
size_t	count_lines(char *content);
char	*allocate_line(size_t len, t_game *game);
char	*find_next_newline(char *str);
int		get_map_width(char **lines, int start);
int		get_map_height(char **lines, int start);
char	*allocate_map_line(t_game *game, int width);
void	ft_clean_map_error(t_game *game, char *msg);
void	check_empty_line(char *line, t_game *game);

#endif