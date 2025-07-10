/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jace <jace@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:01:14 by pzaw              #+#    #+#             */
/*   Updated: 2025/07/10 22:30:13 by jace             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*append_buffer_to_content(char *content, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(content, buffer);
	if (!tmp)
	{
		free(content);
		perror("Error\nMalloc failed");
		exit(1);
	}
	free(content);
	return (tmp);
}

static char	*read_whole_file(int fd, t_game *game)
{
	char	buffer[1025];
	char	*content;
	ssize_t	bytes;

	content = ft_strdup("");
	if (!content)
	{
		perror("Error\nMalloc failed");
		ft_clean_exit(game, 1);
	}
	bytes = read(fd, buffer, 1024);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		content = append_buffer_to_content(content, buffer);
		bytes = read(fd, buffer, 1024);
	}
	if (bytes < 0)
	{
		free(content);
		perror("Error\nFailed to read file");
		ft_clean_exit(game, 1);
	}
	return (content);
}

static char	**allocate_lines_array(size_t line_count, t_game *game)
{
	char	**lines;

	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
	{
		perror("Error\nMalloc failed");
		ft_clean_exit(game, 1);
	}
	return (lines);
}

static void	extract_lines(char **lines, char *content, size_t line_count, t_game *game)
{
	char	*pos;
	size_t	i;

	i = 0;
	pos = content;
	while (i < line_count)
	{
		lines[i] = get_next_line(&pos, game);
		if (!lines[i])
			break ;
		i++;
	}
	lines[i] = NULL;
}

char	**read_file_lines(int fd, t_game *game)
{
	char	*whole;
	char	**lines;
	size_t	line_count;

	whole = read_whole_file(fd, game);
	line_count = count_lines(whole);
	lines = allocate_lines_array(line_count, game);
	extract_lines(lines, whole, line_count, game);
	free(whole);
	return (lines);
}
