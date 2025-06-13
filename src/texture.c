#include "cub3D.h"

// void	load_texture(t_game *game, t_texture *tex, char *path)
// {
// 	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
// 	if (!tex->img)
// 	{
// 		ft_putstr_fd("Error\nFailed to load texture: ", 2);
// 		ft_putstr_fd(path, 2);
// 		ft_putchar_fd('\n', 2);
// 		exit(1);
// 	}
// 	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
// 	if (!tex->addr)
// 	{
// 		ft_putstr_fd("Error\nFailed to get texture data address\n", 2);
// 		exit(1);
// 	}
// }


// int	get_texture_pixel(t_texture *tex, int x, int y)
// {
// 	char	*pixel;

// 	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
// 		return (0); // return black if out of bounds (fail-safe)

// 	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
// 	return (*(int *)pixel);
// }

// t_texture *select_texture(t_game *game, t_ray *ray)
// {
// 	if (ray->side == 0)
// 	{
// 		if (ray->ray_dir_x > 0)
// 			return (&game->texture[3]); // EA
// 		else
// 			return (&game->texture[2]); // WE
// 	}
// 	else
// 	{
// 		if (ray->ray_dir_y > 0)
// 			return (&game->texture[1]); // SO
// 		else
// 			return (&game->texture[0]); // NO
// 	}
// }

static void	get_texture_index(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			game->texture->index = WEST;
		else
			game->texture->index = EAST;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			game->texture->index = SOUTH;
		else
			game->texture->index = NORTH;
	}
}

void	update_texture_pixels(t_game *game, t_tex *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	get_texture_index(game, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->wall_height;
	tex->pos = (ray->wall_top - SCN_HEIGHT / 2
			+ ray->wall_height / 2) * tex->step;
	y = ray->wall_top;
	// printf("x: %d, wall_top: %d, wall_btm: %d, wall_height: %d\n",
	// 		x, ray->wall_top, ray->wall_btm, ray->wall_height);
	while (y < ray->wall_btm)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = game->tex_c[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			game->tex_pixels[y][x] = color;
		y++;
	}
}

void	init_texture_pixels(t_game *game)
{
	int	i;

	if (game->tex_pixels)
		ft_free_strs((void **)(void **)game->tex_pixels);
	game->tex_pixels = ft_calloc(SCN_HEIGHT + 1,
			sizeof * game->tex_pixels);
	if (!game->tex_pixels)
		ft_clean_exit(game, show_err(NULL, ERR_MALLOC, 1));
	i = 0;
	while (i < SCN_HEIGHT)
	{
		game->tex_pixels[i] = ft_calloc(SCN_WIDTH + 1,
				sizeof * game->tex_pixels);
		if (!game->tex_pixels[i])
			ft_clean_exit(game, show_err(NULL, ERR_MALLOC, 1));
		i++;
	}
}