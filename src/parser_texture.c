#include "cub3D.h"

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

static bool	is_acessible(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nFile not accessible");
		return (false);
	}
	close(fd);
	return (true);
}

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
	if (!parts)
	{
		ft_putstr_fd("Error\nTexture not found\n", 2);
		if (parts)
			ft_free_strs((void **)parts); // You can write this to free char** arrays
		ft_clean_up(game);
		free(line);
		exit(1);
	}
	printf("---------------------------------------\n");
	for (int i=0; parts[i]; i++)
		printf("%s\n", parts[i]);
	*destination = ft_strdup(parts[1]);
	if (!*destination)
	{
		ft_putstr_fd("Error\nMalloc failed for texture path\n", 2);
		if (parts)
			ft_free_strs((void **)parts);
		ft_clean_up(game);
		free(line);
		exit(1);
	}
  	if (is_dir(*destination))
	{
		ft_putstr_fd("Error\nTexture path is a directory, not a file\n", 2);
		if (parts)
			ft_free_strs((void **)parts);
		ft_clean_up(game);
		free(line);
		exit(1);
	}
	ext = ft_strrchr(*destination, '.');
	if (ft_strncmp(ext, ".xpm", ft_strlen(ext)) != 0)
	{
		ft_putstr_fd("Error\nTexture file must be .xpm format\n", 2);
		if (parts)
			ft_free_strs((void **)parts);
		ft_clean_up(game);
		free(line);
		exit(1);
	}
	if (is_acessible(*destination) == false)
	{
		if (parts)
			ft_free_strs((void **)parts);
		ft_clean_up(game);
		free(line);
		exit(1);
	}
	ft_free_strs((void **)parts);
}
