/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:17:10 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/13 13:10:28 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_path(char *path)
{
	int			i;
	int			j;

	i = 0;
	while (path[i] != '\0' && path[i] == ' ')
		++i;
	j = i;
	while (path[j] != '\0' && path[j] != ' ' && path[j] != '\n')
		++j;
	if (path[j] != '\0')
		path[j] = '\0';
	return (i);
}

t_buffer	*buffer_init(void *mlx, int width, int height, char *path)
{
	t_buffer	*res;
	int			i;

	res = malloc(sizeof(t_buffer));
	if (!res)
		return (res);
	if (path != NULL)
	{
		i = check_path(path);
		res->data = mlx_xpm_file_to_image(mlx, &path[i], &res->w, &res->h);
		if (!(res->data))
		{
			free(res);
			return (NULL);
		}
	}
	else
	{
		res->data = mlx_new_image(mlx, width, height);
		res->w = width;
		res->h = height;
	}
	res->addr = mlx_get_data_addr(res->data, &res->bits_per_pixel, \
			&res->size_line, &res->endian);
	return (res);
}

void	buffer_destroy(t_buffer **buffer, void *mlx)
{
	if (!(*buffer))
		return ;
	if ((*buffer)->data)
		mlx_destroy_image(mlx, (*buffer)->data);
	free(*buffer);
}
