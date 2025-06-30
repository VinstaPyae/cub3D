#include "cub3D.h"

static int	*xpm_to_img(t_game *game, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(game, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * game->texture->size * game->texture->size);
	if (!buffer)
		ft_clean_exit(game, show_err(NULL, "Could not allocate memory", 1));
	y = 0;
	while (y < game->texture->size)
	{
		x = 0;
		while (x < game->texture->size)
		{
			buffer[y * game->texture->size + x]
				= tmp.addr[y * game->texture->size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_game *game)
{
	game->tex_c = ft_calloc(5, sizeof * game->texture);
	if (!game->tex_c)
		ft_clean_exit(game, show_err(NULL, "Could not allocate memory", 1));
	game->tex_c[NORTH] = xpm_to_img(game, game->config->texture_no);
	game->tex_c[SOUTH] = xpm_to_img(game, game->config->texture_so);
	game->tex_c[EAST] = xpm_to_img(game, game->config->texture_ea);
	game->tex_c[WEST] = xpm_to_img(game, game->config->texture_we);
}