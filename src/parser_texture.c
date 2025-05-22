#include "cub3D.h"

void	parse_texture(char *line, char **destination)
{
	char	**parts;

	if (*destination != NULL)
	{
		ft_putstr_fd("Error\nDuplicate texture identifier\n", 2);
		exit(1);
	}
	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		ft_putstr_fd("Error\nInvalid texture format\n", 2);
		if (parts)
			ft_free_strs(parts); // You can write this to free char** arrays
		exit(1);
	}
	*destination = ft_strdup(parts[1]);
	if (!*destination)
	{
		ft_putstr_fd("Error\nMalloc failed for texture path\n", 2);
		ft_free_strs(parts);
		exit(1);
	}
	ft_free_strs(parts);
}
