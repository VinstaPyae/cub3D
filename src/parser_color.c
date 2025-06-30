/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:50:56 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 19:54:24 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_color_value(char *str,
	char **rgb_parts, char *line, t_game *game)
{
	int	i;
	int	val;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("Error\nInvalid Color code\n", 2);
			free(line);
			ft_free_arr((void **)(void **)rgb_parts);
			ft_clean_up(game);
			exit(1);
		}
	}
	val = ft_atoi(str);
	if (val < 0 || val > 255)
	{
		ft_putstr_fd("Error\nColor values must be between 0 and 255\n", 2);
		free(line);
		ft_free_arr((void **)(void **)rgb_parts);
		ft_clean_up(game);
		exit(1);
	}
	return (val);
}

static void	check_duplicate_color(int *color_out, char *line, t_game *game)
{
	if (*color_out != -1)
	{
		free(line);
		ft_putstr_fd("Error\nDuplicate color definition\n", 2);
		ft_clean_up(game);
		exit(1);
	}
}

static char	**prepare_rgb_parts(char *line)
{
	char	*parts;
	char	**rgb_parts;
	int		i;
	char	*trimmed;

	i = 0;
	while (line[i] == 'F' || line[i] == 'C')
		i++;
	if (i > 1)
		return (NULL);
	parts = ft_strtrim(line, "FC \t");
	rgb_parts = ft_split(parts, ',');
	free(parts);
	i = 0;
	while (rgb_parts && rgb_parts[i])
	{
		trimmed = ft_strtrim(rgb_parts[i], " \t");
		free(rgb_parts[i]);
		rgb_parts[i] = trimmed;
		i++;
	}
	return (rgb_parts);
}

static void	validate_rgb_format(char **rgb_parts, char *line, t_game *game)
{
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1]
		|| !rgb_parts[2] || rgb_parts[3])
	{
		free(line);
		ft_putstr_fd("Error\nInvalid color format\n", 2);
		ft_free_arr((void **)rgb_parts);
		ft_clean_up(game);
		exit(1);
	}
}

void	parse_color(char *line, int *color_out, t_game *game)
{
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;

	check_duplicate_color(color_out, line, game);
	rgb_parts = prepare_rgb_parts(line);
	validate_rgb_format(rgb_parts, line, game);
	r = validate_color_value(rgb_parts[0], rgb_parts, line, game);
	g = validate_color_value(rgb_parts[1], rgb_parts, line, game);
	b = validate_color_value(rgb_parts[2], rgb_parts, line, game);
	ft_free_arr((void **)rgb_parts);
	*color_out = (r << 16) | (g << 8) | b;
}
