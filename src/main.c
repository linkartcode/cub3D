/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:16:14 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/14 13:15:25 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	game_over(t_game *game, char *err_mess, int code, int fd)
{
	game_destroy(&game);
	if (fd > 0)
		close (fd);
	if (err_mess)
		ft_putendl_fd(err_mess, 1);
	exit(code);
}

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

int	main(int argc, char **argv)
{
	int		fd;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		game_over(game, "Memory allocation error", 99, 0);
	game_reset(game);
	if (argc != 2)
		game_over(game, "Program needs one parameter with cub ext", 1, 0);
	if (not_cub_ext(argv[1]))
		game_over(game, "Parameter hasn't .cub extention", 2, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		game_over(game, "File read error", 3, 0);
	game_init(game, fd);
	ft_putendl_fd("File OK", 1);
	mlx_hook(game->win, 17, 0, close_win_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop_hook(game->mlx, game_draw, game);
	mlx_loop(game->mlx);
	game_over(game, "Normal", 0, fd);
	return (0);
}
