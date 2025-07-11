/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jace <jace@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:57:26 by pzaw              #+#    #+#             */
/*   Updated: 2025/07/11 22:36:23 by jace             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

static bool	is_acessible(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nTexture file not accessible");
		return (false);
	}
	close(fd);
	return (true);
}

static void	validate_texture_format(char *path,
	char **parts, t_game *game, char *line)
{
	char	*ext;

	if (is_dir(path))
		handle_error("Error\nTexture path is a directory, not a file\n",
			parts, game, line);
	ext = ft_strrchr(path, '.');
	if (ext == NULL || ft_strncmp(ext, ".xpm", 4) != 0)
		handle_error("Error\nTexture file must be .xpm format\n",
			parts, game, line);
	if (is_acessible(path) == false)
		handle_error("", parts, game, line);
}

static char	*extract_texture_path(char **parts, t_game *game, char *line)
{
	char	*path;

	path = ft_strdup(parts[1]);
	if (!path)
		handle_error("Error\nMalloc failed for texture path\n",
			parts, game, line);
	return (path);
}

void	parse_texture(char *line, char **destination, t_game *game)
{
	char	**parts;

	if (*destination != NULL)
		handle_error("Error\nDuplicate texture identifier\n", NULL, game, line);
	parts = ft_split(line, ' ');
	if (!parts)
		handle_error("Error\nTexture not found\n", parts, game, line);
	if (parts[2])
		handle_error("Error\nToo many arguments for texture\n",
			parts, game, line);
	*destination = extract_texture_path(parts, game, line);
	validate_texture_format(*destination, parts, game, line);
	ft_free_arr((void **)parts);
}
