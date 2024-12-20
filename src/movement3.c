/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:09 by llion             #+#    #+#             */
/*   Updated: 2023/07/16 11:29:43 by llion@student    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	pause_game(t_cub *c)
{
	if (c->pause == 0)
	{
		c->pause = 1;
		mlx_set_cursor_mode(c->mlx, MLX_MOUSE_NORMAL);
		return ;
	}
	if (c->pause == 1)
	{
		c->pause = 0;
		mlx_set_cursor_mode(c->mlx, MLX_MOUSE_HIDDEN);
		return ;
	}
}

void	press_key(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

	c = param;
	if (keydata.key == MLX_KEY_W)
		c->player->is_moving |= 0x01;
	if (keydata.key == MLX_KEY_S)
		c->player->is_moving |= 0x04;
	if (keydata.key == MLX_KEY_A)
		c->player->is_moving |= 0x02;
	if (keydata.key == MLX_KEY_D)
		c->player->is_moving |= 0x08;
	if (keydata.key == MLX_KEY_RIGHT)
		c->player->is_moving |= 0x10;
	if (keydata.key == MLX_KEY_LEFT)
		c->player->is_moving |= 0x20;
	if (keydata.key == MLX_KEY_SPACE)
		c->player->is_moving |= 0x40;
}

void	release_key(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

	c = param;
	if (keydata.key == MLX_KEY_W)
		c->player->is_moving &= ~0x01;
	if (keydata.key == MLX_KEY_S)
		c->player->is_moving &= ~0x04;
	if (keydata.key == MLX_KEY_A)
		c->player->is_moving &= ~0x02;
	if (keydata.key == MLX_KEY_D)
		c->player->is_moving &= ~0x08;
	if (keydata.key == MLX_KEY_RIGHT)
		c->player->is_moving &= ~0x10;
	if (keydata.key == MLX_KEY_LEFT)
		c->player->is_moving &= ~0x20;
	if (keydata.key == MLX_KEY_SPACE)
		c->player->is_moving &= ~0x40;
}

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_cub	*c;

	c = param;
	if (keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_SPACE)
		toggle_door(c);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(c->mlx);
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		pause_game(c);
	if (keydata.action == MLX_PRESS)
		press_key(keydata, param);
	if (keydata.action == MLX_RELEASE)
		release_key(keydata, param);
}

int	check_collision(float x, float y, t_cub *c)
{
	int	j;
	int	i;

	j = x / c->tilesize;
	i = y / c->tilesize;
	if (c->map[i][j] == '1' || c->map[i][j] == '2')
		return (0);
	return (1);
}
