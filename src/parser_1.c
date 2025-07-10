/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jace <jace@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:46:08 by pzaw              #+#    #+#             */
/*   Updated: 2025/07/10 22:30:43 by jace             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*find_next_newline(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '\n')
		str++;
	return (str);
}

char	*allocate_line(size_t len, t_game *game)
{
	char	*line;

	line = malloc(len + 1);
	if (!line)
	{
		perror("Error\nMalloc failed");
		ft_clean_exit(game, 1);
	}
	return (line);
}

void	copy_line_content(char *line, char *start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		line[i] = start[i];
		i++;
	}
	line[i] = '\0';
}

char	*get_next_line(char **pos, t_game *game)
{
	char	*start;
	char	*end;
	char	*line;
	size_t	len;

	if (!pos || !*pos || !**pos)
		return (NULL);
	start = *pos;
	end = find_next_newline(start);
	len = end - start;
	line = allocate_line(len, game);
	copy_line_content(line, start, len);
	if (*end == '\n')
		*pos = end + 1;
	else
		*pos = end;
	return (line);
}

size_t	count_lines(char *content)
{
	size_t	count;
	char	*pos;

	if (!content || !*content)
		return (0);
	count = 0;
	pos = content;
	while (*pos)
	{
		count++;
		pos = find_next_newline(pos);
		if (*pos == '\n')
			pos++;
		else
			break ;
	}
	return (count);
}
