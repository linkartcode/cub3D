/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:19:48 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/14 13:40:51 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <string.h>
# include <stdio.h>
# include <math.h>

# define SYM_WEST		'W'
# define SYM_EAST		'E'
# define SYM_SOUTH		'S'
# define SYM_NORTH		'N'
# define SYM_WALL		'1'
# define SYM_EMPTY		'0'
# define SYM_SPACE		' '

# define KEY_UP			13
# define KEY_DOWN		1
# define KEY_LEFT		0
# define KEY_RIGHT		2

# define KEY_LVIEW		123
# define KEY_RVIEW		124

# define KEY_ESC		53

# define WIN_W			1024
# define WIN_H			768

# define ANGLE			0.66
# define ANG			1.5708

# define MOVE_SPEED		0.15
# define ROT_SPEED		0.06

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_rect
{
	t_point	base;
	int		w;
	int		h;
}	t_rect;

typedef struct s_buffer
{
	void	*data;
	char	*addr;
	int		w;
	int		h;
	int		size_line;
	int		bits_per_pixel;
	int		endian;
}	t_buffer;

typedef struct s_decor
{
	t_buffer	*south;
	t_buffer	*north;
	t_buffer	*east;
	t_buffer	*west;
	int			ceiling;
	int			set_ceiling;
	int			floor;
	int			set_floor;
}	t_decor;

typedef struct s_camera
{
	double	angle_view;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_camera;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	ray_dirx;
	double	ray_diry;
	double	side_distx;
	double	side_disty;
	double	delta_distx;
	double	delta_disty;
	double	dist_perpw;
	double	step;
	int		texx;
	int		texy;
	double	tex_pos;
}	t_dda;

typedef struct s_map
{
	int			width;
	int			height;
	char		**map;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_camera	*camera;
	t_buffer	*buffer;
	t_dda		*dda;
	t_decor		*decor;
	t_map		*map_obj;
}	t_game;

void			game_over(t_game *game, char *err_mess, int code, int fd);

t_decor			*init_decor(void);
void			fill_decor(char *str, t_decor *decor, void *mlx);
void			free_decor(t_decor *decor, void *mlx);
int				read_decor(t_decor *decor, int fd, void *mlx);
void			decor_destroy(t_decor **decor, void *mlx);

void			read_start_pos(t_game *game);
int				camera_create(t_game *game);
void			read_map(t_game *game, int fd);
int				map_create(t_map *map, int fd);
int				check_map(t_map *map);
void			map_destroy(t_map **map);

void			game_destroy(t_game **game);
void			game_init(t_game *game, int fd);
int				player_move(int key, t_game *game);

unsigned int	buf_get_pixel(t_buffer *buff, int x, int y);
void			buf_put_pixel(t_buffer *buffer, int x, int y, int color);
t_buffer		*init_buf(void *mlx, int width, int height, char *path);
void			free_buffer(t_buffer *buffer, void *mlx);
void			buffer_destroy(t_buffer **buffer, void *mlx);

void			draw_vert_tex(int x, int length, t_buffer *text, t_game *game);

void			draw_line(int x, int length, char view, t_game *game);
int				draw_buffer(t_game	*game);

void			print_line(int x, t_game *game);

int				str_empty(char *str);

#endif