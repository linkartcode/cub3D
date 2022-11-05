/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_decor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:07:35 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/13 13:10:47 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_decor	*init_decor(void)
{
	t_decor	*decor;

	decor = malloc(sizeof(t_decor));
	if (decor)
	{
		decor->south = NULL;
		decor->north = NULL;
		decor->east = NULL;
		decor->west = NULL;
		decor->set_ceiling = FT_FALSE;
		decor->set_floor = FT_FALSE;
	}
	return (decor);
}

int	read_decor(t_decor *dec, int fd, void *mlx)
{
	char	*str;

	ft_putendl_fd("Read Decor", 1);
	str = get_next_line(fd);
	while (str)
	{
		fill_decor(str, dec, mlx);
		free(str);
		if (dec->south && dec->north && dec->east && dec->west \
			&& dec->set_ceiling && dec->set_floor)
			break ;
		str = get_next_line(fd);
	}
	return (dec->south && dec->north && dec->east && dec->west \
			&& dec->set_ceiling && dec->set_floor);
}

void	free_decor(t_decor *decor, void *mlx)
{
	if (!decor)
		return ;
	free_buffer(decor->south, mlx);
	free_buffer(decor->north, mlx);
	free_buffer(decor->east, mlx);
	free_buffer(decor->west, mlx);
	free (decor);
}

void	decor_destroy(t_decor **decor, void *mlx)
{
	if (!(*decor))
		return ;
	buffer_destroy(&(*decor)->south, mlx);
	buffer_destroy(&(*decor)->north, mlx);
	buffer_destroy(&(*decor)->west, mlx);
	buffer_destroy(&(*decor)->east, mlx);
	free (*decor);
}
