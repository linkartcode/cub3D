// create init read and destroy decor struct
#include "cub3D.h"

// create decor struct and set it to start state
// return decor struct or null if error malloc
t_decor	*decor_init(void)
{
	t_decor	*decor;

	decor = malloc(sizeof(t_decor));
	if (decor)
	{
		decor->south_wall_texture = NULL;
		decor->north_wall_texture = NULL;
		decor->east_wall_texture = NULL;
		decor->west_wall_texture = NULL;
		decor->set_ceiling = FT_FALSE;
		decor->set_floor = FT_FALSE;
	}
	return (decor);
}

// checks decor struct for full complete
static int	check_decor(t_decor *dec)
{
	return (dec->south_wall_texture && dec->north_wall_texture \
			&& dec->east_wall_texture && dec->west_wall_texture \
			&& dec->set_ceiling && dec->set_floor);
}

// read mapfile and fill decor fields
// return true if full fill and false if not
int	decor_read(t_decor *dec, int fd, void *mlx)
{
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		decor_fill(str, dec, mlx);
		free(str);
		if (check_decor(dec))
			break ;
		str = get_next_line(fd);
	}
	return (check_decor(dec));
}

// destroys decor struct
void	decor_destroy(t_decor **decor, void *mlx)
{
	if (!decor)
		return ;
	buffer_destroy(&(*decor)->south_wall_texture, mlx);
	buffer_destroy(&(*decor)->north_wall_texture, mlx);
	buffer_destroy(&(*decor)->west_wall_texture, mlx);
	buffer_destroy(&(*decor)->east_wall_texture, mlx);
	free (*decor);
}
