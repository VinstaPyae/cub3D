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
void	ft_free_strs(char **strs)
{
	int	i = 0;

	if (!strs)
		return;
	while (strs[i])
    {
		free(strs[i]);
        strs[i++] = NULL;
    }
	free(strs);
    strs = NULL;
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
        ft_free_strs(cfg->lines);
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
    if (cfg->map)
    {
        ft_free_strs(cfg->map);
        cfg->map = NULL;
    }
    if (cfg)
    {
        free(cfg);
        cfg = NULL;
    }
}

void    ft_clean_up(t_game  *game)
{
    if (game->config)
        ft_clean_config(game->config);
    if (game->plyr)
        ft_clean_plyr(game->plyr);
    if (game->ray)
        ft_clean_ray(game->ray);
    if (game)
    {
        free(game);
        game = NULL;
    }
}
