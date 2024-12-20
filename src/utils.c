/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:50:12 by llion             #+#    #+#             */
/*   Updated: 2023/07/16 11:39:25 by llion@student    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_error(char *str)
{
	printf("%s\nExiting...\n", str);
	exit(EXIT_FAILURE);
}

int	free_function(char **file, t_cub *c)
{
	if (c->t)
	{
		if (c->textures[0] != NULL)
			mlx_delete_texture(c->textures[0]);
		if (c->textures[1] != NULL)
			mlx_delete_texture(c->textures[1]);
		if (c->textures[2] != NULL)
			mlx_delete_texture(c->textures[2]);
		if (c->textures[3] != NULL)
			mlx_delete_texture(c->textures[3]);
		free(c->t->no);
		free(c->t->ea);
		free(c->t->so);
		free(c->t->we);
		free(c->textures);
	}
	if (file)
		ft_freetab(file);
	if (c->map)
		ft_freetab(c->map);
	free(c->t);
	free(c);
	return (0);
}

void	init_cub_2(t_cub *c)
{
	c->map_height = ft_tablen(c->map);
	c->map_width = map_width(c->map);
	c->view_ang = 60 * DEFINITION;
	c->tilesize = 64;
	c->tilesize_2d = c->tilesize / 8;
	if (SCREEN_WIDTH < c->view_ang * 1.5)
		c->true_screen_width = c->view_ang;
	else if (SCREEN_WIDTH < c->view_ang * 2.5 && SCREEN_WIDTH >= c->view_ang
		* 1.5)
		c->true_screen_width = c->view_ang * 2;
	else if (SCREEN_WIDTH < c->view_ang * 3.5 && SCREEN_WIDTH >= c->view_ang
		* 2.5)
		c->true_screen_width = c->view_ang * 3;
	else
		c->true_screen_width = c->view_ang * 4;
	c->pause = 0;
	c->rays = ft_calloc(c->view_ang, sizeof(t_rays));
	c->player = ft_calloc(1, sizeof(t_player));
}

int	init_cub(t_cub *c, char **file)
{
	c->nb_line_map_start = get_nb_line_map_start(file);
	c->t = get_textures(c, file);
	if (c->t == NULL)
		return (0);
	c->textures = ft_calloc(sizeof(mlx_texture_t *), 6);
	c->textures[0] = mlx_load_png(c->t->no);
	c->textures[1] = mlx_load_png(c->t->so);
	c->textures[2] = mlx_load_png(c->t->we);
	c->textures[3] = mlx_load_png(c->t->ea);
	if (c->textures[0] == NULL || c->textures[1] == NULL
		|| c->textures[2] == NULL || c->textures[3] == NULL)
		return (ft_error("Missing Texture"));
	c->textures[4] = mlx_load_png("./textures/door.png");
	c->t_exit = load_texture_anim();
	c->map = get_map(file, c->nb_line_map_start);
	if (c->map == NULL)
		return (ft_error("No map"));
	init_cub_2(c);
	if (!c->map)
		return (ft_error("Empty file"));
	c->mlx = mlx_init(c->true_screen_width, SCREEN_HEIGHT, "CUB3D", true);
	mlx_set_cursor_mode(c->mlx, MLX_MOUSE_HIDDEN);
	if (!c->mlx)
		return (ft_error("MLX failed"));
	return (1);
}
