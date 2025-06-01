#include "cub3D.h"

void	parse_texture(char *line, char **destination, t_game *game)
{
	char	**parts;
	char	*ext;

	if (*destination != NULL)
	{
		ft_putstr_fd("Error\nDuplicate texture identifier\n", 2);
		ft_clean_up(game);
		exit(1);
	}
	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		ft_putstr_fd("Error\nInvalid texture format\n", 2);
		if (parts)
			ft_free_strs(parts); // You can write this to free char** arrays
		ft_clean_up(game);
		free(line);
		exit(1);
	}
	printf("---------------------------------------\n");
	for (int i=0; parts[i]; i++)
		printf("%s\n", parts[i]);
	ext = ft_strchr(parts[1], '.');
	if (!ext || ft_strncmp(ext + 1, "xpm", 3) != 0 || ft_strlen(ext + 1) != 3)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		if (parts)
			ft_free_strs(parts);
		ft_clean_up(game);
		free(line);
		exit(1);
	}
	*destination = ft_strdup(parts[1]);
	if (!*destination)
	{
		ft_putstr_fd("Error\nMalloc failed for texture path\n", 2);
		if (parts)
			ft_free_strs(parts);
		ft_clean_up(game);
		free(line);
		exit(1);
	}
	ft_free_strs(parts);
}
