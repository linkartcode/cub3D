/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 07:40:59 by nmordeka          #+#    #+#             */
/*   Updated: 2022/07/12 11:23:45 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	get_hit_view(int side, int step_x, int step_y)
{
	if (side)
	{
		if (step_y < 0)
			return ('N');
		else
			return ('S');
	}
	if (step_x < 0)
		return ('W');
	else
		return ('E');
}

void	set_steps(t_dda *dda, t_camera *cam)
{
	if (dda->ray_dirx < 0)
	{
		dda->step_x = -1;
		dda->side_distx = (cam->pos_x - dda->map_x) * dda->delta_distx;
	}
	else
	{
		dda->step_x = 1;
		dda->side_distx = (dda->map_x + 1.0 - cam->pos_x) * dda->delta_distx;
	}
	if (dda->ray_diry < 0)
	{
		dda->step_y = -1;
		dda->side_disty = (cam->pos_y - dda->map_y) * dda->delta_disty;
	}
	else
	{
		dda->step_y = 1;
		dda->side_disty = (dda->map_y + 1.0 - cam->pos_y) * dda->delta_disty;
	}
}

void	setup_dda(int x, t_dda *dda, t_camera *cam)
{
	double	cam_x;

	cam_x = 2 * x / (double)(WIN_W - 1) - 1;
	dda->ray_dirx = cam->dir_x + cam->plane_x * cam_x;
	dda->ray_diry = cam->dir_y + cam->plane_y * cam_x;
	dda->map_x = (int)cam->pos_x;
	dda->map_y = (int)cam->pos_y;
	if (dda->ray_dirx == 0.00000)
		dda->delta_distx = 1e30;
	else
		dda->delta_distx = fabs(1 / dda->ray_dirx);
	if (dda->ray_diry == 0.00000)
		dda->delta_disty = 1e30;
	else
		dda->delta_disty = fabs(1 / dda->ray_diry);
	set_steps(dda, cam);
}

void	exec_dda(t_dda *dda, t_game *game)
{
	int		hit;
	char	ch;

	hit = 0;
	while ((hit == 0) && (dda->map_x >= 0) && (dda->map_y >= 0) && \
		(dda->map_x < game->width) && (dda->map_y < game->height))
	{
		if (dda->side_distx < dda->side_disty)
		{
			dda->side_distx += dda->delta_distx;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_disty += dda->delta_disty;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		ch = game->map[dda->map_y][dda->map_x];
		if (ch != SYM_EMPTY)
			hit = 1;
	}
}

void	print_line(int x, t_game *game)
{
	char	view;
	int		line_height;
	t_dda	*dda;

	dda = game->dda;
	setup_dda(x, dda, game->camera);
	exec_dda(dda, game);
	if (dda->side == 0)
		dda->dist_perpw = (dda->side_distx - dda->delta_distx);
	else
		dda->dist_perpw = (dda->side_disty - dda->delta_disty);
	line_height = (int)(WIN_H / dda->dist_perpw);
	view = get_hit_view(dda->side, dda->step_x, dda->step_y);
	draw_line(x, line_height, view, game);
}
