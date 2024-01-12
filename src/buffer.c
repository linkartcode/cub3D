// functions for init and destroyed screen buffer
#include "cub3D.h"

// skips start spaces and return position of the first path symbol
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

// init buffer of texture width x height from path
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

//destroyes buffer
void	buffer_destroy(t_buffer **buffer, void *mlx)
{
	if (!(*buffer))
		return ;
	if ((*buffer)->data)
		mlx_destroy_image(mlx, (*buffer)->data);
	free(*buffer);
}
