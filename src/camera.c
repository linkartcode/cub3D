// camera functions
#include "cub3D.h"

// set camera directions and planes according the start position
static void	set_angle(t_camera *cam, char view)
{
	if (view == 'N')
	{
		cam->dir_y = -1;
		cam->plane_x = 1 * cam->angle_view;
	}
	else if (view == 'S')
	{
		cam->dir_y = 1;
		cam->plane_x = -1 * cam->angle_view;
	}
	else if (view == 'W')
	{
		cam->dir_x = -1;
		cam->plane_y = -1 * cam->angle_view;
	}
	else
	{
		cam->dir_x = 1;
		cam->plane_y = 1 * cam->angle_view;
	}
}

// sets all camera properties
static void	camera_init(t_camera *camera, int x, int y, char view)
{
	camera->pos_x = (double) x;
	camera->pos_y = (double) y;
	camera->dir_x = 0;
	camera->dir_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 0;
	camera->angle_view = ANGLE;
	set_angle(camera, view);
}

// analises the map and init camera, if find start point
// start point: W - looks at west, E - at east, S - south, N - north
// return true if success, false if not
int	camera_create(t_game *game)
{
	int		x;
	int		y;
	char	ch;

	y = -1;
	while (++y < game->map_obj->height)
	{
		x = -1;
		while (++x < game->map_obj->width)
		{
			ch = game->map_obj->map[y][x];
			if (ch == 'W' || ch == 'E' || ch == 'S' || ch == 'N')
			{
				game->map_obj->map[y][x] = SYM_EMPTY;
				camera_init(game->camera, x, y, ch);
				return (FT_TRUE);
			}
		}
	}
	return (FT_FALSE);
}
