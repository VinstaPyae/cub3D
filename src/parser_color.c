#include "cub3D.h"

static int	validate_color_value(char *str)
{
	int	val = ft_atoi(str);

	if (val < 0 || val > 255)
	{
		ft_putstr_fd("Error\nColor values must be between 0 and 255\n", 2);
		exit(1);
	}
	return (val);
}

void	parse_color(char *line, int *color_out)
{
	char	**parts;
	char	**rgb_parts;
	int		r, g, b;

	if (*color_out != -1) // already set?
	{
		ft_putstr_fd("Error\nDuplicate color definition\n", 2);
		exit(1);
	}

	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || parts[2])
	{
		ft_putstr_fd("Error\nInvalid color format\n", 2);
		ft_free_strs(parts);
		exit(1);
	}
	rgb_parts = ft_split(parts[1], ',');
	ft_free_strs(parts); // parts[0] = "F", parts[1] = "220,100,0"

	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2] || rgb_parts[3])
	{
		ft_putstr_fd("Error\nColor must have 3 RGB values\n", 2);
		ft_free_strs(rgb_parts);
		exit(1);
	}

	r = validate_color_value(rgb_parts[0]);
	g = validate_color_value(rgb_parts[1]);
	b = validate_color_value(rgb_parts[2]);

	ft_free_strs(rgb_parts);
	*color_out = (r << 16) | (g << 8) | b;
}
