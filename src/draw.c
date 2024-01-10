// low level functions to draw graphics
#include "cub3D.h"

// returns color of pixel x.y
static unsigned int	buf_get_pixel(t_buffer *buff, int x, int y)
{
	unsigned int	color;
	char			*dest;

	dest = buff->addr + (y * buff->size_line + x * (buff->bits_per_pixel / 8));
	color = *(unsigned int *) dest;
	return (color);
}

// set pixel x,y to color
void	put_pixel(t_buffer *buffer, int x, int y, int color)
{
	char	*dest;

	dest = buffer->addr + (y * buffer->size_line + x * \
		(buffer->bits_per_pixel / 8));
	*(unsigned int *) dest = color;
}

static void	set_dda_tex(t_game *game, t_buffer *tex)
{
	t_dda	*dda;
	double	wallx;

	dda = game->dda;
	if (dda->side == 0)
		wallx = game->camera->pos_y + dda->dist_perpw * dda->ray_diry;
	else
		wallx = game->camera->pos_x + dda->dist_perpw * dda->ray_dirx;
	wallx -= floor(wallx);
	dda->texx = (int)(wallx * (double)tex->w);
	if (dda->side == 0 && dda->ray_dirx > 0)
		dda->texx = tex->w - dda->texx - 1;
	if (dda->side == 1 && dda->ray_diry < 0)
		dda->texx = tex->w - dda->texx - 1;
}

// draw vert line of texture
static void	draw_vert_tex(int x, int length, t_buffer *tex, t_game *game)
{
	int				start;
	int				end;
	int				y;
	unsigned int	color;

	start = -length / 2 + WIN_H / 2;
	if (start < 0)
		start = 0;
	end = length / 2 + WIN_H / 2;
	if (end >= WIN_H)
		end = WIN_H - 1;
	set_dda_tex(game, tex);
	game->dda->step = 1.0 * tex->h / length;
	game->dda->tex_pos = (start - WIN_H / 2 + length / 2) * game->dda->step;
	y = start - 1;
	while (++y < end)
	{
		game->dda->texy = (int) game->dda->tex_pos & (tex->h - 1);
		game->dda->tex_pos += game->dda->step;
		color = buf_get_pixel(tex, game->dda->texx, game->dda->texy);
		put_pixel(game->buffer, x, y, color);
	}
}

// select texture and draw according line
void	draw_line(int x, int length, char view, t_game *game)
{
	t_buffer	*texture;

	if (view == 'S')
		texture = game->decor->south_wall_texture;
	else if (view == 'N')
		texture = game->decor->north_wall_texture;
	else if (view == 'W')
		texture = game->decor->west_wall_texture;
	else
		texture = game->decor->east_wall_texture;
	draw_vert_tex(x, length, texture, game);
}
