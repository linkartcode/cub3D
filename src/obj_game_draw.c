// main draw functions of the game
#include "cub3D.h"

// fills all screen buffer by color
static void	buf_clear(t_buffer *buffer, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < buffer->h)
	{
		x = -1;
		while (++x < buffer->w)
			put_pixel(buffer, x, y, color);
	}
}

// fills rect by the color
static void	buf_fill_rect(t_buffer *buffer, t_rect rect, int color)
{
	int	x;
	int	y;

	if (rect.base.x < 0)
		rect.base.x = 0;
	if (rect.base.y < 0)
		rect.base.y = 0;
	if (rect.w >= buffer->w)
		rect.w = buffer->w;
	if (rect.h >= buffer->h)
		rect.h = buffer->h;
	y = rect.base.y - 1;
	while (++y < (rect.base.y + rect.h))
	{
		x = rect.base.x - 1;
		while (++x < (rect.base.x + rect.w))
			put_pixel(buffer, x, y, color);
	}
}

// output ceiling, floor and walls on screen
int	game_draw(t_game	*game)
{
	int		x;
	t_rect	rect;

	mlx_clear_window(game->mlx, game->win);
	buf_clear(game->buffer, 0);
	rect.base.x = 0;
	rect.base.y = 0;
	rect.w = WIN_W;
	rect.h = WIN_H / 2 - 1;
	buf_fill_rect(game->buffer, rect, game->decor->ceiling_color);
	rect.base.y = WIN_H / 2;
	rect.h = WIN_H / 2 - 1;
	buf_fill_rect(game->buffer, rect, game->decor->floor_color);
	x = -1;
	while (++x < WIN_W)
		game_draw_line(x, game);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer->data, 0, 0);
	return (0);
}

// prints game on consol in chars - debugging helper
void	game_char_print(t_game *game)
{
	int	i;

	ft_putendl_fd("Game.", 1);
	ft_putendl_fd("Player:", 1);
	ft_putstr_fd("X = ", 1);
	ft_putnbr_fd((int)game->camera->pos_x, 1);
	ft_putstr_fd(" , Y = ", 1);
	ft_putnbr_fd((int)game->camera->pos_y, 1);
	ft_putstr_fd("\nCeiling color = ", 1);
	ft_putnbr_fd(game->decor->ceiling_color, 1);
	ft_putstr_fd("\nFloor color = ", 1);
	ft_putnbr_fd(game->decor->floor_color, 1);
	ft_putendl_fd("\nMap.", 1);
	ft_putstr_fd("width = ", 1);
	ft_putnbr_fd(game->map_obj->width, 1);
	ft_putstr_fd(" , height = ", 1);
	ft_putnbr_fd(game->map_obj->height, 1);
	ft_putchar_fd('\n', 1);
	i = -1;
	while (++i < game->map_obj->height)
		ft_putendl_fd(game->map_obj->map[i], 1);
}
