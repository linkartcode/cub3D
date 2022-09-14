/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_buffer_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 00:18:10 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/12 13:13:20 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	buf_put_pixel(t_buffer *buffer, int x, int y, int color)
{
	char	*dest;

	dest = buffer->addr + (y * buffer->size_line + x * \
		(buffer->bits_per_pixel / 8));
	*(unsigned int *) dest = color;
}

unsigned int	buf_get_pixel(t_buffer *buff, int x, int y)
{
	unsigned int	color;
	char			*dest;

	dest = buff->addr + (y * buff->size_line + x * (buff->bits_per_pixel / 8));
	color = *(unsigned int *) dest;
	return (color);
}

static void	buf_clear(t_buffer *buffer, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < buffer->h)
	{
		x = -1;
		while (++x < buffer->w)
			buf_put_pixel(buffer, x, y, color);
	}
}

static void	buf_fill_rect(t_buffer *buffer, t_rect rect, int color)
{
	int	x;
	int	y;

	if (rect.base.x < 0)
		rect.base.x = 0;
	if (rect.base.y < 0)
		rect.base.y = 0;
	if (rect.w >= buffer->w)
		rect.w = buffer->w;
	if (rect.h >= buffer->h)
		rect.h = buffer->h;
	y = rect.base.y - 1;
	while (++y < (rect.base.y + rect.h))
	{
		x = rect.base.x - 1;
		while (++x < (rect.base.x + rect.w))
			buf_put_pixel(buffer, x, y, color);
	}
}

int	draw_buffer(t_game	*game)
{
	int		x;
	t_rect	rect;

	mlx_clear_window(game->mlx, game->win);
	buf_clear(game->buffer, 0);
	rect.base.x = 0;
	rect.base.y = 0;
	rect.w = WIN_W;
	rect.h = WIN_H / 2 - 1;
	buf_fill_rect(game->buffer, rect, game->decor->ceiling);
	rect.base.y = WIN_H / 2;
	rect.h = WIN_H / 2 - 1;
	buf_fill_rect(game->buffer, rect, game->decor->floor);
	x = -1;
	while (++x < WIN_W)
		print_line(x, game);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer->data, 0, 0);
	return (0);
}
