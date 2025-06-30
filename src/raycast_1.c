#include "cub3D.h"

int	isWall(int x, int y, t_game *game)
{
	int	col;
	int	row;

	col = x;
	row = y;
	if (col < 0 || row < 0)
		return (1);
	if (col >= game->config->map_width || row >= game->config->map_height)
		return (1);
	if (game->config->map[row][col] == '1')
		return (1);
	return (0);
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void	set_frame_image_pixel(t_game *game, t_img *image, int x, int y)
{
	if (game->tex_pixels[y][x] > 0)
		set_image_pixel(image, x, y, game->tex_pixels[y][x]);
	else if (y < SCN_HEIGHT / 2)
		set_image_pixel(image, x, y, game->config->ceiling_color);
	else if (y < SCN_HEIGHT - 1)
		set_image_pixel(image, x, y, game->config->floor_color);
}

void	render_frame(t_game *game)
{
	t_img	image;
	int		x;
	int		y;

	y = 0;
	image.img = NULL;
	init_img(game, &image, SCN_WIDTH, SCN_HEIGHT);
	while (y < SCN_HEIGHT)
	{
		x = 0;
		while (x < SCN_WIDTH)
		{
			set_frame_image_pixel(game, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}
