#include "cub3D.h"

void	start_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MiniLibX\n", 2);
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, SCN_WIDTH, SCN_HEIGHT, "cub3D");
	if (!game->win)
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		exit(1);
	}
	load_texture(game, &game->texture[0], game->config->texture_no); // NO
	load_texture(game, &game->texture[1], game->config->texture_so); // SO
	load_texture(game, &game->texture[2], game->config->texture_we); // WE
	load_texture(game, &game->texture[3], game->config->texture_ea); // EA
	// TEMP: fill window with a color (we'll replace this with real drawing later)
	mlx_loop(game->mlx); // This blocks the main thread until the window is closed
}


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

int	main(int ac, char *av[])
{
	int			fd;
	int			i = 0;
	t_game		*game;

	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <file.cub>\n", 2), 1);
	if (!check_file_extension(av[1]))
		return (ft_putstr_fd("Error\nFile must end with .cub\n", 2), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error\nMem error\n", 2), 1);
	init_game(game);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nFailed to open file"), ft_clean_up(game), 1);
	game->config->lines = read_file_lines(fd);
	close(fd);
	// for(i=0; lines[i]; i++)
	// 	printf("%s\n", lines[i]);
	// i = 0;
	while (game->config->lines[i])
	{
		char *trimmed = ft_strtrim(game->config->lines[i], " \t");
		if (!trimmed || trimmed[0] == '\0')  // skip empty line
		{
			free(trimmed);
			i++;
			continue;
		}
		printf("trimmed str: %s\n", trimmed);
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
			game->config->map_start_indx = i;  // mark the start of map
			printf("break\n");
			free(trimmed);
			break;
		}
		free(trimmed);
		i++;
	}
	if (!game->config->texture_no || !game->config->texture_so || !game->config->texture_we || !game->config->texture_ea)
	{
		ft_putstr_fd("Error\nMissing one or more wall textures\n", 2);
		ft_clean_up(game);
		exit(1);
	}
	// printf("Tex: %s\n", config->texture_ea);
	// printf("Tex: %s\n", config->texture_so);
	// printf("Tex: %s\n", config->texture_no);
	// printf("Tex: %s\n", config->texture_we);
	if (game->config->floor_color == -1 || game->config->ceiling_color == -1)
	{
		ft_putstr_fd("Error\nMissing floor or ceiling color\n", 2);
		ft_clean_up(game);
		exit(1);
	}
	// printf("Color: %d\n", config->ceiling_color);
	// printf("Color: %d\n", config->floor_color);
	parse_map(game->config->lines, game->config->map_start_indx, game);
	validate_map(game);
	get_plyr_pos(game);
	get_plyr_dir(game);
	start_game(game);
	raycast(game->plyr, game->ray, game);

	for (i=0; game->config->map[i]; i++)
		printf("%s\n", game->config->map[i]);
	i = 0;
	ft_clean_up(game);
	return (0);
}
