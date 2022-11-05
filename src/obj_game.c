/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:19:48 by nmordeka          #+#    #+#             */
/*   Updated: 2022/09/15 08:18:50 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	game_destroy(t_game **game)
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

int	create_game(t_game *game)
{
	game->dda = malloc(sizeof(t_dda));
	if (!(game->dda))
		return (FT_FALSE);
	game->decor = init_decor();
	if (!(game->decor))
		return (FT_FALSE);
	game->map_obj = malloc(sizeof(t_map));
	if (!(game->map_obj))
		return (FT_FALSE);
	game->camera = malloc(sizeof(t_camera));
	if (!(game->camera))
		return (FT_FALSE);
	game->map_obj->map = NULL;
	game->buffer = NULL;
	game->win = NULL;
	game->mlx = NULL;
	return (FT_TRUE);
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
	ft_putnbr_fd(game->map_obj->width, 1);
	ft_putstr_fd(" , height = ", 1);
	ft_putnbr_fd(game->map_obj->height, 1);
	ft_putchar_fd('\n', 1);
	i = -1;
	while (++i < game->map_obj->height)
		ft_putendl_fd(game->map_obj->map[i], 1);
}

void	game_init(t_game *game, int fd)
{
	if (!create_game(game))
		game_over(game, "No enought mamory for game!", 4, fd);
	game->mlx = mlx_init();
	if (!game->mlx)
		game_over(game, "Can't init MLX lib", 5, fd);
	game->buffer = init_buf(game->mlx, WIN_W, WIN_H, NULL);
	if (!game->buffer)
		game_over(game, "Can't create screen buffer", 6, fd);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		game_over(game, "Can't init graphical window", 7, fd);
	if (!read_decor(game->decor, fd, game->mlx))
		game_over(game, "Invalid textures or colors in map", 8, fd);
	if (!map_create(game->map_obj, fd))
		game_over(game, "No enought mamory for map!", 9, fd);
	close (fd);
	if (!camera_create(game))
		game_over(game, "Start position error", 10, 0);
	if (!check_map(game->map_obj))
		game_over(game, NULL, 11, 0);
	game_print(game);
}
