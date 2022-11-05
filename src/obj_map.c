/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:02:54 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/14 08:27:48 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	str_empty(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (i == ft_strlen(str))
		return (FT_TRUE);
	return (FT_FALSE);
}

char	*skip_empty(int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str && str_empty(str))
	{
		free(str);
		str = get_next_line(fd);
	}
	if (!str)
		return (NULL);
	return (str);
}

void	map_destroy(t_map **map)
{
	int	y;
	int	y_max;

	if (!(*map))
		return ;
	y = -1;
	y_max = (*map)->height;
	while (++y < y_max)
		free((*map)->map[y]);
	free((*map));
}

int	map_fill(t_map *map)
{
	char	*str;
	int		h;

	if (!map)
		return (FT_FALSE);
	map->width--;
	h = -1;
	while (map->map[++h])
	{
		if ((int)ft_strlen(map->map[h]) < map->width)
		{
			str = malloc(map->width + 1);
			ft_memset(str, SYM_SPACE, map->width);
			ft_memcpy(str, map->map[h], ft_strlen(map->map[h]));
			str[map->width] = '\0';
			free(map->map[h]);
			map->map[h] = str;
		}
	}
	map->height = h;
	return (FT_TRUE);
}

int	map_create(t_map *map, int fd)
{
	char	*str;
	char	*new_str;
	char	*tmp_str;

	str = skip_empty(fd);
	if (!str)
		return (FT_FALSE);
	map->width = ft_strlen(str);
	new_str = get_next_line(fd);
	while (new_str && !str_empty(new_str))
	{
		if ((int)ft_strlen(new_str) > map->width)
			map->width = ft_strlen(new_str);
		tmp_str = ft_strjoin(str, new_str);
		free(new_str);
		free(str);
		str = tmp_str;
		new_str = get_next_line(fd);
	}
	if (!new_str)
		map->map = ft_split(str, '\n');
	else
		free(new_str);
	free(str);
	return (map_fill(map));
}
