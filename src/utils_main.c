/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:54:25 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 20:54:26 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot)
		return (0);
	return (ft_strncmp(dot, ".cub", 5) == 0);
}

int	validate_args(int ac, char **av)
{
	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <file.cub>\n", 2), 0);
	if (!check_file_extension(av[1]))
		return (ft_putstr_fd("Error\nFile must end with .cub\n", 2), 0);
	return (1);
}

int	read_config_file(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nFailed to open file"), 0);
	game->config->lines = read_file_lines(fd);
	close(fd);
	return (1);
}

int	parse_config_line(char *line, t_game *game, int line_index)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed || trimmed[0] == '\0')
		return (free(trimmed), 1);
	if (starts_with(trimmed, "NO"))
		parse_texture(trimmed, &game->config->texture_no, game);
	else if (starts_with(trimmed, "SO"))
		parse_texture(trimmed, &game->config->texture_so, game);
	else if (starts_with(trimmed, "WE"))
		parse_texture(trimmed, &game->config->texture_we, game);
	else if (starts_with(trimmed, "EA"))
		parse_texture(trimmed, &game->config->texture_ea, game);
	else if (starts_with(trimmed, "F"))
		parse_color(trimmed, &game->config->floor_color, game);
	else if (starts_with(trimmed, "C"))
		parse_color(trimmed, &game->config->ceiling_color, game);
	else
	{
		game->config->map_start_indx = line_index;
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}
