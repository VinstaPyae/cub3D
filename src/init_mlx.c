#include "cub3D.h"

void	init_texture_img(t_game *game, t_img *image, char *path)
{
	init_img_reset(image);
	image->img = mlx_xpm_file_to_image(game->mlx, path, &game->texture->size,
			&game->texture->size);
	if (image->img == NULL)
		ft_clean_exit(game, show_err("mlx", ERR_MLX_IMG, 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

void    init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        ft_clean_exit(game, show_err("mlx", ERR_MLX_START, 1));
    game->win = mlx_new_window(game->mlx, SCN_WIDTH, SCN_HEIGHT, "Cub3D");
    if (!game->win)
        ft_clean_exit(game, show_err("mlx", ERR_MLX_WIN, 1));
    return ;
}