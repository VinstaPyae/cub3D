#include "cub3D.h"

void	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		ft_putstr_fd("Error\nFailed to get texture data address\n", 2);
		exit(1);
	}
}


int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0); // return black if out of bounds (fail-safe)

	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}

t_texture *select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->texture[3]); // EA
		else
			return (&game->texture[2]); // WE
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->texture[1]); // SO
		else
			return (&game->texture[0]); // NO
	}
}


void	draw_pixel_to_buffer(t_game *game, int x, int y, int color)
{
	char *dst = game->texture->img + (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}
