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
void	init_config(t_config *config)
{
	config->lines = NULL;
	config->texture_no = NULL;
	config->texture_ea = NULL;
	config->texture_so = NULL;
	config->texture_we = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->map = NULL;
	config->map_height = 0;
	config->map_width = 0;
	config->map_start_indx = -1;
}

int	main(int ac, char *av[])
{
	int			fd;
	int			i = 0;
	t_config	*config;  // auto-zero everything

	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <file.cub>\n", 2), 1);
	if (!check_file_extension(av[1]))
		return (ft_putstr_fd("Error\nFile must end with .cub\n", 2), 1);
	config = malloc(sizeof(t_config));
	if (!config)
		return (ft_putstr_fd("Error\nMem error\n", 2), 1);
	init_config(config);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nFailed to open file"), ft_clean_up(config), 1);
	config->lines = read_file_lines(fd);
	close(fd);
	// for(i=0; lines[i]; i++)
	// 	printf("%s\n", lines[i]);
	// i = 0;
	while (config->lines[i])
	{
		char *trimmed = ft_strtrim(config->lines[i], " \t");
		if (!trimmed || trimmed[0] == '\0')  // skip empty line
		{
			free(trimmed);
			i++;
			continue;
		}
		printf("trimmed str: %s\n", trimmed);
		if (starts_with(trimmed, "NO"))
			parse_texture(trimmed, &config->texture_no, config);
		else if (starts_with(trimmed, "SO"))
			parse_texture(trimmed, &config->texture_so, config);
		else if (starts_with(trimmed, "WE"))
			parse_texture(trimmed, &config->texture_we, config);
		else if (starts_with(trimmed, "EA"))
			parse_texture(trimmed, &config->texture_ea, config);
		else if (starts_with(trimmed, "F"))
			parse_color(trimmed, &config->floor_color, config);
		else if (starts_with(trimmed, "C"))
			parse_color(trimmed, &config->ceiling_color, config);
		else
		{
			config->map_start_indx = i;  // mark the start of map
			printf("break\n");
			free(trimmed);
			break;
		}
		free(trimmed);
		i++;
	}
	if (!config->texture_no || !config->texture_so || !config->texture_we || !config->texture_ea)
	{
		ft_putstr_fd("Error\nMissing one or more wall textures\n", 2);
		ft_clean_up(config);
		exit(1);
	}
	printf("Tex: %s\n", config->texture_ea);
	printf("Tex: %s\n", config->texture_so);
	printf("Tex: %s\n", config->texture_no);
	printf("Tex: %s\n", config->texture_we);
	if (config->floor_color == -1 || config->ceiling_color == -1)
	{
		ft_putstr_fd("Error\nMissing floor or ceiling color\n", 2);
		// ft_clean_up(config);
		exit(1);
	}
	printf("Color: %d\n", config->ceiling_color);
	printf("Color: %d\n", config->floor_color);
	parse_map(config->lines, config->map_start_indx, config);
	validate_map(config);
	for (i=0; config->map[i]; i++)
		printf("%s\n", config->map[i]);
	i = 0;
	ft_clean_up(config);
	return (0);
}
