// full circle game struct
#include "cub3D.h"

// frees all memory allocated for game and it's parts
static void	game_destroy(t_game **game)
{
	if (!(*game))
		return ;
	map_destroy(&(*game)->map_obj);
	decor_destroy(&(*game)->decor, (*game)->mlx);
	buffer_destroy(&(*game)->buffer, (*game)->mlx);
	if ((*game)->dda)
		free((*game)->dda);
	if ((*game)->camera)
		free((*game)->camera);
	if ((*game)->win)
		mlx_destroy_window((*game)->mlx, (*game)->win);
	if ((*game)->mlx)
		free((*game)->mlx);
	free(*game);
}

// Exit game :
// 1 - Destroy game struct
// 2 - Close fd file descripter
// 3 - Print err_mess
// 4 - Exit with code
void	game_over(t_game *game, char *err_mess, int code, int fd)
{
	game_destroy(&game);
	if (fd > 0)
		close (fd);
	if (err_mess)
		ft_putendl_fd(err_mess, 1);
	exit(code);
}

// set to NULL all fields
static void	game_set_null(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->camera = NULL;
	game->buffer = NULL;
	game->dda = NULL;
	game->decor = NULL;
	game->map_obj = NULL;
}

// allocates memory for all complicated parts of game
int	create_game(t_game *game)
{
	game_set_null(game);
	game->dda = malloc(sizeof(t_dda));
	if (!(game->dda))
		return (FT_FALSE);
	game->decor = decor_init();
	if (!(game->decor))
		return (FT_FALSE);
	game->map_obj = malloc(sizeof(t_map));
	if (!(game->map_obj))
		return (FT_FALSE);
	game->camera = malloc(sizeof(t_camera));
	if (!(game->camera))
		return (FT_FALSE);
	return (FT_TRUE);
}

// inits game and handles all errors
void	game_init(t_game *game, int fd)
{
	if (!create_game(game))
		game_over(game, "No enought memory for game!", 4, fd);
	game->mlx = mlx_init();
	if (!game->mlx)
		game_over(game, "Can't init MLX lib", 5, fd);
	game->buffer = buffer_init(game->mlx, WIN_W, WIN_H, NULL);
	if (!game->buffer)
		game_over(game, "Can't create screen buffer", 6, fd);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		game_over(game, "Can't init graphical window", 7, fd);
	if (!decor_read(game->decor, fd, game->mlx))
		game_over(game, "Invalid textures or colors in map", 8, fd);
	if (!map_create(game->map_obj, fd))
		game_over(game, "No enought mamory for map!", 9, fd);
	close (fd);
	if (!camera_create(game))
		game_over(game, "Start position error", 10, 0);
	if (!map_check(game->map_obj))
		game_over(game, NULL, 11, 0);
}
