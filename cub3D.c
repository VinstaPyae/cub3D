#include "cub3D.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot)
		return (0);
	return (ft_strncmp(dot, ".cub", 5) == 0);
}
static int	validate_args(int ac, char **av)
{
	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <file.cub>\n", 2), 0);
	if (!check_file_extension(av[1]))
		return (ft_putstr_fd("Error\nFile must end with .cub\n", 2), 0);
	return (1);
}

static int	read_config_file(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nFailed to open file"), 0);
	game->config->lines = read_file_lines(fd);
	close(fd);
	return (1);
}

static int	parse_config_line(char *line, t_game *game, int line_index)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return (1);
	}
	if (starts_with(trimmed, "NO"))
		parse_texture(trimmed, &game->config->texture_no, game);
	else if (starts_with(trimmed, "SO"))
		parse_texture(trimmed, &game->config->texture_so, game);
	else if (starts_with(trimmed, "WE"))
		parse_texture(trimmed, &game->config->texture_we, game);
	else if (starts_with(trimmed, "EA"))
		parse_texture(trimmed, &game->config->texture_ea, game);
	else if (starts_with(trimmed, "F"))
		parse_color(trimmed, &game->config->floor_color, game);
	else if (starts_with(trimmed, "C"))
		parse_color(trimmed, &game->config->ceiling_color, game);
	else
	{
		game->config->map_start_indx = line_index;
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

static void	parse_config(t_game *game)
{
	int	i;

	i = 0;
	while (game->config->lines[i])
	{
		if (!parse_config_line(game->config->lines[i], game, i))
			break;
		i++;
	}
}

static void	validate_config(t_game *game)
{
	if (!game->config->texture_no || !game->config->texture_so
		|| !game->config->texture_we || !game->config->texture_ea)
	{
		ft_putstr_fd("Error\nMissing one or more wall textures\n", 2);
		ft_clean_up(game);
		exit(1);
	}
	if (game->config->floor_color == -1 || game->config->ceiling_color == -1)
	{
		ft_putstr_fd("Error\nMissing floor or ceiling color\n", 2);
		ft_clean_up(game);
		exit(1);
	}
}

static void	setup_game(t_game *game)
{
	parse_map(game->config->lines, game->config->map_start_indx, game);
	validate_map(game);
	init_mlx(game);
	init_textures(game);
	get_plyr_pos(game);
	get_plyr_dir(game);
}

static void	run_game(t_game *game)
{
	raycast(game);
	render_frame(game);
	setup_hooks(game);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char *av[])
{
	t_game	game;

	if (!validate_args(ac, av))
		return (1);
	init_game(&game);
	if (!read_config_file(av[1], &game))
	{
		ft_clean_up(&game);
		return (1);
	}
	parse_config(&game);
	validate_config(&game);
	setup_game(&game);
	run_game(&game);
	ft_clean_up(&game);
	return (0);
}
