#include "cub3D.h"

static void	get_texture_index(t_tex *tex, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			tex->index = WEST;
		else
			tex->index = EAST;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			tex->index = SOUTH;
		else
			tex->index = NORTH;
	}
}

void	update_texture_pixels(t_game *game, t_tex *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	get_texture_index(tex, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->wall_height;
	tex->pos = (ray->wall_top - SCN_HEIGHT / 2
			+ ray->wall_height / 2) * tex->step;
	y = ray->wall_top;
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
		ft_free_arr((void **)game->tex_pixels);
	game->tex_pixels = ft_calloc(SCN_HEIGHT + 1,
			sizeof * game->tex_pixels);
	if (!game->tex_pixels)
		ft_clean_exit(game, show_err(NULL, ERR_MALLOC, 1));
	i = 0;
	while (i < SCN_HEIGHT)
	{
		game->tex_pixels[i] = ft_calloc(SCN_WIDTH + 1,
				sizeof * game->tex_pixels[0]);
		if (!game->tex_pixels[i])
			ft_clean_exit(game, show_err(NULL, ERR_MALLOC, 1));
		i++;
	}
}
