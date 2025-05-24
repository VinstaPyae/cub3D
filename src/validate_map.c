#include "cub3D.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || is_player_char(c) || c == ' ');
}

static int	is_in_bounds(int y, int x, t_config *cfg)
{
	return (y >= 0 && x >= 0 && y < cfg->map_height && x < cfg->map_width);
}

// Check 8 surrounding cells
static void	check_enclosure(t_config *cfg, int y, int x)
{
	int	dy[4] = {-1, 1, 0, 0};
	int	dx[4] = {0, 0, -1, 1};
	int	i;
	int ny, nx;

	i = 0;
	while (i < 4)
	{
		ny = y + dy[i];
		nx = x + dx[i];
		if (!is_in_bounds(ny, nx, cfg) || cfg->map[ny][nx] == ' ')
		{
			ft_putstr_fd("Error\nMap is not enclosed by walls\n", 2);
			ft_clean_up(cfg);
			exit(1);
		}
		i++;
	}
}

void	validate_map(t_config *cfg)
{
	int	y = 0;
	int	x;
	int	player_count = 0;

	while (y < cfg->map_height)
	{
		x = 0;
		while (x < cfg->map_width)
		{
			char c = cfg->map[y][x];

			if (!is_valid_char(c))
			{
				ft_putstr_fd("Error\nInvalid character in map\n", 2);
				ft_clean_up(cfg);
				exit(1);
			}
			if (c == '0' || is_player_char(c))
			{
				check_enclosure(cfg, y, x);
			}
			if (is_player_char(c))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		ft_putstr_fd("Error\nMap must have exactly one player start\n", 2);
		ft_clean_up(cfg);
		exit(1);
	}
}
