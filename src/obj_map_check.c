/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_map_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:49:15 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/14 10:34:19 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	print_message(char *str)
{
	ft_putendl_fd(str, 1);
	return (FT_FALSE);
}

static int	is_str_valid(char *symbols, char *checked_str)
{
	int	i;
	int	j;
	int	find_flag;

	find_flag = FT_FALSE;
	i = -1;
	while (checked_str[++i])
	{
		j = -1;
		while (symbols[++j])
		{
			if (symbols[j] == checked_str[i])
			{
				find_flag = FT_TRUE;
				break ;
			}
		}
		if (!find_flag)
			return (find_flag);
		find_flag = FT_FALSE;
	}
	return (FT_TRUE);
}

static int	next_space(t_point p, char **map, int max_y, int max_x)
{
	int	x;
	int	y;

	y = p.y - 2;
	while (++y < (p.y + 2))
	{
		x = p.x - 2;
		while (++x < (p.x + 2))
		{
			if ((x >= 0 && x < max_x && y >= 0 && y < max_y) \
				&& (x != p.x && y != p.y) && map[y][x] == SYM_SPACE)
				return (FT_TRUE);
		}
	}
	return (FT_FALSE);
}

static int	check_closed(char **map, int h, int w)
{
	t_point	p;

	p.y = -1;
	while (++p.y < h)
	{
		p.x = -1;
		while (++p.x < w)
		{
			if (map[p.y][p.x] == SYM_EMPTY && next_space(p, map, h, w))
				return (FT_FALSE);
		}
	}
	return (FT_TRUE);
}

int	check_map(t_game *game)
{
	int	height;

	ft_putendl_fd("Checking Map", 1);
	if (!game->camera)
		return (print_message("Error! No player position on map."));
	height = -1;
	while (++height < game->height)
		if (!is_str_valid("01 ", game->map[height]))
			return (print_message("Error! Invalid symbols on map!"));
	if (!check_closed(game->map, game->height, game->width))
		return (print_message("Error! The map is not closed!"));
	return (FT_TRUE);
}
