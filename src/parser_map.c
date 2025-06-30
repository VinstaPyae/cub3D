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

static void ft_clean_map_error(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_clean_up(game);
	exit(1);
}

static char *allocate_map_line(t_game *game, int width)
{
	char *line = ft_calloc(width + 1, sizeof(char));
	if (!line)
		ft_clean_map_error(game, "Failed to allocate map line\n");
	return (line);
}

static void check_empty_line(char *line, t_game *game)
{
	if (line[0] == '\0')
	{
		printf("Error\n Empty line found in map\n");
		ft_clean_exit(game, 1);
	}
}

static void copy_and_pad_line(char *dst, char *src, int width)
{
	int j = 0;
	
	while (src[j])
	{
		dst[j] = src[j];
		j++;
	}
	while (j < width)  // pad with spaces
		dst[j++] = ' ';
	dst[j] = '\0';
}

static char **allocate_map_array(t_game *game, int height)
{
	char **map = ft_calloc(height + 1, sizeof(char *));
	if (!map)
		ft_clean_map_error(game, "Failed to allocate map memory\n");
	return (map);
}

void parse_map(char **lines, int start, t_game *game)
{
	int i = 0;
	int width = get_map_width(lines, start);
	int height = get_map_height(lines, start);
	
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
	game->config->map[i] = NULL;  // null-terminate the 2D array
}
