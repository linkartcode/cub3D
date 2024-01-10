// some functions to check map
#include "cub3D.h"

// checks one row of the map for invalid symbols
static int	is_str_valid(char *checked_str)
{
	char	ch;
	int	i;

	i = -1;
	while (checked_str[++i])
	{
		ch = checked_str[i];
		if (!(ch == SYM_WALL || ch == SYM_EMPTY || ch == SYM_SPACE))
			return (FT_FALSE);
	}
	return (FT_TRUE);
}

// checks position next to px, py for empty space
// returns true if there is empty space, and false if not
static int	is_space_next(int px, int py, t_map *map)
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

// cheks map for closed or not
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
			if (map->map[y][x] == SYM_EMPTY && is_space_next(x, y, map))
				return (FT_FALSE);
		}
	}
	return (FT_TRUE);
}

// check map for invalid symbols and closed
int	map_check(t_map *map)
{
	int	height;
	int	is_valid;

	is_valid = FT_TRUE;
	height = -1;
	while (++height < map->height)
	{
		if (!is_str_valid(map->map[height]))
		{
			ft_putendl_fd("Error! Invalid symbols on map!", 1);
			is_valid = FT_FALSE;
			break ;
		}
	}
	if (is_valid && !check_closed(map))
	{
		ft_putendl_fd("Error! The map is not closed!", 1);
		is_valid = FT_FALSE;
	}
	return (is_valid);
}
