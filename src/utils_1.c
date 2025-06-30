/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:54:13 by pzaw              #+#    #+#             */
/*   Updated: 2025/06/30 20:54:14 by pzaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_game *game)
{
	return (ft_clean_exit(game, 0), 0);
}

int	starts_with(const char *str, const char *prefix)
{
	int	i;

	i = 0;
	while (prefix[i])
	{
		if (str[i] != prefix[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_arr(void **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i++] = NULL;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

void	handle_error(char *msg, char **parts, t_game *game, char *line)
{
	ft_putstr_fd(msg, 2);
	if (parts)
		ft_free_arr((void **)parts);
	free(line);
	ft_clean_exit(game, 1);
}

void	ft_clean_plyr(t_player *plyr)
{
	if (plyr)
	{
		free(plyr);
		plyr = NULL;
	}
}
