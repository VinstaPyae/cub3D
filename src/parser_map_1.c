/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:54:40 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 19:55:26 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_width(char **lines, int start)
{
	int	max;
	int	len;

	max = 0;
	while (lines[start])
	{
		len = ft_strlen(lines[start]);
		if (len > max)
			max = len;
		start++;
	}
	return (max);
}

int	get_map_height(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start])
	{
		count++;
		start++;
	}
	return (count);
}

void	ft_clean_map_error(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_clean_up(game);
	exit(1);
}

char	*allocate_map_line(t_game *game, int width)
{
	char	*line;

	line = ft_calloc(width + 1, sizeof(char));
	if (!line)
		ft_clean_map_error(game, "Failed to allocate map line\n");
	return (line);
}

void	check_empty_line(char *line, t_game *game)
{
	if (line[0] == '\0')
	{
		printf("Error\n Empty line found in map\n");
		ft_clean_exit(game, 1);
	}
}
