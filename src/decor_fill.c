// functions for fill decor struct
#include "cub3D.h"

// frees color arr
static int	clear_arr(char **color_arr)
{
	int	i;

	if (color_arr)
	{
		i = -1;
		while (color_arr[++i])
			free (color_arr[i]);
		free (color_arr);
	}
	return (FT_FALSE);
}

// checks code of color
static int	check_arr(char	**color_arr)
{
	int	i;
	int	j;

	i = -1;
	while (color_arr[++i])
	{
		j = -1;
		while (color_arr[i][++j])
			if (!(ft_isdigit(color_arr[i][j])) && (color_arr[i][j] != '\n'))
				return (FT_FALSE);
	}
	if (i != 3)
		return (FT_FALSE);
	return (FT_TRUE);
}

// parsers colors of floor and ceiling
static int	ft_pars_color(char type, char *str, t_decor *decor)
{
	char	**color_arr;
	int		r;
	int		g;
	int		b;

	color_arr = ft_split(str, ',');
	if (!color_arr)
		return (FT_FALSE);
	if (!check_arr(color_arr))
		return (clear_arr(color_arr));
	r = ft_atoi(color_arr[0]);
	g = ft_atoi(color_arr[1]);
	b = ft_atoi(color_arr[2]);
	clear_arr(color_arr);
	if (r > 255 || g > 255 || b > 255)
		return (FT_FALSE);
	if (type == 'F')
		decor->floor_color = (r << 16 | g << 8 | b);
	else
		decor->ceiling_color = (r << 16 | g << 8 | b);
	return (FT_TRUE);
}

// fills textures of decor
static void	fill_texture(char type, char *str, t_decor *decor, void *mlx)
{
	if (type == 'S' && !(decor->south_wall_texture))
		decor->south_wall_texture = buffer_init(mlx, 0, 0, str);
	else if (type == 'N' && !(decor->north_wall_texture))
		decor->north_wall_texture = buffer_init(mlx, 0, 0, str);
	else if (type == 'E' && !(decor->east_wall_texture))
		decor->east_wall_texture = buffer_init(mlx, 0, 0, str);
	else if (type == 'W' && !(decor->west_wall_texture))
		decor->west_wall_texture = buffer_init(mlx, 0, 0, str);
}

// analises str and fill fields of decor
void	decor_fill(char *str, t_decor *decor, void *mlx)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n' && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return ;
	if (str[i] == 'F' && str[i + 1] == ' ' && !decor->set_floor)
		decor->set_floor = ft_pars_color('F', &str[i + 2], decor);
	else if (str[i] == 'C' && str[i + 1] == ' ' && !decor->set_ceiling)
		decor->set_ceiling = ft_pars_color('C', &str[i + 2], decor);
	else if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		fill_texture('N', &str[i + 3], decor, mlx);
	else if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		fill_texture('S', &str[i + 3], decor, mlx);
	else if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		fill_texture('W', &str[i + 3], decor, mlx);
	else if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		fill_texture('E', &str[i + 3], decor, mlx);
}
