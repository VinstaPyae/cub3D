#include "cub3D.h"

static void	parse_config(t_game *game)
{
	int	i;

	i = 0;
	while (game->config->lines[i])
	{
		if (!parse_config_line(game->config->lines[i], game, i))
			break ;
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
