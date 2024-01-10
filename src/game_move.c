// some move functions
#include "cub3D.h"

// turn camera to angle
static void	rotate(t_camera *cam, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cam->dir_x;
	cam->dir_x = cam->dir_x * cos(angle) - cam->dir_y * sin(angle);
	cam->dir_y = old_dir_x * sin(angle) + cam->dir_y * cos(angle);
	old_plane_x = cam->plane_x;
	cam->plane_x = cam->plane_x * cos(angle) - cam->plane_y * sin(angle);
	cam->plane_y = old_plane_x * sin(angle) + cam->plane_y * cos(angle);
}

// checks space for empty and moves in dir x, dir y direction if it clear
static void	move(t_game *game, double dir_x, double dir_y, double speed)
{
	t_camera	*cam;
	int			new_x;
	int			new_y;

	cam = game->camera;
	new_x = (int)(cam->pos_x + dir_x * speed);
	new_y = (int)(cam->pos_y + dir_y * speed);
	if (new_x < game->map_obj->width && new_x >= 0 \
		&& game->map_obj->map[(int)(cam->pos_y)][new_x] == '0')
		cam->pos_x += dir_x * speed;
	if (new_y < game->map_obj->height && new_y >= 0 \
		&& game->map_obj->map[new_y][(int)(cam->pos_x)] == '0')
		cam->pos_y += dir_y * speed;
}

// moves according the keys
int	game_move(int key, t_game *game)
{
	t_camera	*cam;

	cam = game->camera;
	if (key == KEY_UP)
		move(game, cam->dir_x, cam->dir_y, MOVE_SPEED);
	else if (key == KEY_DOWN)
		move(game, cam->dir_x, cam->dir_y, -MOVE_SPEED);
	else if (key == KEY_RIGHT)
		move(game, (cam->dir_x * cos(ANG) - cam->dir_y * sin(ANG)), \
		(cam->dir_x * sin(ANG) + cam->dir_y * cos(ANG)), MOVE_SPEED);
	else if (key == KEY_LEFT)
		move(game, (cam->dir_x * cos(ANG) - cam->dir_y * sin(ANG)), \
		(cam->dir_x * sin(ANG) + cam->dir_y * cos(ANG)), -MOVE_SPEED);
	else if (key == KEY_RVIEW)
		rotate(game->camera, ROT_SPEED);
	else if (key == KEY_LVIEW)
		rotate(game->camera, -ROT_SPEED);
	return (0);
}
