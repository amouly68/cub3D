/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:59:49 by llion             #+#    #+#             */
/*   Updated: 2023/07/16 11:26:53 by llion@student    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_nb_lines_in_map_file(int fd, char **argv)
{
	int		num_lines;
	char	*line;

	num_lines = 0;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		num_lines++;
		line = get_next_line(fd);
	}
	free(line);
	return (num_lines);
}

void	loop_map_start(char **f, int *i, int *k, int *z)
{
	int	j;

	j = 0;
	while (f[*i][j] == ' ')
		j++;
	if (f[*i][j] == '\n')
	{
		(*z)++;
		return ;
	}
	if (!((f[*i][j] == 'N' && f[*i][j + 1] == 'O') || (f[*i][j] == 'S'
				&& f[*i][j + 1] == 'O') || (f[*i][j] == 'W' && f[*i][j
				+ 1] == 'E') || (f[*i][j] == 'E' && f[*i][j + 1] == 'A')
			|| (f[*i][j] == 'F' && f[*i][j + 1] == ' ') || (f[*i][j] == 'C'
				&& f[*i][j + 1] == ' ')))
		return ;
	else
		(*k)++;
	(*z)++;
}

int	get_nb_line_map_start(char **f)
{
	int	i;
	int	k;
	int	z;

	i = 0;
	k = 0;
	z = 0;
	while (i < ft_tablen(f) && k < 6 && z < ft_tablen(f))
	{
		loop_map_start(f, &i, &k, &z);
		i++;
	}
	return (z);
}

char	**get_file(char **argv)
{
	char	**map;
	int		i;
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	i = 0;
	map = ft_calloc(sizeof(char *), get_nb_lines_in_map_file(fd, argv) + 1);
	if (map == NULL)
		return (NULL);
	while (i < get_nb_lines_in_map_file(fd, argv))
	{
		line = get_next_line(fd);
		map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return (map);
}

char	**get_map(char **f, int i)
{
	char	**map;
	int		j;

	j = 0;
	map = ft_calloc(ft_tablen(f) - i + 1, sizeof(char *));
	if (!map)
		return (0);
	if (f[i])
	{
		while (f[i])
		{
			if (f[i][0] == '\n')
				i++;
			else
			{
				map[j] = ft_strdup(f[i]);
				i++;
				j++;
			}
		}
	}
	else
		return (NULL);
	return (map);
}
