/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:19:48 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/14 13:41:34 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	game_exit(t_game *game, char *err_mess, int code, int fd)
{
	if (game)
	{
		if (game->map)
			free_map(game);
		if (game->decor)
			free_decor(game->decor, game->mlx);
		if (game->buffer)
			free_buffer(game->buffer, game->mlx);
		if (game->dda)
			free(game->dda);
		if (game->camera)
			free(game->camera);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
			free(game->mlx);
		if (game->win)
			free(game->win);
		free(game);
	}	
	if (fd > 0)
		close (fd);
	if (err_mess)
		ft_putendl_fd(err_mess, 1);
	exit(code);
}

t_game	*create_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->dda = malloc(sizeof(t_dda));
	if (!(*game).dda)
		return (NULL);
	game->decor = init_decor();
	if (!(*game).decor)
		return (NULL);
	game->camera = NULL;
	game->buffer = NULL;
	game->win = NULL;
	game->map = NULL;
	return (game);
}

void	game_print(t_game *game)
{
	int	i;

	ft_putendl_fd("Game.", 1);
	ft_putendl_fd("Player:", 1);
	ft_putstr_fd("X = ", 1);
	ft_putnbr_fd((int)game->camera->pos_x, 1);
	ft_putstr_fd(" , Y = ", 1);
	ft_putnbr_fd((int)game->camera->pos_y, 1);
	ft_putstr_fd("\nCeiling color = ", 1);
	ft_putnbr_fd(game->decor->ceiling, 1);
	ft_putstr_fd("\nFloor color = ", 1);
	ft_putnbr_fd(game->decor->floor, 1);
	ft_putendl_fd("\nMap.", 1);
	ft_putstr_fd("width = ", 1);
	ft_putnbr_fd(game->width, 1);
	ft_putstr_fd(" , height = ", 1);
	ft_putnbr_fd(game->height, 1);
	ft_putchar_fd('\n', 1);
	i = -1;
	while (++i < game->height)
		ft_putendl_fd(game->map[i], 1);
}

t_game	*game_init(int fd)
{
	t_game	*game;

	game = create_game();
	if (!game)
		game_exit(game, "No enought mamory for game!", 4, fd);
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(game, "Can't init MLX lib", 5, fd);
	game->buffer = init_buf(game->mlx, WIN_W, WIN_H, NULL);
	if (!game->buffer)
		game_exit(game, "Can't create screen buffer", 6, fd);
	
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		game_exit(game, "Can't init graphical window", 7, 0);
	if (!read_decor(game->decor, fd, game->mlx))
		game_exit(game, "Invalid textures or colors in map", 8, fd);
	read_map(game, fd);
	if (!game->map)
		game_exit(game, "No enought mamory for map!", 9, fd);
	close (fd);
	read_start_pos(game);
	if (!check_map(game))
		game_exit(game, NULL, 10, 0);
	game_print(game);
	return (game);
}
