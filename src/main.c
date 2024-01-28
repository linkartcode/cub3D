// v 2.1 (c)2024
#include "cub3D.h"

// checks for cub extention 
static int	not_cub_ext(char *filename)
{
	char	*ext;
	int		result;

	if (!filename || ft_strlen(filename) < 5)
		return (FT_TRUE);
	ext = ft_substr(filename, ft_strlen(filename) - 4, 4);
	if (!ext)
		return (FT_TRUE);
	result = ft_strncmp(ext, ".cub", 4);
	free(ext);
	return (result);
}

// check game params 
static void	check_params(int argc, char *map_file)
{
	int	err_code;

	err_code = 0;
	if (argc != 2)
		err_code = 1;
	else if (not_cub_ext(map_file))
		err_code = 2;
	if (!err_code)
		return ;
	if (err_code == 1)
		ft_putendl_fd("Only one parameter accepted", 1);
	else
		ft_putendl_fd("Parameter has to have 'cub' extention", 1);
	exit(err_code);
}

// handle keyboard input
static int	key_hook(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_over(game, "ESC Exit", 0, 0);
	if (key == KEY_DOWN || key == KEY_UP || key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_LVIEW || key == KEY_RVIEW)
		game_move(key, game);
	return (0);
}

// handle close window event
static int	close_win_hook(t_game *game)
{
	game_over(game, "Close window exit", 0, 0);
	return (0);
}

// main function
int	main(int argc, char **argv)
{
	int		fd;
	t_game	*game;

	check_params(argc, argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Can't open file of map", 1);
		exit(3);
	}
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		game_over(game, "Memory allocation error", 99, fd);
	game_init(game, fd);
	mlx_hook(game->win, 17, 0, close_win_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop_hook(game->mlx, game_draw, game);
	mlx_loop(game->mlx);
	game_over(game, "Normal", 0, fd);
	return (0);
}
