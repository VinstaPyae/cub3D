#include "cub3D.h"

static int	get_map_width(char **lines, int start)
{
	int max = 0;
	int len;

	while (lines[start])
	{
		len = ft_strlen(lines[start]);
		if (len > max)
			max = len;
		start++;
	}
	return (max);
}

static int	get_map_height(char **lines, int start)
{
	int count = 0;
	while (lines[start])
	{
		count++;
		start++;
	}
	return (count);
}

void	parse_map(char **lines, int start, t_game *game)
{
	int		i = 0;
	int		width = get_map_width(lines, start);
	int		height = get_map_height(lines, start);

	game->config->map_width = width;
	game->config->map_height = height;

	game->config->map = malloc(sizeof(char *) * (height + 1));
	if (!game->config->map)
	{
		ft_putstr_fd("Error\nFailed to allocate map memory\n", 2);
		ft_clean_up(game);
		exit(1);
	}

	while (i < height)
	{
		game->config->map[i] = malloc(width + 1);
		if (!game->config->map[i])
		{
			ft_putstr_fd("Error\nFailed to allocate map line\n", 2);
			ft_clean_up(game);
			exit(1);
		}
		int j = 0;
		while (lines[start][j])
		{
			game->config->map[i][j] = lines[start][j];
			j++;
		}
		while (j < width)  // pad with spaces
			game->config->map[i][j++] = ' ';
		game->config->map[i][j] = '\0';
		i++;
		start++;
	}
	game->config->map[i] = NULL;  // null-terminate the 2D array
}
