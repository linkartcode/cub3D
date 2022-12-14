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

static int	next_space(int px, int py, t_map *map)
{
	int	x;
	int	y;

	y = py - 2;
	while (++y < (py + 2))
	{
		x = px - 2;
		while (++x < (px + 2))
		{
			if ((x >= 0 && x < map->width && y >= 0 && y < map->height) \
				&& (x != px && y != py) && map->map[y][x] == SYM_SPACE)
				return (FT_TRUE);
		}
	}
	return (FT_FALSE);
}

static int	check_closed(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->map[y][x] == SYM_EMPTY && next_space(x, y, map))
				return (FT_FALSE);
		}
	}
	return (FT_TRUE);
}

int	map_check(t_map *map)
{
	int	height;

	ft_putendl_fd("Checking Map...", 1);
	height = -1;
	while (++height < map->height)
		if (!is_str_valid("01 ", map->map[height]))
			return (print_message("Error! Invalid symbols on map!"));
	if (!check_closed(map))
		return (print_message("Error! The map is not closed!"));
	return (FT_TRUE);
}
