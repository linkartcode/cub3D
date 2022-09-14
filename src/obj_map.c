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

void	fill_map(t_game *game)
{
	char	*str;
	int		h;

	if (!game->map)
		return ;
	game->width--;
	h = -1;
	while (game->map[++h])
	{
		if ((int)ft_strlen(game->map[h]) < game->width)
		{
			str = malloc(game->width + 1);
			ft_memset(str, SYM_SPACE, game->width);
			ft_memcpy(str, game->map[h], ft_strlen(game->map[h]));
			str[game->width] = '\0';
			free(game->map[h]);
			game->map[h] = str;
		}
	}
	game->height = h;
}

void	read_map(t_game *game, int fd)
{
	char	*str;
	char	*new_str;
	char	*tmp_str;

	str = skip_empty(fd);
	if (!str)
		return ;
	game->width = ft_strlen(str);
	new_str = get_next_line(fd);
	while (new_str && !str_empty(new_str))
	{
		if ((int)ft_strlen(new_str) > game->width)
			game->width = ft_strlen(new_str);
		tmp_str = ft_strjoin(str, new_str);
		free(new_str);
		free(str);
		str = tmp_str;
		new_str = get_next_line(fd);
	}
	if (!new_str)
		game->map = ft_split(str, '\n');
	else
		free(new_str);
	free(str);
	fill_map(game);
}

void	free_map(t_game *game)
{
	int	y;

	if (game->map)
	{
		y = -1;
		while (++y < game->height)
			free(game->map[y]);
		free(game->map);
	}
}
