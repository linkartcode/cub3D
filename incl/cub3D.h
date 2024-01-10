// main header file
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <string.h>
# include <stdio.h>
# include <math.h>

//Symbols for start position on map
//difines player's face direction 
# define SYM_WEST		'W'
# define SYM_EAST		'E'
# define SYM_SOUTH	'S'
# define SYM_NORTH	'N'

// Defines symbols of map
# define SYM_WALL		'1'
# define SYM_EMPTY	'0'
# define SYM_SPACE	' '

// keyboard definitions
// keys for moves
# define KEY_UP		13
# define KEY_DOWN		1
# define KEY_LEFT		0
# define KEY_RIGHT	2

// keys for turns to left / right
# define KEY_LVIEW	123
# define KEY_RVIEW	124

// key for exit
# define KEY_ESC		53

// resolution of window
# define WIN_W			1024
# define WIN_H			768

// defines for calculation of moving 
# define ANGLE			0.66		// angle of view
# define ANG			1.5708
# define MOVE_SPEED	0.15
# define ROT_SPEED	0.06

// defines types
// just simple int position
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// simple int rectangle
typedef struct s_rect
{
	t_point	base;
	int		w;
	int		h;
}	t_rect;

// buffer struct for sprite output 
typedef struct s_buffer
{
	void	*data;
	char	*addr;
	int	w;
	int	h;
	int	size_line;
	int	bits_per_pixel;
	int	endian;
}	t_buffer;

// struct contains textures for wall 
// different for south, north... ect.
// colors for ceiling and floor
typedef struct s_decor
{
	t_buffer	*south_wall_texture;
	t_buffer	*north_wall_texture;
	t_buffer	*east_wall_texture;
	t_buffer	*west_wall_texture;
	int		ceiling_color;
	int		floor_color;
	int		set_ceiling;
	int		set_floor;
}	t_decor;

// struct for view calculations
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

// struct provides algoritm of dda
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

// just map
typedef struct s_map
{
	int	width;
	int	height;
	char	**map;
}	t_map;

// main sruct contains almoust all previous
// mlx - provides minilibx lib
// win - support game window
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_camera	*camera;
	t_buffer	*buffer;
	t_dda		*dda;
	t_decor	*decor;
	t_map		*map_obj;
}	t_game;

// functions

//void	game_char_print(t_game *game); //debug function
void		game_init(t_game *game, int fd);
int		game_move(int key, t_game *game);
void		game_draw_line(int x, t_game *game);
int		game_draw(t_game *game);
void		game_over(t_game *game, char *err_mess, int code, int fd);

t_decor	*decor_init(void);
void		decor_fill(char *str, t_decor *decor, void *mlx);
int		decor_read(t_decor *decor, int fd, void *mlx);
void		decor_destroy(t_decor **decor, void *mlx);

int		camera_create(t_game *game);

int		map_create(t_map *map, int fd);
int		map_check(t_map *map);
void		map_destroy(t_map **map);

t_buffer	*buffer_init(void *mlx, int width, int height, char *path);
void		buffer_destroy(t_buffer **buffer, void *mlx);

void		put_pixel(t_buffer *buffer, int x, int y, int color);
void		draw_line(int x, int length, char view, t_game *game);

#endif