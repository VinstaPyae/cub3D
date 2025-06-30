#include "cub3D.h"

/* Set up all the hooks */
void setup_hooks(t_game *game)
{
    mlx_hook(game->win, 17, 1L << 17, close_window, game); /* Window close */
    mlx_hook(game->win, 2, 1L << 0, key_press, game);      /* Key press */
    mlx_hook(game->win, 3, 1L << 1, key_release, game);
}

int render_loop(t_game *game)
{
    handle_movement(game); // Handle player movement
    raycast(game);         // Perform raycasting
    render_frame(game);    // Render the frame
    return (0);
}

/* Window close handler (red X button) */
int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    ft_clean_up(game);
    exit(0);
    return (0);
}

int key_press(int key, t_game *game)
{
    if (key == KEY_ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        ft_clean_up(game);
        exit(0);
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

// double get_frame_time(void)
// {
//     static struct timeval old_time = {0};
//     struct timeval new_time;
//     double frame_time;

//     gettimeofday(&new_time, NULL);
//     if (old_time.tv_sec == 0)
//     {
//         old_time = new_time;
//         return (0.016); // default 60 FPS if first frame
//     }
//     frame_time = (new_time.tv_sec - old_time.tv_sec) * 1000.0;
//     frame_time += (new_time.tv_usec - old_time.tv_usec) / 1000.0;
//     old_time = new_time;
//     return (frame_time / 1000.0); // return in seconds
// }
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
void move_forward(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->plyr->pos_x + game->plyr->dir_x * MOVE_SPEED;
    new_y = game->plyr->pos_y + game->plyr->dir_y * MOVE_SPEED;
    if (!isWall(new_x + game->plyr->dir_x * Wall_Bounce,
                game->plyr->pos_y, game))
        game->plyr->pos_x = new_x;
    if (!isWall(game->plyr->pos_x,
                new_y + game->plyr->dir_y * Wall_Bounce, game))
        game->plyr->pos_y = new_y;
}

void move_backward(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->plyr->pos_x - game->plyr->dir_x * MOVE_SPEED;
    new_y = game->plyr->pos_y - game->plyr->dir_y * MOVE_SPEED;
    if (!isWall(new_x - game->plyr->dir_x * Wall_Bounce,
                game->plyr->pos_y, game))
        game->plyr->pos_x = new_x;
    if (!isWall(game->plyr->pos_x,
                new_y - game->plyr->dir_y * Wall_Bounce, game))
        game->plyr->pos_y = new_y;
}

void move_left(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->plyr->pos_x + game->plyr->dir_y * MOVE_SPEED;
    new_y = game->plyr->pos_y - game->plyr->dir_x * MOVE_SPEED;
    if (!isWall(new_x + game->plyr->dir_y * Wall_Bounce,
                game->plyr->pos_y, game))
        game->plyr->pos_x = new_x;
    if (!isWall(game->plyr->pos_x,
                new_y - game->plyr->dir_x * Wall_Bounce, game))
        game->plyr->pos_y = new_y;
}

void move_right(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->plyr->pos_x - game->plyr->dir_y * MOVE_SPEED;
    new_y = game->plyr->pos_y + game->plyr->dir_x * MOVE_SPEED;
    if (!isWall(new_x - game->plyr->dir_y * Wall_Bounce,
                game->plyr->pos_y, game))
        game->plyr->pos_x = new_x;
    if (!isWall(game->plyr->pos_x,
                new_y + game->plyr->dir_x * Wall_Bounce, game))
        game->plyr->pos_y = new_y;
}
void handle_movement(t_game *game)
{
    if (game->key_w)
        move_forward(game);
    if (game->key_s)
        move_backward(game);
    if (game->key_a)
        move_left(game);
    if (game->key_d)
        move_right(game);
    if (game->key_left)
        rotate_l_or_r(game->plyr, -ROT_SPEED);
    if (game->key_right)
        rotate_l_or_r(game->plyr, ROT_SPEED);
}
