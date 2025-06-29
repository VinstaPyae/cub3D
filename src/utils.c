#include "cub3D.h"

int starts_with(const char *str, const char *prefix)
{
    int i = 0;
    while (prefix[i])
    {
        if (str[i] != prefix[i])
            return (0);
        i++;
    }
    return (1);
}
void	ft_free_arr(void **arr)
{
	int	i = 0;

	if (!arr)
		return;
	while (arr[i])
    {
		free(arr[i]);
        arr[i++] = NULL;
    }
    if (arr)
    {
        free(arr);
        arr = NULL;
    }
}

void    ft_clean_plyr(t_player *plyr)
{
    if (plyr)
    {
        free(plyr);
        plyr = NULL;
    }
}

void    ft_clean_ray(t_ray *ray)
{
    if (ray)
    {
        free(ray);
        ray = NULL;
    }
}

void    ft_clean_config(t_config *cfg)
{
    if (cfg->lines)
    {
        ft_free_arr((void **)cfg->lines);
        cfg->lines = NULL;
    }
    if (cfg->texture_no)
    {
        free(cfg->texture_no);
        cfg->texture_no = NULL;
    }
    if (cfg->texture_so)
    {
        free(cfg->texture_so);
        cfg->texture_so = NULL;
    }
    if (cfg->texture_ea)
    {
        free(cfg->texture_ea);
        cfg->texture_ea = NULL;
    }
    if (cfg->texture_we)
    {
        free(cfg->texture_we);
        cfg->texture_we = NULL;
    }
    if (cfg->tex_pix)
    {
        ft_free_arr((void **)cfg->tex_pix);
        cfg->tex_pix = NULL;
    }
    if (cfg->map)
    {
        ft_free_arr((void **)cfg->map);
        cfg->map = NULL;
    }
    if (cfg)
    {
        free(cfg);
        cfg = NULL;
    }
}

static void	free_tex(t_tex *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
    if (textures)
    {
        free(textures);
        textures = NULL;
    }
}

void    ft_clean_up(t_game  *game)
{
    if (game->config)
        ft_clean_config(game->config);
    if (game->texture)
        free_tex(game->texture);
    if (game->plyr)
        ft_clean_plyr(game->plyr);
    if (game->ray)
        ft_clean_ray(game->ray);
    if (game->tex_c)
        ft_free_arr((void **)game->tex_c);
    if (game->tex_pixels)
        ft_free_arr((void **)game->tex_pixels);
}

void    ft_clean_exit(t_game *game, int status)
{
    if (!game)
        exit(status);
    if (game->win && game->mlx)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        mlx_loop_end(game->mlx);
        free(game->mlx);
    }
    ft_clean_up(game);
    exit(status);
}

int	show_err(char *detail, char *str, int code)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}