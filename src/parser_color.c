#include "cub3D.h"

static int	 validate_color_value(char *str, char **rgb_parts, char *line, t_game *game)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("Error\nInvalid Color code\n", 2);
			free(line);
			ft_free_strs((void **)(void **)rgb_parts);
			ft_clean_up(game);
			exit(1);
		}
	}
	int	val = ft_atoi(str);

	if (val < 0 || val > 255)
	{
		ft_putstr_fd("Error\nColor values must be between 0 and 255\n", 2);
		free(line);
		ft_free_strs((void **)(void **)rgb_parts);
		ft_clean_up(game);
		exit(1);
	}
	return (val);
}

void	parse_color(char *line, int *color_out, t_game *game)
{
	char	*parts;
	char	**rgb_parts;
	int		r, g, b;

	if (*color_out != -1) // already set?
	{
		free(line);
		ft_putstr_fd("Error\nDuplicate color definition\n", 2);
		ft_clean_up(game);
		exit(1);
	}
	parts = ft_strtrim(line, "FC \t");
	printf("%s\n", parts);
	rgb_parts = ft_split(parts, ',');
	free(parts); // parts[0] = "F", parts[1] = "220,100,0"

	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2] || rgb_parts[3])
	{
		free(line);
		ft_putstr_fd("Error\nColor must have 3 RGB values\n", 2);
		ft_free_strs((void **)rgb_parts);
		ft_clean_up(game);
		exit(1);
	}

	r = validate_color_value(rgb_parts[0], rgb_parts, line, game);
	g = validate_color_value(rgb_parts[1], rgb_parts, line, game);
	b = validate_color_value(rgb_parts[2], rgb_parts, line, game);

	ft_free_strs((void **)rgb_parts);
	*color_out = (r << 16) | (g << 8) | b;
}
