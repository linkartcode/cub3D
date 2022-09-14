/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:29:02 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/13 10:21:09 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_camera	*create_camera(int x, int y)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (camera)
	{
		camera->pos_x = (double) x;
		camera->pos_y = (double) y;
		camera->dir_x = 0;
		camera->dir_y = 0;
		camera->plane_x = 0;
		camera->plane_y = 0;
		camera->angle_view = ANGLE;
	}
	return (camera);
}

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

static t_camera	*camera_init(int x, int y, char view)
{
	t_camera	*res;

	res = create_camera(x, y);
	if (res)
		set_angle(res, view);
	return (res);
}

void	read_start_pos(t_game *game)
{
	int		x;
	int		y;
	char	ch;

	if (!game->map)
		return ;
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			ch = game->map[y][x];
			if (ch == 'W' || ch == 'E' || ch == 'S' || ch == 'N')
			{
				game->camera = camera_init(x, y, ch);
				if (game->camera)
					game->map[y][x] = SYM_EMPTY;
				return ;
			}
		}
	}
}
