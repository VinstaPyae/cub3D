/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:55:43 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 19:57:02 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	copy_and_pad_line(char *dst, char *src, int width)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dst[j] = src[j];
		j++;
	}
	while (j < width)
		dst[j++] = ' ';
	dst[j] = '\0';
}

static char	**allocate_map_array(t_game *game, int height)
{
	char	**map;

	map = ft_calloc(height + 1, sizeof(char *));
	if (!map)
		ft_clean_map_error(game, "Failed to allocate map memory\n");
	return (map);
}

void	parse_map(char **lines, int start, t_game *game)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	width = get_map_width(lines, start);
	height = get_map_height(lines, start);
	game->config->map_width = width;
	game->config->map_height = height;
	game->config->map = allocate_map_array(game, height);
	while (i < height)
	{
		check_empty_line(lines[start], game);
		game->config->map[i] = allocate_map_line(game, width);
		copy_and_pad_line(game->config->map[i], lines[start], width);
		i++;
		start++;
	}
	game->config->map[i] = NULL;
