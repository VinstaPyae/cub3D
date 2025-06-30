#include "cub3D.h"

void setup_hooks(t_game *game)
{
    mlx_hook(game->win, 17, 1L << 17, close_window, game);
    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, game);
}

int render_loop(t_game *game)
{
    handle_movement(game);
    raycast(game);
    render_frame(game);
    return (0);
}
void rotate_l_or_r(t_player *player, double angle)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = player->dir_x;
    old_plane_x = player->plane_x;

    // Rotate direction vector
    player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
    player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);

    // Rotate camera plane vector
    player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
    player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

int key_press(int key, t_game *game)
{
    if (key == KEY_ESC)
    {
        return (close_window(game));
    }
    if (key == KEY_W)
        game->key_w = 1;
    if (key == KEY_S)
        game->key_s = 1;
    if (key == KEY_A)
        game->key_a = 1;
    if (key == KEY_D)
        game->key_d = 1;
    if (key == KEY_LEFT)
        game->key_left = 1;
    if (key == KEY_RIGHT)
        game->key_right = 1;
    return (0);
}

int key_release(int key, t_game *game)
{
    if (key == KEY_W)
        game->key_w = 0;
    if (key == KEY_S)
        game->key_s = 0;
    if (key == KEY_A)
        game->key_a = 0;
    if (key == KEY_D)
        game->key_d = 0;
    if (key == KEY_LEFT)
        game->key_left = 0;
    if (key == KEY_RIGHT)
        game->key_right = 0;
    return (0);
}